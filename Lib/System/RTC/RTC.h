#ifndef __RTC_H
#define __RTC_H

///////////////////////////////////////////////////////////

// �ļ����ܣ�RTC����ع��ܺ���
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/12/30
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

void RTC_SetTime(uint16_t Year, uint8_t Month, uint8_t Day, uint8_t Hour, uint8_t Minute, uint8_t Second);

void RTC_RefreshTime(int8_t TimeZone);

uint16_t RTC_GetYear(void);

uint8_t RTC_GetMonth(void);

uint8_t RTC_GetDay(void);

uint8_t RTC_GetHour(void);

uint8_t RTC_GetMinute(void);

uint8_t RTC_GetSecond(void);

uint16_t RTC_GetMiliSecond(void);

#endif
