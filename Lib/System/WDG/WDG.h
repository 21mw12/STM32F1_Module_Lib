#ifndef __WDG_H
#define __WDG_H

///////////////////////////////////////////////////////////

// �ļ����ܣ����Ź�����ع��ܽ���
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2024/01/01
//
// ע���������Ź���ʱʱ�� = 1 / 40KHz * ��Ƶϵ�� * ��IWDG_ARR + 1��
//		 ���ڿ��Ź���ʱʱ�� = 1 / 36MHz * 4096 * ��Ƶϵ�� * ��IWDG_TValue + 1��
//		 ���ڿ��Ź�����ʱ�� = 1 / 36MHz * 4096 * ��Ƶϵ�� * ��IWDG_TValue - IWDG_WValue��
//
//		�������Ź���Ƶϵ��Ĭ��Ϊ16
//		���ڿ��Ź���Ƶϵ��Ĭ��Ϊ8
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

#define IWDG_ARR			2499		// �������Ź�����װ��ֵ
#define IWDG_TValue		54			// ���ڿ��Ź��Ŀ��ƼĴ���
#define IWDG_WValue		21			// ���ڿ��Ź������üĴ���

enum ResetStatus {
	NoReset = 0,
	Reset
};

/**
  * @brief �������Ź���ʼ��
  * @return ��
  */
void IWDG_Init(void);

/**
  * @brief ����Ƿ��Ƕ������Ź�����ĸ�λ
  * @return ��λ״̬
  */
enum ResetStatus IWDG_isReset(void);

/**
  * @brief �������Ź�ι��
  * @return ��
  */
#define IWDG_FeedDog()		IWDG_ReloadCounter()


/**
  * @brief ���ڿ��Ź���ʼ��
  * @return ��
  */
void WWDG_Init(void);

/**
  * @brief ����Ƿ��Ǵ��ڿ��Ź�����ĸ�λ
  * @return ��λ״̬
  */
enum ResetStatus WWDG_isReset(void);

/**
  * @brief ���ڿ��Ź�ι��
  * @return ��
	* ע���������ʼ������̫��
  */
#define WWDG_FeedDog()		WWDG_SetCounter(0x40 | IWDG_TValue)

#endif
