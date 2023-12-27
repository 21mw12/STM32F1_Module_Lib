#ifndef __OLED_H
#define __OLED_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�OLED��ʾ����������
// �汾��V1.3
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/12/27
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "delay.h"
#include "I2C1Hardware.h"

/* OLED I2C��ַ */
#define OLED_ADDRESS			0x78


/* OLED�޸ĵײ�I2C����ʱ��Ҫ�޸�Ϊ��Ӧ�ĺ��� */
#define OLED_Write			I2C1_Hardware_SendByte

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
// V1.2: 2023/07/07
//				�����ع���I2C��ѡ��Ӳ��I2C��Ϊ�ײ��
// V1.3: 2023/12/27
//				����ͨ��ʾ��ͼ�ο��������Ƹ���I2C������ķ�ʽ
//
///////////////////////////////////////////////////////////
