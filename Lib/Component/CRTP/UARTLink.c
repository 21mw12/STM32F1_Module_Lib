#include "UARTLink.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "USART2.h"
#include "CRTP.h"

static bool UARTLink_isInit = false;

static xQueueHandle UART_CacheQueue;
static xQueueHandle UARTLink_CRTP_PacketQueue;
static TaskHandle_t pxUART_DealPacketTask;

static int UARTLink_SetEnable(bool enable);
static int UARTLink_SendPacket(CRTP_Packet *p);
static int UARTLink_ReceivePacket(CRTP_Packet *p);

/* 链路层操作结构体 */
static struct CRTP_LinkOperations uartlinkOp = {
  .setEnable         = UARTLink_SetEnable,
  .sendPacket        = UARTLink_SendPacket,
  .receivePacket     = UARTLink_ReceivePacket,
};

/* UART处理数据包状态 */
enum UART_DealState {
	WAITING = 0,
	GET_SIZE,
	GET_HEADER,		
	GET_DATA,
};

/**
  * @brief 设置链路层使能（暂时无用）
  * @param enable 状态
  * @return 当前状态
  */
static int UARTLink_SetEnable(bool enable) {
  return 0;
}

/**
  * @brief 链路层发送数据包
  * @param p 数据包
  * @return 发送是否成功
  */
static int UARTLink_SendPacket(CRTP_Packet *p) {
	/* 发送0x55头部 */
	USART2_SendByte(UARTLink_PacketHead);
	
	/* 发送size */
	USART2_SendByte(p->size);
	
	/* 发送header */
	USART2_SendByte(p->header);
	
	/* 发送数据 */
	for(uint8_t i = 0; i < p->size; i++) {
		USART2_SendByte(p->data[i]);	
	}
	
	return true;
}

/**
  * @brief 链路层接收数据包
  * @param p 数据包
  * @return 发送接收到
  */
static int UARTLink_ReceivePacket(CRTP_Packet *p) {
	if (xQueueReceive(UARTLink_CRTP_PacketQueue, p, 100) == pdTRUE) {
		return 0;
	}
  return -1;
}

/**
  * @brief 处理UART接收到的CRTP数据包
  * @return 无
  */
static void UART_DealPacket(void *params){
	CRTP_Packet packet;
	uint8_t data;
	uint8_t data_cnt = 0;
	enum UART_DealState status = WAITING;
	
	while(1) {
		/* 等待数据 */
		xQueueReceive(UART_CacheQueue, &data, portMAX_DELAY);
		
		/* 解析出packet */
		switch(status) {
			case WAITING:
				if (data == UARTLink_PacketHead) {
					status = GET_SIZE;
				}
				break;
			case GET_SIZE:
				packet.size = data;
				status = GET_HEADER;
				break;
			case GET_HEADER:
				packet.header = data;
				data_cnt = 0;
				status = GET_DATA;
				break;
			case GET_DATA:
				packet.data[data_cnt++] = data;
				if(data_cnt == packet.size) {
					
					/* 测试打印数据包内容 */
//					char str[80];
//					sprintf(str, "Get packet: channel = %d, port = %d, data = %s\r\n", packet.channel, packet.port, packet.data);
//					USART2_SendString(str);
					
					/* 把packet写入队列 */
					xQueueSend(UARTLink_CRTP_PacketQueue, &packet, 100);
					status = WAITING;
				}
				break;
		}
	}
}

void UARTLink_Init(void) {
	if(UARTLink_isInit) return;
	
	/* 创建CRTP数据包队列 */
	UARTLink_CRTP_PacketQueue = xQueueCreate(UARTLink_PacketCacheSize, sizeof(CRTP_Packet));
	/* 创建串口接收队列 */
	UART_CacheQueue = xQueueCreate(UARTLink_DataCacheSize, sizeof(uint8_t));
	
	/* 创建解析CRTP数据包的任务 */
  xTaskCreate((TaskFunction_t )UART_DealPacket,
              (const char*    )"UART_DealPacket",
              (uint16_t       )200,
              (void*          )NULL,
              (UBaseType_t    )3,
              (TaskHandle_t*  )&pxUART_DealPacketTask);
	
  UARTLink_isInit = true;
}

struct CRTP_LinkOperations* UARTLink_GetLinkOp(void) {
  return &uartlinkOp;
}

void USART2_IRQHandler(void) {
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET) {
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		
		uint8_t USART2_RxData = USART_ReceiveData(USART2);
		
		/* 将数据写入队列，唤醒解析数据包任务UARTParsercket */		
		xQueueSendFromISR(UART_CacheQueue, &USART2_RxData, NULL);	
	}
}
