#ifndef __STM32F10x_I2C_SOFTWARE_H
#define __STM32F10x_I2C_SOFTWARE_H

#include "stm32f10x.h"
#include "delay.h"

///////////////////////////////////////////////////////////
//
// 文件功能：软件模拟I2C的基础功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/07/07
//
///////////////////////////////////////////////////////////

/* 软件I2C端口信息 */
#define I2C_Software_GPIOPeriph		RCC_APB2Periph_GPIOB
#define I2C_Software_PORT					GPIOB
#define I2C_Software_SCL_PIN			GPIO_Pin_8
#define I2C_Software_SDA_PIN			GPIO_Pin_9

/**
  * @brief 软件I2C初始化
  * @return 无
  */
void I2C_Software_Init(void);

/**
  * @brief 软件I2C发送一个字节
  * @param address 从机地址
  * @param command 指令
  * @param data 数据
  * @return 无
  */
void I2C_Software_SendByte(uint8_t SlaveAddr, uint8_t writeAddr, uint8_t pBuffer);

/**
  * @brief 软件I2C发送一个数组
  * @param address 从机地址
  * @param command 指令
  * @param array 数据数组
  * @param length 数据长度（数据数量）
  * @return 无
  */
void I2C_Software_SendArray(uint8_t SlaveAddr, uint8_t WriteAddr, uint8_t* pBuffer, u16 NumByteToWrite);

/**
  * @brief 软件I2C读一个字节
  * @param address 从机地址
  * @param reg 地址
  * @return 读取到的数据
  */
uint8_t I2C_Software_ReadByte(uint8_t SlaveAddr, uint8_t readAddr);

/**
  * @brief 软件I2C读一个数组
  * @param address 从机地址
  * @param reg 地址
  * @param array 数据数组
  * @param length 数据长度（数据数量）
  * @return 无
  */
void I2C_Software_ReadArray(uint8_t SlaveAddr, uint8_t readAddr, uint8_t* pBuffer, u16 NumByteToRead);

#endif
