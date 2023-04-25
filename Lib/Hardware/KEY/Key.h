#ifndef __KEY_H
#define __KEY_H	

///////////////////////////////////////////////////////////
//
// 文件功能：按键的基础功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/4/25
//
// 硬件连接说明：按键一边连接IO口，另一边连接GND！！！
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "delay.h"

/* 按键引脚配置信息 */
#define Key_Periph		RCC_APB2Periph_GPIOB		// 总线时钟
#define Key_PORT			GPIOB										// IO端口组
#define Key_PIN 			GPIO_Pin_1							// IO端口

/**
  * @brief 按键初始化
  * @return 无
  */
void Key_Init(void);

/**
  * @brief 按键初始化
  * @return 按键是否被按下	0：没有按下	1：有按下
  */
uint8_t Key_Get(void);
		 				    
#endif
