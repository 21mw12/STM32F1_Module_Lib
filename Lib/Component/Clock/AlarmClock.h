#ifndef __ALARMCLOCK_H
#define __ALARMCLOCK_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ����ӻ������ܵ�ʵ��
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2024/02/01
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "Clock.h"

/* ���ӱ���״̬���� */
typedef enum {
	aClockState_Idel = 0,
	aClockState_Warn = 1
} AlarmClockState;

/* ���ӽṹ�� */
typedef struct {
	ClockTime cTime;						// ����ʱ����Ϣ
	AlarmClockState aClockWarnState;	// ���ӱ���״̬
	void (*warningFunction)(void);		// ���ӱ���������
} AlarmClock;

/**
  * @brief ���ӹ���״̬�л�
  * @param aClock ���ӽṹ��
  * @return ��
  */
void AlarmClock_ExchangeWorkState(AlarmClock* aClock);

/**
  * @brief ��������ʱ��
  * @param aClock ���ӽṹ��
  * @param newHour �µ�Сʱ
  * @param newMinute �µķ���
  * @return ��
  */
void AlarmClock_SetTime(AlarmClock* aClock, uint8_t newHour, uint8_t newMinute);

/**
  * @brief ��������
  * @param aClock ���ӽṹ��
  * @return ��
  */
void AlarmClock_HeartBeat(AlarmClock* aClock);

/**
  * @brief ���ӱ���
  * @param aClock ���ӽṹ��
  * @return ��
  */
void AlarmClock_Warnning(AlarmClock* aClock);

#endif
