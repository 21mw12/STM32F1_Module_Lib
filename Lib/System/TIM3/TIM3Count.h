#ifndef __TIM3_PWM_H
#define __TIM3_PWM_H

////////////////////////////////////////////////////////////////////
//
// �ļ����ܣ���ʱ��3�ļ�������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/07/09
//
// ��ʱ�����㹫ʽ��
//       TimeOut =((ARR + 1) * (PSC + 1)) / TimeClockFren
//
//       TimeOut����ʱ�����ʱ�䣬���೤ʱ�����һ���жϣ���λΪ�룩
// 			 ARR���Զ���װ����ֵ
// 			 PSC��Ԥ��Ƶ����ֵ
// 			 TimeClockFren����ʱ��������ʱ��Ƶ�ʣ�����ʹ����Ƶ72MHz
// 
// һЩ����ֵ��
//		��ʱ1s  ARR+1Ϊ10000   PSC+1Ϊ7200
//
////////////////////////////////////////////////////////////////////

#include "stm32f10x.h"

/**
  * @brief ��ʱ����ʼ��
  * @param TIM3_arr	�Զ���װ����ֵ��һ����:������ʽ�е�arr+1��
  * @param TIM3_psc	Ԥ��Ƶ����ֵ��һ����:������ʽ�е�psc+1��
  * @return ��
  */
void TIM3_Init(uint16_t TIM3_ARR, uint16_t TIM3_PSC);

/**
  * @brief ��ʱ������
  * @return ��
  */
void TIM3_ON(void);

/**
  * @brief ��ʱ���ر�
  * @return ��
  */
void TIM3_OFF(void);

/* �жϴ�������ģ�壬ʹ��ʱ���临�Ƶ�main.c�ļ��� */
//void TIM3_IRQHandler(void) {
//	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
//		
//		/**
//			* �жϴ����������䣬�ڴ�������Ҫ�����ĺ���
//			*/
//		
//		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
//	}
//}

#endif