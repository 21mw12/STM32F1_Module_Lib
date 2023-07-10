#include "OLED.h"
#include "OLED_Font.h"
#include "OLED_Instruct.h"
#include "i2c_hardware.h"

/**
  * @brief  OLED写命令
  * @param  Command 要写入的命令
  * @retval 无
  */
void OLED_WriteCommand(uint8_t Command) {
	I2C_Hardware_SendByte(OLED_ADDRESS, 0x00, Command);
}

/**
  * @brief  OLED写数据
  * @param  Data 要写入的数据
  * @retval 无
  */
void OLED_WriteData(uint8_t Data) {
	I2C_Hardware_SendByte(OLED_ADDRESS, 0x40, Data);
}

/**
  * @brief  OLED设置光标位置
  * @param  Y 以左上角为原点，向下方向的坐标，范围：0~7
  * @param  X 以左上角为原点，向右方向的坐标，范围：0~127
  * @retval 无
  */
void OLED_SetCursor(uint8_t Y, uint8_t X) {
	OLED_WriteCommand(0xB0 | Y);					//设置Y位置
	OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	//设置X位置低4位
	OLED_WriteCommand(0x00 | (X & 0x0F));			//设置X位置高4位
}

/**
  * @brief  次方函数
  * @retval 返回a的b次方
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
	
	// 设置显示时钟分频比/振荡器频率
	OLED_WriteCommand(Set_Display_ClockOSC);
	OLED_WriteCommand(Display_ClockOSC_Value);
	// 设置多路复用率
	OLED_WriteCommand(Set_Display_Multiplexing);
	OLED_WriteCommand(Display_Multiplexing_Value);
	// 设置预充电周期
	OLED_WriteCommand(Set_Display_ChargingCycle);
	OLED_WriteCommand(Display_ChargingCycle_Value);
	// 设置COM引脚硬件配置
	OLED_WriteCommand(Set_Display_COMPinConfig);
	OLED_WriteCommand(Display_COMPinConfig_Value);
	// 设置充电泵
	OLED_WriteCommand(Set_Display_ChargePump);
	OLED_WriteCommand(Display_ChargePump_Value);
	// 设置VCOMH取消选择级别
	OLED_WriteCommand(Set_Display_VCOMH);
	OLED_WriteCommand(Display_VCOMH_Value);
	
	// 设置显示亮度
	OLED_WriteCommand(Set_Display_Luminance);
	OLED_WriteCommand(Display_Luminance_Value);
	// 设置显示偏移
	OLED_WriteCommand(Set_Display_Skew);
	OLED_WriteCommand(Display_Skew_Value);
	// 设置显示开始行
	OLED_WriteCommand(Display_Start_Line);
	// 设置显示上下左右模式
	OLED_WriteCommand(Display_Left_Right_Nomal);
	OLED_WriteCommand(Display_Up_Down_Nomal);
	// 设置整个显示打开/关闭
	OLED_WriteCommand(0xA4);
	// 设置屏幕是否反色
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

	/* 根据一个字符在屏幕上所占的大小，需要分几次才能写完 */
	/* 因为SSD1306每次只能传输一块的信息，所有要依次写入全部数据 */
	/* 这里每个字符的信息都存储在OLED_Font.h文件中 */

	if (Front_size == 8) {
		for (line = 0; line < 2; line++) {
			// 设置光标位置在每一块的开始位置
			OLED_SetCursor(Y + line, X);
			for (i = 0; i < Front_size; i++) {
				OLED_WriteData(OLED_F8x16[Char - ' '][i + Front_size * line]);
			}
		}
	}
	else if (Front_size == 16) {
		for (line = 0; line < 4; line++) {
			// 设置光标位置在每一块的开始位置
			OLED_SetCursor(Y + line, X);
			for (i = 0; i < Front_size; i++) {
				OLED_WriteData(OLED_F16x32[Char - '0'][i + Front_size * line]);
			}
		}
	}
}

void OLED_ShowString(uint8_t Line, uint8_t Column, char *String, uint8_t Front_size) {
	uint8_t i;
	
	// 依次显示字符串中的每个字符即可
	for (i = 0; String[i] != '\0'; i++) {
		OLED_ShowChar(Line, Column + i, String[i], Front_size);
	}
}

void OLED_ShowNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length, uint8_t Front_size) {
	uint8_t i;
	char showNumber;
	
	// 如果是负数则显示负号
	if (Number < 0) {
		OLED_ShowChar(Line, Column, '-', Front_size);
		Number = -Number;
		Column++;
	}
	
	for (i = 1; i <= Length; i++) {
		// 计算这次要显示的数字
		showNumber = Number % 10 + '0';
		// 显示在屏幕上（从后往前显示）
		OLED_ShowChar(Line, Column + Length - i, showNumber, Front_size);
		// 除去显示过的数字
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
