#ifndef __HX711_H
#define __HX711_H

///////////////////////////////////////////////////////////
//
// 文件功能：HX711称重传感器的基础功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/01/26
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* 重量转换系数，根据不同的传感器有不同的值 */
#define HX711_coefficient				270.5

/* HX711引脚配置信息 */
#define HX711_Periph			RCC_APB2Periph_GPIOC
#define HX711_Port				GPIOC
#define HX711_Pin_DT 			GPIO_Pin_15
#define HX711_Pin_SCK			GPIO_Pin_14

/**
  * @brief HX711初始化
  * @return 无
  */
void HX711_Init(void);

/**
  * @brief HX711复位
  * @return 无
  */
void HX711_Reset(void);

/**
  * @brief HX711获得原始数据
  * @return 原始数据
  */
uint32_t HX711_ReadData(void);

/**
  * @brief HX711获得重量数据
  * @return 重量数据
  */
uint32_t HX711_GetWeight(void);


#endif
