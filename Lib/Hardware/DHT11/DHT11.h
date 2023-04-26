#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f10x.h"

///////////////////////////////////////////////////////////
//
// 文件功能：DHT11温湿度传感器模块的功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/4/26
//
///////////////////////////////////////////////////////////

/* DHT11数据精度 */
#define DHT11_Data_Accurate		1

/* DHT11引脚配置信息 */
#define DHT11_Periph		RCC_APB2Periph_GPIOA		// 总线时钟
#define DHT11_PORT			GPIOA										// IO端口组
#define DHT11_PIN 			GPIO_Pin_11							// IO端口

/**
  * @brief 温湿传感器初始化
  * @return 初始化状态		0：失败 
	* 										1：成功
  */
uint8_t DHT11_Init(void);

/**
  * @brief 读取一次数据
  * @param temp 温度值 范围:0°~50°
  * @param humi 湿度值 范围:20%~90%
  * @return 数据接收状态		0：失败 
	* 											1：正常
  */
uint8_t DHT11_ReadData(uint8_t *temp, uint8_t *humi);

#endif















