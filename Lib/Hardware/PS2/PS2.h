#ifndef __PSTWO_H
#define __PSTWO_H

///////////////////////////////////////////////////////////

// 文件功能：PS2手柄的相关功能函数
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/12/30
//	
// 注：源代码来自www.yfrobot.com作者为pinggai
//
//     PS2手柄红灯模式—左右遥杆发送模拟量0~255
//										 左右遥杆按键有效
//     PS2手柄绿灯模式—左右遥杆及其按键无效，推到顶发送对应按键值
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* PS2引脚配置信息 */
#define PS2_Periph				RCC_APB2Periph_GPIOB
#define PS2_PORT					GPIOB
#define PS2_DAT_PIN 			GPIO_Pin_12
#define PS2_CMD_PIN 			GPIO_Pin_13
#define PS2_CS_PIN 				GPIO_Pin_14
#define PS2_CLK_PIN 			GPIO_Pin_15

/* PS2按键信息 */
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
  * @brief PS2手柄初始化
  * @return 无
  */
void PS2_Init(void);

/**
  * @brief 获取PS2手柄工作模式
  * @return PS2手柄工作模式
  */
enum PS2_Mode PS2_GetMode(void);

/**
  * @brief PS2获取所有按键数据
  * @return 无
  */
void PS2_ReadData(void);

/**
  * @brief 检查对应PS2手柄按键是否有按下
  * @param CheckButton PS2手柄按键（参考上述宏定义）
  * @return 按键状态
  */
enum PS2_Button_State PS2_CheckButton(uint8_t CheckButton);

/**
  * @brief 获取PS2手柄遥杆的模拟量（仅在红灯模式下有效果）
  * @param Joystick PS2遥杆（参考上述宏定义）
  * @return 遥杆的模拟量
  */
uint8_t PS2_GetJoystickData(uint8_t Joystick);

/**
  * @brief 清除所有数据缓存
  * @return 无
  */
void PS2_ClearData(void);

#endif





