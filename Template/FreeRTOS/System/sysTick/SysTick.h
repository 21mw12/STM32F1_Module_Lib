#ifndef _SysTick_H
#define _SysTick_H

#include "system.h"

///////////////////////////////////////////////////////////
//
// 文件功能：实现FreeRTOS中的延时功能
//
///////////////////////////////////////////////////////////

/**
  * @brief 初始化延迟函数
  * @param SYSCLK: 系统时钟频率（SYSTICK的时钟固定为AHB时钟）
  * @return 无
  */
void SysTick_Init(u8 SYSCLK);

/**
  * @brief 延时微秒
  * @param nms: 要延时的微秒数（0~65535）
  * @return 
  */
void delay_ms(u32 nms);

/**
  * @brief 不会引起任务调度的延迟微秒
  * @param nms: 要延时的ms数
  * @return 无
  */
void delay_xms(u32 nms);

/**
  * @brief 延时纳秒
  * @param nus: 要延时的纳秒数（0~204522252 (最大值即2^32/fac_us@fac_us=168)）
  * @return 无
  */
void delay_us(u32 nus);

#endif
