#ifndef __ENCODER_H
#define __ENCODER_H

///////////////////////////////////////////////////////////
//
// 文件功能：旋转编码器的基础功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/05/06
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* 旋转编码器当前计数值 */
extern int8_t Encoder_Count;

/* 旋转编码器配置信息 */
#define Encoder_Periph		RCC_APB2Periph_GPIOB		// 总线时钟
#define Encoder_Port			GPIOB										// IO端口组
#define Encoder_A_Pin 		GPIO_Pin_0							// A相IO端口
#define Encoder_B_Pin 		GPIO_Pin_1							// B相IO端口

#define Encoder_PortSource			GPIO_PortSourceGPIOB		// 中断源IO端口组
#define Encoder_A_PinSource 		GPIO_PinSource0					// 中断源IO端口
#define Encoder_B_PinSource 		GPIO_PinSource1					// 中断源IO端口
#define Encoder_A_EXTI_Line			EXTI_Line0							// 中断线
#define Encoder_B_EXTI_Line			EXTI_Line1							// 中断线
#define Encoder_A_EXTI_IRQn 		EXTI0_IRQn							// 中断通道
#define Encoder_B_EXTI_IRQn 		EXTI1_IRQn							// 中断通道

/**
  * @brief 旋转编码器初始化
  * @return 无
  */
void Encoder_Init(void);

/**
  * @brief 获取当前旋转编码器的值
  * @return 旋转编码器的值
  */
int8_t Encoder_Get(void);

#endif
