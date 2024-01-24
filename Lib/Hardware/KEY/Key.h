#ifndef __KEY_H
#define __KEY_H	

///////////////////////////////////////////////////////////
//
// 文件功能：按键的基础功能
// 版本：V1.1
// 作者：墨蔚（MW）
// 修改时间：2023/4/27
//
// 硬件连接说明：按键一边连接IO口，另一边连接GND！！！
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "delay.h"

/* 按键引脚配置信息 */
#define Key_Periph		RCC_APB2Periph_GPIOB		// 总线时钟
#define Key_Port			GPIOB										// IO端口组
#define Key_Pin 			GPIO_Pin_1							// IO端口

/**
  * 是否启用按键中断
  * 1：表示开启，需要编写对应的中断处理函数（函数定义的下面）
  * 0：表示关闭，调用读取函数获取按键状态
  */
#define Key_Interrupt      1

/* 按键中断配置 */
#define Key_PortSource		GPIO_PortSourceGPIOB		// 中断源IO端口组
#define Key_PinSource 		GPIO_PinSource1					// 中断源IO端口
#define Key_EXTI_Line			EXTI_Line1					// 中断线
#define Key_EXTI_IRQn 		EXTI1_IRQn					// 中断通道

/**
  * @brief 按键初始化
  * @return 无
  */
void Key_Init(void);

#if Key_Interrupt == 0
/**
  * @brief 按键初始化
  * @return 按键是否被按下	0：没有按下	1：有按下
  */
uint8_t Key_Get(void);
#endif

/* 中断处理函数模板，使用时将其复制到main.c文件中 */
//void EXTI1_IRQHandler(void){
//	if (EXTI_GetITStatus(Key_EXTI_Line) == SET){
//		// 按键消抖
//		Delay_ms(20);
//		while (GPIO_ReadInputDataBit(Key_Port, Key_Pin) == 0);
//		Delay_ms(20);
//		
//		/**
//			* 中断处理代码区间，在此填入需要处理的函数
//			*/
//		
//		EXTI_ClearITPendingBit(Key_EXTI_Line);
//	}
//}
#endif

///////////////////////////////////////////////////////////
//
// 更新日志：
// V1.0: 2023/4/25
//				实现了按键的初始化和读取功能
// V1.1: 2023/04/27
//				实现了按键中断的功能
//
///////////////////////////////////////////////////////////
