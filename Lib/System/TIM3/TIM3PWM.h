#ifndef __TIM3_PWM_H
#define __TIM3_PWM_H

//////////////////////////////////////////////////////////////////////////////
//
// �ļ����ܣ���ʱ��2��PWM����
// �汾��V1.0
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
// һЩ����ֵ��
//		  ���     ARR+1Ϊ100    PSC+1Ϊ36
//    ֱ�����   ARR+1Ϊ1000   PSC+1Ϊ576
//              (�����PWMƵ��ѡ����һ����ά�ȵ����⣬�����趨��125Hz��
//              (������Դ��https://blog.csdn.net/u013273161/article/details/88316066)
//
//////////////////////////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* ��ʱ��2��PWM��Ӧͨ��ʹ������ */
/**
  * TIM3�����ĸ�ͨ�����ֱ��ǣ�
	*			ͨ��1 ���� PA6
	*			ͨ��2 ���� PA7
	*			ͨ��3 ���� PB0
	*			ͨ��4 ���� PB1
  *
	* ע�⣺���Ƽ�ȫдд0��ȫд0��ʾ�������κ�ͨ��
  */
#define TIM3_PWMCHANNEL1_ENABLE   1
#define TIM3_PWMCHANNEL2_ENABLE   1
#define TIM3_PWMCHANNEL3_ENABLE   1
#define TIM3_PWMCHANNEL4_ENABLE   1

/**
  * @brief ��ʱ��3��PWM���ܳ�ʼ��
  * @param TIM3_ARR �Զ���װ����ֵ
  * @param TIM3_PSC Ԥ��Ƶ����ֵ
  * @param TIM3_CCR ��ת��ƽ�ļ���ֵ
  * @return ��
  */
void TIM3_PWM_Init(uint16_t TIM3_ARR, uint16_t TIM3_PSC, uint16_t TIM3_CCR);

/**
  * @brief ���ö�ʱ��3��PWMͨ��1�Ĵ�װ��ֵ
  * @param Compare �µ���װ��ֵ
  * @return ��
  */
void TIM3_PWM1_SetCompare(uint16_t Compare);

/**
  * @brief ���ö�ʱ��3��PWMͨ��2�Ĵ�װ��ֵ
  * @param Compare �µ���װ��ֵ
  * @return ��
  */
void TIM3_PWM2_SetCompare(uint16_t Compare);

/**
  * @brief ���ö�ʱ��3��PWMͨ��3�Ĵ�װ��ֵ
  * @param Compare �µ���װ��ֵ
  * @return ��
  */
void TIM3_PWM3_SetCompare(uint16_t Compare);

/**
  * @brief ���ö�ʱ��3��PWMͨ��4�Ĵ�װ��ֵ
  * @param Compare �µ���װ��ֵ
  * @return ��
  */
void TIM3_PWM4_SetCompare(uint16_t Compare);

#endif