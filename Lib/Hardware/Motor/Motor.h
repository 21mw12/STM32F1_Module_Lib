#ifndef __MOTOR_H
#define __MOTOR_H

/////////////////////////////////////////////////////////////////////////////////////
//
// 文件功能：电机功能实现
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/07/12
//
// 直流电机:  ARR+1为1000   PSC+1为576
//           (电机的PWM频率选择是一个多维度的问题，这里设定了125Hz）
//           (数据来源于https://blog.csdn.net/u013273161/article/details/88316066)
//
/////////////////////////////////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* 电机控制IO口配置 */
#define Control_Periph		RCC_APB2Periph_GPIOA		// 总线时钟
#define Control_Port			GPIOA										// IO端口组
#define Control_Pin_1 		GPIO_Pin_2							// IO端口
#define Control_Pin_2 		GPIO_Pin_3							// IO端口

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

#endif
