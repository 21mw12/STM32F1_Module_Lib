#ifndef __TIM3_PWM_H
#define __TIM3_PWM_H

//////////////////////////////////////////////////////////////////////////////
//
// 文件功能：定时器3的PWM功能
// 版本：V1.1
// 作者：墨蔚（MW）
// 修改时间：2023/07/12
//
// PWM计算公式：
//     PWM频率 = CK_PSC / (PSC + 1) / (ARR + 1)
//     PWM占空比 = CCR / (ARR + 1)
//		 PWM分辨率 = 1 / (ARR + 1)
//
//				CK_PSC：系统主频（72MHz）
//				ARR：自动重装器的值
//				PSC：预分频器的值
//				CCR：反转电平的计数值
//
//////////////////////////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* 定时器3的PWM对应通道使能设置 */
/**
  * TIM3共有四个通道，分别是：
	*			通道1 —— PA6
	*			通道2 —— PA7
	*			通道3 —— PB0
	*			通道4 —— PB1
  *
	* 注意：不推荐全写写0，全写0表示不开启任何通道
  */
#define TIM3_PWMCHANNEL1_ENABLE   1
#define TIM3_PWMCHANNEL2_ENABLE   1
#define TIM3_PWMCHANNEL3_ENABLE   1
#define TIM3_PWMCHANNEL4_ENABLE   1

/**
  * @brief 定时器3的PWM功能初始化
  * @param TIM3_ARR 自动重装器的值
  * @param TIM3_PSC 预分频器的值
  * @param TIM3_CCR 反转电平的计数值
  * @return 无
  */
void TIM3_PWM_Init(uint16_t TIM3_ARR, uint16_t TIM3_PSC, uint16_t TIM3_CCR);

/**
  * @brief 设置定时器3的PWM通道1的从装载值
  * @param Compare 新的反转电平计数值
  * @return 无
  */
void TIM3_PWM1_SetCompare(uint16_t Compare);

/**
  * @brief 设置定时器3的PWM通道2的从装载值
  * @param Compare 新的反转电平计数值
  * @return 无
  */
void TIM3_PWM2_SetCompare(uint16_t Compare);

/**
  * @brief 设置定时器3的PWM通道3的从装载值
  * @param Compare 新的反转电平计数值
  * @return 无
  */
void TIM3_PWM3_SetCompare(uint16_t Compare);

/**
  * @brief 设置定时器3的PWM通道4的从装载值
  * @param Compare 新的反转电平计数值
  * @return 无
  */
void TIM3_PWM4_SetCompare(uint16_t Compare);

#endif

///////////////////////////////////////////////////////////
//
// 更新日志：
// V1.0: 2023/07/09
//				进行了定时器功能的重构并将定时器的功能细分
// V1.1: 2023/07/12
//				更新了部分注释
//
///////////////////////////////////////////////////////////
