#include "Buzzer.h"

void Buzzer_Init(void) {
	RCC_APB2PeriphClockCmd(BUZZER_Periph, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
	GPIO_InitStructure.GPIO_Pin = BUZZER_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(BUZZER_PORT, &GPIO_InitStructure);
}
	
void BUZZER_ON(void) {	
	GPIO_ResetBits(BUZZER_PORT, BUZZER_PIN);
}

void BUZZER_OFF(void) {	
	GPIO_SetBits(BUZZER_PORT, BUZZER_PIN);
}
