#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "USART1.h"
#include "I2C1Hardware.h"

#include "KLM.h"

#include "LED.h"
#include "OLED.h"
#include "HCRS04.h"

float length = 0.0;
KLM_Struct RS04_KLM;

int main(void) {                                                                                           
  NVIC_Configuration();
	RCC_Configuration();

	I2C1_Hardware_Init();

	USART1_Init();
	LED_Init();
	OLED_Init();
	HC_SR04_Init();
	
	OLED_ShowChar(1, 4, '.', 8);

	KLM_Struct_Init(&RS04_KLM, 0.2, 3);

	while (1) {
		length = KalmanFilter(&RS04_KLM, HC_SR04_GetLength());
		
		OLED_ShowNum(1, 1, (int32_t)length, 3, 8);
		OLED_ShowNum(1, 5, (int32_t)(length * 100) % 100, 2, 8);
		
		USART1_SendNumber((int32_t)length, 3);
		USART1_SendString(".");
		USART1_SendNumber((int32_t)(length * 100) % 100, 2);
		USART1_SendString("\r\n");

//		LED_Turn();
		Delay_ms(50);
	}
}
