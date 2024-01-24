#ifndef __NIXIEMAX7219_H__
#define __NIXIEMAX7219_H__

///////////////////////////////////////////////////////////
//
// �ļ����ܣ����MAX7219оƬ��8λ����ܵ���ʾ����
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/05/12
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* 8�����������������Ϣ */
#define MAX7219_Periph				RCC_APB2Periph_GPIOA		// ����ʱ��
#define MAX7219_Port					GPIOA										// IO�˿���
#define MAX7219_Pin_DIN				GPIO_Pin_1							// MAX7219��IO�˿�
#define MAX7219_Pin_LOAD			GPIO_Pin_2
#define MAX7219_Pin_CLK				GPIO_Pin_3

/**
  * @brief ����ܳ�ʼ��
  * @param 
  * @return 
  */
void Nixie_Init(void);

/**
  * @brief �������ʾ
  * @param Location Ҫ��ʾ��λ�ã�1~8��
  * @param Number	Ҫ��ʾ�����ݣ�0~10 �� 0~9��-��
  * @return ��
  */
void Nixie_Show(uint8_t Location, uint8_t Number);

#endif
