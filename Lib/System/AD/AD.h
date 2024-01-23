#ifndef __AD_H
#define __AD_H

///////////////////////////////////////////////////////////
//
// 文件功能：ADC1的基础功能
// 版本：V2.0
// 作者：墨蔚（MW）
// 修改时间：2024/01/23
//
// ADC1通道对应IO口：
//     通道0 —— PA0        通道9  —— PB1
//     通道1 —— PA1        通道10 —— PC0
//     通道2 —— PA2        通道11 —— PC1
//     通道3 —— PA3        通道12 —— PC2
//     通道4 —— PA4        通道13 —— PC3
//     通道5 —— PA5        通道14 —— PC4
//     通道6 —— PA6        通道15 —— PC5
//     通道7 —— PA7        通道16 —— 内部温度传感器
//     通道8 —— PB0        通道17 —— 内部Vrefint
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/**
	*	是否开启连续转换
	* 1：表示开启，ADC将不断的进行转换
	* 0：表示关闭，只有手动触发ADC才会进行一次转换
	*/
#define isContinuousConversion		0

/**
  * 开启的通道 （0~15）
	* 范围：0~15 或 小于0的数
	* 含义：若设置为4，表示0~4通道均开启。
	*			  若设置为-1，表示只使用一个自定义通道，在下面的宏中配置
	*/
#define ADCChannelCount						4

#if ADCChannelCount > 0
	/* 多通道下，通道的数据存放在数组的对应下标中 */
	extern uint16_t AD_Value[ADCChannelCount+1];
#else
	/* 自定义ADC通道引脚配置信息 */
	#define ADC_Periph		RCC_APB2Periph_GPIOA
	#define ADC_PORT			GPIOA
	#define ADC_PIN 			GPIO_Pin_0
	#define ADC_Channel		ADC_Channel_0
#endif

/**
  * @brief ADC初始化
  * @return 无
  */
void AD_Init(void);

#if ADCChannelCount > 0
#if isContinuousConversion == 0
/**
  * @brief 读取ADC获取的值
  * @return 无
  */
void AD_GetValue(void);
#else
/**
  * @brief 读取ADC获取的值
  * @return 转换后的值
  */
uint16_t AD_GetValue(void);
#endif
#endif

#endif

///////////////////////////////////////////////////////////
//
// 更新日志：
// V1.0: 2023/05/02
//				实现了单通道的ADC
// V2.0: 2024/01/23
//				实现了DMA多通道采集的ADC，并实现了方便的配置
//
///////////////////////////////////////////////////////////
