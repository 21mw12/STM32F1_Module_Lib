#ifndef __KEYSTATEMACHINE_H
#define __KEYSTATEMACHINE_H

////////////////////////////////////////////////////////////////////////////
//
// �ļ����ܣ�ͨ��״̬����ʵ�ְ����ĵ���˫���ͳ�������
// ���ߣ��������(SCDNƽ̨) | nanshoui163(githubƽ̨)
// CSDN���ӣ�https://blog.csdn.net/qq_44078824/article/details/123753825
//					 https://blog.csdn.net/qq_44078824/article/details/123757354
// github���ӣ�https://github.com/nanshoui163/KeyStateMachine
//             https://github.com/nanshoui163/KeyStateMachine2
//
//	ԭ������Ϣ���ϣ�����ֻ�����˵Ķ�����Ⲣת��Ϊ���˵Ĵ����񣡣���
//
////////////////////////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "delay.h"

/* ��������������Ϣ */
#define Key_Periph		RCC_APB2Periph_GPIOB		// ����ʱ��
#define Key_PORT			GPIOB										// IO�˿���
#define Key_PIN 			GPIO_Pin_10	

/* ״̬��״̬ */
typedef enum {
	KEY_Status_Idle = 0, 					// ����
	KEY_Status_Debounce,  				// ����
	KEY_Status_ConfirmPress,    	// ȷ�ϰ���	
	KEY_Status_ConfirmPressLong, 	// ȷ�ϳ���
	KEY_Status_WaiteAgain, 				// �ȴ��ٴΰ���
	KEY_Status_ConfirmSecondPress // ȷ���ٴΰ���
} KEY_StatusList_TypeDef;

/* �����¼� */
typedef enum {
	KEY_Event_Null = 0x00, 					// ����
	KEY_Event_SingleClick = 0x01, 	// ����
	KEY_Event_DoubleClick = 0x02,  	// ˫��
	KEY_Event_LongPress = 0x04 			// ����
} KEY_EventList_TypeDef;

/* ����״̬ */
typedef enum { 
	KEY_Action_Press = 0,		// ����
	KEY_Action_Release			// �ͷ�
} KEY_Action_TypeDef;

/* �����ṹ�� */
typedef struct {
	uint16_t									KEY_Count;		// ��������ʱ������
	KEY_Action_TypeDef				KEY_Action;		// ����״̬
	KEY_StatusList_TypeDef		KEY_Status;		// ״̬��״̬
	KEY_EventList_TypeDef			KEY_Event;		// �����¼�
} KEY_Configure_TypeDef;

/**
  * @brief ������ʼ��
  * @return ��
  */
void Key_Init(void);

/**
  * @brief ����״̬����ȡ����״̬
  * @return ��
  */
void Key_GetState(void);

/* �жϺ�����ʽ */
//void TIM3_IRQHandler(void) {
//	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
//		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
//		Key_GetState();  //����״̬��
//		
//		// ����
//		if(KeyCfg.KEY_Event == KEY_Event_SingleClick){
//
//		}
//		// ˫��
//		if(KeyCfg.KEY_Event == KEY_Event_DoubleClick){
//
//		}
//		// ����
//		if(KeyCfg.KEY_Event == KEY_Event_LongPress)	{
//
//		}
//		
//	}
//}

#endif
