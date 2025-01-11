#include "stm32f10x.h"
#include "LED.h"

/* 参数为APP的烧录起始地址 */
extern void App_Start(uint32_t App_Vector);

int main(void) {	
	LED_Init();
	LED_Flash(200);	
	
	App_Start(0x08005000);
	
	return 0;
}
