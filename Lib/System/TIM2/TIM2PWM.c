#include "TIM2PWM.h"

void TIM2_PWM_Init(uint16_t TIM2_ARR, uint16_t TIM2_PSC, uint16_t TIM2_CCR) {
	/* �жϿ���ͨ��*/
	uint16_t Enable_GPIO_Pin = 0;
	if (TIM2_PWMCHANNEL1_ENABLE) Enable_GPIO_Pin |= GPIO_Pin_0;
	if (TIM2_PWMCHANNEL2_ENABLE) Enable_GPIO_Pin |= GPIO_Pin_1;
	if (TIM2_PWMCHANNEL3_ENABLE) Enable_GPIO_Pin |= GPIO_Pin_2;
	if (TIM2_PWMCHANNEL4_ENABLE) Enable_GPIO_Pin |= GPIO_Pin_3;

	/* ����ʱ�� */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	/* GPIO��ʼ�� */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = Enable_GPIO_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* ѡ��ʱ����Ԫ */
	TIM_InternalClockConfig(TIM2);
	
	/* ����ʱ����Ԫ */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;				// ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		// ���ϼ���
	TIM_TimeBaseInitStructure.TIM_Period = TIM2_ARR - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = TIM2_PSC - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;		// �ظ�������(�߼���ʱ������)
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	/* ��������Ƚϵ�Ԫ */
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	// ����PWM1�Ƚ�ģʽ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//��������Ƚϼ���
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�������ʹ��
	TIM_OCInitStructure.TIM_Pulse = TIM2_CCR;
	if (TIM2_PWMCHANNEL1_ENABLE) TIM_OC1Init(TIM2, &TIM_OCInitStructure);		//���õ�ͨ��1
	if (TIM2_PWMCHANNEL2_ENABLE) TIM_OC2Init(TIM2, &TIM_OCInitStructure);		//���õ�ͨ��2
	if (TIM2_PWMCHANNEL3_ENABLE) TIM_OC3Init(TIM2, &TIM_OCInitStructure);		//���õ�ͨ��3
	if (TIM2_PWMCHANNEL4_ENABLE) TIM_OC4Init(TIM2, &TIM_OCInitStructure);		//���õ�ͨ��4
	
	/* ���п��� */
	TIM_Cmd(TIM2, ENABLE);
}

void TIM2_PWM1_SetCompare(uint16_t Compare) {
	TIM_SetCompare1(TIM2, Compare);
}

void TIM2_PWM2_SetCompare(uint16_t Compare) {
	TIM_SetCompare2(TIM2, Compare);
}

void TIM2_PWM3_SetCompare(uint16_t Compare) {
	TIM_SetCompare3(TIM2, Compare);
}

void TIM2_PWM4_SetCompare(uint16_t Compare) {
	TIM_SetCompare4(TIM2, Compare);
}
