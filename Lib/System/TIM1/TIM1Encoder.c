#include "TIM1Encoder.h"

void TIM1_Encoder_Init(void) {
	/* Ê±ÖÓÅäÖÃ */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	/* IO¿ÚÅäÖÃ */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* NVICÅäÖÃ */
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM1_UP_IRQn;
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
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
	
	/* ¶¨Ê±Æ÷ÊäÈë²¶»ñÅäÖÃ */
	TIM_ICInitTypeDef TIM_ICInitStructure;
  TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 | TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM1, &TIM_ICInitStructure);
  
  TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  
	TIM_SetCounter(TIM1, 0);
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);	
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM1, ENABLE);
}

int16_t TIM1_Encoder_GetClear(void) {
	int16_t count;
	count = TIM_GetCounter(TIM1);
	TIM_SetCounter(TIM1, 0);
	return count;
}

uint32_t TIM1_Encoder_Get(void) {
	uint32_t count = 0;
	count = TIM1->CNT;
	return count;
}

int16_t TIM1_overtime = 0;
void TIM1_UP_IRQn_IRQHandler(void) {
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET) {
		if(TIM1->CR1 && TIM_CounterMode_Down != TIM_CounterMode_Down) {
			TIM1_overtime++;
		}	else {
			TIM1_overtime--;
		}
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
}    

