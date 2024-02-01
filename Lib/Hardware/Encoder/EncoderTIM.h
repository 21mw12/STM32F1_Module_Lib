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
#include "TIM3Encoder.h"

/* 旋转编码器旋转方向枚举 */
typedef enum {
	EncoderDirect_Idel = 0,		// 未旋转
	EncoderDirect_Clockwise,	// 顺时钟旋转
	EncoderDirect_AntiClockwise	// 逆时钟旋转
} EncoderDirect;

/**
  * @brief 旋转编码器初始化
  * @return 无
  */
#define Encoder_Init()		TIM3_Encoder_Init()

/**
  * @brief 获得旋转编码器旋转的数值和方向
  * @param encoderCount 旋转数值
  * @return 旋转方向
  */
EncoderDirect Encoder_GetSpinCount(uint16_t* encoderCount);

#endif

///////////////////////////////////////////////////////////
//
// 更新日志：
// V1.0: 2023/05/06
//				实现了旋转编码器的基础绘图功能
// V2.0: 2024/02/01
//				基于硬件编码器重构了代码
//
///////////////////////////////////////////////////////////
