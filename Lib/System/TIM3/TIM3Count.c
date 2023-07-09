#include "TIM3COUNT.h"

void TIM3_Init(uint16_t TIM3_ARR, uint16_t TIM3_PSC) {
	/* ����ʱ�� */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_InternalClockConfig(TIM3);
	
	/*����ʱ����Ԫ*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;				// ����Ƶ�ʣ���Ƶ��1��Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		// ������ģʽ�����ϼ�����
	TIM_TimeBaseInitStructure.TIM_Period = TIM3_ARR - 1;							// ���ڣ�ARR�Զ���װ����ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = TIM3_PSC - 1;						// PSCԤ��Ƶ����ֵ
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;							// �ظ���������ֵ���߼���ʱ������
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	/*��������жϿ���*/
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);				// �ֶ������־λ��Ҫ��Ȼһ�ϵ�ͻᴥ���ж�
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	/*����VNIC*/
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	/*���п���*/
	TIM_Cmd(TIM3, ENABLE); 
}

void TIM3_ON(void) {
	TIM_Cmd(TIM3, ENABLE);
}

void TIM3_OFF(void) {
	TIM_Cmd(TIM3, DISABLE);
}
