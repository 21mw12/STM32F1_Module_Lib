#ifndef __CAN_H
#define __CAN_H

///////////////////////////////////////////////////////////
//
// 文件功能：CAN总线的基础功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/02/21
//
// 注：波特率 = PCLK1 / ((SWJ + BS1 + BS2) * BRP)
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* CAN配置 */
#define SWJ			CAN_SJW_1tq		// 范围：CAN_SJW_1tq ~ CAN_SJW_4tq
#define BS1			CAN_BS1_3tq		// 范围：CAN_BS1_1tq ~ CAN_BS1_16tq
#define BS2			CAN_BS2_2tq		// 范围：CAN_BS2_1tq ~	 CAN_BS2_8tq
#define BRP			60						//

/* CAN接收到的数据 */
extern uint8_t CAN1_RxPacket[8];

/**
  * @brief CAN总线初始化
  * @return 无
  */
void CAN1_Init(void);

/**
  * @brief CAN总线发送数据，最多为8字节
  * @param Data 发送的数据
	* @param Len 发送的数据数量
  * @return 0 表示发送失败
	* 				1 表示发送成功
  */
uint8_t CAN1_Send(uint8_t* Data, uint8_t Len);

//uint8_t CAN1_Receive(uint8_t* Data);

#endif
