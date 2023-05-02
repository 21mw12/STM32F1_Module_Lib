#ifndef __ADC_H
#define __ADC_H

///////////////////////////////////////////////////////////
//
// 文件功能：ADC基础功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/05、02
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* ADC配置信息 */
#define ADC_Periph			RCC_APB2Periph_ADC1			// ADC总线时钟
#define ADC							ADC1										// ADC
#define ADC_IO_Periph		RCC_APB2Periph_GPIOA		// 使用ADC的IO口的总线时钟
#define ADC_PORT				GPIOA										// IO端口组
#define ADC_PIN 				GPIO_Pin_0							// IO端口

/**
  * @brief ADC初始化
  * @return 无
  */
void ADC_INit(void);

/**
  * @brief 读取ADC获取的值
  * @return 转换后的值
  */
uint16_t ADC_GetValue(void);

#endif


