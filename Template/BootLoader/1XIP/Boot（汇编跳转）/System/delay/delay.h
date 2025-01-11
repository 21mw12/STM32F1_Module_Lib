#ifndef __DELAY_H
#define __DELAY_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�ʹ�ö�ʱ����ʱ
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/04/21
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/**
  * @brief  ΢�뼶��ʱ
  * @param  xus ��ʱʱ������Χ��0~233015
  * @retval ��
  */
void Delay_us(uint32_t us);

/**
  * @brief  ���뼶��ʱ
  * @param  xms ��ʱʱ������Χ��0~4294967295
  * @retval ��
  */
void Delay_ms(uint32_t ms);

/**
  * @brief  �뼶��ʱ
  * @param  xs ��ʱʱ������Χ��0~4294967295
  * @retval ��
  */
void Delay_s(uint32_t s);

#endif
