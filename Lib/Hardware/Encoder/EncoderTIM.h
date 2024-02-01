#ifndef __ENCODER_H
#define __ENCODER_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ���ʱ������ת�������Ļ�������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/05/06
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "TIM3Encoder.h"

/* ��ת��������ת����ö�� */
typedef enum {
	EncoderDirect_Idel = 0,		// δ��ת
	EncoderDirect_Clockwise,	// ˳ʱ����ת
	EncoderDirect_AntiClockwise	// ��ʱ����ת
} EncoderDirect;

/**
  * @brief ��ת��������ʼ��
  * @return ��
  */
#define Encoder_Init()		TIM3_Encoder_Init()

/**
  * @brief �����ת��������ת����ֵ�ͷ���
  * @param encoderCount ��ת��ֵ
  * @return ��ת����
  */
EncoderDirect Encoder_GetSpinCount(uint16_t* encoderCount);

#endif

///////////////////////////////////////////////////////////
//
// ������־��
// V1.0: 2023/05/06
//				ʵ������ת�������Ļ�����ͼ����
// V2.0: 2024/02/01
//				����Ӳ���������ع��˴���
//
///////////////////////////////////////////////////////////
