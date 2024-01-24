#ifndef __ENCODER_H
#define __ENCODER_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ���ʱ������ת�������Ļ�������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/05/06
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* ��ת������������Ϣ */
#define Encoder_Periph		RCC_APB2Periph_GPIOA		// ����ʱ��
#define Encoder_Port			GPIOA										// IO�˿���
#define Encoder_A_Pin 		GPIO_Pin_6							// A��IO�˿�
#define Encoder_B_Pin 		GPIO_Pin_7							// B��IO�˿�

#define Encoder_TIM				TIM3					// ��ʱ��
#define Encoder_TIM_Periph			RCC_APB1Periph_TIM3			// ��ʱ��ʱ����
#define Encoder_NVIC_IRQn 			TIM3_IRQn								// �ж�ͨ��
#define Encoder_A_TIM_Channel		TIM_Channel_1						// ��ʱ��ͨ��
#define Encoder_B_TIM_Channel		TIM_Channel_2						// ��ʱ��ͨ��

/**
  * @brief ��ת��������ʼ��
  * @return ��
  */
void Encoder_Init(void);

/**
  * @brief ��ȡ��ǰ��ת��������ֵ, ������
  * @return ��ת��������ֵ
  */
int16_t Encoder_GetClear(void);

/**
  * @brief ��ȡ��ǰ��ת��������ֵ
  * @return ��ת��������ֵ
  */
uint32_t Encoder_Get(void);

#endif
