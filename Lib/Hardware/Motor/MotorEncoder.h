#ifndef __MOTORENCODER_H
#define __MOTORENCODER_H

///////////////////////////////////////////////////////////
//
// 文件功能：带编码器的电机功能实现
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/06/24
//
// 直流电机:  ARR+1为1000   PSC+1为576
//           (电机的PWM频率选择是一个多维度的问题，这里设定了125Hz）
//           (数据来源于https://blog.csdn.net/u013273161/article/details/88316066)
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* 电机控制IO口配置 */
#define Control_Periph		RCC_APB2Periph_GPIOA		// 总线时钟
#define Control_Port			GPIOA										// IO端口组
#define Control_Pin_1 		GPIO_Pin_2							// IO端口
#define Control_Pin_2 		GPIO_Pin_3							// IO端口

/* 电机属性（以N20电机为例） */
#define Gear_Ratio									51		// 齿轮比（电机转几圈带动转一圈）
#define HoareEncoder_Circle_Count		28		// 编码器旋转一圈的计数值（四倍频）
#define Tyre_Perimeter							13.5	// 轮胎周长（cm）
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
void MotorEncoder_Init(void);

/**
  * @brief 设置电机状态
  * @param state 状态
  * @return 无
  */
void MotorEncoder_SetState(enum MotorState state);

/**
  * @brief 设置电机的PWM占空比
  * @param Speed 速度值（不要太小，如果要停止建议改变电机状态）
  * @return 无
  */
void MotorEncoder_SetDutyCycle(uint16_t DutyCycle);

/**
  * @brief 计算轮胎转动的RPM
  * @return 轮子的RPS(单位：转/秒)
	* 注：需要使用定时器每隔一定时间计算一次，定时器的时间需要修改在本文件的第27行
  */
float MotorEncoder_CalculateRPS(enum MotorState state);

/**
  * @brief 计算轮胎转动的速度
  * @return 轮子的线速度(单位：厘米/秒)
	* 注：需要使用定时器每隔一定时间计算一次，定时器的时间需要修改在本文件的第27行
  */
float MotorEncoder_CalculateSpeed(enum MotorState state);

/**
  * @brief 计算轮胎转动的距离
  * @return 运行的距离(单位：厘米)
	* 注：需要使用定时器每隔一定时间计算一次，定时器的时间需要修改在本文件的第27行
  */
float MotorEncoder_CalculateDistance(enum MotorState state);


#endif
