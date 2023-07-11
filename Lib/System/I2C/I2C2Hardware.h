#ifndef __I2C2_HARDWARE_H
#define __I2C2_HARDWARE_H

///////////////////////////////////////////////////////////
//
// 文件功能：硬件I2C的基础功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/07/07
//
// 对应引脚：                SCL                 SDA
//            I2C1    PB6 / PB8(重映射)    PB7 / PB9(重映射)
//            I2C2          PB10                PB11
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* 硬件I2C配置信息 */
#define I2C2_HostAddress						0xFC				// 主机I2C的地址（不得和从机地址重复）
#define I2C2_Speed									50000			// I2C总线速度（I2C功能不能用的时候适当调整该参数）
#define I2C2_Timeout								10000				//防卡死计数器的初始值

/**
  * @brief 硬件I2C初始化
  * @return 无
  */
void I2C2_Hardware_Init(void);

/**
  * @brief 硬件I2C发送一个字节
  * @param address 从机地址
  * @param command 指令
  * @param data 数据
  * @return 无
  */
void I2C2_Hardware_SendByte(uint8_t SlaveAddr, uint8_t writeAddr, uint8_t pBuffer);

/**
  * @brief 硬件I2C发送一个数组
  * @param address 从机地址
  * @param command 指令
  * @param array 数据数组
  * @param length 数据长度（数据数量）
  * @return 无
  */
void I2C2_Hardware_SendArray(uint8_t SlaveAddr, uint8_t writeAddr, uint8_t* pBuffer, u16 NumByteToWrite);

/**
  * @brief 硬件I2C接收一个字节
  * @param address 从机地址
  * @param reg 读取寄存器
  * @return 读取到的数据
  */
uint8_t I2C2_Hardware_ReadByte(uint8_t SlaveAddr, uint8_t readAddr);

/**
  * @brief 硬件I2C接收一个数组
  * @param address 从机地址
  * @param reg 读取寄存器
  * @param array 数据数组
  * @param length 数据长度（数据数量）
  * @return 无
  */
uint8_t I2C2_Hardware_ReadArray(uint8_t SlaveAddr, uint8_t readAddr, uint8_t* pBuffer, u16 NumByteToRead);

#endif
