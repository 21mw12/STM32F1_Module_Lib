#ifndef __SPI_SOFTWARE_H
#define __SPI_SOFTWARE_H

///////////////////////////////////////////////////////////
//
// 文件功能：软件模拟SPI的基础功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/12/27
//
// 注：在江协科技的代码基础上做通用性的修改
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* 软件SPI端口信息 */
#define SPI_Software_GPIOPeriph		RCC_APB2Periph_GPIOA
#define SPI_Software_Port					GPIOA
#define SPI_Software_Pin_CLK			GPIO_Pin_5
#define SPI_Software_Pin_MISO			GPIO_Pin_6
#define SPI_Software_Pin_MOSI			GPIO_Pin_7

/**
  * @brief 软件SPI初始化
  * @return 无
  */
void SPI_Software_Init(void);

/**
  * @brief SPI交换一个字节（模式0）
  * @param SendByte 要发送的数据
  * @return 接收到的数据
  */
uint8_t SPI_Software_SwapByte(uint8_t SendByte);

#endif
