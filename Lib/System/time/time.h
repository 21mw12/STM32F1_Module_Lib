#ifndef __TIME_H
#define __TIME_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ���ʱ����������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/04/27
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* ��ʱ��������Ϣ */
#define Time_Periph				RCC_APB1Periph_TIM2		// ����ʱ��
#define Time							TIM2									// ��ʱ��ѡ��
#define Time_EXTI_IRQn 		TIM2_IRQn							// �ж�ͨ��

/**
  * ��ʱ�����㹫ʽ��
	*				TimeOut =((arr + 1) * (psc + 1)) / TimeClockFren
	*
	*				TimeOut����ʱ�����ʱ�䣬���೤ʱ�����һ���жϣ���λΪ�룩
	*				arr���Զ���װ����ֵ
	*				psc��Ԥ��Ƶ����ֵ
	*				TimeClockFren����ʱ��������ʱ��Ƶ�ʣ�����ʹ����Ƶ72MHz
  */

/**
  * @brief ��ʱ����ʼ��
  * @param arrA1	�Զ���װ����ֵ��һ����:������ʽ�е�arr+1��
  * @param pscA1	Ԥ��Ƶ����ֵ��һ����:������ʽ�е�psc+1��
  * @return ��
  */
void TIM_Init(uint16_t arrA1, uint16_t pscA1);

/**
  * @brief ��ʱ������
  * @return ��
  */
void TIM_ON(void);

/**
  * @brief ��ʱ���ر�
  * @return ��
  */
void TIM_OFF(void);

/* �жϴ�����ģ�壬ʹ��ʱ���临�Ƶ�main.c�ļ��� */
//void TIM2_IRQHandler(void) {
//	if (TIM_GetITStatus(Time, TIM_IT_Update) != RESET) {
//		
//		/**
//			* �жϴ���������䣬�ڴ�������Ҫ����ĺ���
//			*/
//		
//		TIM_ClearITPendingBit(Time, TIM_IT_Update);
//	}
//}

#endif
