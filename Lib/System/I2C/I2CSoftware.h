#ifndef __I2C_SOFTWARE_H
#define __I2C_SOFTWARE_H

#include "stm32f10x.h"
#include "delay.h"

///////////////////////////////////////////////////////////
//
// 文件功能：软件模拟I2C的基础功能
// 版本：V2.0
// 作者：墨蔚（MW）
// 修改时间：2024/01/28
//
///////////////////////////////////////////////////////////

/* 软件I2C端口信息 */
#define I2C_Software_GPIOPeriph		RCC_APB2Periph_GPIOB
#define I2C_Software_Port					GPIOB
#define I2C_Software_Pin_SCL			GPIO_Pin_10
#define I2C_Software_Pin_SDA			GPIO_Pin_11

/**
  * @brief 软件I2C初始化
  * @return 无
  */
void I2C_Software_Init(void);

/**
  * @brief  I2C开始
  * @param  GPIOx ： IO端口组
  * @param  GPIO_Pin ： IO端口
  * @retval 无
  */
void I2C_Software_StartSignal(void);

/**
  * @brief  I2C停止
  * @param  GPIOx ： IO端口组
  * @param  GPIO_Pin ： IO端口
  * @retval 无
  */
void I2C_Software_StopSignal(void);

/**
  * @brief  I2C发送一个字节
  * @param  Byte 要发送的一个字节
  * @retval 无
  */
void I2C_Software_SendData(uint8_t Byte);

/**
  * @brief  I2C接收一个字节
  * @retval 接收到的数据
  */
uint8_t I2C_Software_ReceiveByte(void);

/**
  * @brief  发送应答
  * @param  应答信息
  * @retval 无
  */
void I2C_Software_SendAck(uint8_t AckBit);

/**
  * @brief  接收应答
  * @retval 应答信息
  */
uint8_t I2C_Software_ReceiveAck(void);

/*************************************************************************/

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


///////////////////////////////////////////////////////////
//
// 更新日志：
// V1.0: 2023/07/07
//				实现了软件模拟I2C的基础功能
// V2.0: 2024/01/28
//				依据硬件I2C将基本时序独立
//
///////////////////////////////////////////////////////////
