#include "TIM4Encoder.h"

void TIM4_Encoder_Init(void) {
	/* Ê±ÖÓÅäÖÃ */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	/* IO¿ÚÅäÖÃ */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* NVICÅäÖÃ */
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM4_IRQn;
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
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
	
	/* ¶¨Ê±Æ÷ÊäÈë²¶»ñÅäÖÃ */
	TIM_ICInitTypeDef TIM_ICInitStructure;
  TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 | TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
  
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  
	TIM_SetCounter(TIM4, 0);
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);	
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM4, ENABLE);
}

int16_t TIM4_Encoder_GetClear(void) {
	int16_t count;
	count = TIM_GetCounter(TIM4);
	TIM_SetCounter(TIM4, 0);
	return count;
}

uint32_t TIM4_Encoder_Get(void) {
	uint32_t count = 0;
	count = TIM4->CNT;
	return count;
}

int16_t TIM4_overflow = 0;
void TIM4_IRQHandler(void) {
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) == SET) {
		if(TIM4->CR1 && TIM_CounterMode_Down != TIM_CounterMode_Down) {
			TIM4_overflow++;
		}	else {
			TIM4_overflow--;
		}
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}    

