#include <stdbool.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "CRTP.h"
#include "CRTP_Service.h"
#include "CRTP_Base.h"

static bool CRTPService_isInit = false;

/**
  * @brief CRTP�����й������Ӷ˿ڵĴ������У�
  * @return ��
  */
static void CRTPService_LinkTask(void* param) {
  static CRTP_Packet p;
  CRTP_InitTaskQueue(CRTP_PORT_LINK);

  while(1) {
		/* ��ȡ�˿�port */
    CRTP_ReceivePacketBlock(CRTP_PORT_LINK, &p);

		/* ȷ��ͨ��channel */
    switch (p.channel) {
      case CRTP_LINK_Echo:
        CRTP_SendPacketBlock(&p);
        break;
      case CRTP_LINK_Source:
        p.size = CRTP_DataPackage_Size;
        memset(p.data, 0, CRTP_DataPackage_Size);
        strcpy((char*)p.data, "Bitcraze Crazyflie");
        CRTP_SendPacketBlock(&p);
        break;
      case CRTP_LINK_Sink:
        break;
      default:
        break;
    }
  }
}

///**
//  * @brief CRTP�����й������Ӷ˿ڵĴ���(�ص�����)
//  * @return ��
//  */
//static void CRTPService_LinkCB(CRTP_Packet* p) {
//		/* ȷ��ͨ��channel */
//    switch (p->channel) {
//      case CRTP_LINK_Echo:
//        CRTP_SendPacketBlock(p);
//        break;
//      case CRTP_LINK_Source:
//        p->size = CRTP_DataPackage_Size;
//        memset(p->data, 0, CRTP_DataPackage_Size);
//        strcpy((char*)p->data, "Bitcraze Crazyflie");
//        CRTP_SendPacketBlock(p);
//        break;
//      case CRTP_LINK_Sink:
//        break;
//      default:
//        break;
//		}
//}

void CRTPService_Init(void) {
  if (CRTPService_isInit){
		return;
	}
	
	/* CRTPЭ����ʼ�� */
	CRTP_Init();

	/* ����CRTPӦ�÷��� */
	xTaskCreate(CRTPService_LinkTask, "LinkTask", 150, NULL, 2, NULL);
	
	/* ע��CRTPӦ�ûص����� */
//	CRTP_RegisterPortCB(CRTP_PORT_LINK, CRTPService_LinkCB);

  CRTPService_isInit = true;
}

bool CRTPService_Test(void) {
  return CRTPService_isInit;
}

