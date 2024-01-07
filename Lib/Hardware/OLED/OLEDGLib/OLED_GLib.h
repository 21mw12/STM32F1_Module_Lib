#ifndef __OLED_GLIB_H
#define __OLED_GLIB_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�OLEDͼ�ο�
// �汾��V2.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/01/07
//
// ˼·��ԴBվup��������������һ����OLED��Ļ��(BV18h411K7MZ)
// ����������Ƶ�й��ܵ�ʵ�֣��Լ�����˸���Ĺ���
//
// ������˵��
//			-------------------> x�᷽��
//		|
//		|		    OLED��Ļ
//	  |
//	  ��
//   y�᷽��
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "I2C1Hardware.h"

/* OLED I2C��ַ */
#define OLED_ADDRESS			0x78

/* ����OLED����ʾ��С */
#define OLED_GRAM_Size	 1024
#define OLED_Line				 64
#define OLED_Column			 128

/* OLED�޸ĵײ�I2C����ʱ��Ҫ�޸�Ϊ��Ӧ�ĺ��� */
#define OLED_Write			I2C1_Hardware_SendByte


#define Image const uint8_t

typedef enum {
	Zero_Percent = 0,		// 0%ռ��
	TwentyFive_Percent,	// 25%ռ��
	Fifty_Percent,			// 50%ռ��
	SeventyFive_Percent,// 75%ռ��
	Hundred_Percent			// 100%ռ��
} ShowPercent;

/**
  * @brief  OLED��ͼ��ʼ��
  * @return ��
  */
void OLED_GLib_Init(void);

/**
  * @brief  OLEDˢ���Դ�
  * @return ��
  */
void OLED_RefreshRam(void);

/**
  * @brief  OLEDˢ�²����Դ�
  * @param X_start ˢ������ʼ��x����
  * @param Y_start ˢ������ʼ��y����
  * @param X_length ˢ������x�᷽���ϵĳ���
  * @param Y_length ˢ������y�᷽���ϵĳ���
  * @return ��
	* ע������Y�����ˢ��8�����������Բ����������Ļ�ǿ�Ʋ���
  */
void OLED_RefreshRamPart(uint8_t X_start, uint8_t Y_start, uint8_t X_length, uint8_t Y_length);

/**
  * @brief  OLED������л�������
  * @return ��
  */
void OLED_RamClear(void);

/**
  * @brief ��һ����
  * @param X x����
  * @param Y y����
  * @return ��
  */
void OLED_DrawPoint(uint8_t X, uint8_t Y);

/**
  * @brief ���һ����
  * @param X x����
  * @param Y y����
  * @return ��
  */
void OLED_ClearPoint(uint8_t X, uint8_t Y);

/**
  * @brief ��һ����
  * @param X_start �߶˿�ʼ��x����
  * @param Y_start �߶˿�ʼ��y����
  * @param X_end �߶˽�����x����
  * @param Y_end �߶˽�����y����
  * @param step �����߶˵Ĳ���
  * @return ��
	*
	* ע; ֻ�ܻ��ƴ���Ļ��ߵ���Ļ�ұߵ��߶Σ����ܷ��Ż�������
  */
void OLED_DrawLine(uint8_t X_start, uint8_t Y_start, uint8_t X_end, uint8_t Y_end, uint8_t step);

/**
  * @brief ���һ����
  * @param X_start �߶˿�ʼ��x����
  * @param Y_start �߶˿�ʼ��y����
  * @param X_end �߶˽�����x����
  * @param Y_end �߶˽�����y����
  * @param step ����߶˵Ĳ���
	*
	* ע; ֻ�ܻ��ƴ���Ļ��ߵ���Ļ�ұߵ��߶Σ����ܷ��Ż�������
  * @return ��
  */
void OLED_ClearLine(uint8_t X_start, uint8_t Y_start, uint8_t X_end, uint8_t Y_end, uint8_t step);

/**
  * @brief ������
  * @param X_start ���ο�ʼ��x����
  * @param Y_start ���ο�ʼ��y����
  * @param X_length ����x�᷽���ϵĳ���
  * @param Y_length ����y�᷽���ϵĳ���
  * @param wide ���
  * @return ��
  */
void OLED_DrawRectangle(uint8_t X_start, uint8_t Y_start, uint8_t X_length, uint8_t Y_length, uint8_t wide);

/**
  * @brief ��Բ
  * @param X_center Բ�ĵ�x����
  * @param Y_center Բ�ĵ�y����
  * @param radius �뾶
  * @param wide ���
  * @return ��
  */
void OLED_DrawCircle(uint8_t X_center, uint8_t Y_center, uint8_t radius, uint8_t wide);

/**
  * @brief ����Բ
  * @param X_start ���ο�ʼ��x����
  * @param Y_start ���ο�ʼ��y����
  * @param X_end ����x�᷽���ϵĳ���
  * @param Y_end ����y�᷽���ϵĳ���
  * @return ��
  */
void OLED_DrawEllipse(uint8_t X_center, uint8_t Y_center, uint8_t X_radius, uint8_t Y_radius);

/**
  * @brief ��Բ�Ǿ���
  * @param X_start ���ο�ʼ��x����
  * @param Y_start ���ο�ʼ��y����
  * @param X_length ����x�᷽���ϵĳ���
  * @param Y_length ����y�᷽���ϵĳ���
  * @param radius �뾶
  * @param wide ���
  * @return ��
  */
void OLED_DrawRoundedRectangle(uint8_t X_start, uint8_t Y_start, uint8_t X_length, uint8_t Y_length, uint8_t radius, uint8_t wide);

/**
  * @brief ��ʾͼƬ
  * @param X ��ʾͼƬ��x����ʼλ��
  * @param Y ��ʾͼƬ��y����ʼλ��
  * @param img_Length ��ʾͼƬ�ĳ��ȣ�x����
  * @param img_High ��ʾͼƬ�ĸ߶ȣ�y����
  * @param image ��ʾ��ͼƬ
  * @return ��
  */
void OLED_DrawImg(uint8_t X, uint8_t Y, uint8_t img_Length, uint8_t img_High, Image* image);

/**
  * @brief ����ͼƬ��ʾ�ɰ�
  * @param percent ��ʾ�ٷֱ�
  * @return ��
  */
void OLED_SetDensity(ShowPercent percent);

/**
  * @brief  OLED����һ���ַ�
  * @param  Line ��λ��
  * @param  Column ��λ��
  * @param  Char Ҫ��ʾ��һ���ַ�����Χ��ASCII�ɼ��ַ�
  * @retval ��
  */
void OLED_DrawChar(uint8_t Line, uint8_t Column, char Char);

/**
  * @brief  OLED�����ַ���
  * @param  Line ��ʼ��λ��
  * @param  Column ��ʼ��λ��
  * @param  String Ҫ��ʾ���ַ�������Χ��ASCII�ɼ��ַ�
  * @retval ��
  */
void OLED_DrawString(uint8_t Line, uint8_t Column, char *String);

/**
  * @brief  OLED�������֣�ʮ���ƣ�����������
  * @param  Line ��ʼ��λ��
  * @param  Column ��ʼ��λ��
  * @param  Number Ҫ��ʾ�����֣���Χ��0~4294967295
  * @param  Length Ҫ��ʾ���ֵĳ��ȣ���Χ��1~10
  * @param  Front_size �ַ��Ĵ�С��8��8*16��С  16: 16*32��С
  * @retval ��
  */
void OLED_DrawNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);

/**
  * @brief  OLED�������֣��˽��ƣ�����������
  * @param  Line ��ʼ��λ��
  * @param  Column ��ʼ��λ��
  * @param  Number Ҫ��ʾ�����֣���Χ��-2147483648~2147483647
  * @param  Length Ҫ��ʾ���ֵĳ��ȣ���Χ��1~10
  * @param  Front_size �ַ��Ĵ�С��8��8*16��С  16: 16*32��С
  * @retval ��
  */
void OLED_DrawSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);

/**
  * @brief  OLED�������֣�ʮ�����ƣ�������
  * @param  Line ��ʼ��λ��
  * @param  Column ��ʼ��λ��
  * @param  Number Ҫ��ʾ�����֣���Χ��0~0xFFFFFFFF
  * @param  Length Ҫ��ʾ���ֵĳ��ȣ���Χ��1~8
  * @param  Front_size �ַ��Ĵ�С��8��8*16��С  16: 16*32��С
  * @retval ��
  */
void OLED_DrawHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

/**
  * @brief  OLED�������֣������ƣ�������
  * @param  Line ��ʼ��λ�ã���Χ��1~4
  * @param  Column ��ʼ��λ�ã���Χ��1~16
  * @param  Number Ҫ��ʾ�����֣���Χ��0~1111 1111 1111 1111
  * @param  Length Ҫ��ʾ���ֵĳ��ȣ���Χ��1~16
  * @param  Front_size �ַ��Ĵ�С��8��8*16��С  16: 16*32��С
  * @retval ��
  */
void OLED_DrawBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

#endif

///////////////////////////////////////////////////////////
//
// ������־��
// V1.0: 2023/12/27
//				ʵ����OLED�Ļ�����ͼ����
// V2.0: 2024/01/07
//				�����µ�I2Cԭ�ӻ��ع��˵ײ����
//
///////////////////////////////////////////////////////////
