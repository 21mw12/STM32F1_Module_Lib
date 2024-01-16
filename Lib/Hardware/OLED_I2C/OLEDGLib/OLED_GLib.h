#ifndef __OLED_GLIB_H
#define __OLED_GLIB_H

///////////////////////////////////////////////////////////
//
// 文件功能：OLED图形库
// 版本：V2.0
// 作者：墨蔚（MW）
// 修改时间：2023/01/07
//
// 思路来源B站up主——大明狐《一起玩OLED屏幕》(BV18h411K7MZ)
// 这里做了视频中功能的实现，以及添加了更多的功能
//
// 坐标轴说明
//			-------------------> x轴方向
//		|
//		|		    OLED屏幕
//	  |
//	  ﹀
//   y轴方向
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "I2C1Hardware.h"

/* OLED I2C地址 */
#define OLED_ADDRESS			0x78

/* 设置OLED的显示大小 */
#define OLED_GRAM_Size	 1024
#define OLED_Line				 64
#define OLED_Column			 128

/* OLED修改底层I2C依赖时需要修改为对应的函数 */
#define OLED_Write			I2C1_Hardware_SendByte


#define Image const uint8_t

typedef enum {
	Zero_Percent = 0,		// 0%占比
	TwentyFive_Percent,	// 25%占比
	Fifty_Percent,			// 50%占比
	SeventyFive_Percent,// 75%占比
	Hundred_Percent			// 100%占比
} ShowPercent;

/**
  * @brief  OLED绘图初始化
  * @return 无
  */
void OLED_GLib_Init(void);

/**
  * @brief  OLED刷新显存
  * @return 无
  */
void OLED_RefreshRam(void);

/**
  * @brief  OLED刷新部分显存
  * @param X_start 刷新区域开始的x坐标
  * @param Y_start 刷新区域开始的y坐标
  * @param X_length 刷新区域x轴方向上的长度
  * @param Y_length 刷新区域y轴方向上的长度
  * @return 无
	* 注：由于Y轴必须刷新8整数倍，所以不足整数倍的会强制补齐
  */
void OLED_RefreshRamPart(uint8_t X_start, uint8_t Y_start, uint8_t X_length, uint8_t Y_length);

/**
  * @brief  OLED清除所有缓存内容
  * @return 无
  */
void OLED_RamClear(void);

/**
  * @brief 画一个点
  * @param X x坐标
  * @param Y y坐标
  * @return 无
  */
void OLED_DrawPoint(uint8_t X, uint8_t Y);

/**
  * @brief 清除一个点
  * @param X x坐标
  * @param Y y坐标
  * @return 无
  */
void OLED_ClearPoint(uint8_t X, uint8_t Y);

/**
  * @brief 画一条线
  * @param X_start 线端开始的x坐标
  * @param Y_start 线端开始的y坐标
  * @param X_end 线端结束的x坐标
  * @param Y_end 线端结束的y坐标
  * @param step 绘制线端的步长
  * @return 无
	*
	* 注; 只能绘制从屏幕左边到屏幕右边的线段，不能反着画！！！
  */
void OLED_DrawLine(uint8_t X_start, uint8_t Y_start, uint8_t X_end, uint8_t Y_end, uint8_t step);

/**
  * @brief 清除一条线
  * @param X_start 线端开始的x坐标
  * @param Y_start 线端开始的y坐标
  * @param X_end 线端结束的x坐标
  * @param Y_end 线端结束的y坐标
  * @param step 清除线端的步长
	*
	* 注; 只能绘制从屏幕左边到屏幕右边的线段，不能反着画！！！
  * @return 无
  */
void OLED_ClearLine(uint8_t X_start, uint8_t Y_start, uint8_t X_end, uint8_t Y_end, uint8_t step);

/**
  * @brief 画矩形
  * @param X_start 矩形开始的x坐标
  * @param Y_start 矩形开始的y坐标
  * @param X_length 矩形x轴方向上的长度
  * @param Y_length 矩形y轴方向上的长度
  * @param wide 宽度
  * @return 无
  */
void OLED_DrawRectangle(uint8_t X_start, uint8_t Y_start, uint8_t X_length, uint8_t Y_length, uint8_t wide);

/**
  * @brief 画圆
  * @param X_center 圆心的x坐标
  * @param Y_center 圆心的y坐标
  * @param radius 半径
  * @param wide 宽度
  * @return 无
  */
void OLED_DrawCircle(uint8_t X_center, uint8_t Y_center, uint8_t radius, uint8_t wide);

/**
  * @brief 画椭圆
  * @param X_start 矩形开始的x坐标
  * @param Y_start 矩形开始的y坐标
  * @param X_end 矩形x轴方向上的长度
  * @param Y_end 矩形y轴方向上的长度
  * @return 无
  */
void OLED_DrawEllipse(uint8_t X_center, uint8_t Y_center, uint8_t X_radius, uint8_t Y_radius);

/**
  * @brief 画圆角矩形
  * @param X_start 矩形开始的x坐标
  * @param Y_start 矩形开始的y坐标
  * @param X_length 矩形x轴方向上的长度
  * @param Y_length 矩形y轴方向上的长度
  * @param radius 半径
  * @param wide 宽度
  * @return 无
  */
void OLED_DrawRoundedRectangle(uint8_t X_start, uint8_t Y_start, uint8_t X_length, uint8_t Y_length, uint8_t radius, uint8_t wide);

/**
  * @brief 显示图片
  * @param X 显示图片的x轴起始位置
  * @param Y 显示图片的y轴起始位置
  * @param img_Length 显示图片的长度（x方向）
  * @param img_High 显示图片的高度（y方向）
  * @param image 显示的图片
  * @return 无
  */
void OLED_DrawImg(uint8_t X, uint8_t Y, uint8_t img_Length, uint8_t img_High, Image* image);

/**
  * @brief 设置图片显示蒙版
  * @param percent 显示百分比
  * @return 无
  */
void OLED_SetDensity(ShowPercent percent);

/**
  * @brief  OLED绘制一个字符
  * @param  Line 行位置
  * @param  Column 列位置
  * @param  Char 要显示的一个字符，范围：ASCII可见字符
  * @retval 无
  */
void OLED_DrawChar(uint8_t Line, uint8_t Column, char Char);

/**
  * @brief  OLED绘制字符串
  * @param  Line 起始行位置
  * @param  Column 起始列位置
  * @param  String 要显示的字符串，范围：ASCII可见字符
  * @retval 无
  */
void OLED_DrawString(uint8_t Line, uint8_t Column, char *String);

/**
  * @brief  OLED绘制数字（十进制，带符号数）
  * @param  Line 起始行位置
  * @param  Column 起始列位置
  * @param  Number 要显示的数字，范围：0~4294967295
  * @param  Length 要显示数字的长度，范围：1~10
  * @param  Front_size 字符的大小，8：8*16大小  16: 16*32大小
  * @retval 无
  */
void OLED_DrawNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);

/**
  * @brief  OLED绘制数字（八进制，带符号数）
  * @param  Line 起始行位置
  * @param  Column 起始列位置
  * @param  Number 要显示的数字，范围：-2147483648~2147483647
  * @param  Length 要显示数字的长度，范围：1~10
  * @param  Front_size 字符的大小，8：8*16大小  16: 16*32大小
  * @retval 无
  */
void OLED_DrawSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);

/**
  * @brief  OLED绘制数字（十六进制，正数）
  * @param  Line 起始行位置
  * @param  Column 起始列位置
  * @param  Number 要显示的数字，范围：0~0xFFFFFFFF
  * @param  Length 要显示数字的长度，范围：1~8
  * @param  Front_size 字符的大小，8：8*16大小  16: 16*32大小
  * @retval 无
  */
void OLED_DrawHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

/**
  * @brief  OLED绘制数字（二进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~1111 1111 1111 1111
  * @param  Length 要显示数字的长度，范围：1~16
  * @param  Front_size 字符的大小，8：8*16大小  16: 16*32大小
  * @retval 无
  */
void OLED_DrawBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

#endif

///////////////////////////////////////////////////////////
//
// 更新日志：
// V1.0: 2023/12/27
//				实现了OLED的基础绘图功能
// V2.0: 2024/01/07
//				根据新的I2C原子化重构了底层代码
//
///////////////////////////////////////////////////////////
