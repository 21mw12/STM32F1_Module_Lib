#ifndef __ADC_H
#define __ADC_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�ADC��������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/05��02
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* ADC������Ϣ */
#define ADC_Periph			RCC_APB2Periph_ADC1			// ADC����ʱ��
#define ADC							ADC1										// ADC
#define ADC_IO_Periph		RCC_APB2Periph_GPIOA		// ʹ��ADC��IO�ڵ�����ʱ��
#define ADC_PORT				GPIOA										// IO�˿���
#define ADC_PIN 				GPIO_Pin_0							// IO�˿�

/**
  * @brief ADC��ʼ��
  * @return ��
  */
void ADC_INit(void);

/**
  * @brief ��ȡADC��ȡ��ֵ
  * @return ת�����ֵ
  */
uint16_t ADC_GetValue(void);

#endif


