#ifndef __AD_H
#define __AD_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�ADC1�Ļ�������
// �汾��V2.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2024/01/23
//
// ADC1ͨ����ӦIO�ڣ�
//     ͨ��0 ���� PA0        ͨ��9  ���� PB1
//     ͨ��1 ���� PA1        ͨ��10 ���� PC0
//     ͨ��2 ���� PA2        ͨ��11 ���� PC1
//     ͨ��3 ���� PA3        ͨ��12 ���� PC2
//     ͨ��4 ���� PA4        ͨ��13 ���� PC3
//     ͨ��5 ���� PA5        ͨ��14 ���� PC4
//     ͨ��6 ���� PA6        ͨ��15 ���� PC5
//     ͨ��7 ���� PA7        ͨ��16 ���� �ڲ��¶ȴ�����
//     ͨ��8 ���� PB0        ͨ��17 ���� �ڲ�Vrefint
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/**
	*	�Ƿ�������ת��
	* 1����ʾ������ADC�����ϵĽ���ת��
	* 0����ʾ�رգ�ֻ���ֶ�����ADC�Ż����һ��ת��
	*/
#define isContinuousConversion		0

/**
  * ������ͨ�� ��0~15��
	* ��Χ��0~15 �� С��0����
	* ���壺������Ϊ4����ʾ0~4ͨ����������
	*			  ������Ϊ-1����ʾֻʹ��һ���Զ���ͨ����������ĺ�������
	*/
#define ADCChannelCount						4

#if ADCChannelCount > 0
	/* ��ͨ���£�ͨ�������ݴ��������Ķ�Ӧ�±��� */
	extern uint16_t AD_Value[ADCChannelCount+1];
#else
	/* �Զ���ADCͨ������������Ϣ */
	#define ADC_Periph		RCC_APB2Periph_GPIOA
	#define ADC_PORT			GPIOA
	#define ADC_PIN 			GPIO_Pin_0
	#define ADC_Channel		ADC_Channel_0
#endif

/**
  * @brief ADC��ʼ��
  * @return ��
  */
void AD_Init(void);

#if ADCChannelCount > 0
#if isContinuousConversion == 0
/**
  * @brief ��ȡADC��ȡ��ֵ
  * @return ��
  */
void AD_GetValue(void);
#else
/**
  * @brief ��ȡADC��ȡ��ֵ
  * @return ת�����ֵ
  */
uint16_t AD_GetValue(void);
#endif
#endif

#endif

///////////////////////////////////////////////////////////
//
// ������־��
// V1.0: 2023/05/02
//				ʵ���˵�ͨ����ADC
// V2.0: 2024/01/23
//				ʵ����DMA��ͨ���ɼ���ADC����ʵ���˷��������
//
///////////////////////////////////////////////////////////
