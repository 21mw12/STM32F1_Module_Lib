#ifndef _SysTick_H
#define _SysTick_H

#include "system.h"

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�ʵ��FreeRTOS�е���ʱ����
//
///////////////////////////////////////////////////////////

/**
  * @brief ��ʼ���ӳٺ���
  * @param SYSCLK: ϵͳʱ��Ƶ�ʣ�SYSTICK��ʱ�ӹ̶�ΪAHBʱ�ӣ�
  * @return ��
  */
void SysTick_Init(u8 SYSCLK);

/**
  * @brief ��ʱ΢��
  * @param nms: Ҫ��ʱ��΢������0~65535��
  * @return 
  */
void delay_ms(u32 nms);

/**
  * @brief ��������������ȵ��ӳ�΢��
  * @param nms: Ҫ��ʱ��ms��
  * @return ��
  */
void delay_xms(u32 nms);

/**
  * @brief ��ʱ����
  * @param nus: Ҫ��ʱ����������0~204522252 (���ֵ��2^32/fac_us@fac_us=168)��
  * @return ��
  */
void delay_us(u32 nus);

#endif
