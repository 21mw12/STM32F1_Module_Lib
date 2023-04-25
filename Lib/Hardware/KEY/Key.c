#include "key.h"

void Key_Init(void){
  RCC_APB2PeriphClockCmd(Key_Periph, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin = Key_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Key_PORT, &GPIO_InitStructure);			
}
 
uint8_t Key_Get(void) {
	if (GPIO_ReadInputDataBit(Key_PORT, Key_PIN) == 0) {
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(Key_PORT, Key_PIN) == 0);
		Delay_ms(20);
		return 1;
	}	
	return 0;
}
