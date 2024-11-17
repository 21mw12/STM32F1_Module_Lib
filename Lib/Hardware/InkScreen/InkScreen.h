#ifndef __INK_SCREEN_H_
#define __INK_SCREEN_H_

///////////////////////////////////////////////////////////
//
// �ļ����ܣ��о�԰1.54����ɫīˮ����������
// ���ߣ��о�԰���ӣ�����ֻ�����˵Ķ�����Ⲣת��Ϊ���˵Ĵ����񣡣�����
// �޸�ʱ�䣺2024/11/17
//
//	��������(3.3V)��
//			SCL -- SPI_CLK
//			SDA -- SPI_MOSI
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* �˿���Ϣ */
#define Ink_Screen_GPIOPeriph			RCC_APB2Periph_GPIOA
#define Ink_Screen_Port						GPIOA
#define Ink_Screen_Pin_RES				GPIO_Pin_2
#define Ink_Screen_Pin_DC					GPIO_Pin_3
#define Ink_Screen_Pin_CS					GPIO_Pin_4
#define Ink_Screen_Pin_BUSY				GPIO_Pin_5

/* �ں�����ͼ�� */
#define CanvasLayer					uint8_t
extern CanvasLayer InkScreen_BlackLayer[];	// ��ɫͼ�� 
extern CanvasLayer InkScreen_RedLayer[];		// ��ɫͼ��

/* ͼ���Ƿ���ɫ */ 
#define CanvasColourType		uint16_t
extern CanvasColourType CANVAS_Colourless;	// ��ɫ	
extern CanvasColourType CANVAS_Coloured;		// ��ɫ

/* E-Paper��ʾ����(��ѡ0/90/180/270) */
#define Rotation 		0

/**
  * @brief īˮ����ʼ��
  * @return ��
  */
void InkScreen_Init(void);

/**
  * @brief ����īˮ��
  * @return ��
  */
void InkScreen_Wakeup(void);

/**
  * @brief īˮ���������˯��
  * @return ��
  */
void InkScreen_DeepSleep(void);

/**
  * @brief īˮ������
  * @return ��
  */
void InkScreen_Clear(void);

/**
  * @brief īˮ��ˢ����ʾ
  * @param imageBW �ڰ�ͼ��
  * @param imageR ��ɫͼ��
  * @return ��
  */
void InkScreen_Display(void);


/*****************************************�������ƺ���************************************************/

/**
  * @brief īˮ��ѡ��ͼ��
  * @param layer ָ��ͼ�㣨��ѡInkScreen_BlackLayer��InkScreen_RedLayer��
  * @return ��
  */
void InkScreen_SelectLayer(CanvasLayer *layer);

/**
  * @brief īˮ�����ͼ��
  * @return ��
  */
void InkScreen_LayerClear(void);

/**
  * @brief ��һ����
  * @param Xpoint x����
  * @param Ypoint y����
  * @param ColorType �Ƿ���ɫ
  * @return ��
  */
void InkScreen_DrawPoint(uint8_t X, uint8_t Y, CanvasColourType ColorType);

/**
  * @brief ��һ����
  * @param X_start �߶˿�ʼ��x����
  * @param Y_start �߶˿�ʼ��y����
  * @param X_end �߶˽�����x����
  * @param Y_end �߶˽�����y����
  * @param step �����߶˵Ĳ���
  * @param ColorType �Ƿ���ɫ
  * @return ��
	*
	* ע; ֻ�ܻ��ƴ���Ļ��ߵ���Ļ�ұߵ��߶Σ����ܷ��Ż�������
  */
void InkScreen_DrawLine(uint8_t X_start, uint8_t Y_start, uint8_t X_end, uint8_t Y_end, uint8_t step, CanvasColourType ColorType);

/**
  * @brief ������
  * @param X_start ���ο�ʼ��x����
  * @param Y_start ���ο�ʼ��y����
  * @param X_length ����x�᷽���ϵĳ���
  * @param Y_length ����y�᷽���ϵĳ���
  * @param wide ���
  * @param ColorType �Ƿ���ɫ
  * @return ��
  */
void InkScreen_DrawRectangle(uint8_t X_start, uint8_t Y_start, uint8_t X_length, uint8_t Y_length, uint8_t wide, CanvasColourType ColorType);

/**
  * @brief ��Բ
  * @param X_center Բ�ĵ�x����
  * @param Y_center Բ�ĵ�y����
  * @param radius �뾶
  * @param wide ���
  * @param ColorType �Ƿ���ɫ
  * @return ��
  */
void InkScreen_DrawCircle(uint8_t X_center, uint8_t Y_center, uint8_t radius, uint8_t wide, CanvasColourType ColorType);

/**
  * @brief ��ͼƬ
  * @param X ͼƬ��x�������
  * @param Y ͼƬ��y�������
  * @param wide ͼƬ���
  * @param high ͼƬ�߶�
  * @param picture ͼƬ��������
  * @param ColorType �Ƿ���ɫ
  * @return ��
  */
void InkScreen_DrawPicture(uint16_t X, uint16_t Y, uint16_t wide, uint16_t high, const uint8_t picture[], CanvasColourType ColorType);

/**
  * @brief ���ַ�
  * @param X �ַ���x�������
  * @param Y �ַ���y�������
  * @param Char Ҫ���Ƶ��ַ�
  * @param Front_size �ַ���С
  * @param ColorType �Ƿ���ɫ
  * @return ��
  */
void InkScreen_DrawChar(uint8_t X, uint8_t Y, char Char, uint8_t Front_size, CanvasColourType ColorType);

/**
  * @brief ���ַ���
  * @param X �ַ�����x�������
  * @param Y �ַ�����y�������
  * @param String Ҫ���Ƶ��ַ���
  * @param Front_size �ַ�����С
  * @param ColorType �Ƿ���ɫ
  * @return ��
  */
void InkScreen_DrawString(uint8_t X, uint8_t Y, char* String, uint8_t Front_size, CanvasColourType ColorType);

/**
  * @brief ������
  * @param X ���ֵ�x�������
  * @param Y ���ֵ�y�������
  * @param Num Ҫ���Ƶ�����
  * @param Len ���ֳ���
  * @param Front_size ���ִ�С
  * @param ColorType �Ƿ���ɫ
  * @return ��
  */
void InkScreen_DrawNum(uint8_t X, uint8_t Y,uint32_t Num, uint16_t Len, uint8_t Front_size, CanvasColourType ColorType);

/**
  * @brief ������
  * @param X ���ֵ�x�������
  * @param Y ���ִ���y�������
  * @param Chinese Ҫ���Ƶĺ���
  * @param Front_size ���ִ�С
  * @param ColorType �Ƿ���ɫ
  * @return ��
  */
void InkScreen_DrawChinese(uint8_t X, uint8_t Y, uint8_t* Chinese, uint8_t Front_size, CanvasColourType ColorType);


#endif
