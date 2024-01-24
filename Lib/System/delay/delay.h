#ifndef __DELAY_H
#define __DELAY_H

///////////////////////////////////////////////////////////
//
// 文件功能：使用定时器延时
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/04/21
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/**
  * @brief  微秒级延时
  * @param  xus 延时时长，范围：0~233015
  * @retval 无
  */
void Delay_us(uint32_t us);

/**
  * @brief  毫秒级延时
  * @param  xms 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_ms(uint32_t ms);

/**
  * @brief  秒级延时
  * @param  xs 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_s(uint32_t s);

#endif
