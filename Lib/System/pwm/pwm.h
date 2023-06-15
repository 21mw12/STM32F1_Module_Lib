#ifndef __PWM_H
#define __PWM_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�ʵ����PWM����ع���
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/06/25
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* ����������� */
/**
  * �޸�PWM�������ʱͬʱҪ���ö�ʱ���Ķ�Ӧͨ�������ö�Ӧ�޸ļ�����
	* �ֱ���Servo.c�ļ��ĵ�10���Լ���36�еĺ�����������
  */
#define PWM_Periph		RCC_APB2Periph_GPIOA		// ����ʱ��
#define PWM_PORT			GPIOA										// IO�˿���
#define PWM_PIN 			GPIO_Pin_1							// IO�˿�

/* ��ʱʱ������ */
#define Tim_Periph			RCC_APB1Periph_TIM2		// ����ʱ��
#define Tim							TIM2									// ��ʱ��ѡ��

/* PWM�������� */
/**
  * PWM���㹫ʽ��
	*			PWMƵ�� = CK_PSC / (PSC + 1) / (ARR + 1)
	*     PWMռ�ձ� = CCR / (ARR + 1)
	*			PWM�ֱ��� = 1 / (ARR + 1)
	*
	*				CK_PSC��ϵͳ��Ƶ��72MHz��
	*				arr���Զ���װ����ֵ
	*				psc��Ԥ��Ƶ����ֵ
	*				ccr����ת��ƽ�ļ���ֵ
  */
#define ARR		20000 - 1
#define PSC		72 - 1
#define CCR		0

/**
  * @brief PWM��ʼ��
  * @return ��
  */
void PWM_Init(void);

/**
  * @brief ����PWM�Ĵ�װ��ֵ
  * @param Compare �µ���װ��ֵ
  * @return ��
  */
void PWM_SetCompare(uint16_t Compare);

#endif
