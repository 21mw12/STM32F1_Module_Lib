#include "TIM2COUNT.h"

void TIM2_Init(uint16_t TIM2_ARR, uint16_t TIM2_PSC) {
	/* ����ʱ�� */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_InternalClockConfig(TIM2);
	
	/*����ʱ����Ԫ*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;				// ����Ƶ�ʣ���Ƶ��1��Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		// ������ģʽ�����ϼ�����
	TIM_TimeBaseInitStructure.TIM_Period = TIM2_ARR - 1;							// ���ڣ�ARR�Զ���װ����ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = TIM2_PSC - 1;						// PSCԤ��Ƶ����ֵ
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;							// �ظ���������ֵ���߼���ʱ������
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	/*��������жϿ���*/
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);				// �ֶ������־λ��Ҫ��Ȼһ�ϵ�ͻᴥ���ж�
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	/*����VNIC*/
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	/*���п���*/
	TIM_Cmd(TIM2, ENABLE); 
}

void TIM2_ON(void) {
	TIM_Cmd(TIM2, ENABLE);
}

void TIM2_OFF(void) {
	TIM_Cmd(TIM2, DISABLE);
}
