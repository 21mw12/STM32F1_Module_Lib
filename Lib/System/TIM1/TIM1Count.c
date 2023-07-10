#include "TIM1COUNT.h"

void TIM1_Init(uint16_t TIM1_ARR, uint16_t TIM1_PSC) {
	/* ����ʱ�� */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	/*����ʱ����Ԫ*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;				// ����Ƶ�ʣ���Ƶ��1��Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		// ������ģʽ�����ϼ�����
	TIM_TimeBaseInitStructure.TIM_Period = TIM1_ARR - 1;							// ���ڣ�ARR�Զ���װ����ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = TIM1_PSC - 1;						// PSCԤ��Ƶ����ֵ
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;							// �ظ���������ֵ���߼���ʱ������
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
	
	/*��������жϿ���*/
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);				// �ֶ������־λ��Ҫ��Ȼһ�ϵ�ͻᴥ���ж�
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	
	/*����VNIC*/
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM1_UP_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	/*���п���*/
	TIM_Cmd(TIM1, ENABLE); 
}

void TIM1_ON(void) {
	TIM_Cmd(TIM1, ENABLE);
}

void TIM1_OFF(void) {
	TIM_Cmd(TIM1, DISABLE);
}
