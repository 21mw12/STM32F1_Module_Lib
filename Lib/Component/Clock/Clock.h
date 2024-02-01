#ifndef __CLOCK_H
#define __CLOCK_H

///////////////////////////////////////////////////////////
//
// 文件功能：时钟基本功能的实现
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/02/01
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* 时钟工作状态枚举体 */
typedef enum {
	cTimeState_Idel = 0,
	cTimeState_Working = 1
} ClockTimeState;

/* 时钟结构体 */
typedef struct {
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	ClockTimeState cTimeState;
} ClockTime;

/**
  * @brief时钟工作状态切换
  * @param cTime 时钟时间结构体
  * @return 无
  */
void Clock_ExchangeWorkState(ClockTime* cTime);

/**
  * @brief 时钟时间减少
  * @param cTime 时钟时间结构体
  * @return 时钟是否结束
  */
ClockTimeState Clock_ReduceTime(ClockTime* cTime);

/**
  * @brief 时钟时间增加
  * @param cTime 时钟时间结构体
  * @return 时钟是否结束
  */
ClockTimeState Clock_IncreaseTime(ClockTime* cTime);

#endif
