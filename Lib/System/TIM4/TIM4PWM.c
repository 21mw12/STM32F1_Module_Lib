#include "TIM4PWM.h"

void TIM4_PWM_Init(uint16_t TIM4_ARR, uint16_t TIM4_PSC, uint16_t TIM4_CCR) {
	/* �жϿ���ͨ��*/
	uint16_t Enable_GPIO_Pin = 0;
	if (TIM4_PWMCHANNEL1_ENABLE) Enable_GPIO_Pin |= GPIO_Pin_6;
	if (TIM4_PWMCHANNEL2_ENABLE) Enable_GPIO_Pin |= GPIO_Pin_7;
	if (TIM4_PWMCHANNEL3_ENABLE) Enable_GPIO_Pin |= GPIO_Pin_8;
	if (TIM4_PWMCHANNEL4_ENABLE) Enable_GPIO_Pin |= GPIO_Pin_9;

	/* ����ʱ�� */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	/* GPIO��ʼ�� */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = Enable_GPIO_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* ѡ��ʱ����Ԫ */
	TIM_InternalClockConfig(TIM4);
	
	/* ����ʱ����Ԫ */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;				// ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		// ���ϼ���
	TIM_TimeBaseInitStructure.TIM_Period = TIM4_ARR - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = TIM4_PSC - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;		// �ظ�������(�߼���ʱ������)
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
	
	/* ��������Ƚϵ�Ԫ */
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	// ����PWM1�Ƚ�ģʽ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//��������Ƚϼ���
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�������ʹ��
	TIM_OCInitStructure.TIM_Pulse = TIM4_CCR;
	if (TIM4_PWMCHANNEL1_ENABLE) TIM_OC1Init(TIM4, &TIM_OCInitStructure);		//���õ�ͨ��1
	if (TIM4_PWMCHANNEL2_ENABLE) TIM_OC2Init(TIM4, &TIM_OCInitStructure);		//���õ�ͨ��2
	if (TIM4_PWMCHANNEL3_ENABLE) TIM_OC3Init(TIM4, &TIM_OCInitStructure);		//���õ�ͨ��3
	if (TIM4_PWMCHANNEL4_ENABLE) TIM_OC4Init(TIM4, &TIM_OCInitStructure);		//���õ�ͨ��4
	
	/* ���п��� */
	TIM_Cmd(TIM4, ENABLE);
}

void TIM4_PWM1_SetCompare(uint16_t Compare) {
	TIM_SetCompare1(TIM4, Compare);
}

void TIM4_PWM2_SetCompare(uint16_t Compare) {
	TIM_SetCompare2(TIM4, Compare);
}

void TIM4_PWM3_SetCompare(uint16_t Compare) {
	TIM_SetCompare3(TIM4, Compare);
}

void TIM4_PWM4_SetCompare(uint16_t Compare) {
	TIM_SetCompare4(TIM4, Compare);
}
