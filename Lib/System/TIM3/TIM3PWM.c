#include "TIM3PWM.h"

void TIM3_PWM_Init(uint16_t TIM3_ARR, uint16_t TIM3_PSC, uint16_t TIM3_CCR) {
	uint16_t Enable_GPIO_Pin = 0;

	/* 开启时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	
	/* GPIO初始化 */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	/* 判断开启通道 */
	if (TIM3_PWMCHANNEL1_ENABLE || TIM3_PWMCHANNEL2_ENABLE) {
		if (TIM3_PWMCHANNEL1_ENABLE) Enable_GPIO_Pin |= GPIO_Pin_6;
		if (TIM3_PWMCHANNEL2_ENABLE) Enable_GPIO_Pin |= GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Pin = Enable_GPIO_Pin;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	}
	Enable_GPIO_Pin = 0;
	if (TIM3_PWMCHANNEL3_ENABLE || TIM3_PWMCHANNEL4_ENABLE) {
		if (TIM3_PWMCHANNEL3_ENABLE) Enable_GPIO_Pin |= GPIO_Pin_0;
		if (TIM3_PWMCHANNEL4_ENABLE) Enable_GPIO_Pin |= GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Pin = Enable_GPIO_Pin;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	}
	
	/* 选择时基单元 */
	TIM_InternalClockConfig(TIM3);
	
	/* 配置时基单元 */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;				// 不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		// 向上计数
	TIM_TimeBaseInitStructure.TIM_Period = TIM3_ARR - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = TIM3_PSC - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;		// 重复计数器(高级定时器才有)
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	/* 配置输出比较单元 */
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	// 设置PWM1比较模式
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//设置输出比较极性
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //设置输出使能
	TIM_OCInitStructure.TIM_Pulse = TIM3_CCR;
	if (TIM3_PWMCHANNEL1_ENABLE) TIM_OC1Init(TIM3, &TIM_OCInitStructure);		//设置到通道1
	if (TIM3_PWMCHANNEL2_ENABLE) TIM_OC2Init(TIM3, &TIM_OCInitStructure);		//设置到通道2
	if (TIM3_PWMCHANNEL3_ENABLE) TIM_OC3Init(TIM3, &TIM_OCInitStructure);		//设置到通道3
	if (TIM3_PWMCHANNEL4_ENABLE) TIM_OC4Init(TIM3, &TIM_OCInitStructure);		//设置到通道4
	
	/* 运行控制 */
	TIM_Cmd(TIM3, ENABLE);
}

void TIM3_PWM1_SetCompare(uint16_t Compare) {
	TIM_SetCompare1(TIM3, Compare);
}

void TIM3_PWM2_SetCompare(uint16_t Compare) {
	TIM_SetCompare2(TIM3, Compare);
}

void TIM3_PWM3_SetCompare(uint16_t Compare) {
	TIM_SetCompare3(TIM3, Compare);
}

void TIM3_PWM4_SetCompare(uint16_t Compare) {
	TIM_SetCompare4(TIM3, Compare);
}
