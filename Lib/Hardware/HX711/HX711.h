#ifndef __HX711_H
#define __HX711_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�HX711���ش������Ļ�������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2024/01/26
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* ����ת��ϵ�������ݲ�ͬ�Ĵ������в�ͬ��ֵ */
#define HX711_coefficient				270.5

/* HX711����������Ϣ */
#define HX711_Periph			RCC_APB2Periph_GPIOC
#define HX711_Port				GPIOC
#define HX711_Pin_DT 			GPIO_Pin_15
#define HX711_Pin_SCK			GPIO_Pin_14

/**
  * @brief HX711��ʼ��
  * @return ��
  */
void HX711_Init(void);

/**
  * @brief HX711��λ
  * @return ��
  */
void HX711_Reset(void);

/**
  * @brief HX711���ԭʼ����
  * @return ԭʼ����
  */
uint32_t HX711_ReadData(void);

/**
  * @brief HX711�����������
  * @return ��������
  */
uint32_t HX711_GetWeight(void);


#endif
