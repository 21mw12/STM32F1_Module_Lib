#ifndef __KEY_H
#define __KEY_H	

///////////////////////////////////////////////////////////
//
// �ļ����ܣ������Ļ�������
// �汾��V1.1
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/4/27
//
// Ӳ������˵��������һ������IO�ڣ���һ������GND������
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "delay.h"

/* ��������������Ϣ */
#define Key_Periph		RCC_APB2Periph_GPIOB		// ����ʱ��
#define Key_Port			GPIOB										// IO�˿���
#define Key_Pin 			GPIO_Pin_1							// IO�˿�

/**
  * �Ƿ����ð����ж�
  * 1����ʾ��������Ҫ��д��Ӧ���жϴ�������������������棩
  * 0����ʾ�رգ����ö�ȡ������ȡ����״̬
  */
#define Key_Interrupt      1

/* �����ж����� */
#define Key_PortSource		GPIO_PortSourceGPIOB		// �ж�ԴIO�˿���
#define Key_PinSource 		GPIO_PinSource1					// �ж�ԴIO�˿�
#define Key_EXTI_Line			EXTI_Line1					// �ж���
#define Key_EXTI_IRQn 		EXTI1_IRQn					// �ж�ͨ��

/**
  * @brief ������ʼ��
  * @return ��
  */
void Key_Init(void);

#if Key_Interrupt == 0
/**
  * @brief ������ʼ��
  * @return �����Ƿ񱻰���	0��û�а���	1���а���
  */
uint8_t Key_Get(void);
#endif

/* �жϴ�����ģ�壬ʹ��ʱ���临�Ƶ�main.c�ļ��� */
//void EXTI1_IRQHandler(void){
//	if (EXTI_GetITStatus(Key_EXTI_Line) == SET){
//		// ��������
//		Delay_ms(20);
//		while (GPIO_ReadInputDataBit(Key_Port, Key_Pin) == 0);
//		Delay_ms(20);
//		
//		/**
//			* �жϴ���������䣬�ڴ�������Ҫ����ĺ���
//			*/
//		
//		EXTI_ClearITPendingBit(Key_EXTI_Line);
//	}
//}
#endif

///////////////////////////////////////////////////////////
//
// ������־��
// V1.0: 2023/4/25
//				ʵ���˰����ĳ�ʼ���Ͷ�ȡ����
// V1.1: 2023/04/27
//				ʵ���˰����жϵĹ���
//
///////////////////////////////////////////////////////////
