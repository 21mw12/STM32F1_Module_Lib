#include "I2C1Hardware.h"
#include <stdarg.h>

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

void I2C1_Hardware_StartSignal(void) {
	uint32_t To = I2C1_Timeout;
	
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)) {if((To--) == 0) return;};	// 等待总线空闲
	I2C_GenerateSTART(I2C1, ENABLE);		// 发送起始信号
	To = I2C1_Timeout;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) {if((To--) == 0) return;};	// 检测EV5事件
}

void I2C1_Hardware_StopSignal(void) {
	I2C_GenerateSTOP(I2C1, ENABLE);		// 发送停止信号
}

void I2C1_Hardware_SendWriteAddress(uint8_t Address) {
	uint32_t To = I2C1_Timeout;
	
	I2C_Send7bitAddress(I2C1, Address, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {if((To--) == 0) return;};		// 检测EV6事件
}

void I2C1_Hardware_SendReadAddress(uint8_t Address) {
	uint32_t To = I2C1_Timeout;
	
	I2C_Send7bitAddress(I2C1, Address, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {if((To--) == 0) return;};		// 检测EV6事件
}

void I2C1_Hardware_SendData(uint8_t Data) {
	uint32_t To = I2C1_Timeout;
	
	I2C_SendData(I2C1, Data);	 // 发送数据
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {if((To--) == 0) return;};		// 检测EV8事件
}

uint8_t I2C1_Hardware_ReceiveData(void) {
	uint32_t To = I2C1_Timeout;
	
	while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED)) {if((To--) == 0) return 0;};  //检测EV7事件
	return I2C_ReceiveData(I2C1);
}

void I2C1_Hardware_CloseACKSignal(void) {
	I2C_AcknowledgeConfig(I2C1, DISABLE);
}

void I2C1_Hardware_OpenACKSignal(void) {
	I2C_AcknowledgeConfig(I2C1, ENABLE);
}
