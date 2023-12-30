#ifndef __RTC_H
#define __RTC_H

///////////////////////////////////////////////////////////

// 文件功能：RTC的相关功能函数
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/12/30
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

#define RTC_Count_Default			0			// 32位的时间戳
#define RTC_Sign_BPKDR				BKP_DR10

/**
  * @brief RTC初始化
  * @return 无
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
