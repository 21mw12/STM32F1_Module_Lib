#ifndef __OLED_H
#define __OLED_H

///////////////////////////////////////////////////////////
//
// 文件功能：使用SPI协议的OLED基础功能实现
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/01/16
//
// 引脚说明：
//		D0为时钟引脚，接入对应的硬件SPI的SCK引脚上
// 		D1为数据引脚，接入对应的硬件SPI的MOSI引脚上
// 		RES为重启引脚，可由用户自定义
// 		DC为命令数据选择引脚，可由用户自定义
// 		CS为片选引脚，可由用户自定义
//
// 硬件SPI模式：SPI模式0，高位先行
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* OLED引脚配置信息 */
#define OLED_Periph		RCC_APB2Periph_GPIOB
#define OLED_PORT			GPIOB
#define OLED_PIN_DC 	GPIO_Pin_10
#define OLED_PIN_RES 	GPIO_Pin_11
#define OLED_PIN_CS 	GPIO_Pin_12

/**
  * @brief  OLED初始化
  * @param  无
  * @retval 无
  */
void OLED_Init(void);

/**
  * @brief  OLED清屏
  * @param  无
  * @retval 无
  */
void OLED_Clear(void);

/**
  * @brief  OLED显示一个字符
  * @param  Line 行位置
  * @param  Column 列位置
  * @param  Char 要显示的一个字符，范围：ASCII可见字符
  * @param  Front_size 字符的大小，8：8*16大小  16: 16*32大小
  * @retval 无
  */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char, uint8_t Front_size);

/**
  * @brief  OLED显示字符串
  * @param  Line 起始行位置
  * @param  Column 起始列位置
  * @param  String 要显示的字符串，范围：ASCII可见字符
  * @param  Front_size 字符的大小，8：8*16大小  16: 16*32大小
  * @retval 无
  */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String, uint8_t Front_size);

/**
  * @brief  OLED显示数字（十进制，带符号数）
  * @param  Line 起始行位置
  * @param  Column 起始列位置
  * @param  Number 要显示的数字，范围：0~4294967295
  * @param  Length 要显示数字的长度，范围：1~10
  * @param  Front_size 字符的大小，8：8*16大小  16: 16*32大小
  * @retval 无
  */
void OLED_ShowNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length, uint8_t Front_size);

/**
  * @brief  OLED显示数字（八进制，带符号数）
  * @param  Line 起始行位置
  * @param  Column 起始列位置
  * @param  Number 要显示的数字，范围：-2147483648~2147483647
  * @param  Length 要显示数字的长度，范围：1~10
  * @param  Front_size 字符的大小，8：8*16大小  16: 16*32大小
  * @retval 无
  */
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length, uint8_t Front_size);

/**
  * @brief  OLED显示数字（十六进制，正数）
  * @param  Line 起始行位置
  * @param  Column 起始列位置
  * @param  Number 要显示的数字，范围：0~0xFFFFFFFF
  * @param  Length 要显示数字的长度，范围：1~8
  * @param  Front_size 字符的大小，8：8*16大小  16: 16*32大小
  * @retval 无
  */
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length, uint8_t Front_size);

/**
  * @brief  OLED显示数字（二进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~1111 1111 1111 1111
  * @param  Length 要显示数字的长度，范围：1~16
  * @param  Front_size 字符的大小，8：8*16大小  16: 16*32大小
  * @retval 无
  */
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length, uint8_t Front_size);

#endif
