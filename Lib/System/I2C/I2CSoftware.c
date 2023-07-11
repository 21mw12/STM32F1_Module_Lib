#include "I2CSoftware.h"

///////////////////////////////////////////////////////////
//
// I2C����ʱ��ʵ��
//
///////////////////////////////////////////////////////////

/**
  * @brief  SCLд����
  * @param  state �� ��������
  * @retval ��
  */
void SCL_Write(uint8_t state) {
	GPIO_WriteBit(I2C_Software_PORT, I2C_Software_SCL_PIN, (BitAction)state);
}

/**
  * @brief  SDAд����
  * @param  state �� ��������
  * @retval ��
  */
void SDA_Write(uint8_t state) {
	GPIO_WriteBit(I2C_Software_PORT, I2C_Software_SDA_PIN, (BitAction)state);
}

/**
  * @brief  SDA������
  * @retval ��ȡ��������
  */
uint8_t SDA_Read(void) {
    uint8_t BitValue;
    BitValue = GPIO_ReadInputDataBit(I2C_Software_PORT, I2C_Software_SDA_PIN);
    Delay_us(10);
    return BitValue;
}

/**
  * @brief  I2C��ʼ
  * @param  GPIOx �� IO�˿���
  * @param  GPIO_Pin �� IO�˿�
  * @retval ��
  */
void I2C_Start(void) {
	SDA_Write(1);
	SCL_Write(1);
	SDA_Write(0);
	SCL_Write(0);
}

/**
  * @brief  I2Cֹͣ
  * @param  GPIOx �� IO�˿���
  * @param  GPIO_Pin �� IO�˿�
  * @retval ��
  */
void I2C_Stop(void) {
	SDA_Write(0);
	SCL_Write(1);
	SDA_Write(1);
}

/**
  * @brief  I2C����һ���ֽ�
  * @param  Byte Ҫ���͵�һ���ֽ�
  * @retval ��
  */
void I2C_SendByte(uint8_t Byte) {
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		SDA_Write(Byte & (0x80 >> i));
		SCL_Write(1);
		SCL_Write(0);
	}
	SCL_Write(1);	//�����һ��ʱ�ӣ�������Ӧ���ź�
	SCL_Write(0);
}

/**
  * @brief  I2C����һ���ֽ�
  * @retval ���յ�������
  */
uint8_t I2C_ReceiveByte(void) {
    uint8_t i;
    uint8_t Byte = 0x00;
    SDA_Write(1);
    for (i = 0; i < 8; i++) {
        SCL_Write(1);
        if (SDA_Read() == 1) {
            Byte |= (0x80 >> i);
        }
        SCL_Write(0);
    }
    return Byte;
}

/**
  * @brief  ����Ӧ��
  * @param  Ӧ����Ϣ
  * @retval ��
  */
void I2C_SendAck(uint8_t AckBit) {
    SDA_Write(AckBit);
    SCL_Write(1);
    SCL_Write(0);
}

/**
  * @brief  ����Ӧ��
  * @retval Ӧ����Ϣ
  */
uint8_t I2C_ReceiveAck(void) {
    uint8_t AckBit;
    SDA_Write(1);
    SCL_Write(1);
    AckBit = SDA_Read();
    SCL_Write(0);
    return AckBit;
}

///////////////////////////////////////////////////////////
//
// I2C��������ʵ��
//
///////////////////////////////////////////////////////////

void I2C_Software_Init(void) {
  RCC_APB2PeriphClockCmd(I2C_Software_GPIOPeriph, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = I2C_Software_SCL_PIN | I2C_Software_SDA_PIN;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(I2C_Software_PORT, &GPIO_InitStructure);
	
	SCL_Write(1);
	SDA_Write(1);
}

void I2C_Software_SendByte(uint8_t SlaveAddr, uint8_t writeAddr, uint8_t pBuffer) {
	I2C_Start();
	I2C_SendByte(SlaveAddr);
	I2C_SendByte(writeAddr);
	I2C_SendByte(pBuffer); 
	I2C_Stop();
}

void I2C_Software_SendArray(uint8_t SlaveAddr, uint8_t WriteAddr, uint8_t* pBuffer, u16 NumByteToWrite) {
	I2C_Start();
	I2C_SendByte(SlaveAddr);
	I2C_SendByte(WriteAddr);
	
	for (uint16_t i = 0; i < NumByteToWrite; i++) {
		I2C_SendByte(*(pBuffer + i)); 
	}
	
	I2C_Stop();
}

uint8_t I2C_Software_ReadByte(uint8_t SlaveAddr, uint8_t readAddr) {
	uint8_t data;

	I2C_Start();
	I2C_SendByte(SlaveAddr);
	I2C_SendByte(readAddr);
	data = I2C_ReceiveByte();
	I2C_Stop();

	return data;
}

void I2C_Software_ReadArray(uint8_t SlaveAddr, uint8_t readAddr, uint8_t* pBuffer, u16 NumByteToRead) {
	I2C_Start();
	I2C_SendByte(SlaveAddr);
	I2C_SendByte(readAddr);

	for (uint16_t i = 0; i < NumByteToRead; i++) {
		*(pBuffer + i) = I2C_ReceiveByte();
	}

	I2C_Stop();
}
