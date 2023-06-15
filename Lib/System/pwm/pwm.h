#ifndef __PWM_H
#define __PWM_H

///////////////////////////////////////////////////////////
//
// 文件功能：实现了PWM的相关功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/06/25
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* 输出引脚配置 */
/**
  * 修改PWM输出引脚时同时要设置定时器的对应通道和设置对应修改计数器
	* 分别在Servo.c文件的第10行以及第36行的函数名！！！
  */
#define PWM_Periph		RCC_APB2Periph_GPIOA		// 总线时钟
#define PWM_PORT			GPIOA										// IO端口组
#define PWM_PIN 			GPIO_Pin_1							// IO端口

/* 定时时钟配置 */
#define Tim_Periph			RCC_APB1Periph_TIM2		// 总线时钟
#define Tim							TIM2									// 定时器选择

/* PWM参数配置 */
/**
  * PWM计算公式：
	*			PWM频率 = CK_PSC / (PSC + 1) / (ARR + 1)
	*     PWM占空比 = CCR / (ARR + 1)
	*			PWM分辨率 = 1 / (ARR + 1)
	*
	*				CK_PSC：系统主频（72MHz）
	*				arr：自动重装器的值
	*				psc：预分频器的值
	*				ccr：反转电平的计数值
  */
#define ARR		20000 - 1
#define PSC		72 - 1
#define CCR		0

/**
  * @brief PWM初始化
  * @return 无
  */
void PWM_Init(void);

/**
  * @brief 设置PWM的从装载值
  * @param Compare 新的重装载值
  * @return 无
  */
void PWM_SetCompare(uint16_t Compare);

#endif
