#include "OLED.h"
#include "OLED_Font.h"
#include "OLED_Instruct.h"
#include "i2c_hardware.h"

/**
  * @brief  OLEDд����
  * @param  Command Ҫд�������
  * @retval ��
  */
void OLED_WriteCommand(uint8_t Command) {
	I2C_Hardware_SendByte(OLED_ADDRESS, 0x00, Command);
}

/**
  * @brief  OLEDд����
  * @param  Data Ҫд�������
  * @retval ��
  */
void OLED_WriteData(uint8_t Data) {
	I2C_Hardware_SendByte(OLED_ADDRESS, 0x40, Data);
}

/**
  * @brief  OLED���ù��λ��
  * @param  Y �����Ͻ�Ϊԭ�㣬���·�������꣬��Χ��0~7
  * @param  X �����Ͻ�Ϊԭ�㣬���ҷ�������꣬��Χ��0~127
  * @retval ��
  */
void OLED_SetCursor(uint8_t Y, uint8_t X) {
	OLED_WriteCommand(0xB0 | Y);					//����Yλ��
	OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	//����Xλ�õ�4λ
	OLED_WriteCommand(0x00 | (X & 0x0F));			//����Xλ�ø�4λ
}

/**
  * @brief  �η�����
  * @retval ����a��b�η�
  */
uint32_t Pow(uint32_t a, uint32_t b) {
	uint32_t Result = 1;
	while (b--) {
		Result *= a;
	}
	return Result;
}

void OLED_Init(void) {	
	Delay_ms(1000);
	
	OLED_WriteCommand(Display_OFF);
	
	// ������ʾʱ�ӷ�Ƶ��/����Ƶ��
	OLED_WriteCommand(Set_Display_ClockOSC);
	OLED_WriteCommand(Display_ClockOSC_Value);
	// ���ö�·������
	OLED_WriteCommand(Set_Display_Multiplexing);
	OLED_WriteCommand(Display_Multiplexing_Value);
	// ����Ԥ�������
	OLED_WriteCommand(Set_Display_ChargingCycle);
	OLED_WriteCommand(Display_ChargingCycle_Value);
	// ����COM����Ӳ������
	OLED_WriteCommand(Set_Display_COMPinConfig);
	OLED_WriteCommand(Display_COMPinConfig_Value);
	// ���ó���
	OLED_WriteCommand(Set_Display_ChargePump);
	OLED_WriteCommand(Display_ChargePump_Value);
	// ����VCOMHȡ��ѡ�񼶱�
	OLED_WriteCommand(Set_Display_VCOMH);
	OLED_WriteCommand(Display_VCOMH_Value);
	
	// ������ʾ����
	OLED_WriteCommand(Set_Display_Luminance);
	OLED_WriteCommand(Display_Luminance_Value);
	// ������ʾƫ��
	OLED_WriteCommand(Set_Display_Skew);
	OLED_WriteCommand(Display_Skew_Value);
	// ������ʾ��ʼ��
	OLED_WriteCommand(Display_Start_Line);
	// ������ʾ��������ģʽ
	OLED_WriteCommand(Display_Left_Right_Nomal);
	OLED_WriteCommand(Display_Up_Down_Nomal);
	// ����������ʾ��/�ر�
	OLED_WriteCommand(0xA4);
	// ������Ļ�Ƿ�ɫ
	OLED_WriteCommand(Display_Color_Nomal);
	
	OLED_WriteCommand(Display_ON);
		
	OLED_Clear();
}

void OLED_Clear(void) {  
	uint8_t i, j;
	for (j = 0; j < 4; j++) {
		OLED_SetCursor(j, 0);
		for(i = 0; i < 128; i++) {
			OLED_WriteData(0x00);
		}
	}
}

void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char, uint8_t Front_size) {      	
	uint8_t i, line;
	uint8_t Y = (Line - 1) * 2;
	uint8_t X = (Column - 1) * Front_size;

	/* ����һ���ַ�����Ļ����ռ�Ĵ�С����Ҫ�ּ��β���д�� */
	/* ��ΪSSD1306ÿ��ֻ�ܴ���һ�����Ϣ������Ҫ����д��ȫ������ */
	/* ����ÿ���ַ�����Ϣ���洢��OLED_Font.h�ļ��� */

	if (Front_size == 8) {
		for (line = 0; line < 2; line++) {
			// ���ù��λ����ÿһ��Ŀ�ʼλ��
			OLED_SetCursor(Y + line, X);
			for (i = 0; i < Front_size; i++) {
				OLED_WriteData(OLED_F8x16[Char - ' '][i + Front_size * line]);
			}
		}
	}
	else if (Front_size == 16) {
		for (line = 0; line < 4; line++) {
			// ���ù��λ����ÿһ��Ŀ�ʼλ��
			OLED_SetCursor(Y + line, X);
			for (i = 0; i < Front_size; i++) {
				OLED_WriteData(OLED_F16x32[Char - '0'][i + Front_size * line]);
			}
		}
	}
}

void OLED_ShowString(uint8_t Line, uint8_t Column, char *String, uint8_t Front_size) {
	uint8_t i;
	
	// ������ʾ�ַ����е�ÿ���ַ�����
	for (i = 0; String[i] != '\0'; i++) {
		OLED_ShowChar(Line, Column + i, String[i], Front_size);
	}
}

void OLED_ShowNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length, uint8_t Front_size) {
	uint8_t i;
	char showNumber;
	
	// ����Ǹ�������ʾ����
	if (Number < 0) {
		OLED_ShowChar(Line, Column, '-', Front_size);
		Number = -Number;
		Column++;
	}
	
	for (i = 1; i <= Length; i++) {
		// �������Ҫ��ʾ������
		showNumber = Number % 10 + '0';
		// ��ʾ����Ļ�ϣ��Ӻ���ǰ��ʾ��
		OLED_ShowChar(Line, Column + Length - i, showNumber, Front_size);
		// ��ȥ��ʾ��������
		Number /= 10;
	}
}

void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length, uint8_t Front_size) {
	uint8_t i;
	char showNumber;
	
	if (Number < 0) {
		OLED_ShowChar(Line, Column, '-', Front_size);
		Number = -Number;
		Column++;
	}
	
	for (i = 0; i < Length; i++) {
		showNumber = Number % 8 + '0';
		OLED_ShowChar(Line, Column + Length - i, showNumber, Front_size);
		Number /= 8;
	}
}

void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length, uint8_t Front_size) {
	uint8_t i, SingleNumber;
	
	for (i = 0; i < Length; i++) {
		SingleNumber = Number % 16;
		if (SingleNumber < 10) {
			OLED_ShowChar(Line, Column + Length - i, SingleNumber + '0', Front_size);
		} else {
			OLED_ShowChar(Line, Column + Length - i, SingleNumber - 10 + 'A', Front_size);
		}
		Number /= 16;
	}
}

void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length, uint8_t Front_size) {
	uint8_t i;
	char showNumber;
	
	for (i = 0; i < Length; i++) {
		showNumber = Number % 2 + '0';		
		OLED_ShowChar(Line, Column + Length - i, showNumber, Front_size);
		Number /= 2;
	}
}
