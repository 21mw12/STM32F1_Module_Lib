#include "stm32f10x.h"
#include "LED.h"

int main(void) {
	uint32_t *p = (uint32_t *) 0x08005004;
	uint32_t vec = *p;
	
	void (*app)(void);
	
	app = (void (*)(void))vec;
	
	LED_Init();
	LED_Flash(200);	
	
	app();
	
	return 0;
}
