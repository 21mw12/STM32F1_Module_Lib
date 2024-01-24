#ifndef __SPI2_HARDWARE_H
#define __SPI2_HARDWARE_H

///////////////////////////////////////////////////////////
//
// 文件功能：硬件SPI2的基础功能
// 版本：V2.0
// 作者：墨蔚（MW）
// 修改时间：2024/01/16
//
// 注：在江协科技的代码基础上做通用性的修改
//
// 对应引脚：      MOSI            MISO            SCK              NSS
//     SPI1  PA7/PB5(重映射)  PA6/PB4(重映射)  PA5/PB3(重映射)  PA4/PA15(重映射)
//     SPI2       PB15            PB14            PB13             PB12
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "delay.h"

/* SPI模式0~3 */
#define SPI1_Mode				0
/* SPI先行位，0表示低位先行，1表示高位先行 */
#define SPI1_FirstBit		1

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

///////////////////////////////////////////////////////////
//
// 更新日志：
// V1.0: 2023/12/27
//				实现了硬件SPI的基础显示
// V2.0: 2024/01/16
//				实现了各种模式的便捷切换
//
///////////////////////////////////////////////////////////
