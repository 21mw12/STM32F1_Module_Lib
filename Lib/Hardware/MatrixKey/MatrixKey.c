#include "MatrixKey.h"
#include "Delay.h"

void MatrixKey_Init(void) {
	RCC_APB2PeriphClockCmd(MatrixKey_RPeriph, ENABLE);
	RCC_APB2PeriphClockCmd(MatrixKey_CPeriph, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruture;
	GPIO_InitStruture.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruture.GPIO_Pin = MatrixKey_Row1 | MatrixKey_Row2 | MatrixKey_Row3 | MatrixKey_Row4;
	GPIO_InitStruture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MatrixKey_RPort, &GPIO_InitStruture);
	
	GPIO_InitStruture.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruture.GPIO_Pin = MatrixKey_Column1 | MatrixKey_Column2 | MatrixKey_Column3 | MatrixKey_Column4;
	GPIO_Init(MatrixKey_CPort, &GPIO_InitStruture);
}

/**
  * @brief 设置所有引脚为高电平
  * @return 无
  */
void MatrixKey_SetAllPin(void){
	GPIO_SetBits(MatrixKey_RPort, MatrixKey_Row1);
	GPIO_SetBits(MatrixKey_RPort, MatrixKey_Row2);
	GPIO_SetBits(MatrixKey_RPort, MatrixKey_Row3);
	GPIO_SetBits(MatrixKey_RPort, MatrixKey_Row4);
	GPIO_SetBits(MatrixKey_CPort, MatrixKey_Column1);
	GPIO_SetBits(MatrixKey_CPort, MatrixKey_Column2);
	GPIO_SetBits(MatrixKey_CPort, MatrixKey_Column3);
	GPIO_SetBits(MatrixKey_CPort, MatrixKey_Column4);
}

uint8_t MatrixKey_GetCode(void) {
	uint8_t KeyNumber = 0;
	
	/* 扫描第一行按键 */
	MatrixKey_SetAllPin();
	GPIO_ResetBits(MatrixKey_RPort, MatrixKey_Row1);
	if (!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column1)) {
		Delay_us(20);
    while(!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column1));
		Delay_ms(20);
		KeyNumber = 1;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column2)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column2));
		Delay_ms(20);
		KeyNumber = 2;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column3)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column3));
		Delay_ms(20);
		KeyNumber = 3;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column4)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column4));
		Delay_ms(20);
		KeyNumber = 4;
	}
	
	/* 扫描第二行按键 */
	MatrixKey_SetAllPin();
	GPIO_ResetBits(MatrixKey_RPort, MatrixKey_Row2);
	if (!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column1)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column1));
		Delay_ms(20);
		KeyNumber = 5;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column2)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column2));
		Delay_ms(20);
		KeyNumber = 6;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column3)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column3));
		Delay_ms(20);
		KeyNumber = 7;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column4)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column4));
		Delay_ms(20);
		KeyNumber = 8;
	}
	
	/* 扫描第三行按键 */
	MatrixKey_SetAllPin();
	GPIO_ResetBits(MatrixKey_RPort, MatrixKey_Row3);
	if (!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column1)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column1));
		Delay_ms(20);
		KeyNumber = 9;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column2)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column2));
		Delay_ms(20);
		KeyNumber = 10;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column3)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column3));
		Delay_ms(20);
		KeyNumber = 11;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column4)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column4));
		Delay_ms(20);
		KeyNumber = 12;
	}
	
	/* 扫描第四行按键 */
	MatrixKey_SetAllPin();
	GPIO_ResetBits(MatrixKey_RPort, MatrixKey_Row4);
	if (!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column1)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column1));
		Delay_ms(20);
		KeyNumber = 13;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column2)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column2));
		Delay_ms(20);
		KeyNumber = 14;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column3)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column3));
		Delay_ms(20);
		KeyNumber = 15;
	}
	if (!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column4)) {
		Delay_us(20);
		while(!GPIO_ReadInputDataBit(MatrixKey_CPort, MatrixKey_Column4));
		Delay_ms(20);
		KeyNumber = 16;
	}
	
	return KeyNumber;
}

Button MatrixKey_TransitionKeyCode(uint8_t KeyCode) {
	switch (KeyCode) {
		case 1:
			return Button_Num1;
		case 2:
			return Button_Num2;
		case 3:
			return Button_Num3;
		case 4:
			return Button_A;
		case 5:
			return Button_Num4;
		case 6:
			return Button_Num5;
		case 7:
			return Button_Num6;
		case 8:
			return Button_B;
		case 9:
			return Button_Num7;
		case 10:
			return Button_Num8;
		case 11:
			return Button_Num9;
		case 12:
			return Button_C;
		case 13:
			return Button_Asterisk;
		case 14:
			return Button_Num0;
		case 15:
			return Button_WellNumber;
		case 16:
			return Button_D;
		default:
			return Button_NULL;
	}
}
