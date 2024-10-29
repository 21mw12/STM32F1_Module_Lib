#ifndef __CRTP_BASE_H_
#define __CRTP_BASE_H_

///////////////////////////////////////////////////////////
//
// 文件功能：CRTP协议的底层定义
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/10/29
//
///////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>

/* CRTP数据包最大长度 */
#define CRTP_DataPackage_Size			30

/* CRTP协议端口 */
typedef enum {
  CRTP_PORT_CONSOLE          = 0x00,
  CRTP_PORT_PARAM            = 0x02,
  CRTP_PORT_SETPOINT         = 0x03,
  CRTP_PORT_MEM              = 0x04,
  CRTP_PORT_LOG              = 0x05,
  CRTP_PORT_LOCALIZATION     = 0x06,
  CRTP_PORT_SETPOINT_GENERIC = 0x07,
  CRTP_PORT_SETPOINT_HL      = 0x08,
  CRTP_PORT_PLATFORM         = 0x0D,
  CRTP_PORT_LINK             = 0x0F,
} CRTP_Port;

/* CRTP中Link端口的通道 */
typedef enum {
  CRTP_LINK_Echo   = 0x00,
  CRTP_LINK_Source = 0x01,
  CRTP_LINK_Sink   = 0x02,
} CRTP_LINK_CHANNEL;

/* CRTP协议数据包 */
typedef struct _CRTPPacket {
  uint8_t size;                         // 数据包中data大小
  union {
    struct {
      union {
        uint8_t header;                 // 数据包头包含通道和端口信息
        struct {
#ifndef CRTP_HEADER_COMPAT
          uint8_t channel     : 2;      // 通道信息只占2位，共4种
          uint8_t reserved    : 2;			// 保留
          uint8_t port        : 4;      // 端口信息只占4位，共16种
#else
          uint8_t channel  : 2;
          uint8_t port     : 4;
          uint8_t reserved : 2;
#endif
        };
      };
      uint8_t data[CRTP_DataPackage_Size]; // 数据位
    };
    uint8_t raw[CRTP_DataPackage_Size + 1];
  };
} __attribute__((packed)) CRTP_Packet;

/* 协议层使用的链路层操作句柄结构体 */
struct CRTP_LinkOperations {
  int (*setEnable)(bool enable);
  int (*sendPacket)(CRTP_Packet *pk);
  int (*receivePacket)(CRTP_Packet *pk);
  bool (*isConnected)(void);
  int (*reset)(void);
};


#endif
