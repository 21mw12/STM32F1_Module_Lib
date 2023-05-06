#include "Encoder.h"

int8_t Encoder_Count;

void Encoder_Init(void) {
	RCC_APB2PeriphClockCmd(Encoder_Periph, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = Encoder_A_PIN | Encoder_B_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Encoder_PORT, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(Encoder_PortSource, Encoder_A_PinSource);
	GPIO_EXTILineConfig(Encoder_PortSource, Encoder_B_PinSource);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = Encoder_A_EXTI_Line | Encoder_B_EXTI_Line;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = Encoder_A_EXTI_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = Encoder_B_EXTI_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);
}

int8_t Encoder_Get(void) {
	int8_t Number;
	Number = Encoder_Count;
	Encoder_Count = 0;
	return Number;
}

void EXTI0_IRQHandler(void) {
	if (EXTI_GetITStatus(Encoder_A_EXTI_Line) == SET) {
		if (GPIO_ReadInputDataBit(Encoder_PORT, Encoder_B_PIN) == 0) {
			Encoder_Count--;
		}
		EXTI_ClearITPendingBit(Encoder_A_EXTI_Line);
	}
}

void EXTI1_IRQHandler(void) {
	if (EXTI_GetITStatus(Encoder_B_EXTI_Line) == SET) {
		if (GPIO_ReadInputDataBit(Encoder_PORT, Encoder_A_PIN) == 0) {
			Encoder_Count++;
		}
		EXTI_ClearITPendingBit(Encoder_B_EXTI_Line);
	}
}     
