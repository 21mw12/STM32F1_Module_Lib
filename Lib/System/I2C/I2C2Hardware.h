#ifndef __I2C2_HARDWARE_H
#define __I2C2_HARDWARE_H

///////////////////////////////////////////////////////////
//
// 文件功能：硬件I2C的基础功能
// 版本：V2.0
// 作者：墨蔚（MW）
// 修改时间：2024/01/07
//
// 对应引脚：                SCL                 SDA
//            I2C2    PB6 / PB8(重映射)    PB7 / PB9(重映射)
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
  * @brief 硬件I2C2开始信号
  * @return 无
  */
void I2C2_Hardware_StartSignal(void);

/**
  * @brief 硬件I2C2结束信号
  * @return 无
  */
void I2C2_Hardware_StopSignal(void);

/**
  * @brief 硬件I2C2发送设备写地址
  * @param Address 从机地址
  * @return 无
  */
void I2C2_Hardware_SendWriteAddress(uint8_t Address);

/**
  * @brief 硬件I2C2发送设备读地址
  * @param Address 从机地址
  * @return 无
  */
void I2C2_Hardware_SendReadAddress(uint8_t Address);

/**
  * @brief 硬件I2C2发送一字节数据
  * @param I2CData 发送的数据
  * @return 无
  */
void I2C2_Hardware_SendData(uint8_t Data);

/**
  * @brief 硬件I2C2接收一字节数据
  * @return 接收到的数据
  */
uint8_t I2C2_Hardware_ReceiveData(void);

/**
  * @brief 硬件I2C2关闭应答信号
  * @return 无
  */
void I2C2_Hardware_CloseACKSignal(void);

/**
  * @brief 硬件I2C2打开应答信号
  * @return 无
  */
void I2C2_Hardware_OpenACKSignal(void);

#endif

///////////////////////////////////////////////////////////
//
// 更新日志：
// V1.0: 2023/07/07
//				实现了硬件IC的基础功能
// V2.0: 2024/01/07
//				将I2C的功能原子化，编译代码复用以及兼容更多模块
//
///////////////////////////////////////////////////////////
