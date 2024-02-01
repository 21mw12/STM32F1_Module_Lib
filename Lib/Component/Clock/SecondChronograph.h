#ifndef __SECONDCHRONOGRAPH_H
#define __SECONDCHRONOGRAPH_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ����������ܵ�ʵ��
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2024/02/01
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "Clock.h"

/* ���ṹ�� */
typedef struct {
	ClockTime cTime;			// ���ʱ����Ϣ
} SecondChronograph;

/**
  * @brief �����״̬�л�
  * @param sClock ���ṹ��
  * @return ��
  */
void SecondChronograph_ExchangeWorkState(SecondChronograph* sClock);

/**
  * @brief �������
  * @param sClock ���ṹ��
  * @return ��
  */
void SecondChronograph_HeartBeat(SecondChronograph* sClock);

/**
  * @brief ����������
  * @param sClock ���ṹ��
  * @return ��
  */
void SecondChronograph_ClearTime(SecondChronograph* sClock);

#endif
