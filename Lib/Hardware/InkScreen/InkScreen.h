#ifndef __INK_SCREEN_H_
#define __INK_SCREEN_H_

///////////////////////////////////////////////////////////
//
// 文件功能：中景园1.54寸三色墨水屏驱动函数
// 作者：中景园电子（这里只做个人的二次理解并转换为个人的代码风格！！！）
// 修改时间：2024/11/17
//
//	引脚连接(3.3V)：
//			SCL -- SPI_CLK
//			SDA -- SPI_MOSI
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* 端口信息 */
#define Ink_Screen_GPIOPeriph			RCC_APB2Periph_GPIOA
#define Ink_Screen_Port						GPIOA
#define Ink_Screen_Pin_RES				GPIO_Pin_2
#define Ink_Screen_Pin_DC					GPIO_Pin_3
#define Ink_Screen_Pin_CS					GPIO_Pin_4
#define Ink_Screen_Pin_BUSY				GPIO_Pin_5

/* 黑红两种图层 */
#define CanvasLayer					uint8_t
extern CanvasLayer InkScreen_BlackLayer[];	// 黑色图层 
extern CanvasLayer InkScreen_RedLayer[];		// 红色图层

/* 图层是否着色 */ 
#define CanvasColourType		uint16_t
extern CanvasColourType CANVAS_Colourless;	// 无色	
extern CanvasColourType CANVAS_Coloured;		// 着色

/* E-Paper显示方向(可选0/90/180/270) */
#define Rotation 		0

/**
  * @brief 墨水屏初始化
  * @return 无
  */
void InkScreen_Init(void);

/**
  * @brief 唤醒墨水屏
  * @return 无
  */
void InkScreen_Wakeup(void);

/**
  * @brief 墨水屏进入深度睡眠
  * @return 无
  */
void InkScreen_DeepSleep(void);

/**
  * @brief 墨水屏清屏
  * @return 无
  */
void InkScreen_Clear(void);

/**
  * @brief 墨水屏刷新显示
  * @param imageBW 黑白图层
  * @param imageR 红色图层
  * @return 无
  */
void InkScreen_Display(void);


/*****************************************画布绘制函数************************************************/

/**
  * @brief 墨水屏选择图层
  * @param layer 指定图层（可选InkScreen_BlackLayer或InkScreen_RedLayer）
  * @return 无
  */
void InkScreen_SelectLayer(CanvasLayer *layer);

/**
  * @brief 墨水屏清除图层
  * @return 无
  */
void InkScreen_LayerClear(void);

/**
  * @brief 画一个点
  * @param Xpoint x坐标
  * @param Ypoint y坐标
  * @param ColorType 是否着色
  * @return 无
  */
void InkScreen_DrawPoint(uint8_t X, uint8_t Y, CanvasColourType ColorType);

/**
  * @brief 画一条线
  * @param X_start 线端开始的x坐标
  * @param Y_start 线端开始的y坐标
  * @param X_end 线端结束的x坐标
  * @param Y_end 线端结束的y坐标
  * @param step 绘制线端的步长
  * @param ColorType 是否着色
  * @return 无
	*
	* 注; 只能绘制从屏幕左边到屏幕右边的线段，不能反着画！！！
  */
void InkScreen_DrawLine(uint8_t X_start, uint8_t Y_start, uint8_t X_end, uint8_t Y_end, uint8_t step, CanvasColourType ColorType);

/**
  * @brief 画矩形
  * @param X_start 矩形开始的x坐标
  * @param Y_start 矩形开始的y坐标
  * @param X_length 矩形x轴方向上的长度
  * @param Y_length 矩形y轴方向上的长度
  * @param wide 宽度
  * @param ColorType 是否着色
  * @return 无
  */
void InkScreen_DrawRectangle(uint8_t X_start, uint8_t Y_start, uint8_t X_length, uint8_t Y_length, uint8_t wide, CanvasColourType ColorType);

/**
  * @brief 画圆
  * @param X_center 圆心的x坐标
  * @param Y_center 圆心的y坐标
  * @param radius 半径
  * @param wide 宽度
  * @param ColorType 是否着色
  * @return 无
  */
void InkScreen_DrawCircle(uint8_t X_center, uint8_t Y_center, uint8_t radius, uint8_t wide, CanvasColourType ColorType);

/**
  * @brief 画图片
  * @param X 图片的x起点坐标
  * @param Y 图片的y起点坐标
  * @param wide 图片宽度
  * @param high 图片高度
  * @param picture 图片数据数组
  * @param ColorType 是否着色
  * @return 无
  */
void InkScreen_DrawPicture(uint16_t X, uint16_t Y, uint16_t wide, uint16_t high, const uint8_t picture[], CanvasColourType ColorType);

/**
  * @brief 画字符
  * @param X 字符的x起点坐标
  * @param Y 字符的y起点坐标
  * @param Char 要绘制的字符
  * @param Front_size 字符大小
  * @param ColorType 是否着色
  * @return 无
  */
void InkScreen_DrawChar(uint8_t X, uint8_t Y, char Char, uint8_t Front_size, CanvasColourType ColorType);

/**
  * @brief 画字符串
  * @param X 字符串的x起点坐标
  * @param Y 字符串的y起点坐标
  * @param String 要绘制的字符串
  * @param Front_size 字符串大小
  * @param ColorType 是否着色
  * @return 无
  */
void InkScreen_DrawString(uint8_t X, uint8_t Y, char* String, uint8_t Front_size, CanvasColourType ColorType);

/**
  * @brief 画数字
  * @param X 数字的x起点坐标
  * @param Y 数字的y起点坐标
  * @param Num 要绘制的数字
  * @param Len 数字长度
  * @param Front_size 数字大小
  * @param ColorType 是否着色
  * @return 无
  */
void InkScreen_DrawNum(uint8_t X, uint8_t Y,uint32_t Num, uint16_t Len, uint8_t Front_size, CanvasColourType ColorType);

/**
  * @brief 画汉字
  * @param X 汉字的x起点坐标
  * @param Y 数字串的y起点坐标
  * @param Chinese 要绘制的汉字
  * @param Front_size 汉字大小
  * @param ColorType 是否着色
  * @return 无
  */
void InkScreen_DrawChinese(uint8_t X, uint8_t Y, uint8_t* Chinese, uint8_t Front_size, CanvasColourType ColorType);


#endif
