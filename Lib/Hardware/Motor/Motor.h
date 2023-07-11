#ifndef __MOTOR_H
#define __MOTOR_H

///////////////////////////////////////////////////////////
//
// 文件功能：带编码器的电机功能实现
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/06/24
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "TIM3Encoder.h"
#include "TIM2PWM.h"

/* 电机控制IO口配置 */
#define Control_Periph		RCC_APB2Periph_GPIOA		// 总线时钟
#define Control_PORT			GPIOA										// IO端口组
#define Control_PIN_1 		GPIO_Pin_2							// IO端口
#define Control_PIN_2 		GPIO_Pin_3							// IO端口

/* 电机属性（以N20电机为例） */
#define Gear_Ratio									51		// 齿轮比（电机转几圈带动转一圈）
#define HoareEncoder_Circle_Count		28		// 编码器旋转一圈的计数值（四倍频）
#define Tyre_Perimeter							50		// 轮胎周长（cm）
#define Calculate_Time							1			// 计算间隔时间（s）

/* 电机状态结构体 */
enum MotorState {
	ForwardTurn,	// 向前转
	ReverseTurn,	// 向后转
	Stop,					// 停转
};

/**
  * @brief 电机初始化
  * @return 无
  */
void Motor_Init(void);

/**
  * @brief 设置电机状态
  * @param state 状态
  * @return 无
  */
void Motor_SetState(enum MotorState state);

/**
  * @brief 设置电机的PWM占空比
  * @param Speed 速度值（不要太小，如果要停止建议改变电机状态）
  * @return 无
  */
void Motor_SetDutyCycle(int8_t DutyCycle);

/**
  * @brief 计算轮胎转动速度
  * @return 轮胎速度(单位cm/s)
	* 注：需要使用定时器每隔一定时间计算一次，定时器的时间需要修改在本文件的第27行
  */
float Motor_CalculateSpeed(void);

#endif
