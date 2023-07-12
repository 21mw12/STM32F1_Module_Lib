#include "HCRS04.h"

uint16_t TIM_Trigger_Count = 0;

void HC_SR04_Init(void) {
	/* ����ʱ�� */
	RCC_APB2PeriphClockCmd(HCSR04_Trig_Periph | HCSR04_Echo_Periph, ENABLE);

	/* ����Trig���� */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = HCSR04_TRIG_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(HCSR04_Trig_PORT, &GPIO_InitStructure);
	GPIO_ResetBits(HCSR04_Trig_PORT, HCSR04_TRIG_Pin);

	/* ����Echo���� */
	GPIO_InitStructure.GPIO_Pin = HCSR04_Echo_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(HCSR04_Echo_PORT, &GPIO_InitStructure);

	/* ���ö�ʱ�� */
	// ����Ϊÿ1ms����һ��
	TIM2_Init(1000, 72);
	TIM2_OFF();
}

/**
  * @brief ����10us�����崥���ź�
  * @return ��
  */
void HC_SR04_Start(void) {   
	GPIO_ResetBits(HCSR04_Trig_PORT, HCSR04_TRIG_Pin);                           
	Delay_us(10);
	// ��һ��10us�ĸߵ�ƽ��������������
	GPIO_SetBits(HCSR04_Trig_PORT, HCSR04_TRIG_Pin);
	Delay_us(10);
	GPIO_ResetBits(HCSR04_Trig_PORT, HCSR04_TRIG_Pin);
}

/**
  * @brief ��ȡ��ʱ��������ֵ
  * @return ������ֵ
  */
uint32_t GetEchoTimer(void) {
	uint32_t TIM_Count = 0;
	
	// �ö�ʱ���Ĵ�����������1000�������������
	TIM_Count = TIM_Trigger_Count * 1000;
	// �ټ��϶�ʱ��ʣ��ļ��������ܹ���ʱ��
	TIM_Count += TIM2_GetCount();
	
	TIM2_ClearCount();
	Delay_ms(50);
	
	return TIM_Count;
}

float HC_SR04_GetLength(void) {
	float Length = 0;
	float Length_Sum = 0;
	uint32_t Time = 0;
	int i = 0;

	/* ��5��ȡƽ��ֵ */
	while(i != Average_CalCount)    {
		/* ������ʼ�ź� */
		HC_SR04_Start();
		
		/* �ȴ�Echo��Ϊ�ߵ�ƽ���������ֵ������ʱ�� */
		while(GPIO_ReadInputDataBit(HCSR04_Echo_PORT, HCSR04_Echo_Pin) == 0);      
		TIM2_ClearCount();
		TIM_Trigger_Count = 0;
		TIM2_ON();
		
		i++;
		
		/* �ȴ�Echo��Ϊ�͵�ƽ����ȡ����ֵ���ر�ʱ�� */
		while( GPIO_ReadInputDataBit(HCSR04_Echo_PORT, HCSR04_Echo_Pin) == 1);
		TIM2_OFF();
		Time = GetEchoTimer();
		
		/* ���㱾�εĳ��� */
		Length = ((float)Time / 58.0);
		Length_Sum += Length;    
	}
	
	// ȡƽ��ֵ
	Length = Length_Sum / Average_CalCount;

	return Length;
}

/* ��ʱ���жϺ��� */
void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);		
		TIM_Trigger_Count++;		
	}
}
