#include "CRTP.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "UARTLink.h"


static bool CRTP_isInit;

/* 链路层操作句柄，这里定义了全空的函数防止空指针 */
static int nopFunc(void) {
  return -1;
}
static struct CRTP_LinkOperations nopLink = {
  .setEnable         = (void*) nopFunc,
  .sendPacket        = (void*) nopFunc,
  .receivePacket     = (void*) nopFunc,
};
static struct CRTP_LinkOperations *CRTP_LinkOp = &nopLink;

/* 统计信息 */
#define STATS_INTERVAL 500
static struct {
  uint32_t rxCount;
  uint32_t txCount;

  uint16_t rxRate;
  uint16_t txRate;

  uint32_t nextStatisticsTime;
  uint32_t previousStatisticsTime;
} stats;

/* 定义端口队列和端口回调函数队列 */
#define CRTP_NBR_OF_PORTS 	16
static xQueueHandle txQueue;
static xQueueHandle queues[CRTP_NBR_OF_PORTS];
static volatile CrtpCallback callbacks[CRTP_NBR_OF_PORTS];

//#define CRTP_HEADER(port, channel) (((port & 0x0F) << 4) | (channel & 0x0F))
//#define CRTP_IS_NULL_PACKET(P) ((P.header&0xF3)==0xF3)

/**
  * @brief 协议层设置链路层操作句柄
  * @param lk 链路层操作句柄
  * @return 无
  */
void CRTP_SetLink(struct CRTP_LinkOperations* lk) {
  if(CRTP_LinkOp)
    CRTP_LinkOp->setEnable(false);

  if (lk)
    CRTP_LinkOp = lk;
  else
    CRTP_LinkOp = &nopLink;

  CRTP_LinkOp->setEnable(true);
}

/**
  * @brief 清空统计信息
  * @return 无
  */
static void clearStats(void) {
  stats.rxCount = 0;
  stats.txCount = 0;
}

/**
  * @brief 更新统计信息
  * @return 无
  */
static void updateStats(void) {
  uint32_t now = xTaskGetTickCount();
  if(now > stats.nextStatisticsTime) {
    float interval = now - stats.previousStatisticsTime;
    stats.rxRate = (uint16_t)(1000.0f * stats.rxCount / interval);
    stats.txRate = (uint16_t)(1000.0f * stats.txCount / interval);

    clearStats();
    stats.previousStatisticsTime = now;
    stats.nextStatisticsTime = now + STATS_INTERVAL;
  }
}

/**
  * @brief CRTP发送任务
  * @return 无
  */
void CRTP_TxTask(void *param) {
  CRTP_Packet p;

  while(1) {
		/* 等待链路操作句柄获得 */
    if(CRTP_LinkOp == &nopLink) {
			vTaskDelay(pdMS_TO_TICKS(10));
			continue;
		}
		
		/* 等待需要发送的数据包 */
		if(xQueueReceive(txQueue, &p, portMAX_DELAY) == pdTRUE) {
			/* 调用链路层发送数据包 */
			while(CRTP_LinkOp->sendPacket(&p) == false) {
				vTaskDelay(pdMS_TO_TICKS(10));
			}
			stats.txCount++;
			updateStats();
		}
  }
}

/**
  * @brief CRTP接收任务
  * @return 无
  */
void CRTP_RxTask(void *param) {
  CRTP_Packet p;

  while(1) {
		/* 操作句柄获得 */
    if(CRTP_LinkOp == &nopLink) {
			vTaskDelay(pdMS_TO_TICKS(10));
			continue;
		}
		
			/* 调用链路层接收数据包 */
		if(!CRTP_LinkOp->receivePacket(&p)) {
			if (queues[p.port]) {
				/* 将数据包存入对应端口队列 */
				xQueueSend(queues[p.port], &p, portMAX_DELAY);
			}
			
			/* 调用对应端口的回调函数 */
			if(callbacks[p.port]) {
				callbacks[p.port](&p);
			}

			stats.rxCount++;
			updateStats();
		}
  }
}

void CRTP_Init(void) {
  if(CRTP_isInit) return;
	
	/* 链路层初始化 */
	UARTLink_Init();
	CRTP_SetLink(UARTLink_GetLinkOp());
	
	/* 协议层初始化 */
  txQueue = xQueueCreate(CRTP_TX_QUEUE_SIZE, sizeof(CRTP_Packet));
	
	xTaskCreate(CRTP_TxTask, "CRTP_TxTask", 150, NULL, 2, NULL);
	xTaskCreate(CRTP_RxTask, "CRTP_RxTask", 150, NULL, 2, NULL);

  CRTP_isInit = true;
}

bool CRTP_Test(void) {
  return CRTP_isInit;
}

bool CRTP_IsConnected(void) {
  if (CRTP_LinkOp->isConnected)
    return CRTP_LinkOp->isConnected();
  return true;
}

int CRTP_Reset(void) {
  xQueueReset(txQueue);
  if(CRTP_LinkOp->reset) {
    CRTP_LinkOp->reset();
  }
  return 0;
}

void CRTP_InitTaskQueue(CRTP_Port portId) {
//  ASSERT(queues[portId] == NULL);
  queues[portId] = xQueueCreate(CRTP_RX_QUEUE_SIZE, sizeof(CRTP_Packet));
//  DEBUG_QUEUE_MONITOR_REGISTER(queues[portId]);
}

int CRTP_ReceivePacket(CRTP_Port portId, CRTP_Packet *p) {
//  ASSERT(queues[portId]);
//  ASSERT(p);
  return xQueueReceive(queues[portId], p, 0);
}

int CRTP_ReceivePacketBlock(CRTP_Port portId, CRTP_Packet *p) {
//  ASSERT(queues[portId]);
//  ASSERT(p);
  return xQueueReceive(queues[portId], p, portMAX_DELAY);
}

int CRTP_ReceivePacketWait(CRTP_Port portId, CRTP_Packet *p, int wait) {
//  ASSERT(queues[portId]);
//  ASSERT(p);
  return xQueueReceive(queues[portId], p, pdMS_TO_TICKS(wait));
}

int CRTP_SendPacket(CRTP_Packet *p) {
//  ASSERT(p);
//  ASSERT(p->size <= CRTP_MAX_DATA_SIZE);
  return xQueueSend(txQueue, p, 0);
}

int CRTP_SendPacketBlock(CRTP_Packet *p) {
//  ASSERT(p);
//  ASSERT(p->size <= CRTP_MAX_DATA_SIZE);
  return xQueueSend(txQueue, p, portMAX_DELAY);
}

int CRTP_GetFreeTxQueuePackets(void) {
  return (CRTP_TX_QUEUE_SIZE - uxQueueMessagesWaiting(txQueue));
}

void CRTP_RegisterPortCB(int port, CrtpCallback cb) {
  if (port>CRTP_NBR_OF_PORTS)
    return;
  callbacks[port] = cb;
}

