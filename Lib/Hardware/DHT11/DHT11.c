#include "DHT11.h"
#include "Delay.h"

/**
  * @brief 将端口变为输出
  * @return 无
  */
void DHT11_IO_OUT (void){
	GPIO_InitTypeDef GPIO_InitStructure; 	
  GPIO_InitStructure.GPIO_Pin = DHT11_Pin 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DHT11_Port, &GPIO_InitStructure);
}

/**
  * @brief 将端口变为输入
  * @return 无
  */
void DHT11_IO_IN (void) {
	GPIO_InitTypeDef GPIO_InitStructure; 	
  GPIO_InitStructure.GPIO_Pin = DHT11_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(DHT11_Port, &GPIO_InitStructure);
}

/**
  * @brief DHT11端口复位，发出起始信号
  * @return 无
  */
void DHT11_RST(void) {
	DHT11_IO_OUT();
	
	GPIO_ResetBits(DHT11_Port, DHT11_Pin);
	Delay_ms(20);	// 拉低至少18ms
	GPIO_SetBits(DHT11_Port, DHT11_Pin);
	Delay_us(30);	// 主机拉高20~40us
}

/**
  * @brief 等待DHT11回应
  * @return 检测状态			0：未检测到DHT11
	* 										1：成功检测到DHT11
  */
uint8_t DHT11_Check(void){
    uint8_t timeout = 0;
    DHT11_IO_IN();

    while(GPIO_ReadInputDataBit(DHT11_Port, DHT11_Pin) && timeout < 100) {	// DHT11会拉低40~80us
        timeout++;
        Delay_us(1);
    }
		
    if(timeout >= 100) {
			return 0;
		}
		
		timeout = 0;
    while(!GPIO_ReadInputDataBit(DHT11_Port, DHT11_Pin) && timeout < 100) {	// DHT11拉低后会再次拉高40~80us
        timeout++;
        Delay_us(1);
    }
		
    if(timeout >= 100) {
			return 0;
		}
		
    return 1;
}

/**
  * @brief 从DHT11读取一位数据
  * @return 数据1或0
  */
uint8_t DHT11_ReadBit(void){
	uint8_t timeout=0;

	while(GPIO_ReadInputDataBit(DHT11_Port, DHT11_Pin) && timeout < 100) {	// 等待变为低电平
			timeout++;
			Delay_us(1);
	}
	
	timeout=0;
	while(!GPIO_ReadInputDataBit(DHT11_Port, DHT11_Pin) && timeout < 100){	// 等待变高电平
			timeout++;
			Delay_us(1);
	}
	
	Delay_us(40);// 等待40us
	
	return GPIO_ReadInputDataBit(DHT11_Port, DHT11_Pin);   
}

/**
  * @brief 从DHT11读取一字节数据
  * @return 读到的数据
  */
uint8_t DHT11_ReadByte(void){
    uint8_t i, data;
    data = 0;
    for (i = 0; i < 8; i++){ 
        data <<= 1; 
        data |= DHT11_ReadBit();
    }						    
    return data;
}


uint8_t DHT11_Init (void) {
	RCC_APB2PeriphClockCmd(DHT11_Periph, ENABLE);
	
	DHT11_RST();
	return DHT11_Check();
}

uint8_t DHT11_ReadData(uint8_t *Temp, uint8_t *Hum){
	uint8_t i;
	uint8_t	buf[5];
	
	DHT11_RST();	// DHT11端口复位，发出起始信号

	if(DHT11_Check()){	// 等待DHT11回应
		for(i = 0; i < 5; i++){
			buf[i] = DHT11_ReadByte();
		}
		/* 数据校验 */
		if((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4]){	
			*Hum = buf[0];
			*Temp = buf[2];
		}
	} else {
		return 0;
	}
	return 1;	    
}
