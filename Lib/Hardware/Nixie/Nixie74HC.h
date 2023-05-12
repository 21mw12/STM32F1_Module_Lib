#ifndef __NIXIE74HC_H__
#define __NIXIE74HC_H__

///////////////////////////////////////////////////////////
//
// �ļ����ܣ����74HC138��74HC245оƬ��8λ����ܵ���ʾ����
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/05/12
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "delay.h"

/* 8�����������������Ϣ */
#define Nixie_Periph				RCC_APB2Periph_GPIOB		// ����ʱ��
#define Nixie_PORT					GPIOB										// IO�˿���
#define HC254_PIN_A0				GPIO_Pin_0							// 74HC254��IO�˿�
#define HC254_PIN_A1				GPIO_Pin_1
#define HC254_PIN_A2				GPIO_Pin_2
#define HC254_PIN_A3				GPIO_Pin_3
#define HC254_PIN_A4				GPIO_Pin_4
#define HC254_PIN_A5				GPIO_Pin_5
#define HC254_PIN_A6				GPIO_Pin_6
#define HC254_PIN_A7				GPIO_Pin_7
#define HC138_PIN_A					GPIO_Pin_8							// 74HC138��IO�˿�
#define HC138_PIN_B					GPIO_Pin_9
#define HC138_PIN_C					GPIO_Pin_10

/**
  * @brief ����ܳ�ʼ��
  * @return ��
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
