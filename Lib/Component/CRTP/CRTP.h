/**
 *    ||          ____  _ __
 * +------+      / __ )(_) /_______________ _____  ___
 * | 0xBC |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * +------+    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *  ||  ||    /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * Crazyflie control firmware
 *
 * Copyright (C) 2011-2012 Bitcraze AB
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, in version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * crtp.h - CrazyRealtimeTransferProtocol stack
 */

#ifndef __CRTP_H_
#define __CRTP_H_

///////////////////////////////////////////////////////////
//
// 文件功能：CRTP协议层功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/10/29
//
///////////////////////////////////////////////////////////

#include "CRTP_Base.h"

/* CRTP协议发送接收数据包缓存大小 */
#define CRTP_TX_QUEUE_SIZE 		5
#define CRTP_RX_QUEUE_SIZE 		5

/* 定义回调函数 */
typedef void (*CrtpCallback)(CRTP_Packet *);

/**
  * @brief CRTP协议初始化
  * @return 无
  */
void CRTP_Init(void);

/**
  * @brief CRTP协议测试
  * @return True表示正常
  */
bool CRTP_Test(void);

/**
  * @brief CRTP协议连接状态（暂时没实现）
  * @return True表示正常
  */
bool CRTP_IsConnected(void);

/**
  * @brief CRTP协议重启（暂时没实现）
  * @return 无意义
  */
int CRTP_Reset(void);

/**
  * @brief 初始化CRTP对应端口的任务队列
  * @param portId 端口号
  * @return 无
  */
void CRTP_InitTaskQueue(CRTP_Port portId);

/**
  * @brief CRTP接收数据包
  * @param portId 端口号
  * @param p 数据包
  * @return 是否接收到
  */
int CRTP_ReceivePacket(CRTP_Port portId, CRTP_Packet *p);

/**
  * @brief CRTP阻塞式接收数据包
  * @param portId 端口号
  * @param p 数据包
  * @return 是否接收到
  */
int CRTP_ReceivePacketBlock(CRTP_Port portId, CRTP_Packet *p);

/**
  * @brief CRTP等待固定时间接收数据包
  * @param portId 端口号
  * @param p 数据包
  * @return 是否接收到
  */
int CRTP_ReceivePacketWait(CRTP_Port portId, CRTP_Packet *p, int wait);

/**
  * @brief CRTP发送数据包
  * @param p 数据包
  * @return 是否发送成功
  */
int CRTP_SendPacket(CRTP_Packet *p);

/**
  * @brief CRTP阻塞式发送数据包
  * @param p 数据包
  * @return 是否发送成功
  */
int CRTP_SendPacketBlock(CRTP_Packet *p);

/**
  * @brief 获取CRTP剩余空闲的接收队列缓存大小
  * @return 空闲队列大小
  */
int CRTP_GetFreeTxQueuePackets(void);

/**
  * @brief 注册CRTP对应端口的回调函数
  * @return 无
  */
void CRTP_RegisterPortCB(int port, CrtpCallback cb);


///**
// * Initializes the queue and dispatch of an task.
// *
// * @param[in] taskId The id of the CRTP task
// */
//void crtpInitTaskQueue(CRTPPort taskId);

///**
// * Register a callback to be called for a particular port.
// *
// * @param[in] port Crtp port for which the callback is set
// * @param[in] cb Callback that will be called when a packet is received on
// *            'port'.
// *
// * @note Only one callback can be registered per port! The last callback
// *       registered will be the one called
// */
//void crtpRegisterPortCB(int port, CrtpCallback cb);

///**
// * Put a packet in the TX task
// *
// * If the TX stack is full, the oldest lowest priority packet is dropped
// *
// * @param[in] p CRTP_Packet to send
// */
//int crtpSendPacket(CRTP_Packet *p);

///**
// * Put a packet in the TX task
// *
// * If the TX stack is full, the function block until one place is free (Good for console implementation)
// */
//int crtpSendPacketBlock(CRTP_Packet *p);

///**
// * Fetch a packet with a specidied task ID.
// *
// * @param[in]  taskId The id of the CRTP task
// * @param[out] p      The CRTP Packet with infomation (unchanged if nothing to fetch)
// *
// * @returns status of fetch from queue
// */
//int crtpReceivePacket(CRTPPort taskId, CRTP_Packet *p);

///**
// * Fetch a packet with a specidied task ID. Wait some time befor giving up
// *
// * @param[in]  taskId The id of the CRTP task
// * @param[out] p      The CRTP Packet with infomation (unchanged if nothing to fetch)
// * @param[in] wait    Wait time in milisecond
// *
// * @returns status of fetch from queue
// */
//int crtpReceivePacketWait(CRTPPort taskId, CRTP_Packet *p, int wait);

///**
// * Get the number of free tx packets in the queue
// *
// * @return Number of free packets
// */
//int crtpGetFreeTxQueuePackets(void);

///**
// * Wait for a packet to arrive for the specified taskID
// *
// * @param[in]  taskId The id of the CRTP task
// * @paran[out] p      The CRTP Packet with information
// *
// * @return status of fetch from queue
// */
//int crtpReceivePacketBlock(CRTPPort taskId, CRTP_Packet *p);

///**
// * Check if the connection timeout has been reached, otherwise
// * we will assume that we are connected.
// *
// * @return true if conencted, otherwise false
// */
//bool crtpIsConnected(void);



#endif
