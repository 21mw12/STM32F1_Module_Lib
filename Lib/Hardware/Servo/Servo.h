#ifndef __SERVO_H
#define __SERVO_H

///////////////////////////////////////////////////////////
//
// 文件功能：舵机的基础功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/06/15
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "pwm.h"

/**
  * @brief 舵机初始化
  * @return 无
  */
void Servo_Init(void);

/**
  * @brief 设置舵机角度
  * @param Angle 角度值
  * @return 无
  */
void Servo_SetAngle(float Angle);

#endif
