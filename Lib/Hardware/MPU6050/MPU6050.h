#ifndef __MPU6050_H
#define __MPU6050_H

///////////////////////////////////////////////////////////
//
// 文件功能：MPU6050陀螺仪的基础功能
// 版本：V2.0
// 作者：墨蔚（MW）
// 修改时间：2024/10/14
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

/**
  * 是否使用数字运动处理器DMP进行姿态解算
	*  0 表示不使用
	*  1 表示使用
	*/
#define useDMP			1
// IMU采集的频率
#define IMU_DEFAULT_HZ			100

/**
  * 是否使用中断
	*  0 表示不使用
	*  1 表示使用
	*/
#define MPU_Interrupt					1
#define MPU_INT_Periph				RCC_APB2Periph_GPIOB		// 总线时钟
#define MPU_INT_Port					GPIOB										// IO端口组
#define MPU_INT_Pin 					GPIO_Pin_5							// IO端口
#define MPU_INT_PortSource		GPIO_PortSourceGPIOB		// 中断源IO端口组
#define MPU_INT_PinSource 		GPIO_PinSource5 				// 中断源IO端口
#define MPU_INT_EXTI_Line			EXTI_Line5							// 中断线
#define MPU_INT_EXTI_IRQn 		EXTI9_5_IRQn						// 中断通道

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

#if useDMP == 1
/**
  * @brief DMP读取角度数据
  * @param Pitch 俯仰角，绕着X轴旋转
  * @param Roll 翻滚角，绕着Y轴旋转
  * @param Yaw 偏航角，绕着Z轴旋转
  * @return 返回0表示正常运行
  */
uint8_t MPU_DMP_ReadAngle(float *Pitch, float *Roll, float *Yaw);

/**
  * @brief DMP写数据（用于DMP库使用）
  * @param address 从机地址
  * @param command 指令
  * @param array 数据数组
  * @param length 数据长度（数据数量）
  * @return 无
  */
int DMP_Write(uint8_t SlaveAddr, uint8_t WriteAddr, u16 NumByteToWrite, uint8_t* pBuffer);

/**
  * @brief DMP读数据（用于DMP库使用）
  * @param address 从机地址
  * @param reg 地址
  * @param array 数据数组
  * @param length 数据长度（数据数量）
  * @return 无
  */
int DMP_Read(uint8_t SlaveAddr, uint8_t readAddr, u16 NumByteToRead, uint8_t* pBuffer);
#endif

#if MPU_Interrupt == 1
/**
  * @brief 开启MPU6050的中断引脚
  * @return 无
  */
void MPU6050_INT_Enable(void);

/**
  * @brief 关闭MPU6050的中断引脚
  * @return 无
  */
void MPU6050_INT_Disable(void);
#endif

#endif


///////////////////////////////////////////////////////////
//
// 更新日志：
// V1.0: 2024/07/17
//				实现了读取三轴加速度计和角速度计的功能
// V2.0: 2024/10/14
//				移植了eMPL库使用DMP读取三轴角度
//
///////////////////////////////////////////////////////////