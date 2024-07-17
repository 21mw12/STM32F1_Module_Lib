#ifndef __MPU6050_H
#define __MPU6050_H

///////////////////////////////////////////////////////////
//
// 文件功能：MPU6050陀螺仪的基础功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/07/17
//
// 注：在满量程16g的情况下
//     加速度值 / 32768 = x / 16 (其中x表示该轴上的重力加速度)
//     陀螺仪值 / 32768 = x / 16 (其中x表示该轴上的角速度值)     
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/**
  * 是否使用SPI总线
	*  0 表示使用软件I2C
	*  1 表示使用I2C1
	*  2 表示使用I2C2
	*/
#define whichI2C		0

// X、Y、Z三轴加速度/陀螺仪原始数据
// 从下标0到5分别是： AX、 AY、 AZ、 GX、 GY、 GZ
extern int16_t MPU6050_data[6];

/**
  * @brief MPU6050陀螺仪初始化
  * @return 无
  */
void MPU6050_Init(void);

/**
  * @brief MPU6050获取期间ID
  * @return ID号
  */
uint8_t MPU6050_GetID(void);

/**
  * @brief MPU6050读取数据
  * @return 无
  */
void MPU6050_READ(void);

#endif
