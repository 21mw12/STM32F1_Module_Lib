#ifndef __SECONDCHRONOGRAPH_H
#define __SECONDCHRONOGRAPH_H

///////////////////////////////////////////////////////////
//
// 文件功能：秒表基本功能的实现
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/02/01
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "Clock.h"

/* 秒表结构体 */
typedef struct {
	ClockTime cTime;			// 秒表时间信息
} SecondChronograph;

/**
  * @brief 秒表工作状态切换
  * @param sClock 秒表结构体
  * @return 无
  */
void SecondChronograph_ExchangeWorkState(SecondChronograph* sClock);

/**
  * @brief 秒表心跳
  * @param sClock 秒表结构体
  * @return 无
  */
void SecondChronograph_HeartBeat(SecondChronograph* sClock);

/**
  * @brief 秒表计数清零
  * @param sClock 秒表结构体
  * @return 无
  */
void SecondChronograph_ClearTime(SecondChronograph* sClock);

#endif
