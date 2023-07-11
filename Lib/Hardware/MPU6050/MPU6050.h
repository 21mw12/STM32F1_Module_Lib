#ifndef __MPU6050_H
#define __MPU6050_H

///////////////////////////////////////////////////////////
//
// 文件功能：MPU6050陀螺仪的基础功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/07/07
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "delay.h"
#include "MPU6050_Register.h"
#include "I2C1Hardware.h"

extern uint16_t MPU6050_data[5];

/**
  * @brief MPU6050陀螺仪初始化
  * @return 无
  */
void MPU6050_Init(void);

uint8_t MPU6050_GetID(void);

void MPU6050_READ(void);

#endif
