#include "pwm.h"

void PWM_Init(void) {
	/* ����ʱ�� */
	RCC_APB1PeriphClockCmd(Tim_Periph, ENABLE);
	RCC_APB2PeriphClockCmd(PWM_Periph, ENABLE);
	/* GPIO��ʼ�� */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = PWM_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PWM_PORT, &GPIO_InitStructure);
	/* ѡ��ʱ����Ԫ */
	TIM_InternalClockConfig(Tim);
	/* ����ʱ����Ԫ */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;				// ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		// ���ϼ���
	TIM_TimeBaseInitStructure.TIM_Period = ARR;
	TIM_TimeBaseInitStructure.TIM_Prescaler = PSC;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;		// �ظ�������(�߼���ʱ������)
	TIM_TimeBaseInit(Tim, &TIM_TimeBaseInitStructure);
	/* ��������Ƚϵ�Ԫ */
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	// ����PWM1�Ƚ�ģʽ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//��������Ƚϼ���
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�������ʹ��
	TIM_OCInitStructure.TIM_Pulse = CCR;
	TIM_OC2Init(Tim, &TIM_OCInitStructure);		//���õ�ͨ��2
	/* ���п��� */
	TIM_Cmd(Tim, ENABLE);
}

void PWM_SetCompare(uint16_t Compare) {
	TIM_SetCompare2(Tim, Compare);
}
