#include "TIM1PWM.h"

void TIM1_PWM_Init(uint16_t TIM1_ARR, uint16_t TIM1_PSC, uint16_t TIM1_CCR) {
	/* �жϿ���ͨ��*/
	uint16_t Enable_GPIO_Pin = 0;
	if (TIM1_PWMCHANNEL1_ENABLE) Enable_GPIO_Pin |= GPIO_Pin_8;
	if (TIM1_PWMCHANNEL2_ENABLE) Enable_GPIO_Pin |= GPIO_Pin_9;
	if (TIM1_PWMCHANNEL3_ENABLE) Enable_GPIO_Pin |= GPIO_Pin_10;
	if (TIM1_PWMCHANNEL4_ENABLE) Enable_GPIO_Pin |= GPIO_Pin_11;

	/* ����ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	/* GPIO��ʼ�� */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = Enable_GPIO_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* ѡ��ʱ����Ԫ */
	TIM_InternalClockConfig(TIM1);
	
	/* ����ʱ����Ԫ */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;				// ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		// ���ϼ���
	TIM_TimeBaseInitStructure.TIM_Period = TIM1_ARR - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = TIM1_PSC - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;		// �ظ�������(�߼���ʱ������)
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
	
	/* ��������Ƚϵ�Ԫ */                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;	// ����PWM1�Ƚ�ģʽ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//��������Ƚϼ���
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�������ʹ��
	TIM_OCInitStructure.TIM_Pulse = TIM1_CCR;
	
	if (TIM1_PWMCHANNEL1_ENABLE) TIM_OC1Init(TIM1, &TIM_OCInitStructure);		//���õ�ͨ��1
	if (TIM1_PWMCHANNEL2_ENABLE) TIM_OC2Init(TIM1, &TIM_OCInitStructure);		//���õ�ͨ��2
	if (TIM1_PWMCHANNEL3_ENABLE) TIM_OC3Init(TIM1, &TIM_OCInitStructure);		//���õ�ͨ��3
	if (TIM1_PWMCHANNEL4_ENABLE) TIM_OC4Init(TIM1, &TIM_OCInitStructure);		//���õ�ͨ��4
	
	/* ���п��� */
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
