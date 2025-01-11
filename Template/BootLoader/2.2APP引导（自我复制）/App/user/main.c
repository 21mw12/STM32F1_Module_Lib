#include "stm32f10x.h"
#include "LED.h"

void APP_CopyToRAM(int* from, int* to, int len) {
	int i = 0;
	
	for (i = 0; i < len/4+1; i++) {
		to[i] = from[i];
	}
}

int app_main(void) {
	
	LED_Init();
	
	while(1) {
		LED_Flash(200);
	}
}
