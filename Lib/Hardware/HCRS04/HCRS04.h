#ifndef __HC_RS04_H
#define __HC_RS04_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�������ģ��Ĺ���
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/07/12
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "TIM2COUNT.h"
#include "delay.h"

/* ������ģ���������� */
#define HCSR04_Trig_Periph      RCC_APB2Periph_GPIOA
#define HCSR04_Echo_Periph      RCC_APB2Periph_GPIOA
#define HCSR04_Trig_PORT     		GPIOA
#define HCSR04_Echo_PORT     		GPIOA
#define HCSR04_TRIG_Pin         GPIO_Pin_9
#define HCSR04_Echo_Pin         GPIO_Pin_10

/* ȡƽ������ */
#define Average_CalCount		5

/**
  * @brief ������ģ���ʼ��
  * @return ��
  */
void HC_SR04_Init(void);

/**
  * @brief ������ģ���ȡ����
  * @return ����
  */
float HC_SR04_GetLength(void);

#endif
