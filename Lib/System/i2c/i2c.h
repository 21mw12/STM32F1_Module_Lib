#ifndef __STM32F10x_I2C_H
#define __STM32F10x_I2C_H

#include "stm32f10x.h"

///////////////////////////////////////////////////////////
//
// 文件功能：I2C的基础功能
// 版本：V1.1
// 作者：墨蔚（MW）
// 修改时间：2023/07/07
//
///////////////////////////////////////////////////////////

// 选择软件I2C还是硬件I2C
// 			0: 软件I2C
// 			1: 硬件I2C
#define SoftOrHaradWareI2C		1

/**
  * @brief I2C总线初始化
  * @return 无
  */
void I2C_Bus_Init(void);

/**
  * @brief I2C发送一个字节
  * @param address 从机地址
  * @param command 指令
  * @param data 数据
  * @return 无
  */
void I2C_Bus_SendByte(uint8_t SlaveAddr, uint8_t writeAddr, uint8_t pBuffer);

/**
  * @brief I2C发送一个数组
  * @param address 从机地址
  * @param command 指令
  * @param array 数据数组
  * @param length 数据长度（数据数量）
  * @return 无
  */
void I2C_Bus_SendArray(uint8_t SlaveAddr, uint8_t writeAddr, uint8_t* pBuffer, uint16_t NumByteToWrite);

/**
  * @brief I2C接收一个字节
  * @param address 从机地址
  * @param reg 读取寄存器
  * @return 读取到的数据
  */
uint8_t I2C_Bus_ReadByte(uint8_t SlaveAddr, uint8_t readAddr);

/**
  * @brief I2C接收一个数组
  * @param address 从机地址
  * @param reg 读取寄存器
  * @param array 数据数组
  * @param length 数据长度（数据数量）
  * @return 无
  */
uint8_t I2C_Bus_ReadArray(uint8_t SlaveAddr, uint8_t readAddr, uint8_t* pBuffer, uint16_t NumByteToRead);

#endif

///////////////////////////////////////////////////////////
//
// 更新日志：
// V1.0: 2023/04/21
//				实现了软件I2C的基本功能
// V1.1: 2023/07/07
//				实现了软硬件I2C的基本功能并可以简单的切换
//
///////////////////////////////////////////////////////////
