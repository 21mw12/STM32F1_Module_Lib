#include "I2CSoftware.h"

/**
  * @brief  SCL写数据
  * @param  state ： 数据内容
  * @retval 无
  */
void SCL_Write(uint8_t state) {
	GPIO_WriteBit(I2C_Software_Port, I2C_Software_Pin_SCL, (BitAction)state);
  Delay_us(10);
}

/**
  * @brief  SDA写数据
  * @param  state ： 数据内容
  * @retval 无
  */
void SDA_Write(uint8_t state) {
	GPIO_WriteBit(I2C_Software_Port, I2C_Software_Pin_SDA, (BitAction)state);
  Delay_us(10);
}

/**
  * @brief  SDA读数据
  * @retval 读取到的数据
  */
uint8_t SDA_Read(void) {
	uint8_t BitValue;
	BitValue = GPIO_ReadInputDataBit(I2C_Software_Port, I2C_Software_Pin_SDA);
	Delay_us(10);
	return BitValue;
}

///////////////////////////////////////////////////////////
//
// I2C基础时序实现
//
///////////////////////////////////////////////////////////

void I2C_Software_StartSignal(void) {
	SDA_Write(1);
	SCL_Write(1);
	SDA_Write(0);
	SCL_Write(0);
}

void I2C_Software_StopSignal(void) {
	SDA_Write(0);
	SCL_Write(1);
	SDA_Write(1);
}

void I2C_Software_SendData(uint8_t Byte) {
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		SDA_Write(Byte & (0x80 >> i));
		SCL_Write(1);
		SCL_Write(0);
	}
//	SCL_Write(1);	//额外的一个时钟，不处理应答信号
//	SCL_Write(0);
	I2C_Software_ReceiveAck();
}

uint8_t I2C_Software_ReceiveByte(void) {
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

void I2C_Software_SendAck(uint8_t AckBit) {
    SDA_Write(AckBit);
    SCL_Write(1);
    SCL_Write(0);
}

uint8_t I2C_Software_ReceiveAck(void) {
    uint8_t AckBit;
    SDA_Write(1);
    SCL_Write(1);
    AckBit = SDA_Read();
    SCL_Write(0);
    return AckBit;
}

///////////////////////////////////////////////////////////
//
// I2C基础功能实现
//
///////////////////////////////////////////////////////////

void I2C_Software_Init(void) {
  RCC_APB2PeriphClockCmd(I2C_Software_GPIOPeriph, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = I2C_Software_Pin_SCL | I2C_Software_Pin_SDA;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(I2C_Software_Port, &GPIO_InitStructure);
	
	SCL_Write(1);
	SDA_Write(1);
}

void I2C_Software_SendByte(uint8_t SlaveAddr, uint8_t writeAddr, uint8_t pBuffer) {
	I2C_Software_StartSignal();
	I2C_Software_SendData(SlaveAddr);
	I2C_Software_SendData(writeAddr);
	I2C_Software_SendData(pBuffer); 
	I2C_Software_StopSignal();
}

void I2C_Software_SendArray(uint8_t SlaveAddr, uint8_t WriteAddr, uint8_t* pBuffer, u16 NumByteToWrite) {
	I2C_Software_StartSignal();
	I2C_Software_SendData(SlaveAddr);
	I2C_Software_SendData(WriteAddr);
	
	for (uint16_t i = 0; i < NumByteToWrite; i++) {
		I2C_Software_SendData(*(pBuffer + i)); 
	}
	
	I2C_Software_StopSignal();
}

uint8_t I2C_Software_ReadByte(uint8_t SlaveAddr, uint8_t readAddr) {
	uint8_t data;

	I2C_Software_StartSignal();
	I2C_Software_SendData(SlaveAddr);
	I2C_Software_SendData(readAddr);
	data = I2C_Software_ReceiveByte();
	I2C_Software_StopSignal();

	return data;
}

void I2C_Software_ReadArray(uint8_t SlaveAddr, uint8_t readAddr, uint8_t* pBuffer, u16 NumByteToRead) {
	I2C_Software_StartSignal();
	I2C_Software_SendData(SlaveAddr);
	I2C_Software_SendData(readAddr);

	for (uint16_t i = 0; i < NumByteToRead; i++) {
		*(pBuffer + i) = I2C_Software_ReceiveByte();
	}

	I2C_Software_StopSignal();
}
