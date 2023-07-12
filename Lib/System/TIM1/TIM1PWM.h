#ifndef __TIM1_PWM_H
#define __TIM1_PWM_H

//////////////////////////////////////////////////////////////////////////////
//
// �ļ����ܣ���ʱ��1��PWM����
// �汾��V1.1
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/07/12
//
// PWM���㹫ʽ��
//     PWMƵ�� = CK_PSC / (PSC + 1) / (ARR + 1)
//     PWMռ�ձ� = CCR / (ARR + 1)
//		 PWM�ֱ��� = 1 / (ARR + 1)
//
//				CK_PSC��ϵͳ��Ƶ��72MHz��
//				ARR���Զ���װ����ֵ
//				PSC��Ԥ��Ƶ����ֵ
//				CCR����ת��ƽ�ļ���ֵ
//
//////////////////////////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* ��ʱ��1��PWM��Ӧͨ��ʹ������ */
/**
  * TIM1�����ĸ�ͨ�����ֱ��ǣ�
	*			ͨ��1 ���� PA8
	*			ͨ��2 ���� PA9
	*			ͨ��3 ���� PA10
	*			ͨ��4 ���� PA11
  *
	* ע�⣺���Ƽ�ȫдд0��ȫд0��ʾ�������κ�ͨ��
  */
#define TIM1_PWMCHANNEL1_ENABLE   1
#define TIM1_PWMCHANNEL2_ENABLE   1
#define TIM1_PWMCHANNEL3_ENABLE   1
#define TIM1_PWMCHANNEL4_ENABLE   1

/**
  * @brief ��ʱ��1��PWM���ܳ�ʼ��
  * @return ��
  */
void TIM1_PWM_Init(uint16_t TIM1_ARR, uint16_t TIM1_PSC, uint16_t TIM1_CCR);

/**
  * @brief ���ö�ʱ��1��PWMͨ��1�Ĵ�װ��ֵ
  * @param Compare �µķ�ת��ƽ����ֵ
  * @return ��
  */
void TIM1_PWM1_SetCompare(uint16_t Compare);

/**
  * @brief ���ö�ʱ��1��PWMͨ��2�Ĵ�װ��ֵ
  * @param Compare �µķ�ת��ƽ����ֵ
  * @return ��
  */
void TIM1_PWM2_SetCompare(uint16_t Compare);

/**
  * @brief ���ö�ʱ��1��PWMͨ��3�Ĵ�װ��ֵ
  * @param Compare �µķ�ת��ƽ����ֵ
  * @return ��
  */
void TIM1_PWM3_SetCompare(uint16_t Compare);

/**
  * @brief ���ö�ʱ��1��PWMͨ��4�Ĵ�װ��ֵ
  * @param Compare �µķ�ת��ƽ����ֵ
  * @return ��
  */
void TIM1_PWM4_SetCompare(uint16_t Compare);

#endif

///////////////////////////////////////////////////////////
//
// ������־��
// V1.0: 2023/07/09
//				�����˶�ʱ�����ܵ��ع�������ʱ���Ĺ���ϸ��
// V1.1: 2023/07/12
//				�����˲���ע��
//
///////////////////////////////////////////////////////////
