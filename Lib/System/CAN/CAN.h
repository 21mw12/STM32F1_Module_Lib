#ifndef __CAN_H
#define __CAN_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�CAN���ߵĻ�������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2024/02/21
//
// ע�������� = PCLK1 / ((SWJ + BS1 + BS2) * BRP)
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* CAN���� */
#define SWJ			CAN_SJW_1tq		// ��Χ��CAN_SJW_1tq ~ CAN_SJW_4tq
#define BS1			CAN_BS1_3tq		// ��Χ��CAN_BS1_1tq ~ CAN_BS1_16tq
#define BS2			CAN_BS2_2tq		// ��Χ��CAN_BS2_1tq ~	 CAN_BS2_8tq
#define BRP			60						//

/* CAN���յ������� */
extern uint8_t CAN1_RxPacket[8];

/**
  * @brief CAN���߳�ʼ��
  * @return ��
  */
void CAN1_Init(void);

/**
  * @brief CAN���߷������ݣ����Ϊ8�ֽ�
  * @param Data ���͵�����
	* @param Len ���͵���������
  * @return 0 ��ʾ����ʧ��
	* 				1 ��ʾ���ͳɹ�
  */
uint8_t CAN1_Send(uint8_t* Data, uint8_t Len);

//uint8_t CAN1_Receive(uint8_t* Data);

#endif
