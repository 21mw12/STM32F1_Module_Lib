#ifndef __RTC_H
#define __RTC_H

///////////////////////////////////////////////////////////

// 文件功能：RTC的相关功能函数
// 版本：V1.1
// 作者：墨蔚（MW）
// 修改时间：2023/12/31
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

/**
  * @brief 获取时间戳
  * @return 时间戳
	* 注：有库函数提供，不要去除注释
  */
// uint32_t RTC_GetCounter(void);

/**
  * @brief 设置RTC基准时间
  * @param Year 年份
  * @param Month 月份
  * @param Day 天数
  * @param Hour 小时
  * @param Minute 分钟
  * @param Second 秒
  * @return 无
  */
void RTC_SetTime(uint16_t Year, uint8_t Month, uint8_t Day, uint8_t Hour, uint8_t Minute, uint8_t Second);

/**
  * @brief 刷新RTC时钟（需要将时间戳转换为基本时间是再调用）
  * @param TimeZone 时区（例如：北京为东8区）
  * @return 无
  */
void RTC_RefreshTime(int8_t TimeZone);

/**
  * @brief 获取RTC时钟的年份
  * @return 年份
  */
uint16_t RTC_GetYear(void);

/**
  * @brief 获取RTC时钟的月份
  * @return 月份
  */
uint8_t RTC_GetMonth(void);

/**
  * @brief 获取RTC时钟的天数
  * @return 天数
  */
uint8_t RTC_GetDay(void);

/**
  * @brief 获取RTC时钟的小时
  * @return 小时
  */
uint8_t RTC_GetHour(void);

/**
  * @brief 获取RTC时钟的分钟
  * @return 分钟
  */
uint8_t RTC_GetMinute(void);

/**
  * @brief 获取RTC时钟的秒
  * @return 秒
  */
uint8_t RTC_GetSecond(void);

/**
  * @brief 获取RTC时钟的毫秒
  * @return 毫秒
  */
uint16_t RTC_GetMiliSecond(void);

/**
  * @brief 设置RTC闹钟倒计时
  * @param AlarmValue 闹钟时间戳
  * @return 无
  */
 void RTC_SetAlarmCountDown(uint32_t AlarmValue);

/**
  * @brief 检查RTC闹钟是否到时
  * @return 1表示到时
  */
uint8_t RTC_CheckAlarm(void);

#endif

///////////////////////////////////////////////////////////
//
// 更新日志：
// V1.0: 2023/12/30
//				实现了RTC实时时钟的功能
// V1.1: 2023/12/31
//				实现了RTC闹钟的部分功能
//
///////////////////////////////////////////////////////////
