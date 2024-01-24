#include "PS2.h"
#include "delay.h"
#include "PS2_Instruct.h"

#define PS2_DAT_Read()					GPIO_ReadInputDataBit(PS2_Port, PS2_Pin_DAT)
#define PS2_CMD_Write(state)		GPIO_WriteBit(PS2_Port, PS2_Pin_CMD, (BitAction)state)
#define PS2_CS_Write(state)			GPIO_WriteBit(PS2_Port, PS2_Pin_CS, (BitAction)state)
#define PS2_CLK_Write(state)		GPIO_WriteBit(PS2_Port, PS2_Pin_CLK, (BitAction)state)

uint16_t Handkey;

uint8_t PS2Data[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

void PS2_Init(void) {
	RCC_APB2PeriphClockCmd(PS2_Periph, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = PS2_Pin_CMD | PS2_Pin_CS | PS2_Pin_CLK;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PS2_Port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = PS2_Pin_DAT;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(PS2_Port, &GPIO_InitStructure);
}

/**
  * @brief 向PS2手柄接收器发送命令
  * @param PS2_CMD 手柄指令
  * @return 无
  */
uint8_t PS2_SendCmd(uint8_t PS2_CMD) {
	uint8_t receiveData = 0x00;
	
	for (uint8_t i = 0; i < 8; i++) {
		if(PS2_CMD & (0x01 << i))	{
			PS2_CMD_Write(Bit_SET);
		} else {
			PS2_CMD_Write(Bit_RESET);
		}

		PS2_CLK_Write(Bit_SET);
		Delay_us(50);
		PS2_CLK_Write(Bit_RESET);
		Delay_us(50);
		PS2_CLK_Write(Bit_SET);
		
		if (PS2_DAT_Read()) {
			receiveData |= (0x01 << i);
		}
	}
	
	return receiveData;
}

enum PS2_Mode PS2_GetMode(void) {

	switch (PS2Data[1]) {
		case PS2_RED_MODE_INSTRUCT: return PS2_Mode_Red;
		case PS2_GREEN_MODE_INSTRUCT: return PS2_Mode_Green;
		default: return PS2_Modeeee_Error;
	}
}

void PS2_ReadData(void) {
	PS2_ClearData();
	
	PS2_CS_Write(Bit_RESET);

	PS2Data[0] = PS2_SendCmd(PS2_START_CMD);
	PS2Data[1] = PS2_SendCmd(PS2_ASK_DATA_CMD);
	PS2Data[2] = PS2_SendCmd(PS2_DUMMY_BYTE);
	PS2Data[3] = PS2_SendCmd(PS2_DUMMY_BYTE);
	PS2Data[4] = PS2_SendCmd(PS2_DUMMY_BYTE);
	PS2Data[5] = PS2_SendCmd(PS2_DUMMY_BYTE);
	PS2Data[6] = PS2_SendCmd(PS2_DUMMY_BYTE);
	PS2Data[7] = PS2_SendCmd(PS2_DUMMY_BYTE);
	PS2Data[8] = PS2_SendCmd(PS2_DUMMY_BYTE);

	PS2_CS_Write(Bit_SET);	
}

enum PS2_Button_State PS2_CheckButton(uint8_t CheckButton) {
	uint8_t index = 0x01;
	
	switch (CheckButton / 8) {
		case 0:
			index <<= CheckButton;
			return ((PS2Data[3] & index) == 0x00) ? PS2_BUTTON_STATE_PUSH : PS2_BUTTON_STATE_NULL;
		case 1:
			index <<= (CheckButton - 8);
			return ((PS2Data[4] & index) == 0x00) ? PS2_BUTTON_STATE_PUSH : PS2_BUTTON_STATE_NULL;
		default:
			return PS2_BUTTON_STATE_NULL;
	}
}

uint8_t PS2_GetJoystickData(uint8_t Joystick) {
	
	switch (Joystick) {
		case PS2_PSS_RX: return PS2Data[5];
		case PS2_PSS_RY: return PS2Data[6];
		case PS2_PSS_LX: return PS2Data[7];
		case PS2_PSS_LY: return PS2Data[8];
		default: return 0xFF;
	}
}

void PS2_ClearData(void){
	
	for(uint8_t i = 0; i < 9; i++) {
		PS2Data[i] = 0x00;
	}
}




