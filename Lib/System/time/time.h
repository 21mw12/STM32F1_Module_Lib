#ifndef __TIME_H
#define __TIME_H

///////////////////////////////////////////////////////////
//
// 文件功能：定时器基础功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/04/27
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* 定时器配置信息 */
#define Time_Periph				RCC_APB1Periph_TIM2		// 总线时钟
#define Time							TIM2									// 定时器选择
#define Time_EXTI_IRQn 		TIM2_IRQn							// 中断通道

/**
  * 定时器计算公式：
	*				TimeOut =((arr + 1) * (psc + 1)) / TimeClockFren
	*
	*				TimeOut：定时器溢出时间，即多长时间进入一次中断（单位为秒）
	*				arr：自动重装器的值
	*				psc：预分频器的值
	*				TimeClockFren：定时器的输入时钟频率，这里使用主频72MHz
  */

/**
  * @brief 定时器初始化
  * @param arrA1	自动重装器的值加一（即:上述公式中的arr+1）
  * @param pscA1	预分频器的值加一（即:上述公式中的psc+1）
  * @return 无
  */
void TIM_Init(uint16_t arrA1, uint16_t pscA1);

/**
  * @brief 定时器启动
  * @return 无
  */
void TIM_ON(void);

/**
  * @brief 定时器关闭
  * @return 无
  */
void TIM_OFF(void);

/* 中断处理函数模板，使用时将其复制到main.c文件中 */
//void TIM2_IRQHandler(void) {
//	if (TIM_GetITStatus(Time, TIM_IT_Update) != RESET) {
//		
//		/**
//			* 中断处理代码区间，在此填入需要处理的函数
//			*/
//		
//		TIM_ClearITPendingBit(Time, TIM_IT_Update);
//	}
//}

#endif
