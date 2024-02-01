#include "OLED_GLib.h"
#include "Delay.h"
#include "OLED_Font.h"
#include "OLED_Instruct.h"
#include <math.h>
#if isSPIAgreement == 1
#include "SPISoftware.h"
#else
#include "I2CSoftware.h"
#endif


/* ����OLED����ʾ��С */
#if is96Screen == 1
#define OLED_GRAM_Size	 1024
#define OLED_Line				 64
#define OLED_Column			 128
#else
#define OLED_GRAM_Size	 512
#define OLED_Line				 32
#define OLED_Column			 128
#endif

uint8_t GARM[OLED_GRAM_Size];

void OLED_Write(uint8_t ComType, uint8_t Data) {
#if isSPIAgreement == 1
	/* ָ������� */
	if(ComType == OLED_Data) {
		GPIO_SetBits(GPIOB, OLED_DC_Pin);
	} else {
	  GPIO_ResetBits(GPIOB, OLED_DC_Pin);	
	}

	/* Ƭѡ���������� */
	GPIO_ResetBits(GPIOB, OLED_CS_Pin);
	SPI_Software_SwapByte(Data);
  GPIO_SetBits(GPIOB, OLED_CS_Pin);
	
	GPIO_SetBits(GPIOB, OLED_DC_Pin);
#else
	I2C_Software_StartSignal();
	
	I2C_Software_SendData(OLED_ADDRESS);	// ���ʹ�������ַ
	I2C_Software_SendData(ComType);
	I2C_Software_SendData(Data);
	
	I2C_Software_StopSignal();
#endif
}

/**
  * @brief  OLED���ù��λ��
  * @param  Y �����Ͻ�Ϊԭ�㣬���·�������꣬��Χ��0~7
  * @param  X �����Ͻ�Ϊԭ�㣬���ҷ�������꣬��Χ��0~127
  * @retval ��
  */
void OLED_SetCursor(uint8_t X,uint8_t Y) {
	OLED_Write(OLED_Command, 0xB0 | Y);					//����Yλ��
	OLED_Write(OLED_Command, 0x10 | ((X & 0xF0) >> 4));	//����Xλ�õ�4λ
	OLED_Write(OLED_Command, 0x00 | (X & 0x0F));			//����Xλ�ø�4λ
}


void OLED_GLib_Init(void) {
#if isSPIAgreement == 1
	SPI_Software_Init();
	
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
	I2C_Software_Init();
	
	Delay_ms(1000);
	
	OLED_Write(OLED_Command, Display_OFF);
#endif
	
	/* Ĭ������ */
	OLED_Write(OLED_Command, Set_Display_RefreshRate);
	OLED_Write(OLED_Command, 0xF0);
	OLED_Write(OLED_Command, Set_Display_Multiplexing);
#if is96Screen == 1
	OLED_Write(OLED_Command, 0x3F);
#else
	OLED_Write(OLED_Command, 0x1F);
#endif
	OLED_Write(OLED_Command, Set_Display_Skew);			// ������ʾƫ��
	OLED_Write(OLED_Command, 0x00);
	OLED_Write(OLED_Command, Display_Start_Line);		// ������ʾ��ʼ��
	OLED_Write(OLED_Command, Set_Display_ChargingCycle);
	OLED_Write(OLED_Command, 0xF1);
	OLED_Write(OLED_Command, Set_Display_VCOMH);
	OLED_Write(OLED_Command, 0x30);
	OLED_Write(OLED_Command, Set_Display_ChargePump);
	OLED_Write(OLED_Command, 0x14);
	OLED_Write(OLED_Command, Display_VideoMemory_ON);
	
	/* Ĭ������ */
	OLED_Write(OLED_Command, Set_Display_Luminance);	// ��������ֵ����Χ��0x00 ~ 0xFF��
	OLED_Write(OLED_Command, 0x7F);
	OLED_Write(OLED_Command, Display_Left_Right_Nomal);// ������ʾ��������ģʽ
	OLED_Write(OLED_Command, Display_Up_Down_Nomal);
	OLED_Write(OLED_Command, Display_Color_Nomal);		// ������Ļ�Ƿ�ɫ
	
	/**
    * �����Դ��ַģʽ
		* 0x00 -	ˮƽ��ַģʽ ("֮"����)
		* 0x01 - ��ֱ��ַģʽ ��"N"�ͣ�
		* 0x02 - ҳ��ַģʽ (����˳������)
		*/
	OLED_Write(OLED_Command, Display_SetAddressPattern);
	OLED_Write(OLED_Command, 0x00);
	
	/* ���������� */
	OLED_Write(OLED_Command, Set_Display_ColumnPinConfig);
#if is96Screen == 1
	OLED_Write(OLED_Command, 0x12);		// �ֱ���Ϊ128*64��0.96�磩
#else
	OLED_Write(OLED_Command, 0x02);		// �ֱ���Ϊ128*32��0.91�磩
#endif
	
	OLED_Write(OLED_Command, Display_ON);
	
	/* �����ˢ��һ���Դ� */
	OLED_ClearRam();
	OLED_RefreshRam();
}

void OLED_RefreshRam(void) {
	uint16_t k = 0;
	
	for (uint8_t Y = 0; Y < OLED_Line / 8; Y++) {
		OLED_SetCursor(0, Y);
		
		for (uint8_t X = 0; X < OLED_Column; X++) {
			OLED_Write(OLED_Data, GARM[k++]);
		}
	}
}

void OLED_RefreshRamPart(uint8_t X_start, uint8_t Y_start, uint8_t X_length, uint8_t Y_length) {
	uint8_t Y, YEnd;
	uint16_t index;
	
	Y = Y_start / 8;
	if (Y_start % 8 != 0) Y++;
	YEnd = (Y_start + Y_length) / 8;
	if ((Y_start + Y_length) % 8 != 0) YEnd++;
	
	for (; Y < YEnd; Y++) {
		OLED_SetCursor(X_start, Y);
		
		index = Y * OLED_Column + X_start;
		
		for (uint8_t X = 0; X < X_length; X++) {
			OLED_Write(OLED_Data, GARM[index + X]);
		}
	}
}

void OLED_ClearRam(void) {
	uint16_t k = 0;
	
	for (uint8_t Y = 0; Y < OLED_Line / 8; Y++) {
		OLED_SetCursor(0, Y);
		for(uint8_t X = 0; X < OLED_Column; X++) {
			OLED_Write(OLED_Data, 0x00);
			GARM[k++] = 0x00;
		}
	}
}

void OLED_ClearRamPart(uint8_t Line, uint8_t Column, uint8_t Line_length, uint8_t Column_length) {
	uint16_t index = 0;
	
	for (uint8_t Y = 0; Y < Line_length; Y++) {
		
		index = (Y + Line) * OLED_Column + Column;
		
		for (uint8_t X = 0; X < Column_length; X++) {
			GARM[index + Column + X] = 0x00;
		}
	}
}

void OLED_ReversalRamPart(uint8_t X_start, uint8_t Y_start, uint8_t X_length, uint8_t Y_length) {
	uint8_t upNoReversalLength = (Y_start < 8) ? Y_start : Y_start % 8;	// ���㿪ʼ�ĵ�һ�����鲻��Ҫ��ת�ĳ���
	uint8_t otherLength = (upNoReversalLength == 0) ? Y_length : (Y_length - 8 + upNoReversalLength);
	uint8_t otherFullBlock = otherLength / 8;		// ʣ����������
	if ((otherLength) % 8) otherFullBlock++;		// �������ְ���һ���������
	uint8_t downNoReversalLength = (Y_length - upNoReversalLength) % 8;		// �����°뷴ת�ĳ���
	if (downNoReversalLength != 0) downNoReversalLength = 8 - downNoReversalLength;

	uint16_t index = (Y_start / 8) * OLED_Column + X_start;	// ��ʼ�±�
	uint8_t mask = 0;		// ��ת����
	
//	OLED_DrawNum(1, 1, upNoReversalLength, 3);
//	OLED_DrawNum(2, 1, otherFullBlock, 3);
//	OLED_DrawNum(3, 1, downNoReversalLength, 3);
	
	if (upNoReversalLength != 0) {
		mask = ~((0x01 << upNoReversalLength) - 1);
		for (uint8_t i = 0; i <= X_length; i++) {
			GARM[index + i] ^= mask;
		}
		index += OLED_Column;
	}
	
	if (otherFullBlock != 0) {
		for (uint8_t i = 0; i < otherFullBlock; i++) {
			for (uint8_t i = 0; i <= X_length; i++) {
				GARM[index + i] = ~GARM[index + i];
			}
			index += OLED_Column;
		}
	}

	if (downNoReversalLength != 0) {
		index -= OLED_Column;
		mask = ~((0x01 << downNoReversalLength) - 1);
		for (uint8_t i = 0; i <= X_length; i++) {
			GARM[index + i] ^= mask;
		}
	}
}

void OLED_DrawPoint(uint8_t X, uint8_t Y) {
	GARM[Y / 8 * 128 + X] |= 0x01 << (Y % 8);
}

void OLED_ClearPoint(uint8_t X, uint8_t Y) {
	GARM[Y / 8 * 128 + X] &= 0xFE << (Y % 8);
}

void OLED_DrawLine(uint8_t X_start, uint8_t Y_start, uint8_t X_end, uint8_t Y_end, uint8_t step) {
	uint8_t lengthX = (X_end > X_start) ? X_end - X_start : X_start - X_end;	// x�᷽��ĳ���
	uint8_t lengthY = (Y_end > Y_start) ? Y_end - Y_start : Y_start - Y_end;	// x�᷽��ĳ���
	
	uint8_t dm = (lengthX > lengthY) ? lengthX : lengthY;
	
	float dx = (float)lengthX / dm;		// x�᷽��ÿ�εı仯��
	float dy = (float)lengthY / dm;		// x�᷽��ÿ�εı仯��
	
	float x = X_start + 0.5;	// ��֤��������
	float y = Y_start + 0.5;
	
	for (uint8_t i = 0; i <= dm; i++) {
		if (!(i % step)) {
			OLED_DrawPoint(x, y);
		}
		
		x += dx;
		y += dy;
	}
}

void OLED_ClearLine(uint8_t X_start, uint8_t Y_start, uint8_t X_end, uint8_t Y_end, uint8_t step) {
	uint8_t lengthX = (X_end > X_start) ? X_end - X_start : X_start - X_end;	// x�᷽��ĳ���
	uint8_t lengthY = (Y_end > Y_start) ? Y_end - Y_start : Y_start - Y_end;	// x�᷽��ĳ���
	
	uint8_t dm = (lengthX > lengthY) ? lengthX : lengthY;
	
	float dx = (float)lengthX / dm;		// x�᷽��ÿ�εı仯��
	float dy = (float)lengthY / dm;		// x�᷽��ÿ�εı仯��
	
	float x = X_start + 0.5;	// ��֤��������
	float y = Y_start + 0.5;
	
	for (uint8_t i = 0; i <= dm; i++) {
		if (!(i % step)) {
			OLED_ClearPoint(x, y);
		}
		
		x += dx;
		y += dy;
	}
}

void OLED_DrawRectangle(uint8_t X_start, uint8_t Y_start, uint8_t X_length, uint8_t Y_length, uint8_t wide) {
	if (wide == 1) {
		OLED_DrawLine(X_start, Y_start, X_start + X_length, Y_start, 1);
		OLED_DrawLine(X_start, Y_start, X_start, Y_start + Y_length, 1);
		OLED_DrawLine(X_start + X_length, Y_start, X_start + X_length, Y_start + Y_length, 1);
		OLED_DrawLine(X_start, Y_start + Y_length, X_start + X_length, Y_start + Y_length, 1);
	} else {
		/* ���ƺ���߿� */
		for (uint8_t i = 0; i <= X_length; i++) {
			OLED_DrawLine(X_start + i, Y_start, X_start + i, Y_start + wide, 1);
			OLED_DrawLine(X_start + i, Y_length - wide, X_start + i, Y_length, 1);
		}
		/* ��������߿� */
		for (uint8_t i = 0; i <= Y_length - wide * 2; i++) {
			OLED_DrawLine(X_start, Y_start + wide + i, X_start + wide, Y_start + wide + i, 1);
			OLED_DrawLine(X_start + X_length - wide, Y_start + wide + i, X_start + X_length, Y_start + wide + i, 1);
		}
	}
}

void OLED_DrawCircle(uint8_t X_center, uint8_t Y_center, uint8_t radius, uint8_t wide) {
	uint8_t x0 = 0;
	uint8_t y0 = radius;
	int8_t d = 3 - 2 * radius;
	
	while (x0 <= y0) {
		if (wide == 1) {
			/* �������ӡ˳�� */
			OLED_DrawPoint(X_center + y0, Y_center - x0);
			OLED_DrawPoint(X_center + x0, Y_center - y0);
			OLED_DrawPoint(X_center - x0, Y_center - y0);
			OLED_DrawPoint(X_center - y0, Y_center - x0);
			OLED_DrawPoint(X_center - y0, Y_center + x0);
			OLED_DrawPoint(X_center - x0, Y_center + y0);
			OLED_DrawPoint(X_center + x0, Y_center + y0);
			OLED_DrawPoint(X_center + y0, Y_center + x0);
		} else {
			/* �������ӡ˳�� */
			OLED_DrawLine(X_center + y0 - wide, Y_center - x0, X_center + y0, Y_center - x0, 1);
			OLED_DrawLine(X_center + x0, Y_center - y0, X_center + x0, Y_center - y0 + wide, 1);
			OLED_DrawLine(X_center - x0, Y_center - y0, X_center - x0, Y_center - y0 + wide, 1);
			OLED_DrawLine(X_center - y0, Y_center - x0, X_center - y0 + wide, Y_center - x0, 1);
			OLED_DrawLine(X_center - y0, Y_center + x0, X_center - y0 + wide, Y_center + x0, 1);
			OLED_DrawLine(X_center - x0, Y_center + y0 - wide, X_center - x0, Y_center + y0, 1);
			OLED_DrawLine(X_center + x0, Y_center + y0 - wide, X_center + x0, Y_center + y0, 1);
			OLED_DrawLine(X_center + y0 - wide, Y_center + x0, X_center + y0, Y_center + x0, 1);
		}
		
		if (d < 0) {
			d += 4 * x0 + 6;
		} else {
			d += 4 * (x0 - y0) + 10;
			y0--;
		}
		x0++;
	}
}

void OLED_DrawEllipse(uint8_t X_center, uint8_t Y_center, uint8_t X_radius, uint8_t Y_radius) {
	double Rad, x0, y0;
	
	for (uint16_t angle = 0; angle < 360; angle++) {
		Rad = angle * 3.14 / 180;
		
		x0 = X_radius * cos(Rad);
		y0 = Y_radius * sin(Rad);
		
		OLED_DrawPoint(X_center + x0, Y_center + y0);
	}
}

void OLED_DrawRoundedRectangle(uint8_t X_start, uint8_t Y_start, uint8_t X_length, uint8_t Y_length, uint8_t radius, uint8_t wide) {
	uint8_t A, B, C, D;
	uint8_t x0 = 0;
	uint8_t y0 = radius;
	int8_t d = 3 - 2 * radius;

	if (radius * 2 > X_length || radius * 2 > Y_length)
		radius = (X_length > Y_length) ? (Y_length / 2) : (X_length / 2);
	if (wide > radius)
		wide = radius;

	/** �ĸ�����ֵ������γɲ�ֺ���ĸ�Բ��Բ������
			����Բ�����꣨B, A��
			����Բ�����꣨C, A��
			����Բ�����꣨B, D��
			����Բ�����꣨C, D��
	*/	
	A = Y_start + radius;
	B = X_start + radius;
	C = X_start + X_length - radius;
	D = Y_start + Y_length - radius;
	
	while (x0 <= y0) {
		if (wide == 1) {
			/* �������ӡ˳�� */
			OLED_DrawPoint(C + y0, A - x0);
			OLED_DrawPoint(C + x0, A - y0);
			OLED_DrawPoint(B - x0, A - y0);
			OLED_DrawPoint(B - y0, A - x0);
			OLED_DrawPoint(B - y0, D + x0);
			OLED_DrawPoint(B - x0, D + y0);
			OLED_DrawPoint(C + x0, D + y0);
			OLED_DrawPoint(C + y0, D + x0);
		} else {
			/* �������ӡ˳�� */
			OLED_DrawLine(C + y0 - wide, A - x0, C + y0, A - x0, 1);
			OLED_DrawLine(C + x0, A - y0, C + x0, A - y0 + wide, 1);
			OLED_DrawLine(B - x0, A - y0, B - x0, A - y0 + wide, 1);
			OLED_DrawLine(B - y0, A - x0, B - y0 + wide, A - x0, 1);
			OLED_DrawLine(B - y0, D + x0, B - y0 + wide, D + x0, 1);
			OLED_DrawLine(B - x0, D + y0 - wide, B - x0, D + y0, 1);
			OLED_DrawLine(C + x0, D + y0 - wide, C + x0, D + y0, 1);
			OLED_DrawLine(C + y0 - wide, D + x0, C + y0, D + x0, 1);
		}
		
		if (d < 0) {
			d += 4 * x0 + 6;
		} else {
			d += 4 * (x0 - y0) + 10;
			y0--;
		}
		x0++;
	}
	
	for (int i = 0; i < wide; i++) {
		OLED_DrawLine(B, A - radius + i, C, A - radius + i, 1);
		OLED_DrawLine(C + radius - i, A, C + radius - i, D, 1);
		OLED_DrawLine(B, D + radius - i, C, D + radius - i, 1);
		OLED_DrawLine(B - radius + i, A, B - radius + i, D, 1);
	}
}

//// ���ƶ�̬����ͼ��ѭ�����з�����
//void OLED_ShowDynamicData(uint32_t data, uint32_t data_Max) {
//	float scale = (float)(OLED_Line -1) / data_Max;
//	
//	for (uint8_t i = OLED_Column - 1; i > 0; i--) {
//		for (uint8_t j = 0; j < 8; j++) {
//			GARM[j * OLED_Column + i] = GARM[j * OLED_Column + i - 1];
//		}
//	}
//}

void OLED_DrawImg(uint8_t X, uint8_t Y, uint8_t img_Length, uint8_t img_High, Image* image) {
	uint8_t errValue = Y % 8;									// ���㵥����ʾ��Ԫ����8���ص���������ƫ�����
	uint8_t totalHigh = img_High + errValue;		// ͼƬʵ�ʸ߶�
	uint8_t temp = 0x00;											// ƫ��������ʱ����
	
	uint8_t scanLineStart = Y / 8;						// ����Y�᷽��Ӽ��п�ʼ
	uint8_t scanLine = totalHigh / 8 + ((totalHigh % 8) ? 1 : 0);	// ����Y�᷽����Ҫɨ�輸��
	
	uint16_t GARMIndeInit = scanLineStart * OLED_Column + X;
	uint16_t GARMInde = GARMIndeInit;		// �����������ʽ��(i + scanLineStart) * 128 + j + X
	uint16_t imgInde = 0;								// ͼƬ�������ʽ��i * imgLength + j
	
	for (uint8_t j = 0; j < img_Length; j++) {
		GARMInde += j;
		imgInde += j;
		
		for (uint8_t i = 0; i < scanLine; i++) {			
			GARM[GARMInde] = temp | (image[imgInde] << errValue);
			temp = image[imgInde] >> (8 - errValue);
			
			GARMInde += 128;
			imgInde += img_Length;
		}
		GARMInde = GARMIndeInit;
		imgInde = 0;
	}
}

/**
  * @brief �����ܶȵ�Ԫ��2*2��
  * @param (x, y) Ҫ�����ĵ�Ԫ����
	*						����������������
  * 				 | (0,0) | (1,0) |
	*						����������������
  * 				 | (0,1) | (1,1) |
	*						����������������
  * @return ��
  */
void OLED_DensityUnit(uint8_t x, uint8_t y, uint8_t* image) {
	for (uint8_t i = y; i < OLED_Line; i += 2) {
		for(uint8_t j = x; j < OLED_Column; j += 2) {
			GARM[i / 8 * 128 + j] |= ((0x01 << (i % 8)) & image[i / 8 * 128 + j]);
		}
	}
}

void OLED_SetDensity(ShowPercent percent) {
	if (percent == Zero_Percent) {
			return;
	}
	
	uint8_t GGARM[OLED_GRAM_Size];
	
	for (uint16_t i = 0; i < OLED_GRAM_Size; i++) {
		GGARM[i] = GARM[i];
		GARM[i] = 0x00;
	}
	
	switch((uint8_t) percent) {
		case 1:
			OLED_DensityUnit(0, 0, GGARM);
			break;
		case 2:
			OLED_DensityUnit(0, 0, GGARM);
			OLED_DensityUnit(1, 1, GGARM);
			break;
		case 3:
			OLED_DensityUnit(0, 0, GGARM);
			OLED_DensityUnit(1, 0, GGARM);
			OLED_DensityUnit(1, 1, GGARM);
			break;
		case 4:
			OLED_DensityUnit(0, 0, GGARM);
			OLED_DensityUnit(1, 0, GGARM);
			OLED_DensityUnit(0, 1, GGARM);
			OLED_DensityUnit(1, 1, GGARM);
			break;
	}
}

void OLED_DrawChar(uint8_t Line, uint8_t Column, char Char, uint8_t Front_size) {
	uint16_t index = (Line - 1)* 2 * OLED_Column + (Column - 1) * Front_size;
	
	if (Front_size == 8) {
		for (uint8_t Y = 0; Y < 2; Y++) {
			for (uint8_t X = 0; X < 8; X++) {
				GARM[index + X] = OLED_F8x16[Char - ' '][Y * Front_size + X];
			}
			index += OLED_Column;
		}
	} else {
		for (uint8_t Y = 0; Y < 4; Y++) {
			for (uint8_t X = 0; X < Front_size; X++) {
				GARM[index + X] = OLED_F16x32[Char - '0'][Y * Front_size + X];
			}
			index += OLED_Column;
		}		
	}
}


void OLED_DrawString(uint8_t Line, uint8_t Column, char* String, uint8_t Front_size) {
	for (uint8_t i = 0; String[i] != '\0'; i++) {
		OLED_DrawChar(Line, Column + i, String[i], Front_size);
	}
}

void OLED_DrawNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length, uint8_t Front_size) {
	uint8_t i;
	char showNumber;
	
	if (Number < 0) {
		OLED_DrawChar(Line, Column, '-', 8);
		Number = -Number;
		Column++;
	}
	
	for (i = 1; i <= Length; i++) {
		showNumber = Number % 10 + '0';
		OLED_DrawChar(Line, Column + Length - i, showNumber, Front_size);
		Number /= 10;
	}
}

void OLED_DrawSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length, uint8_t Front_size) {
	uint8_t i;
	char showNumber;
	
	if (Number < 0) {
		OLED_DrawChar(Line, Column, '-', 8);
		Number = -Number;
		Column++;
	}
	
	for (i = 1; i <= Length; i++) {
		showNumber = Number % 8 + '0';
		OLED_DrawChar(Line, Column + Length - i, showNumber, Front_size);
		Number /= 8;
	}
}

void OLED_DrawHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length, uint8_t Front_size) {
	uint8_t i, SingleNumber;
	
	for (i = 1; i <= Length; i++) {
		SingleNumber = Number % 16;
		if (SingleNumber < 10) {
			OLED_DrawChar(Line, Column + Length - i, SingleNumber + '0', Front_size);
		} else {
			OLED_DrawChar(Line, Column + Length - i, SingleNumber - 10 + 'A', Front_size);
		}
		Number /= 16;
	}
}

void OLED_DrawBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length, uint8_t Front_size) {
	uint8_t i;
	char showNumber;
	
	for (i = 1; i <= Length; i++) {
		showNumber = Number % 2 + '0';		
		OLED_DrawChar(Line, Column + Length - i, showNumber, Front_size);
		Number /= 2;
	}
}
