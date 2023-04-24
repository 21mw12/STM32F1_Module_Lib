#include "stm32f10x.h"
#include "delay.h"

///////////////////////////////////////////////////////////
//
// �ļ����ܣ����ģ��I2C�Ļ�������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/04/21
//
///////////////////////////////////////////////////////////

/* I2CĬ�ϵĶ˿���Ϣ */
#define I2C_PORT		GPIOB
#define SCL_PIN			GPIO_Pin_8
#define SDA_PIN			GPIO_Pin_9

/**
  * @brief  SCLд����
  * @param  state �� ��������
  * @retval ��
  */
void SCL_Write(uint8_t state);

/**
  * @brief  SDAд����
  * @param  state �� ��������
  * @retval ��
  */
void SDA_Write(uint8_t state);

/**
  * @brief  SDA������
  * @retval ��ȡ��������
  */
uint8_t SDA_Read(void);

/**
  * @brief  I2C��ʼ
  * @param  GPIOx �� IO�˿���
  * @param  GPIO_Pin �� IO�˿�
  * @retval ��
  */
void I2C_Start(void);

/**
  * @brief  I2Cֹͣ
  * @param  GPIOx �� IO�˿���
  * @param  GPIO_Pin �� IO�˿�
  * @retval ��
  */
void I2C_Stop(void);

/**
  * @brief  I2C����һ���ֽ�
  * @param  Byte Ҫ���͵�һ���ֽ�
  * @retval ��
  */
void I2C_SendByte(uint8_t Byte);

/**
  * @brief  I2C����һ���ֽ�
  * @retval ���յ�������
  */
uint8_t I2C_ReceiveByte(void);

/**
  * @brief  ����Ӧ��
  * @param  Ӧ����Ϣ
  * @retval ��
  */
void I2C_SendAck(uint8_t AckBit);

/**
  * @brief  ����Ӧ��
  * @retval Ӧ����Ϣ
  */
uint8_t I2C_ReceiveAck(void);
