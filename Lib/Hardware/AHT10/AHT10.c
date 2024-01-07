#include "AHT10.h"
#include "delay.h"
#include "I2C1Hardware.h"

void AHT10_Init(void) {
	I2C1_Hardware_StartSignal();
	
	I2C1_Hardware_SendWriteAddress(AHT10_ADDRESS);
	I2C1_Hardware_SendData(0xE1);
	I2C1_Hardware_SendData(0x08);
	I2C1_Hardware_SendData(0x00);
	
	I2C1_Hardware_StopSignal();
	
	Delay_ms(20);
}

void AHT10_SoftReset(void) {
	I2C1_Hardware_StartSignal();
	
	I2C1_Hardware_SendWriteAddress(AHT10_ADDRESS);
	I2C1_Hardware_SendData(0xBA);
	
	I2C1_Hardware_StopSignal();
	
	Delay_ms(20);
}

AHT10_State AHT10_GetData(float *Temp, float *Hum) {
  uint8_t Data[6];
	
	/* ����ָ������� */
	I2C1_Hardware_StartSignal();
	I2C1_Hardware_SendWriteAddress(AHT10_ADDRESS);
	I2C1_Hardware_SendData(0XAC);
	I2C1_Hardware_SendData(0X33);
	I2C1_Hardware_SendData(0x00);
	I2C1_Hardware_StopSignal();

	/* ��Ҫ����ʱ���ȴ�������� */
	Delay_ms(70);

	/* ��ȡ���� */
	I2C1_Hardware_StartSignal();
	I2C1_Hardware_SendReadAddress(AHT10_ADDRESS);
	for(uint8_t i = 0; i < 6; i++) {
		if(i == 5) I2C1_Hardware_CloseACKSignal();
		
		Data[i] = I2C1_Hardware_ReceiveData();
		
		if(i == 5) I2C1_Hardware_StopSignal();
	}
	I2C1_Hardware_OpenACKSignal();
	I2C1_Hardware_StopSignal();

	/* ���ݴ��� */
	if((Data[0] & 0x08) == 0 ) {	// ���״У׼ʹ��λ�Ƿ�Ϊ0
		AHT10_Init();
		return AHT10_State_Error;
	}
	else if((Data[0] & 0x80) == 0 )	{	// ���æ��ָʾ�Ƿ�Ϊ0
		
		/* ���ԭʼ��ʪ������ */
		uint32_t Temp_Original = ((Data[3] & 0x0f) << 16) | (Data[4] << 8) | Data[5];
		uint32_t Hum_Original = (Data[1] << 12) | (Data[2] << 4) | (Data[3] >> 4);

		/* �����ֲ���Ĺ�ʽת����ʪ�ȶ����� */
		*Temp = (Temp_Original * 200.0) / 1024.0 / 1024 - 50;
		*Hum = (Hum_Original * 100.0) / 1024.0 / 1024;

		return AHT10_State_Normal;
	}
	
	return AHT10_State_Error;	
}
