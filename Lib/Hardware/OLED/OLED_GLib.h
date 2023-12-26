#ifndef __OLED_GLIB_H
#define __OLED_GLIB_H

///////////////////////////////////////////////////////////
//
// 文件功能：OLED图形库
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/0
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
#include "OLED.h"

/* 设置OLED的显示大小 */
#define OLED_GRAM_Size	 1024
#define OLED_Line				 64
#define OLED_Column			 128

typedef enum {
	Empty = 0,
	Fill
} FillPattern;

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
  */
void OLED_RefreshRamPart(uint8_t X_start, uint8_t Y_start, uint8_t X_length, uint8_t Y_length);

/**
  * @brief  OLED清屏
  * @return 无
  */
void OLED_Clear(void);

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
  * @param pattern 内部是否填充
  * @return 无
  */
void OLED_DrawRectangle(uint8_t X_start, uint8_t Y_start, uint8_t X_length, uint8_t Y_length, FillPattern pattern);

/**
  * @brief 画圆
  * @param X_center 圆心的x坐标
  * @param Y_center 圆心的y坐标
  * @param radius 半径
  * @param pattern 内部是否填充
  * @return 无
  */
void OLED_DrawCircle(uint8_t X_center, uint8_t Y_center, uint8_t radius, FillPattern pattern);

/**
  * @brief 画椭圆
  * @param X_start 矩形开始的x坐标
  * @param Y_start 矩形开始的y坐标
  * @param X_end 矩形x轴方向上的长度
  * @param Y_end 矩形y轴方向上的长度
  * @param pattern 内部是否填充
  * @return 无
  */
void OLED_DrawEllipse(uint8_t X_center, uint8_t Y_center, uint8_t X_radius, uint8_t Y_radius, FillPattern pattern);

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
  * @brief 设置图片显示蒙版
  * @param percent 显示百分比
  * @return 无
  */
void OLED_SetDensity(ShowPercent percent);

/**
  * @brief 显示图片
  * @param X 显示图片的x轴起始位置
  * @param Y 显示图片的y轴起始位置
  * @param img_Length 显示图片的长度（x方向）
  * @param img_High 显示图片的高度（y方向）
  * @param image 显示的图片
  * @return 无
  */
void OLED_ShowImg(uint8_t X, uint8_t Y, uint8_t img_Length, uint8_t img_High, uint8_t* image);

#endif
