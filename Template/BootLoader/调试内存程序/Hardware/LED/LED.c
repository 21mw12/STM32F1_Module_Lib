#include "Led.h"
#include "Delay.h"

void LED_Init(void) {
	RCC_APB2PeriphClockCmd(LED_Periph, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
	GPIO_InitStructure.GPIO_Pin = LED_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(LED_Port, &GPIO_InitStructure);
	
	LED_ON();
}

#if LED_Pin_State	
	void LED_ON(void) {	
		GPIO_SetBits(LED_Port, LED_Pin);
	}

	void LED_OFF(void) {	
		GPIO_ResetBits(LED_Port, LED_Pin);
	}
	
	void LED_Turn(void) {
		if (GPIO_ReadOutputDataBit(LED_Port, LED_Pin)) {
			LED_OFF();
		} else {
			LED_ON();
		}
	}
#else
	void LED_ON(void) {	
		GPIO_ResetBits(LED_Port, LED_Pin);
	}

	void LED_OFF(void) {	
		GPIO_SetBits(LED_Port, LED_Pin);
	}
	
	void LED_Turn(void) {
		if (!GPIO_ReadOutputDataBit(LED_Port, LED_Pin)) {
			LED_OFF();
		} else {
			LED_ON();
		}
	}
#endif

void LED_Flash(int ms) {
	LED_ON();
	Delay_ms(ms);
	LED_OFF();
	Delay_ms(ms);
}
