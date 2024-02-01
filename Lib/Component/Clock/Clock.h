#ifndef __CLOCK_H
#define __CLOCK_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�ʱ�ӻ������ܵ�ʵ��
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2024/02/01
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* ʱ�ӹ���״̬ö���� */
typedef enum {
	cTimeState_Idel = 0,
	cTimeState_Working = 1
} ClockTimeState;

/* ʱ�ӽṹ�� */
typedef struct {
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	ClockTimeState cTimeState;
} ClockTime;

/**
  * @briefʱ�ӹ���״̬�л�
  * @param cTime ʱ��ʱ��ṹ��
  * @return ��
  */
void Clock_ExchangeWorkState(ClockTime* cTime);

/**
  * @brief ʱ��ʱ�����
  * @param cTime ʱ��ʱ��ṹ��
  * @return ʱ���Ƿ����
  */
ClockTimeState Clock_ReduceTime(ClockTime* cTime);

/**
  * @brief ʱ��ʱ������
  * @param cTime ʱ��ʱ��ṹ��
  * @return ʱ���Ƿ����
  */
ClockTimeState Clock_IncreaseTime(ClockTime* cTime);

#endif
