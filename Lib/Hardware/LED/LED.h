#ifndef __LED_H
#define __LED_H

///////////////////////////////////////////////////////////
//
// 文件功能：使用STM32系列单片机时LED的相关功能函数
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/04/21
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "delay.h"

/* LED引脚状态：0表示高电平点亮，1表示低电平点亮 */
#define LED_PIN_STATE		0

/* LED引脚配置信息 */
#define LED_Periph		RCC_APB2Periph_GPIOC		// 总线时钟
#define LED_PORT			GPIOC										// IO端口组
#define LED_PIN 			GPIO_Pin_13							// IO端口

/**
  * @brief LED初始化
  * @return 无
  */
void LED_Init(void);

/**
  * @brief LED点亮
  * @return 无
  */
void LED_ON(void);

/**
  * @brief LED熄灭
  * @return 无
  */
void LED_OFF(void);

/**
  * @brief LED闪烁
  * @return 无
  */
void LED_Flash(int ms);

#endif
