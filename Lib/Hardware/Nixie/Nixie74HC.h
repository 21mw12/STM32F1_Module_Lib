#ifndef __NIXIE74HC_H__
#define __NIXIE74HC_H__

///////////////////////////////////////////////////////////
//
// 文件功能：配合74HC138和74HC245芯片的8位数码管的显示功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/05/12
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "delay.h"

/* 8段数码管引脚配置信息 */
#define Nixie_Periph				RCC_APB2Periph_GPIOB		// 总线时钟
#define Nixie_PORT					GPIOB										// IO端口组
#define HC254_PIN_A0				GPIO_Pin_0							// 74HC254的IO端口
#define HC254_PIN_A1				GPIO_Pin_1
#define HC254_PIN_A2				GPIO_Pin_2
#define HC254_PIN_A3				GPIO_Pin_3
#define HC254_PIN_A4				GPIO_Pin_4
#define HC254_PIN_A5				GPIO_Pin_5
#define HC254_PIN_A6				GPIO_Pin_6
#define HC254_PIN_A7				GPIO_Pin_7
#define HC138_PIN_A					GPIO_Pin_8							// 74HC138的IO端口
#define HC138_PIN_B					GPIO_Pin_9
#define HC138_PIN_C					GPIO_Pin_10

/**
  * @brief 数码管初始化
  * @return 无
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
