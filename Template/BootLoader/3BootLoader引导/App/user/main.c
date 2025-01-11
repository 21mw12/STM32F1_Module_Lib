#include "stm32f10x.h"
#include "LED.h"

int app_main(void) {
	
	LED_Init();
	
	while(1) {
		LED_Flash(200);
	}
}
