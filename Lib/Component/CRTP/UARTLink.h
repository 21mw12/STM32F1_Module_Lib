/*
 *    ||          ____  _ __
 * +------+      / __ )(_) /_______________ _____  ___
 * | 0xBC |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * +------+    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *  ||  ||    /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * Crazyflie control firmware
 *
 * Copyright (C) 2012 BitCraze AB
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
 * uartlink.c
 */
 
#ifndef __UART_LINK_H_
#define __UART_LINK_H_
 
///////////////////////////////////////////////////////////
//
// 文件功能：CRTP链路层使用UART实现功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/10/29
//
///////////////////////////////////////////////////////////

#include "CRTP_Base.h"

/* 数据链路层的数据包头 */
#define UARTLink_PacketHead						0x55
/* 数据链路层的串口数据缓存大小 */
#define UARTLink_DataCacheSize				20
/* 数据链路层的数据包缓存大小 */
#define UARTLink_PacketCacheSize			5

/**
  * @brief UART链路层初始化
  * @return 无
  */
void UARTLink_Init(void);

/**
  * @brief 获取UART链路层的操作
  * @return 链路层操作结构体
  */
struct CRTP_LinkOperations* UARTLink_GetLinkOp(void);

#endif
