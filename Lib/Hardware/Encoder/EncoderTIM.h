#ifndef __ENCODER_H
#define __ENCODER_H

///////////////////////////////////////////////////////////
//
// 文件功能：定时器的旋转编码器的基础功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/05/06
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* 旋转编码器配置信息 */
#define Encoder_Periph		RCC_APB2Periph_GPIOA		// 总线时钟
#define Encoder_Port			GPIOA										// IO端口组
#define Encoder_A_Pin 		GPIO_Pin_6							// A相IO端口
#define Encoder_B_Pin 		GPIO_Pin_7							// B相IO端口

#define Encoder_TIM				TIM3					// 定时器
#define Encoder_TIM_Periph			RCC_APB1Periph_TIM3			// 定时器时钟线
#define Encoder_NVIC_IRQn 			TIM3_IRQn								// 中断通道
#define Encoder_A_TIM_Channel		TIM_Channel_1						// 定时器通道
#define Encoder_B_TIM_Channel		TIM_Channel_2						// 定时器通道

/**
  * @brief 旋转编码器初始化
  * @return 无
  */
void Encoder_Init(void);

/**
  * @brief 获取当前旋转编码器的值, 并清零
  * @return 旋转编码器的值
  */
int16_t Encoder_GetClear(void);

/**
  * @brief 获取当前旋转编码器的值
  * @return 旋转编码器的值
  */
uint32_t Encoder_Get(void);

#endif
