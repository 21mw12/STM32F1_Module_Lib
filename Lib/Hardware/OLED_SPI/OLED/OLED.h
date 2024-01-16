#ifndef __OLED_H
#define __OLED_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�ʹ��SPIЭ���OLED��������ʵ��
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2024/01/16
//
// ����˵����
//		D0Ϊʱ�����ţ������Ӧ��Ӳ��SPI��SCK������
// 		D1Ϊ�������ţ������Ӧ��Ӳ��SPI��MOSI������
// 		RESΪ�������ţ������û��Զ���
// 		DCΪ��������ѡ�����ţ������û��Զ���
// 		CSΪƬѡ���ţ������û��Զ���
//
// Ӳ��SPIģʽ��SPIģʽ0����λ����
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* OLED����������Ϣ */
#define OLED_Periph		RCC_APB2Periph_GPIOB
#define OLED_PORT			GPIOB
#define OLED_PIN_DC 	GPIO_Pin_10
#define OLED_PIN_RES 	GPIO_Pin_11
#define OLED_PIN_CS 	GPIO_Pin_12

/**
  * @brief  OLED��ʼ��
  * @param  ��
  * @retval ��
  */
void OLED_Init(void);

/**
  * @brief  OLED����
  * @param  ��
  * @retval ��
  */
void OLED_Clear(void);

/**
  * @brief  OLED��ʾһ���ַ�
  * @param  Line ��λ��
  * @param  Column ��λ��
  * @param  Char Ҫ��ʾ��һ���ַ�����Χ��ASCII�ɼ��ַ�
  * @param  Front_size �ַ��Ĵ�С��8��8*16��С  16: 16*32��С
  * @retval ��
  */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char, uint8_t Front_size);

/**
  * @brief  OLED��ʾ�ַ���
  * @param  Line ��ʼ��λ��
  * @param  Column ��ʼ��λ��
  * @param  String Ҫ��ʾ���ַ�������Χ��ASCII�ɼ��ַ�
  * @param  Front_size �ַ��Ĵ�С��8��8*16��С  16: 16*32��С
  * @retval ��
  */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String, uint8_t Front_size);

/**
  * @brief  OLED��ʾ���֣�ʮ���ƣ�����������
  * @param  Line ��ʼ��λ��
  * @param  Column ��ʼ��λ��
  * @param  Number Ҫ��ʾ�����֣���Χ��0~4294967295
  * @param  Length Ҫ��ʾ���ֵĳ��ȣ���Χ��1~10
  * @param  Front_size �ַ��Ĵ�С��8��8*16��С  16: 16*32��С
  * @retval ��
  */
void OLED_ShowNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length, uint8_t Front_size);

/**
  * @brief  OLED��ʾ���֣��˽��ƣ�����������
  * @param  Line ��ʼ��λ��
  * @param  Column ��ʼ��λ��
  * @param  Number Ҫ��ʾ�����֣���Χ��-2147483648~2147483647
  * @param  Length Ҫ��ʾ���ֵĳ��ȣ���Χ��1~10
  * @param  Front_size �ַ��Ĵ�С��8��8*16��С  16: 16*32��С
  * @retval ��
  */
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length, uint8_t Front_size);

/**
  * @brief  OLED��ʾ���֣�ʮ�����ƣ�������
  * @param  Line ��ʼ��λ��
  * @param  Column ��ʼ��λ��
  * @param  Number Ҫ��ʾ�����֣���Χ��0~0xFFFFFFFF
  * @param  Length Ҫ��ʾ���ֵĳ��ȣ���Χ��1~8
  * @param  Front_size �ַ��Ĵ�С��8��8*16��С  16: 16*32��С
  * @retval ��
  */
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length, uint8_t Front_size);

/**
  * @brief  OLED��ʾ���֣������ƣ�������
  * @param  Line ��ʼ��λ�ã���Χ��1~4
  * @param  Column ��ʼ��λ�ã���Χ��1~16
  * @param  Number Ҫ��ʾ�����֣���Χ��0~1111 1111 1111 1111
  * @param  Length Ҫ��ʾ���ֵĳ��ȣ���Χ��1~16
  * @param  Front_size �ַ��Ĵ�С��8��8*16��С  16: 16*32��С
  * @retval ��
  */
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length, uint8_t Front_size);

#endif
