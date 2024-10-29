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
// �ļ����ܣ�CRTP��·��ʹ��UARTʵ�ֹ���
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2024/10/29
//
///////////////////////////////////////////////////////////

#include "CRTP_Base.h"

/* ������·������ݰ�ͷ */
#define UARTLink_PacketHead						0x55
/* ������·��Ĵ������ݻ����С */
#define UARTLink_DataCacheSize				20
/* ������·������ݰ������С */
#define UARTLink_PacketCacheSize			5

/**
  * @brief UART��·���ʼ��
  * @return ��
  */
void UARTLink_Init(void);

/**
  * @brief ��ȡUART��·��Ĳ���
  * @return ��·������ṹ��
  */
struct CRTP_LinkOperations* UARTLink_GetLinkOp(void);

#endif
