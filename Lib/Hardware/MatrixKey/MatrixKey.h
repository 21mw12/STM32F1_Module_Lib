#ifndef __MATRIXKEY_H_
#define __MATRIXKEY_H_

///////////////////////////////////////////////////////////
//
// 文件功能：矩阵按键的基础功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/05/06
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "delay.h"

/* 矩阵按键引脚配置信息 */
#define MatrixKey_Periph			RCC_APB2Periph_GPIOB		// 总线时钟
#define MatrixKey_PORT				GPIOB										// IO端口组
#define MatrixKey_ROW1				GPIO_Pin_3							// 矩阵键盘每行的IO端口
#define MatrixKey_ROW2				GPIO_Pin_2
#define MatrixKey_ROW3				GPIO_Pin_1
#define MatrixKey_ROW4				GPIO_Pin_0
#define MatrixKey_COLUMN1			GPIO_Pin_4							// 矩阵键盘每列的IO端口
#define MatrixKey_COLUMN2			GPIO_Pin_5
#define MatrixKey_COLUMN3			GPIO_Pin_6
#define MatrixKey_COLUMN4			GPIO_Pin_7

/**
  * @brief 矩阵按键初始化
  * @return 无
  */
void MatrixKey_Init(void);

/**
  * @brief 获取矩阵按键建码值
  * @return 无
  */
uint8_t Get_MatrixKeyCode(void);

/**
  * @brief 将建码值转换为数字（仅适配4*4矩阵键盘中的数字按键部分）
  * @param KeyCode 建码值
  * @return 建码值对应的数字
  */
uint8_t KeyCode_Transition(uint8_t KeyCode);

#endif
