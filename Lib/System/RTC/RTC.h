#ifndef __RTC_H
#define __RTC_H

///////////////////////////////////////////////////////////

// �ļ����ܣ�RTC����ع��ܺ���
// �汾��V1.1
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/12/31
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

#define RTC_Count_Default			0			// 32λ��ʱ���
#define RTC_Sign_BPKDR				BKP_DR10

/**
  * @brief RTC��ʼ��
  * @return ��
  */
void RTC_Init(void);

/**
  * @brief ��ȡʱ���
  * @return ʱ���
	* ע���п⺯���ṩ����Ҫȥ��ע��
  */
// uint32_t RTC_GetCounter(void);

/**
  * @brief ����RTC��׼ʱ��
  * @param Year ���
  * @param Month �·�
  * @param Day ����
  * @param Hour Сʱ
  * @param Minute ����
  * @param Second ��
  * @return ��
  */
void RTC_SetTime(uint16_t Year, uint8_t Month, uint8_t Day, uint8_t Hour, uint8_t Minute, uint8_t Second);

/**
  * @brief ˢ��RTCʱ�ӣ���Ҫ��ʱ���ת��Ϊ����ʱ�����ٵ��ã�
  * @param TimeZone ʱ�������磺����Ϊ��8����
  * @return ��
  */
void RTC_RefreshTime(int8_t TimeZone);

/**
  * @brief ��ȡRTCʱ�ӵ����
  * @return ���
  */
uint16_t RTC_GetYear(void);

/**
  * @brief ��ȡRTCʱ�ӵ��·�
  * @return �·�
  */
uint8_t RTC_GetMonth(void);

/**
  * @brief ��ȡRTCʱ�ӵ�����
  * @return ����
  */
uint8_t RTC_GetDay(void);

/**
  * @brief ��ȡRTCʱ�ӵ�Сʱ
  * @return Сʱ
  */
uint8_t RTC_GetHour(void);

/**
  * @brief ��ȡRTCʱ�ӵķ���
  * @return ����
  */
uint8_t RTC_GetMinute(void);

/**
  * @brief ��ȡRTCʱ�ӵ���
  * @return ��
  */
uint8_t RTC_GetSecond(void);

/**
  * @brief ��ȡRTCʱ�ӵĺ���
  * @return ����
  */
uint16_t RTC_GetMiliSecond(void);

/**
  * @brief ����RTC���ӵ���ʱ
  * @param AlarmValue ����ʱ���
  * @return ��
  */
 void RTC_SetAlarmCountDown(uint32_t AlarmValue);

/**
  * @brief ���RTC�����Ƿ�ʱ
  * @return 1��ʾ��ʱ
  */
uint8_t RTC_CheckAlarm(void);

#endif

///////////////////////////////////////////////////////////
//
// ������־��
// V1.0: 2023/12/30
//				ʵ����RTCʵʱʱ�ӵĹ���
// V1.1: 2023/12/31
//				ʵ����RTC���ӵĲ��ֹ���
//
///////////////////////////////////////////////////////////
