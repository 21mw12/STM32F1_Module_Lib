#ifndef __TIM2_PWM_H
#define __TIM2_PWM_H

//////////////////////////////////////////////////////////////////////////////
//
// �ļ����ܣ���ʱ��2��PWM����
// �汾��V1.2
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/07/09
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

/* ��ʱ��2��PWM��Ӧͨ��ʹ������ */
/**
  * TIM2�����ĸ�ͨ�����ֱ��ǣ�
	*			ͨ��1 ���� PA0
	*			ͨ��2 ���� PA1
	*			ͨ��3 ���� PA2
	*			ͨ��4 ���� PA3
  *
	* ע�⣺���Ƽ�ȫдд0��ȫд0��ʾ�������κ�ͨ��
  */
#define TIM2_PWMCHANNEL1_ENABLE   1
#define TIM2_PWMCHANNEL2_ENABLE   1
#define TIM2_PWMCHANNEL3_ENABLE   1
#define TIM2_PWMCHANNEL4_ENABLE   1

/**
  * @brief ��ʱ��2��PWM���ܳ�ʼ��
  * @param TIM2_ARR �Զ���װ����ֵ
  * @param TIM2_PSC Ԥ��Ƶ����ֵ
  * @param TIM2_CCR ��ת��ƽ�ļ���ֵ
  * @return ��
  */
void TIM2_PWM_Init(uint16_t TIM2_ARR, uint16_t TIM2_PSC, uint16_t TIM2_CCR);

/**
  * @brief ���ö�ʱ��2��PWMͨ��1�Ĵ�װ��ֵ
  * @param Compare �µķ�ת��ƽ����ֵ
  * @return ��
  */
void TIM2_PWM1_SetCompare(uint16_t Compare);

/**
  * @brief ���ö�ʱ��2��PWMͨ��2�Ĵ�װ��ֵ
  * @param Compare �µķ�ת��ƽ����ֵ
  * @return ��
  */
void TIM2_PWM2_SetCompare(uint16_t Compare);

/**
  * @brief ���ö�ʱ��2��PWMͨ��3�Ĵ�װ��ֵ
  * @param Compare �µķ�ת��ƽ����ֵ
  * @return ��
  */
void TIM2_PWM3_SetCompare(uint16_t Compare);

/**
  * @brief ���ö�ʱ��2��PWMͨ��4�Ĵ�װ��ֵ
  * @param Compare �µķ�ת��ƽ����ֵ
  * @return ��
  */
void TIM2_PWM4_SetCompare(uint16_t Compare);

#endif

///////////////////////////////////////////////////////////
//
// ������־��
// V1.0: 2023/06/25
//				ʵ����PWM����ع���
// V1.1: 2023/07/09
//				�����˶�ʱ�����ܵ��ع�������ʱ���Ĺ���ϸ��
// V1.2: 2023/07/12
//				�����˲���ע��
//
///////////////////////////////////////////////////////////
