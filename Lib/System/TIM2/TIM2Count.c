#include "TIM2COUNT.h"

void TIM2_Init(uint16_t TIM2_ARR, uint16_t TIM2_PSC) {
	/* 开启时钟 */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//TIM_InternalClockConfig(TIM2);
	
	/*配置时基单元*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;				// 采样频率：主频的1分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		// 计数器模式，向上计数法
	TIM_TimeBaseInitStructure.TIM_Period = TIM2_ARR - 1;							// 周期，ARR自动重装器的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = TIM2_PSC - 1;						// PSC预分频器的值
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	/*配置输出中断控制*/
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);				// 手动清除标志位，要不然一上电就会触发中断
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	/*配置VNIC*/
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	/*运行控制*/
	TIM_Cmd(TIM2, ENABLE); 
}

void TIM2_ON(void) {
	TIM_Cmd(TIM2, ENABLE);
}

void TIM2_OFF(void) {
	TIM_Cmd(TIM2, DISABLE);
}

uint16_t TIM2_GetCount(void) {
	return TIM_GetCounter(TIM2);
}

void TIM2_ClearCount(void) {
	TIM_SetCounter(TIM2, 0);
}
