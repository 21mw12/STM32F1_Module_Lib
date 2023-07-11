#include "I2C1Hardware.h"

void I2C1_Hardware_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);

	I2C_InitTypeDef I2C_InitStructure;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = I2C1_HostAddress;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = I2C1_Speed; 
	I2C_Init(I2C1, &I2C_InitStructure);
	
	I2C_Cmd(I2C1, ENABLE);
}

void I2C1_Hardware_SendByte(uint8_t slaveAddr, uint8_t writeAddr, uint8_t pBuffer){
	I2C_GenerateSTART(I2C1, ENABLE);
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C1, slaveAddr, I2C_Direction_Transmitter);
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	I2C_SendData(I2C1, writeAddr);
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2C1, pBuffer);
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_GenerateSTOP(I2C1, ENABLE);
}

void I2C1_Hardware_SendArray(uint8_t slaveAddr, uint8_t writeAddr, uint8_t* pBuffer, uint16_t NumByteToWrite) {
	I2C_GenerateSTART(I2C1, ENABLE);
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C1, slaveAddr, I2C_Direction_Transmitter);
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	I2C_SendData(I2C1, writeAddr);
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	while(NumByteToWrite--) {
		I2C_SendData(I2C1, *pBuffer);
		pBuffer++;
			while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	}
	I2C_GenerateSTOP(I2C1, ENABLE);
}

uint8_t I2C1_Hardware_ReadByte(uint8_t slaveAddr, uint8_t readAddr) {
	uint8_t data;
	
		while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2C1, ENABLE);
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C1, slaveAddr, I2C_Direction_Transmitter); 
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	I2C_Cmd(I2C1, ENABLE);
	I2C_SendData(I2C1, readAddr);
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_GenerateSTART(I2C1, ENABLE);
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C1, slaveAddr, I2C_Direction_Receiver);
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	I2C_AcknowledgeConfig(I2C1, DISABLE);
	I2C_GenerateSTOP(I2C1, ENABLE);
	data = I2C_ReceiveData(I2C1);
	
	return data;
}

uint8_t I2C1_Hardware_ReadArray(uint8_t slaveAddr, uint8_t readAddr, uint8_t* pBuffer, uint16_t NumByteToRead){ 
	u32 cou = I2C1_Timeout;
	
		while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)){if((cou--)==0)return 0;}
	I2C_GenerateSTART(I2C1, ENABLE);
	cou = I2C1_Timeout;
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)){if((cou--)==0)return 0;}
	I2C_Send7bitAddress(I2C1, slaveAddr,  I2C_Direction_Transmitter);
	cou = I2C1_Timeout;
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)){if((cou--)==0)return 0;}
	I2C_Cmd(I2C1, ENABLE);
	I2C_SendData(I2C1, readAddr);
	cou = I2C1_Timeout;
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)){if((cou--)==0)return 0;}
	I2C_GenerateSTART(I2C1, ENABLE);
	cou = I2C1_Timeout;
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)){if((cou--)==0)return 0;}
	I2C_Send7bitAddress(I2C1, slaveAddr, I2C_Direction_Receiver);
	cou = I2C1_Timeout;
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)){if((cou--)==0)return 0;}
	
	while(NumByteToRead) {
		if(NumByteToRead == 1) {
			I2C_AcknowledgeConfig(I2C1, DISABLE);
			I2C_GenerateSTOP(I2C1, ENABLE);
		}
		if(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)) {
			*pBuffer = I2C_ReceiveData(I2C1);
			pBuffer++;
			NumByteToRead--;
		}
	}
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);		
	return 1;
}
