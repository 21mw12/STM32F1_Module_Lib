#include "time.h"

void TIM_Init(uint16_t arr, uint16_t psc) {
  RCC_APB1PeriphClockCmd(Time_Periph, ENABLE);
	TIM_InternalClockConfig(Time);
	
	/*����ʱ����Ԫ*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//����Ƶ�ʣ���Ƶ��1��Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//������ģʽ�����ϼ�����
	TIM_TimeBaseInitStructure.TIM_Period = arr - 1;//���ڣ�ARR�Զ���װ����ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc - 1;//PSCԤ��Ƶ����ֵ
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//�ظ���������ֵ���߼���ʱ������
	TIM_TimeBaseInit(Time, &TIM_TimeBaseInitStructure);
	
	/*��������жϿ���*/
	TIM_ClearFlag(Time, TIM_FLAG_Update);//�ֶ������־λ��Ҫ��Ȼһ�ϵ�ͻᴥ���ж�
	TIM_ITConfig(Time, TIM_IT_Update, ENABLE);
	
	/*����VNIC*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = Time_EXTI_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	/*���п���*/
	TIM_Cmd(Time, ENABLE); 
}

void TIM_ON(void) {
	TIM_Cmd(Time, ENABLE);
}

void TIM_OFF(void) {
	TIM_Cmd(Time, DISABLE);
}
 

//void TIM2_IRQHandler(void) {
//	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
//		
//		
//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//	}
//}
