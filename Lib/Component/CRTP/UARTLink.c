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

/* ��·������ṹ�� */
static struct CRTP_LinkOperations uartlinkOp = {
  .setEnable         = UARTLink_SetEnable,
  .sendPacket        = UARTLink_SendPacket,
  .receivePacket     = UARTLink_ReceivePacket,
};

/* UART�������ݰ�״̬ */
enum UART_DealState {
	WAITING = 0,
	GET_SIZE,
	GET_HEADER,		
	GET_DATA,
};

/**
  * @brief ������·��ʹ�ܣ���ʱ���ã�
  * @param enable ״̬
  * @return ��ǰ״̬
  */
static int UARTLink_SetEnable(bool enable) {
  return 0;
}

/**
  * @brief ��·�㷢�����ݰ�
  * @param p ���ݰ�
  * @return �����Ƿ�ɹ�
  */
static int UARTLink_SendPacket(CRTP_Packet *p) {
	/* ����0x55ͷ�� */
	USART2_SendByte(UARTLink_PacketHead);
	
	/* ����size */
	USART2_SendByte(p->size);
	
	/* ����header */
	USART2_SendByte(p->header);
	
	/* �������� */
	for(uint8_t i = 0; i < p->size; i++) {
		USART2_SendByte(p->data[i]);	
	}
	
	return true;
}

/**
  * @brief ��·��������ݰ�
  * @param p ���ݰ�
  * @return ���ͽ��յ�
  */
static int UARTLink_ReceivePacket(CRTP_Packet *p) {
	if (xQueueReceive(UARTLink_CRTP_PacketQueue, p, 100) == pdTRUE) {
		return 0;
	}
  return -1;
}

/**
  * @brief ����UART���յ���CRTP���ݰ�
  * @return ��
  */
static void UART_DealPacket(void *params){
	CRTP_Packet packet;
	uint8_t data;
	uint8_t data_cnt = 0;
	enum UART_DealState status = WAITING;
	
	while(1) {
		/* �ȴ����� */
		xQueueReceive(UART_CacheQueue, &data, portMAX_DELAY);
		
		/* ������packet */
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
					
					/* ���Դ�ӡ���ݰ����� */
//					char str[80];
//					sprintf(str, "Get packet: channel = %d, port = %d, data = %s\r\n", packet.channel, packet.port, packet.data);
//					USART2_SendString(str);
					
					/* ��packetд����� */
					xQueueSend(UARTLink_CRTP_PacketQueue, &packet, 100);
					status = WAITING;
				}
				break;
		}
	}
}

void UARTLink_Init(void) {
	if(UARTLink_isInit) return;
	
	/* ����CRTP���ݰ����� */
	UARTLink_CRTP_PacketQueue = xQueueCreate(UARTLink_PacketCacheSize, sizeof(CRTP_Packet));
	/* �������ڽ��ն��� */
	UART_CacheQueue = xQueueCreate(UARTLink_DataCacheSize, sizeof(uint8_t));
	
	/* ��������CRTP���ݰ������� */
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
		
		/* ������д����У����ѽ������ݰ�����UARTParsercket */		
		xQueueSendFromISR(UART_CacheQueue, &USART2_RxData, NULL);	
	}
}
