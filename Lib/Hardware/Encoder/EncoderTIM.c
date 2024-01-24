#include "EncoderTIM.h"

void Encoder_Init(void) {
	/* Ê±ÖÓÅäÖÃ */
	RCC_APB1PeriphClockCmd(Encoder_TIM_Periph, ENABLE);
	RCC_APB2PeriphClockCmd(Encoder_Periph, ENABLE);
	
	/* IO¿ÚÅäÖÃ */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = Encoder_A_Pin | Encoder_B_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Encoder_Port, &GPIO_InitStructure);
	
	/* NVICÅäÖÃ */
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = Encoder_NVIC_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority =1;
	NVIC_Init(&NVIC_InitStruct);
	
	/* ¶¨Ê±Æ÷ÅäÖÃ */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65535;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(Encoder_TIM, &TIM_TimeBaseInitStructure);
	
	/* ¶¨Ê±Æ÷ÊäÈë²¶»ñÅäÖÃ */
	TIM_ICInitTypeDef TIM_ICInitStructure;
  TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = Encoder_A_TIM_Channel | Encoder_B_TIM_Channel;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(Encoder_TIM, &TIM_ICInitStructure);
    
  TIM_EncoderInterfaceConfig(Encoder_TIM, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  
	TIM_SetCounter(Encoder_TIM, 0);
  TIM_ClearFlag(Encoder_TIM, TIM_FLAG_Update);	
  TIM_ITConfig(Encoder_TIM,TIM_IT_Update, ENABLE);
  TIM_Cmd(Encoder_TIM, ENABLE);
}

int16_t Encoder_GetClear(void) {
    int16_t count;
    count = TIM_GetCounter(Encoder_TIM);
	  TIM_SetCounter(Encoder_TIM, 0);
    return count;
}

uint32_t Encoder_Get(void) {
	uint32_t count = 0;
	count = Encoder_TIM->CNT;
	return count;
}

int16_t overtime = 0;
void TIM3_IRQHandler(void) {
	if(TIM_GetITStatus(Encoder_TIM, TIM_IT_Update) == SET) {
		if(Encoder_TIM->CR1 && TIM_CounterMode_Down != TIM_CounterMode_Down) {
			overtime++;
		}	else {
			overtime--;
		}
		TIM_ClearITPendingBit(Encoder_TIM, TIM_IT_Update);
	}
}    
