#ifndef __PSTWO_H
#define __PSTWO_H

///////////////////////////////////////////////////////////

// �ļ����ܣ�PS2�ֱ�����ع��ܺ���
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/12/30
//	
// ע��Դ��������www.yfrobot.com����Ϊpinggai
//
//     PS2�ֱ����ģʽ������ң�˷���ģ����0~255
//										 ����ң�˰�����Ч
//     PS2�ֱ��̵�ģʽ������ң�˼��䰴����Ч���Ƶ������Ͷ�Ӧ����ֵ
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* PS2����������Ϣ */
#define PS2_Periph				RCC_APB2Periph_GPIOB
#define PS2_PORT					GPIOB
#define PS2_DAT_PIN 			GPIO_Pin_12
#define PS2_CMD_PIN 			GPIO_Pin_13
#define PS2_CS_PIN 				GPIO_Pin_14
#define PS2_CLK_PIN 			GPIO_Pin_15

/* PS2������Ϣ */
#define PS2_SELECT				0
#define PS2_L3						1
#define PS2_R3						2
#define PS2_START					3
#define PS2_UP						4
#define PS2_RIGHT					5
#define PS2_DOWN					6
#define PS2_LEFT					7
#define PS2_L2						8
#define PS2_R2						9
#define PS2_L1						10
#define PS2_R1						11
#define PS2_TRIANGLE			12
#define PS2_CIRCLE				13
#define PS2_FORK					14
#define PS2_SQUARE				15
#define PS2_PSS_RX				16
#define PS2_PSS_RY				17
#define PS2_PSS_LX				18
#define PS2_PSS_LY				19

enum PS2_Mode {
	PS2_Mode_Red = 0,
	PS2_Mode_Green,
	PS2_Modeeee_Error
};

enum PS2_Button_State {
	PS2_BUTTON_STATE_NULL = 0,
	PS2_BUTTON_STATE_PUSH,
};

/**
  * @brief PS2�ֱ���ʼ��
  * @return ��
  */
void PS2_Init(void);

/**
  * @brief ��ȡPS2�ֱ�����ģʽ
  * @return PS2�ֱ�����ģʽ
  */
enum PS2_Mode PS2_GetMode(void);

/**
  * @brief PS2��ȡ���а�������
  * @return ��
  */
void PS2_ReadData(void);

/**
  * @brief ����ӦPS2�ֱ������Ƿ��а���
  * @param CheckButton PS2�ֱ��������ο������궨�壩
  * @return ����״̬
  */
enum PS2_Button_State PS2_CheckButton(uint8_t CheckButton);

/**
  * @brief ��ȡPS2�ֱ�ң�˵�ģ���������ں��ģʽ����Ч����
  * @param Joystick PS2ң�ˣ��ο������궨�壩
  * @return ң�˵�ģ����
  */
uint8_t PS2_GetJoystickData(uint8_t Joystick);

/**
  * @brief ����������ݻ���
  * @return ��
  */
void PS2_ClearData(void);

#endif





