#include "NixieMAX7219.h"
#include "Delay.h"

uint8_t NixieTable[] = {
    0x7E,   // 0
    0x30,   // 1
    0x6D,   // 2
    0x79,   // 3
    0x33,   // 4
    0x5B,   // 5
    0x5F,   // 6
    0x70,   // 7
    0x7F,   // 8
    0x7B,   // 9
    0x01,   // 横杠
    0x00    // 空格
};

void MAX7219_Write(uint8_t data) {
	uint8_t i;
	GPIO_ResetBits(MAX7219_Port, MAX7219_Pin_LOAD);
	for(i = 0; i < 8; i++) {
		GPIO_ResetBits(MAX7219_Port, MAX7219_Pin_CLK);

		if ((data & 0x80) == 0x00) {
			GPIO_ResetBits(MAX7219_Port, MAX7219_Pin_DIN);
		} else {
			GPIO_SetBits(MAX7219_Port, MAX7219_Pin_DIN);
		}

		data <<= 1;
		GPIO_SetBits(MAX7219_Port, MAX7219_Pin_CLK);
	}
}

void MAX2719_Config(uint8_t address, uint8_t data) {
	GPIO_ResetBits(MAX7219_Port, MAX7219_Pin_LOAD);		

	MAX7219_Write(address);
	Delay_us(10);
	MAX7219_Write(data);
	Delay_us(10);

	GPIO_SetBits(MAX7219_Port, MAX7219_Pin_LOAD);		
}

void MAX2719_Init(void) {
	MAX2719_Config(0x0C, 0x01);      //开启正常工作模式（0xX1）
  MAX2719_Config(0x0F, 0x00);      //选择工作模式（0xX0）
	MAX2719_Config(0x09, 0x00);      //选用全译码模式(0xFF)
	MAX2719_Config(0x0B, 0x07);      //8只LED全用
	MAX2719_Config(0x0A, 0x04);      //设置初始亮度
}


void Nixie_Init(void) {
	RCC_APB2PeriphClockCmd(MAX7219_Periph, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
	GPIO_InitStructure.GPIO_Pin = MAX7219_Pin_DIN | MAX7219_Pin_LOAD | MAX7219_Pin_CLK;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(MAX7219_Port, &GPIO_InitStructure);
	
	MAX2719_Init();
}

void Nixie_Show(uint8_t Location, uint8_t Number){
	GPIO_ResetBits(MAX7219_Port, MAX7219_Pin_LOAD);		

	MAX7219_Write(Location);
	Delay_us(10);
	MAX7219_Write(NixieTable[Number]);
	Delay_us(10);

	GPIO_SetBits(MAX7219_Port, MAX7219_Pin_LOAD);			 
}
