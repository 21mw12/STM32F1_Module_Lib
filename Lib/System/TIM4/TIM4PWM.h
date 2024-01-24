#ifndef __TIM4_PWM_H
#define __TIM4_PWM_H

//////////////////////////////////////////////////////////////////////////////
//
// �ļ����ܣ���ʱ��4��PWM����
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
// TIM4�����ĸ�ͨ�����ֱ��ǣ�
//     ͨ��1 ���� PB6
//     ͨ��2 ���� PB7
//     ͨ��3 ���� PB8
//     ͨ��4 ���� PB9
//
//////////////////////////////////////////////////////////////////////////////

#include "stm32f10x.h"

/**
  * ��ʱ��4��PWM��Ӧͨ��ʹ������
	* ע�����Ƽ�ȫдд0��ȫд0��ʾ�������κ�ͨ��
  */
#define TIM4_PWMCHANNEL1_ENABLE   1
#define TIM4_PWMCHANNEL2_ENABLE   1
#define TIM4_PWMCHANNEL3_ENABLE   1
#define TIM4_PWMCHANNEL4_ENABLE   1

/**
  * @brief ��ʱ��4��PWM���ܳ�ʼ��
  * @param TIM4_ARR �Զ���װ����ֵ
  * @param TIM4_PSC Ԥ��Ƶ����ֵ
  * @param TIM4_CCR ��ת��ƽ�ļ���ֵ
  * @return ��
  */
void TIM4_PWM_Init(uint16_t TIM4_ARR, uint16_t TIM4_PSC, uint16_t TIM4_CCR);

/**
  * @brief ���ö�ʱ��4��PWMͨ��1�Ĵ�װ��ֵ
  * @param Compare �µķ�ת��ƽ����ֵ
  * @return ��
  */
void TIM4_PWM1_SetCompare(uint16_t Compare);

/**
  * @brief ���ö�ʱ��4��PWMͨ��2�Ĵ�װ��ֵ
  * @param Compare �µķ�ת��ƽ����ֵ
  * @return ��
  */
void TIM4_PWM2_SetCompare(uint16_t Compare);

/**
  * @brief ���ö�ʱ��4��PWMͨ��3�Ĵ�װ��ֵ
  * @param Compare �µķ�ת��ƽ����ֵ
  * @return ��
  */
void TIM4_PWM3_SetCompare(uint16_t Compare);

/**
  * @brief ���ö�ʱ��4��PWMͨ��4�Ĵ�װ��ֵ
  * @param Compare �µķ�ת��ƽ����ֵ
  * @return ��
  */
void TIM4_PWM4_SetCompare(uint16_t Compare);

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
