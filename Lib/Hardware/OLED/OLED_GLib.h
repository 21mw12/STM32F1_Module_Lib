#ifndef __OLED_GLIB_H
#define __OLED_GLIB_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�OLEDͼ�ο�
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/0
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
#include "OLED.h"

/* ����OLED����ʾ��С */
#define OLED_GRAM_Size	 1024
#define OLED_Line				 64
#define OLED_Column			 128

typedef enum {
	Empty = 0,
	Fill
} FillPattern;

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
  */
void OLED_RefreshRamPart(uint8_t X_start, uint8_t Y_start, uint8_t X_length, uint8_t Y_length);

/**
  * @brief  OLED����
  * @return ��
  */
void OLED_Clear(void);

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
  * @param pattern �ڲ��Ƿ����
  * @return ��
  */
void OLED_DrawRectangle(uint8_t X_start, uint8_t Y_start, uint8_t X_length, uint8_t Y_length, FillPattern pattern);

/**
  * @brief ��Բ
  * @param X_center Բ�ĵ�x����
  * @param Y_center Բ�ĵ�y����
  * @param radius �뾶
  * @param pattern �ڲ��Ƿ����
  * @return ��
  */
void OLED_DrawCircle(uint8_t X_center, uint8_t Y_center, uint8_t radius, FillPattern pattern);

/**
  * @brief ����Բ
  * @param X_start ���ο�ʼ��x����
  * @param Y_start ���ο�ʼ��y����
  * @param X_end ����x�᷽���ϵĳ���
  * @param Y_end ����y�᷽���ϵĳ���
  * @param pattern �ڲ��Ƿ����
  * @return ��
  */
void OLED_DrawEllipse(uint8_t X_center, uint8_t Y_center, uint8_t X_radius, uint8_t Y_radius, FillPattern pattern);

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
  * @brief ����ͼƬ��ʾ�ɰ�
  * @param percent ��ʾ�ٷֱ�
  * @return ��
  */
void OLED_SetDensity(ShowPercent percent);

/**
  * @brief ��ʾͼƬ
  * @param X ��ʾͼƬ��x����ʼλ��
  * @param Y ��ʾͼƬ��y����ʼλ��
  * @param img_Length ��ʾͼƬ�ĳ��ȣ�x����
  * @param img_High ��ʾͼƬ�ĸ߶ȣ�y����
  * @param image ��ʾ��ͼƬ
  * @return ��
  */
void OLED_ShowImg(uint8_t X, uint8_t Y, uint8_t img_Length, uint8_t img_High, uint8_t* image);

#endif
