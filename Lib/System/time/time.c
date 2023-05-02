#include "time.h"

void TIM_Init(uint16_t arr, uint16_t psc) {
  RCC_APB1PeriphClockCmd(Time_Periph, ENABLE);
	TIM_InternalClockConfig(Time);
	
	/*配置时基单元*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//采样频率：主频的1分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//计数器模式，向上计数法
	TIM_TimeBaseInitStructure.TIM_Period = arr - 1;//周期，ARR自动重装器的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc - 1;//PSC预分频器的值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//重复计数器的值，高级定时器才有
	TIM_TimeBaseInit(Time, &TIM_TimeBaseInitStructure);
	
	/*配置输出中断控制*/
	TIM_ClearFlag(Time, TIM_FLAG_Update);//手动清除标志位，要不然一上电就会触发中断
	TIM_ITConfig(Time, TIM_IT_Update, ENABLE);
	
	/*配置VNIC*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = Time_EXTI_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	/*运行控制*/
	TIM_Cmd(Time, ENABLE); 
}

void TIM_ON(void) {
	TIM_Cmd(Time, ENABLE);
}

void TIM_OFF(void) {
	TIM_Cmd(Time, DISABLE);
}
 

//void TIM2_IRQHandler(void) {
//	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
//		
//		
//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//	}
//}
