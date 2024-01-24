#include "Nixie74HC.h"
#include "Delay.h"

/* 共阴数码管的数字对应数据 */
uint8_t NixieTable[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x40};

void Nixie_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(Nixie_Periph, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = HC254_Pin_A0 | HC254_Pin_A1 | HC254_Pin_A2 | HC254_Pin_A3 | HC254_Pin_A4 | HC254_Pin_A5 | HC254_Pin_A6 | HC254_Pin_A7 | 
																HC138_Pin_A | HC138_Pin_B | HC138_Pin_C;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Nixie_Port, &GPIO_InitStructure);
}

void Nixie_Show(uint8_t Location, uint8_t Number) {
	uint16_t data = (--Location << 8) | NixieTable[Number];		// 计算要发送的数据
	
	GPIO_Write(Nixie_Port, data);		// 向数据线发送对应信息
	Delay_ms(1);
	GPIO_Write(Nixie_Port, 0x00);		// 数据线清空
}
