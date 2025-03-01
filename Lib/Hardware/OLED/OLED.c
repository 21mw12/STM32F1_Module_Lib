#include "OLED.h"
#include "OLED_Font.h"
#include "OLED_Instruct.h" 
#include "Delay.h"
#if isSPIAgreement == 1
#include "SPISoftware.h"
#else
#include "I2CSoftware.h"
#endif

/* 设置OLED的大小 */
#define OLED_Line				 64
#define OLED_Column			 128

/**
  * @brief OLED写入一个字节
  * @param ComType 数据类型
  * @param Data 数据
  * @return 无
  */
void OLED_Write(uint8_t ComType, uint8_t Data) {
#if isSPIAgreement == 1
	/* 指令还是数据 */
	if(ComType == OLED_Data) {
		GPIO_SetBits(GPIOB, OLED_DC_Pin);
	} else {
	  GPIO_ResetBits(GPIOB, OLED_DC_Pin);	
	}

	/* 片选并传输数据 */
	GPIO_ResetBits(GPIOB, OLED_CS_Pin);
	SPI_Software_SwapByte(Data);
  GPIO_SetBits(GPIOB, OLED_CS_Pin);
	
	GPIO_SetBits(GPIOB, OLED_DC_Pin);
#else
	I2C_Software_StartSignal();
	
	I2C_Software_SendData(OLED_ADDRESS);	// 发送从器件地址
	I2C_Software_SendData(ComType);
	I2C_Software_SendData(Data);
	
	I2C_Software_StopSignal();
#endif
}

/**
  * @brief  OLED设置光标位置
  * @param  Y 以左上角为原点，向下方向的坐标，范围：0~7
  * @param  X 以左上角为原点，向右方向的坐标，范围：0~127
  * @retval 无
  */
void OLED_SetCursor(uint8_t X,uint8_t Y) {
	OLED_Write(OLED_Command, 0xB0 | Y);					//设置Y位置
	OLED_Write(OLED_Command, 0x10 | ((X & 0xF0) >> 4));	//设置X位置低4位
	OLED_Write(OLED_Command, 0x00 | (X & 0x0F));			//设置X位置高4位
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
#if isSPIAgreement == 1
	RCC_APB2PeriphClockCmd(OLED_Periph, ENABLE);
 
 	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = OLED_DC_Pin | OLED_RES_Pin | OLED_CS_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(OLED_Port, &GPIO_InitStructure);

 	GPIO_SetBits(OLED_Port, OLED_DC_Pin | OLED_RES_Pin | OLED_CS_Pin);
	
	Delay_ms(1000);
	
	GPIO_ResetBits(OLED_Port, OLED_RES_Pin);
	Delay_ms(200);
  GPIO_SetBits(OLED_Port, OLED_RES_Pin);
#else
	Delay_ms(1000);
	
	OLED_Write(OLED_Command, Display_OFF);
#endif

	
	/* 默认配置 */
	OLED_Write(OLED_Command, Set_Display_RefreshRate);
	OLED_Write(OLED_Command, 0xF0);
	OLED_Write(OLED_Command, Set_Display_Multiplexing);
	OLED_Write(OLED_Command, 0x3F);
	OLED_Write(OLED_Command, Set_Display_Skew);			// 设置显示偏移
	OLED_Write(OLED_Command, 0x00);
	OLED_Write(OLED_Command, Display_Start_Line);		// 设置显示开始行
	OLED_Write(OLED_Command, Set_Display_ChargingCycle);
	OLED_Write(OLED_Command, 0xF1);
	OLED_Write(OLED_Command, Set_Display_VCOMH);
	OLED_Write(OLED_Command, 0x30);
	OLED_Write(OLED_Command, Set_Display_ChargePump);
	OLED_Write(OLED_Command, 0x14);
	OLED_Write(OLED_Command, Display_VideoMemory_ON);
	
	/* 默认设置 */
	OLED_Write(OLED_Command, Set_Display_Luminance);	// 设置亮度值（范围：0x00 ~ 0xFF）
	OLED_Write(OLED_Command, 0x7F);;
	OLED_Write(OLED_Command, Display_Left_Right_Nomal);// 设置显示上下左右模式
	OLED_Write(OLED_Command, Display_Up_Down_Nomal);
	OLED_Write(OLED_Command, Display_Color_Nomal);		// 设置屏幕是否反色
	
	/* 设置显存地址模式 */
	// 0x00 -	水平地址模式 ("之"字型)
	// 0x01 - 垂直地址模式 （"N"型）
	// 0x02 - 页地址模式 (按行顺序排列)
	OLED_Write(OLED_Command, Display_SetAddressPattern);
	OLED_Write(OLED_Command, 0x00);
	
	/* 设置列引脚 */
	// 0x02 - 分辨率为128*32（0.91寸）
	// 0x12 - 分辨率为128*64（0.96寸）
	OLED_Write(OLED_Command, Set_Display_ColumnPinConfig);
	OLED_Write(OLED_Command, 0x12);
	
	OLED_Write(OLED_Command, Display_ON);
	
	OLED_Clear();
}
  
void OLED_Clear(void) {  
	uint8_t X, Y;
	for (Y = 0; Y < OLED_Line / 8; Y++) {
		OLED_SetCursor(0, Y);
		for(X = 0; X < OLED_Column; X++) {
			OLED_Write(OLED_Data, 0x00);
		}
	}
}

void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char, uint8_t Front_size)  {
	uint8_t i, j;
	uint8_t Y = (Line - 1) * 2;
	uint8_t X = (Column - 1) * 8;
	
	if (Front_size == 8) {
		for (i = 0; i < 2; i++) {
			// 设置光标位置在每一块的开始位置
			OLED_SetCursor(X, Y + i);
			for (j = 0; j < Front_size; j++) {
				OLED_Write(OLED_Data, OLED_F8x16[Char - ' '][i * Front_size + j]);
			}
		}
	}
	else if (Front_size == 16) {
		for (i = 0; i < 4; i++) {
			// 设置光标位置在每一块的开始位置
			OLED_SetCursor(X, Y + i);
			for (j = 0; j < Front_size; j++) {
				OLED_Write(OLED_Data, OLED_F16x32[Char - '0'][i * Front_size + j]);
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
	
	for (i = 1; i <= Length; i++) {
		showNumber = Number % 8 + '0';
		OLED_ShowChar(Line, Column + Length - i, showNumber, Front_size);
		Number /= 8;
	}
}

void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length, uint8_t Front_size) {
	uint8_t i, SingleNumber;
	
	for (i = 1; i <= Length; i++) {
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
	
	for (i = 1; i <= Length; i++) {
		showNumber = Number % 2 + '0';		
		OLED_ShowChar(Line, Column + Length - i, showNumber, Front_size);
		Number /= 2;
	}
}
