#ifndef __ENCODER_H
#define __ENCODER_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ���ת�������Ļ�������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/05/06
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* ��ת��������ǰ����ֵ */
extern int8_t Encoder_Count;

/* ��ת������������Ϣ */
#define Encoder_Periph		RCC_APB2Periph_GPIOB		// ����ʱ��
#define Encoder_Port			GPIOB										// IO�˿���
#define Encoder_A_Pin 		GPIO_Pin_0							// A��IO�˿�
#define Encoder_B_Pin 		GPIO_Pin_1							// B��IO�˿�

#define Encoder_PortSource			GPIO_PortSourceGPIOB		// �ж�ԴIO�˿���
#define Encoder_A_PinSource 		GPIO_PinSource0					// �ж�ԴIO�˿�
#define Encoder_B_PinSource 		GPIO_PinSource1					// �ж�ԴIO�˿�
#define Encoder_A_EXTI_Line			EXTI_Line0							// �ж���
#define Encoder_B_EXTI_Line			EXTI_Line1							// �ж���
#define Encoder_A_EXTI_IRQn 		EXTI0_IRQn							// �ж�ͨ��
#define Encoder_B_EXTI_IRQn 		EXTI1_IRQn							// �ж�ͨ��

/**
  * @brief ��ת��������ʼ��
  * @return ��
  */
void Encoder_Init(void);

/**
  * @brief ��ȡ��ǰ��ת��������ֵ
  * @return ��ת��������ֵ
  */
int8_t Encoder_Get(void);

#endif
