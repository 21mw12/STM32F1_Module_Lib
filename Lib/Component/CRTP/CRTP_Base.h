#ifndef __CRTP_BASE_H_
#define __CRTP_BASE_H_

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�CRTPЭ��ĵײ㶨��
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2024/10/29
//
///////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>

/* CRTP���ݰ���󳤶� */
#define CRTP_DataPackage_Size			30

/* CRTPЭ��˿� */
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

/* CRTP��Link�˿ڵ�ͨ�� */
typedef enum {
  CRTP_LINK_Echo   = 0x00,
  CRTP_LINK_Source = 0x01,
  CRTP_LINK_Sink   = 0x02,
} CRTP_LINK_CHANNEL;

/* CRTPЭ�����ݰ� */
typedef struct _CRTPPacket {
  uint8_t size;                         // ���ݰ���data��С
  union {
    struct {
      union {
        uint8_t header;                 // ���ݰ�ͷ����ͨ���Ͷ˿���Ϣ
        struct {
#ifndef CRTP_HEADER_COMPAT
          uint8_t channel     : 2;      // ͨ����Ϣֻռ2λ����4��
          uint8_t reserved    : 2;			// ����
          uint8_t port        : 4;      // �˿���Ϣֻռ4λ����16��
#else
          uint8_t channel  : 2;
          uint8_t port     : 4;
          uint8_t reserved : 2;
#endif
        };
      };
      uint8_t data[CRTP_DataPackage_Size]; // ����λ
    };
    uint8_t raw[CRTP_DataPackage_Size + 1];
  };
} __attribute__((packed)) CRTP_Packet;

/* Э���ʹ�õ���·���������ṹ�� */
struct CRTP_LinkOperations {
  int (*setEnable)(bool enable);
  int (*sendPacket)(CRTP_Packet *pk);
  int (*receivePacket)(CRTP_Packet *pk);
  bool (*isConnected)(void);
  int (*reset)(void);
};


#endif
