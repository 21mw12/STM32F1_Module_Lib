#ifndef __HC_RS04_H
#define __HC_RS04_H

///////////////////////////////////////////////////////////
//
// 文件功能：超声波模块的功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/07/12
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "TIM2COUNT.h"
#include "delay.h"

/* 超声波模块引脚配置 */
#define HCSR04_Trig_Periph      RCC_APB2Periph_GPIOA
#define HCSR04_Echo_Periph      RCC_APB2Periph_GPIOA
#define HCSR04_Trig_PORT     		GPIOA
#define HCSR04_Echo_PORT     		GPIOA
#define HCSR04_TRIG_Pin         GPIO_Pin_9
#define HCSR04_Echo_Pin         GPIO_Pin_10

/* 取平均次数 */
#define Average_CalCount		5

/**
  * @brief 超声波模块初始化
  * @return 无
  */
void HC_SR04_Init(void);

/**
  * @brief 超声波模块获取距离
  * @return 距离
  */
float HC_SR04_GetLength(void);

#endif
