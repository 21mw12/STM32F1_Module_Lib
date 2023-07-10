#include "TIM2Encoder.h"

void TIM2_Encoder_Init(void) {
	/* Ê±ÖÓÅäÖÃ */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	/* IO¿ÚÅäÖÃ */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* NVICÅäÖÃ */
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
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
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	/* ¶¨Ê±Æ÷ÊäÈë²¶»ñÅäÖÃ */
	TIM_ICInitTypeDef TIM_ICInitStructure;
  TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 | TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
  
  TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  
	TIM_SetCounter(TIM2, 0);
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);	
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM2, ENABLE);
}

int16_t TIM2_Encoder_GetClear(void) {
	int16_t count;
	count = TIM_GetCounter(TIM2);
	TIM_SetCounter(TIM2, 0);
	return count;
}

uint32_t TIM2_Encoder_Get(void) {
	uint32_t count = 0;
	count = TIM2->CNT;
	return count;
}

int16_t TIM2_overtime = 0;
void TIM2_IRQHandler(void) {
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
		if(TIM2->CR1 && TIM_CounterMode_Down != TIM_CounterMode_Down) {
			TIM2_overtime++;
		}	else {
			TIM2_overtime--;
		}
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}    

