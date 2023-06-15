#include "pwm.h"

void PWM_Init(void) {
	/* 开启时钟 */
	RCC_APB1PeriphClockCmd(Tim_Periph, ENABLE);
	RCC_APB2PeriphClockCmd(PWM_Periph, ENABLE);
	/* GPIO初始化 */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = PWM_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PWM_PORT, &GPIO_InitStructure);
	/* 选择时基单元 */
	TIM_InternalClockConfig(Tim);
	/* 配置时基单元 */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;				// 不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		// 向上计数
	TIM_TimeBaseInitStructure.TIM_Period = ARR;
	TIM_TimeBaseInitStructure.TIM_Prescaler = PSC;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;		// 重复计数器(高级定时器才有)
	TIM_TimeBaseInit(Tim, &TIM_TimeBaseInitStructure);
	/* 配置输出比较单元 */
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	// 设置PWM1比较模式
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//设置输出比较极性
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //设置输出使能
	TIM_OCInitStructure.TIM_Pulse = CCR;
	TIM_OC2Init(Tim, &TIM_OCInitStructure);		//设置到通道2
	/* 运行控制 */
	TIM_Cmd(Tim, ENABLE);
}

void PWM_SetCompare(uint16_t Compare) {
	TIM_SetCompare2(Tim, Compare);
}
