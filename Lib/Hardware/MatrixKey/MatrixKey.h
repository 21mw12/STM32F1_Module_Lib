#ifndef __MATRIXKEY_H_
#define __MATRIXKEY_H_

///////////////////////////////////////////////////////////
//
// �ļ����ܣ����󰴼��Ļ�������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/05/06
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "delay.h"

/* ���󰴼�����������Ϣ */
#define MatrixKey_Periph			RCC_APB2Periph_GPIOB		// ����ʱ��
#define MatrixKey_PORT				GPIOB										// IO�˿���
#define MatrixKey_ROW1				GPIO_Pin_3							// �������ÿ�е�IO�˿�
#define MatrixKey_ROW2				GPIO_Pin_2
#define MatrixKey_ROW3				GPIO_Pin_1
#define MatrixKey_ROW4				GPIO_Pin_0
#define MatrixKey_COLUMN1			GPIO_Pin_4							// �������ÿ�е�IO�˿�
#define MatrixKey_COLUMN2			GPIO_Pin_5
#define MatrixKey_COLUMN3			GPIO_Pin_6
#define MatrixKey_COLUMN4			GPIO_Pin_7

/**
  * @brief ���󰴼���ʼ��
  * @return ��
  */
void MatrixKey_Init(void);

/**
  * @brief ��ȡ���󰴼�����ֵ
  * @return ��
  */
uint8_t Get_MatrixKeyCode(void);

/**
  * @brief ������ֵת��Ϊ���֣�������4*4��������е����ְ������֣�
  * @param KeyCode ����ֵ
  * @return ����ֵ��Ӧ������
  */
uint8_t KeyCode_Transition(uint8_t KeyCode);

#endif
