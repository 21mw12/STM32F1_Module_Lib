#ifndef __SPI2_HARDWARE_H
#define __SPI2_HARDWARE_H

#include "stm32f10x.h"
#include "delay.h"

///////////////////////////////////////////////////////////
//
// 文件功能：硬件SPI2的基础功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/12/27
//
// 注：在江协科技的代码基础上做通用性的修改
//
///////////////////////////////////////////////////////////

/**
  * @brief 硬件SPI2初始化
  * @return 无
  */
void SPI2_Hardware_Init(void);

/**
  * @brief SPI2交换一个字节（模式0）
  * @param SendByte 要发送的数据
  * @return 接收到的数据
  */
uint8_t SPI2_Hardware_SwapByte(uint8_t SendByte);

#endif
