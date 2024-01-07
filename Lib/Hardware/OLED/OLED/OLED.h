#ifndef __OLED_H
#define __OLED_H

///////////////////////////////////////////////////////////
//
// 文件功能：OLED显示屏基础功能
// 版本：V4.0
// 作者：墨蔚（MW）
// 修改时间：2024/01/06
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "delay.h"
#include "I2C1Hardware.h"

/* OLED I2C地址 */
#define OLED_ADDRESS			0x78

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

///////////////////////////////////////////////////////////
//
// 更新日志：
// V1.0: 2023/04/26
//				实现了OLED的基础显示
// V1.1: 2023/04/27
//				修改了显示多个16*32字符会重叠的bug
//				修改了16*32中"8"的字符库保证所有字符一样大小
// V2.0: 2023/07/07
//				根据重构的I2C库选用硬件I2C作为底层库
// V3.0: 2023/12/27
//				将普通显示和图形库解耦，并改善更换I2C依赖库的方式
// V3.1: 2023/12/28
//				修复了清屏时会出现的花屏Bug
// V4.0: 2024/01/06
//				根据新的I2C原子化重构了底层代码
//				修复了16进制显示错误的Bug
//
///////////////////////////////////////////////////////////
