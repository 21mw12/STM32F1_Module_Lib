#ifndef __MATRIXKEY_H_
#define __MATRIXKEY_H_

///////////////////////////////////////////////////////////
//
// 文件功能：矩阵按键的基础功能
// 版本：V2.1
// 作者：墨蔚（MW）
// 修改时间：2024/01/31
//
// 默认矩阵位置说明：
//				  C1	C2	C3	C4
//		R1		1		2		3		A
//		R2		4		5		6		B
//		R3		7		8		9		C
//		R4		*		0		#		D
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* 矩阵按键引脚配置信息 */
/* 矩阵键盘行的IO端口 */
#define MatrixKey_RPeriph			RCC_APB2Periph_GPIOB
#define MatrixKey_RPort				GPIOB
#define MatrixKey_Row1				GPIO_Pin_12
#define MatrixKey_Row2				GPIO_Pin_13
#define MatrixKey_Row3				GPIO_Pin_14
#define MatrixKey_Row4				GPIO_Pin_15
/* 矩阵键盘列的IO端口 */
#define MatrixKey_CPeriph			RCC_APB2Periph_GPIOA
#define MatrixKey_CPort				GPIOA
#define MatrixKey_Column1			GPIO_Pin_8
#define MatrixKey_Column2			GPIO_Pin_9
#define MatrixKey_Column3			GPIO_Pin_10
#define MatrixKey_Column4			GPIO_Pin_11

/* 键码值转换 */
typedef enum {
	Button_Num0 = 0,
	Button_Num1,
	Button_Num2,
	Button_Num3,
	Button_Num4,
	Button_Num5,
	Button_Num6,
	Button_Num7,
	Button_Num8,
	Button_Num9,
	Button_Asterisk,		// *
	Button_WellNumber,	// #
	Button_A,
	Button_B,
	Button_C,
	Button_D,
	Button_NULL,
} Button;

/**
  * @brief 矩阵按键初始化
  * @return 无
  */
void MatrixKey_Init(void);

/**
  * @brief 获取矩阵按键建码值
  * @return 无
  */
uint8_t MatrixKey_GetCode(void);

/**
  * @brief 将建码值转换为数字（仅适配4*4矩阵键盘中的数字按键部分）
  * @param KeyCode 建码值
  * @return 建码值对应的数字
  */
Button MatrixKey_TransitionKeyCode(uint8_t KeyCode);

#endif

///////////////////////////////////////////////////////////
//
// 更新日志：
// V1.0: 2023/05/06
//				实现了矩阵按键的基础显示
// V2.0: 2024/01/30
//				实现了更加通用化的设计
// V2.1: 2024/01/31
//				修复了不按按键无法转换键码值
//
///////////////////////////////////////////////////////////
