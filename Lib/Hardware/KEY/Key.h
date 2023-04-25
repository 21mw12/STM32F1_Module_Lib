#ifndef __KEY_H
#define __KEY_H	

///////////////////////////////////////////////////////////
//
// �ļ����ܣ������Ļ�������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/4/25
//
// Ӳ������˵��������һ������IO�ڣ���һ������GND������
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "delay.h"

/* ��������������Ϣ */
#define Key_Periph		RCC_APB2Periph_GPIOB		// ����ʱ��
#define Key_PORT			GPIOB										// IO�˿���
#define Key_PIN 			GPIO_Pin_1							// IO�˿�

/**
  * @brief ������ʼ��
  * @return ��
  */
void Key_Init(void);

/**
  * @brief ������ʼ��
  * @return �����Ƿ񱻰���	0��û�а���	1���а���
  */
uint8_t Key_Get(void);
		 				    
#endif
