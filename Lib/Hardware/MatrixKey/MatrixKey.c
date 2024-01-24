#include "MatrixKey.h"
#include "Delay.h"

void MatrixKey_Init(void) {
	RCC_APB2PeriphClockCmd(MatrixKey_Periph, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruture;
	
	GPIO_InitStruture.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruture.GPIO_Pin = MatrixKey_Row1 | MatrixKey_Row2 | MatrixKey_Row3 | MatrixKey_Row4;
	GPIO_InitStruture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MatrixKey_Port, &GPIO_InitStruture);
	
	GPIO_InitStruture.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruture.GPIO_Pin = MatrixKey_Column1 | MatrixKey_Column2 | MatrixKey_Column3 | MatrixKey_Column4;
	GPIO_Init(MatrixKey_Port, &GPIO_InitStruture);
}

uint8_t MatrixKey(void) {
	uint8_t KeyNumber = 0;
	
	GPIO_Write(MatrixKey_Port, 0xFF);
	GPIO_ResetBits(MatrixKey_Port, MatrixKey_Row1);
	if (!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column1)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column1));
		Delay_ms(20);
		KeyNumber = 1;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column2)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column2));
		Delay_ms(20);
		KeyNumber = 2;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column3)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column3));
		Delay_ms(20);
		KeyNumber = 3;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column4)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column4));
		Delay_ms(20);
		KeyNumber = 4;
	}
	
	GPIO_Write(MatrixKey_Port, 0xFF);
	GPIO_ResetBits(MatrixKey_Port, MatrixKey_Row2);
	if (!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column1)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column1));
		Delay_ms(20);
		KeyNumber = 5;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column2)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column2));
		Delay_ms(20);
		KeyNumber = 6;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column3)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column3));
		Delay_ms(20);
		KeyNumber = 7;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column4)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column4));
		Delay_ms(20);
		KeyNumber = 8;
	}
	
	GPIO_Write(MatrixKey_Port, 0xFF);
	GPIO_ResetBits(MatrixKey_Port, MatrixKey_Row3);
	if (!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column1)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column1));
		Delay_ms(20);
		KeyNumber = 9;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column2)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column2));
		Delay_ms(20);
		KeyNumber = 10;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column3)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column3));
		Delay_ms(20);
		KeyNumber = 11;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column4)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column4));
		Delay_ms(20);
		KeyNumber = 12;
	}
	
	GPIO_Write(MatrixKey_Port, 0xFF);
	GPIO_ResetBits(MatrixKey_Port, MatrixKey_Row4);
	if (!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column1)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column1));
		Delay_ms(20);
		KeyNumber = 13;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column2)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column2));
		Delay_ms(20);
		KeyNumber = 14;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column3)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column3));
		Delay_ms(20);
		KeyNumber = 15;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column4)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_Port, MatrixKey_Column4));
		Delay_ms(20);
		KeyNumber = 16;
	}
	
	return KeyNumber;
}

uint8_t KeyCodeTransition(uint8_t KeyCode) {
	switch (KeyCode) {
		case 2:
			return 0;
		case 5:
			return 1;
		case 6:
			return 2;
		case 7:
			return 3;
		case 9:
			return 4;
		case 10:
			return 5;
		case 11:
			return 6;
		case 13:
			return 7;
		case 14:
			return 8;
		case 15:
			return 9;
		default:
			return 10;
	}
}
