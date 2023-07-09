#include "TIM4COUNT.h"

void TIM4_Init(uint16_t TIM4_ARR, uint16_t TIM4_PSC) {
	/* 开启时钟 */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_InternalClockConfig(TIM4);
	
	/*配置时基单元*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;				// 采样频率：主频的1分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		// 计数器模式，向上计数法
	TIM_TimeBaseInitStructure.TIM_Period = TIM4_ARR - 1;							// 周期，ARR自动重装器的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = TIM4_PSC - 1;						// PSC预分频器的值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;							// 重复计数器的值，高级定时器才有
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
	
	/*配置输出中断控制*/
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);				// 手动清除标志位，要不然一上电就会触发中断
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	/*配置VNIC*/
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	/*运行控制*/
	TIM_Cmd(TIM4, ENABLE); 
}

void TIM4_ON(void) {
	TIM_Cmd(TIM4, ENABLE);
}

void TIM4_OFF(void) {
	TIM_Cmd(TIM4, DISABLE);
}
