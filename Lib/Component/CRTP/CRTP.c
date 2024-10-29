#include "CRTP.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "UARTLink.h"


static bool CRTP_isInit;

/* ��·�������������ﶨ����ȫ�յĺ�����ֹ��ָ�� */
static int nopFunc(void) {
  return -1;
}
static struct CRTP_LinkOperations nopLink = {
  .setEnable         = (void*) nopFunc,
  .sendPacket        = (void*) nopFunc,
  .receivePacket     = (void*) nopFunc,
};
static struct CRTP_LinkOperations *CRTP_LinkOp = &nopLink;

/* ͳ����Ϣ */
#define STATS_INTERVAL 500
static struct {
  uint32_t rxCount;
  uint32_t txCount;

  uint16_t rxRate;
  uint16_t txRate;

  uint32_t nextStatisticsTime;
  uint32_t previousStatisticsTime;
} stats;

/* ����˿ڶ��кͶ˿ڻص��������� */
#define CRTP_NBR_OF_PORTS 	16
static xQueueHandle txQueue;
static xQueueHandle queues[CRTP_NBR_OF_PORTS];
static volatile CrtpCallback callbacks[CRTP_NBR_OF_PORTS];

//#define CRTP_HEADER(port, channel) (((port & 0x0F) << 4) | (channel & 0x0F))
//#define CRTP_IS_NULL_PACKET(P) ((P.header&0xF3)==0xF3)

/**
  * @brief Э���������·��������
  * @param lk ��·��������
  * @return ��
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
  * @brief ���ͳ����Ϣ
  * @return ��
  */
static void clearStats(void) {
  stats.rxCount = 0;
  stats.txCount = 0;
}

/**
  * @brief ����ͳ����Ϣ
  * @return ��
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
  * @brief CRTP��������
  * @return ��
  */
void CRTP_TxTask(void *param) {
  CRTP_Packet p;

  while(1) {
		/* �ȴ���·���������� */
    if(CRTP_LinkOp == &nopLink) {
			vTaskDelay(pdMS_TO_TICKS(10));
			continue;
		}
		
		/* �ȴ���Ҫ���͵����ݰ� */
		if(xQueueReceive(txQueue, &p, portMAX_DELAY) == pdTRUE) {
			/* ������·�㷢�����ݰ� */
			while(CRTP_LinkOp->sendPacket(&p) == false) {
				vTaskDelay(pdMS_TO_TICKS(10));
			}
			stats.txCount++;
			updateStats();
		}
  }
}

/**
  * @brief CRTP��������
  * @return ��
  */
void CRTP_RxTask(void *param) {
  CRTP_Packet p;

  while(1) {
		/* ���������� */
    if(CRTP_LinkOp == &nopLink) {
			vTaskDelay(pdMS_TO_TICKS(10));
			continue;
		}
		
			/* ������·��������ݰ� */
		if(!CRTP_LinkOp->receivePacket(&p)) {
			if (queues[p.port]) {
				/* �����ݰ������Ӧ�˿ڶ��� */
				xQueueSend(queues[p.port], &p, portMAX_DELAY);
			}
			
			/* ���ö�Ӧ�˿ڵĻص����� */
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
	
	/* ��·���ʼ�� */
	UARTLink_Init();
	CRTP_SetLink(UARTLink_GetLinkOp());
	
	/* Э����ʼ�� */
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

