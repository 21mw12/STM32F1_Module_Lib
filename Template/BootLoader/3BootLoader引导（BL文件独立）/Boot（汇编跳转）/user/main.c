#include "stm32f10x.h"
#include "BootLoader.h"
#include "LED.h"

int main(void) {	
	LED_Init();
	LED_Flash(200);
	
	BootLoader_LoadAPP(0x08005000);
	
	return 0;
}
