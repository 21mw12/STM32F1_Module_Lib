#include "TIM1PWM.h"

void TIM1_PWM_Init(uint16_t TIM1_ARR, uint16_t TIM1_PSC, uint16_t TIM1_CCR) {
	/* 判断开启通道*/
	uint16_t Enable_GPIO_Pin = 0;
	if (TIM1_PWMCHANNEL1_ENABLE) Enable_GPIO_Pin |= GPIO_Pin_8;
	if (TIM1_PWMCHANNEL2_ENABLE) Enable_GPIO_Pin |= GPIO_Pin_9;
	if (TIM1_PWMCHANNEL3_ENABLE) Enable_GPIO_Pin |= GPIO_Pin_10;
	if (TIM1_PWMCHANNEL4_ENABLE) Enable_GPIO_Pin |= GPIO_Pin_11;

	/* 开启时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	/* GPIO初始化 */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = Enable_GPIO_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* 选择时基单元 */
	TIM_InternalClockConfig(TIM1);
	
	/* 配置时基单元 */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;				// 不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		// 向上计数
	TIM_TimeBaseInitStructure.TIM_Period = TIM1_ARR - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = TIM1_PSC - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;		// 重复计数器(高级定时器才有)
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
	
	/* 配置输出比较单元 */                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;	// 设置PWM1比较模式
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//设置输出比较极性
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //设置输出使能
	TIM_OCInitStructure.TIM_Pulse = TIM1_CCR;
	
	if (TIM1_PWMCHANNEL1_ENABLE) TIM_OC1Init(TIM1, &TIM_OCInitStructure);		//设置到通道1
	if (TIM1_PWMCHANNEL2_ENABLE) TIM_OC2Init(TIM1, &TIM_OCInitStructure);		//设置到通道2
	if (TIM1_PWMCHANNEL3_ENABLE) TIM_OC3Init(TIM1, &TIM_OCInitStructure);		//设置到通道3
	if (TIM1_PWMCHANNEL4_ENABLE) TIM_OC4Init(TIM1, &TIM_OCInitStructure);		//设置到通道4
	
	/* 运行控制 */
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	TIM_Cmd(TIM1, ENABLE);
}

void TIM1_PWM1_SetCompare(uint16_t Compare) {
	TIM_SetCompare1(TIM1, Compare);
}

void TIM1_PWM2_SetCompare(uint16_t Compare) {
	TIM_SetCompare2(TIM1, Compare);
}

void TIM1_PWM3_SetCompare(uint16_t Compare) {
	TIM_SetCompare3(TIM1, Compare);
}

void TIM1_PWM4_SetCompare(uint16_t Compare) {
	TIM_SetCompare4(TIM1, Compare);
}
