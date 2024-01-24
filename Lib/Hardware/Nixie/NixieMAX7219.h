#ifndef __NIXIEMAX7219_H__
#define __NIXIEMAX7219_H__

///////////////////////////////////////////////////////////
//
// 文件功能：配合MAX7219芯片的8位数码管的显示功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/05/12
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* 8段数码管引脚配置信息 */
#define MAX7219_Periph				RCC_APB2Periph_GPIOA		// 总线时钟
#define MAX7219_Port					GPIOA										// IO端口组
#define MAX7219_Pin_DIN				GPIO_Pin_1							// MAX7219的IO端口
#define MAX7219_Pin_LOAD			GPIO_Pin_2
#define MAX7219_Pin_CLK				GPIO_Pin_3

/**
  * @brief 数码管初始化
  * @param 
  * @return 
  */
void Nixie_Init(void);

/**
  * @brief 数码管显示
  * @param Location 要显示的位置（1~8）
  * @param Number	要显示的内容（0~10 即 0~9和-）
  * @return 无
  */
void Nixie_Show(uint8_t Location, uint8_t Number);

#endif
