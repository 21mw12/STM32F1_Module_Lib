#ifndef __TIM2_ENCODER_H
#define __TIM2_ENCODER_H

//////////////////////////////////////////////////////////////////////////////
//
// �ļ����ܣ���ʱ��2�ı���������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/07/10
//
//////////////////////////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* ��ʱ��2��PWM��Ӧͨ��ʹ������ */
/**
  * TIM2�����ĸ�ͨ�����ֱ��ǣ�
	*     ͨ��1 ���� PA0 �Щ� ������
	*			ͨ��2 ���� PA1 ��
	*			ͨ��3 ���� PA2
	*			ͨ��4 ���� PA3
  *
	* ע�⣺һ����ʱ��ֻ������һ��������
  */

/**
  * @brief ��ת��������ʼ��
  * @return ��
  */
void TIM2_Encoder_Init(void);

/**
  * @brief ��ȡ��ǰ��ת��������ֵ, ������
  * @return ��ת��������ֵ
  */
int16_t TIM2_Encoder_GetClear(void);

/**
  * @brief ��ȡ��ǰ��ת��������ֵ
  * @return ��ת��������ֵ
  */
uint32_t TIM2_Encoder_Get(void);

#endif