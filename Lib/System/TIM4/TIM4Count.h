#ifndef __TIM4_COUNT_H
#define __TIM4_COUNT_H

////////////////////////////////////////////////////////////////////
//
// 文件功能：定时器4的计数功能
// 版本：V1.1
// 作者：墨蔚（MW）
// 修改时间：2023/07/12
//
// 定时器计算公式：
//       TimeOut =((ARR + 1) * (PSC + 1)) / TimeClockFren
//
//       TimeOut：定时器溢出时间，即多长时间进入一次中断（单位为秒）
// 			 ARR：自动重装器的值
// 			 PSC：预分频器的值
// 			 TimeClockFren：定时器的输入时钟频率，这里使用主频72MHz
// 
// 一些特征值：
//		定时1s  ARR+1为10000   PSC+1为7200
//
////////////////////////////////////////////////////////////////////

#include "stm32f10x.h"

/**
  * @brief 定时器初始化
  * @param TIM4_arr	自动重装器的值加一（即:上述公式中的arr+1）
  * @param TIM4_psc	预分频器的值加一（即:上述公式中的psc+1）
  * @return 无
  */
void TIM4_Init(uint16_t TIM4_ARR, uint16_t TIM4_PSC);

/**
  * @brief 定时器启动
  * @return 无
  */
void TIM4_ON(void);

/**
  * @brief 定时器关闭
  * @return 无
  */
void TIM4_OFF(void);

/**
  * @brief 获取定时器计数值
  * @return 定时器计数值
  */
uint16_t TIM4_GetCount(void);

/**
  * @brief 清理定时器计数值
  * @return 无
  */
void TIM4_ClearCount(void);

/* 中断处理函数模板，使用时将其复制到main.c文件中 */
//void TIM4_IRQHandler(void) {
//	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) {
//		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
//		
//		/**
//			* 中断处理代码区间，在此填入需要处理的函数
//			*/
//	}
//}

#endif

///////////////////////////////////////////////////////////
//
// 更新日志：
// V1.0: 2023/07/09
//				进行了定时器功能的重构并将定时器的功能细分
// V1.1: 2023/07/12
//				封装了清除和获取定时器计数的函数
//
///////////////////////////////////////////////////////////
