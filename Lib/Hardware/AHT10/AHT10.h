#ifndef __AHT10_H
#define __AHT10_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�AHT10��ʪ�ȴ�����ģ��Ĺ���
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2024/01/06
//
// ע������˼·������https://zhuanlan.zhihu.com/p/582329736
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* AHT10 I2C��ַ */
#define AHT10_ADDRESS			0x38 << 1

typedef enum {
	AHT10_State_Error = 0,
	AHT10_State_Normal
} AHT10_State;

/**
  * @brief AHT10��ʼ��
  * @return 
  */
void AHT10_Init(void);

/**
  * @brief �����λAHT10
  * @return 
  */
void AHT10_SoftReset(void);

/**
  * @brief ��ȡAHT10��ʪ������
  * @param Temp �¶�ֵ
  * @param Hum ʪ��ֵ
  * @return AHT0��ȡ״̬
  */
AHT10_State AHT10_GetData(float *Temp, float *Hum);

#endif
