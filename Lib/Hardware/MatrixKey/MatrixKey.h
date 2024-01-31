#ifndef __MATRIXKEY_H_
#define __MATRIXKEY_H_

///////////////////////////////////////////////////////////
//
// �ļ����ܣ����󰴼��Ļ�������
// �汾��V2.1
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2024/01/31
//
// Ĭ�Ͼ���λ��˵����
//				  C1	C2	C3	C4
//		R1		1		2		3		A
//		R2		4		5		6		B
//		R3		7		8		9		C
//		R4		*		0		#		D
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* ���󰴼�����������Ϣ */
/* ��������е�IO�˿� */
#define MatrixKey_RPeriph			RCC_APB2Periph_GPIOB
#define MatrixKey_RPort				GPIOB
#define MatrixKey_Row1				GPIO_Pin_12
#define MatrixKey_Row2				GPIO_Pin_13
#define MatrixKey_Row3				GPIO_Pin_14
#define MatrixKey_Row4				GPIO_Pin_15
/* ��������е�IO�˿� */
#define MatrixKey_CPeriph			RCC_APB2Periph_GPIOA
#define MatrixKey_CPort				GPIOA
#define MatrixKey_Column1			GPIO_Pin_8
#define MatrixKey_Column2			GPIO_Pin_9
#define MatrixKey_Column3			GPIO_Pin_10
#define MatrixKey_Column4			GPIO_Pin_11

/* ����ֵת�� */
typedef enum {
	Button_Num0 = 0,
	Button_Num1,
	Button_Num2,
	Button_Num3,
	Button_Num4,
	Button_Num5,
	Button_Num6,
	Button_Num7,
	Button_Num8,
	Button_Num9,
	Button_Asterisk,		// *
	Button_WellNumber,	// #
	Button_A,
	Button_B,
	Button_C,
	Button_D,
	Button_NULL,
} Button;

/**
  * @brief ���󰴼���ʼ��
  * @return ��
  */
void MatrixKey_Init(void);

/**
  * @brief ��ȡ���󰴼�����ֵ
  * @return ��
  */
uint8_t MatrixKey_GetCode(void);

/**
  * @brief ������ֵת��Ϊ���֣�������4*4��������е����ְ������֣�
  * @param KeyCode ����ֵ
  * @return ����ֵ��Ӧ������
  */
Button MatrixKey_TransitionKeyCode(uint8_t KeyCode);

#endif

///////////////////////////////////////////////////////////
//
// ������־��
// V1.0: 2023/05/06
//				ʵ���˾��󰴼��Ļ�����ʾ
// V2.0: 2024/01/30
//				ʵ���˸���ͨ�û������
// V2.1: 2024/01/31
//				�޸��˲��������޷�ת������ֵ
//
///////////////////////////////////////////////////////////
