#ifndef __BUZZER_H
#define __BUZZER_H

///////////////////////////////////////////////////////////
//
// 文件功能：有源蜂鸣器的基础功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/05/02
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* 蜂鸣器引脚配置信息 */
#define BUZZER_Periph		RCC_APB2Periph_GPIOC		// 总线时钟
#define BUZZER_PORT			GPIOC										// IO端口组
#define BUZZER_PIN 			GPIO_Pin_14							// IO端口

/**
  * @brief 蜂鸣器初始化
  * @return 无
  */
void Buzzer_Init(void);

/**
  * @brief 蜂鸣器响
  * @return 无
  */
void BUZZER_ON(void);

/**
  * @brief 蜂鸣器关闭
  * @return 无
  */
void BUZZER_OFF(void);

#endif
