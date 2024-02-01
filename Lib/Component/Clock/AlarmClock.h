#ifndef __ALARMCLOCK_H
#define __ALARMCLOCK_H

///////////////////////////////////////////////////////////
//
// 文件功能：闹钟基本功能的实现
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/02/01
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "Clock.h"

/* 闹钟报警状态举体 */
typedef enum {
	aClockState_Idel = 0,
	aClockState_Warn = 1
} AlarmClockState;

/* 闹钟结构体 */
typedef struct {
	ClockTime cTime;						// 闹钟时间信息
	AlarmClockState aClockWarnState;	// 闹钟报警状态
	void (*warningFunction)(void);		// 闹钟报警处理函数
} AlarmClock;

/**
  * @brief 闹钟工作状态切换
  * @param aClock 闹钟结构体
  * @return 无
  */
void AlarmClock_ExchangeWorkState(AlarmClock* aClock);

/**
  * @brief 设置闹钟时间
  * @param aClock 闹钟结构体
  * @param newHour 新的小时
  * @param newMinute 新的分钟
  * @return 无
  */
void AlarmClock_SetTime(AlarmClock* aClock, uint8_t newHour, uint8_t newMinute);

/**
  * @brief 闹钟心跳
  * @param aClock 闹钟结构体
  * @return 无
  */
void AlarmClock_HeartBeat(AlarmClock* aClock);

/**
  * @brief 闹钟报警
  * @param aClock 闹钟结构体
  * @return 无
  */
void AlarmClock_Warnning(AlarmClock* aClock);

#endif
