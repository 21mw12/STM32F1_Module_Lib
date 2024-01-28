#ifndef __OLED_H
#define __OLED_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�֧��2��Э���OLED��������ʵ��
// �汾��V5.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2024/01/28
//
// SPI����ģ������˵����
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

/**
  * �Ƿ�ʹ��SPI����
	*  1��ʾʹ��SPI����
	*  0��ʾʹ��I2C����
	* ע��������������Ĭ��ʹ�����ģ��
	*/
#define isSPIAgreement		1

#if isSPIAgreement == 1
/* OLED SPI��������������Ϣ */
#define OLED_Periph		RCC_APB2Periph_GPIOB
#define OLED_Port			GPIOB
#define OLED_DC_Pin 	GPIO_Pin_10
#define OLED_RES_Pin 	GPIO_Pin_11
#define OLED_CS_Pin 	GPIO_Pin_12
#else
/* OLED I2C����������ַ */
#define OLED_ADDRESS			0x78
#endif

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

///////////////////////////////////////////////////////////
//
// ������־��
// V1.0: 2023/04/26
//				ʵ����OLED�Ļ�����ʾ
// V1.1: 2023/04/27
//				�޸�����ʾ���16*32�ַ����ص���bug
//				�޸���16*32��"8"���ַ��Ᵽ֤�����ַ�һ����С
// V2.0: 2023/07/07
//				�����ع���I2C��ѡ��Ӳ��I2C��Ϊ�ײ��
// V3.0: 2023/12/27
//				����ͨ��ʾ��ͼ�ο��������Ƹ���I2C������ķ�ʽ
// V3.1: 2023/12/28
//				�޸�������ʱ����ֵĻ���Bug
// V4.0: 2024/01/06
//				�����µ�I2Cԭ�ӻ��ع��˵ײ����
//				�޸���16������ʾ�����Bug
// V5.0: 2024/01/28
//				�ϲ���SPIЭ�飬�����Լ򵥵�Э������Э��ʹ��
//
///////////////////////////////////////////////////////////

