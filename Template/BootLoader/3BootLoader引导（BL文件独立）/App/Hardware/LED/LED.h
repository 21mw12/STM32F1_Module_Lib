#ifndef __LED_H
#define __LED_H

///////////////////////////////////////////////////////////
//
// 文件功能：LED的相关功能函数
// 版本：V1.1
// 作者：墨蔚（MW）
// 修改时间：2023/04/27
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* LED引脚状态：0表示高电平点亮，1表示低电平点亮 */
#define LED_Pin_State		0

/* LED引脚配置信息 */
#define LED_Periph		RCC_APB2Periph_GPIOC		// 总线时钟
#define LED_Port			GPIOC										// IO端口组
#define LED_Pin 			GPIO_Pin_13							// IO端口

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
  * @brief LED状态反转
  * @return 无
  */
void LED_Turn(void);

/**
  * @brief LED闪烁
	* @param ms 闪烁间隔的毫秒数
  * @return 无
  */
void LED_Flash(int ms);

#endif

///////////////////////////////////////////////////////////
//
// 更新日志：
// V1.0: 2023/04/21
//				实现了LED的亮灭以及LED的闪烁功能
// V1.1: 2023/04/27
//				实现了LED的状态反转功能
//
///////////////////////////////////////////////////////////
