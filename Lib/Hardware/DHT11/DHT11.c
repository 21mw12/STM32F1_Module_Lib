#include "DHT11.h"
#include "Delay.h"

/**
  * @brief 将端口变为输出
  * @return 无
  */
void DHT11_IO_OUT (void){
	GPIO_InitTypeDef GPIO_InitStructure; 	
  GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DHT11_PORT, &GPIO_InitStructure);
}

/**
  * @brief 将端口变为输入
  * @return 无
  */
void DHT11_IO_IN (void) {
	GPIO_InitTypeDef GPIO_InitStructure; 	
  GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(DHT11_PORT, &GPIO_InitStructure);
}

/**
  * @brief DHT11端口复位，发出起始信号
  * @return 无
  */
void DHT11_RST(void) {
	DHT11_IO_OUT();
	
	GPIO_ResetBits(DHT11_PORT, DHT11_PIN);
	// 拉低至少18ms
	Delay_ms(20);
	GPIO_SetBits(DHT11_PORT, DHT11_PIN);
	// 主机拉高20~40us
	Delay_us(30);
}

/**
  * @brief 等待DHT11回应
  * @return 检测状态			0：未检测到DHT11
	* 										1：成功检测到DHT11
  */
uint8_t DHT11_Check(void){
    uint8_t timeout = 0;
    DHT11_IO_IN();

		// DHT11会拉低40~80us
    while(GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN) && timeout < 100) {
        timeout++;
        Delay_us(1);
    }
		
    if(timeout >= 100) {
			return 0;
		}
		
		// DHT11拉低后会再次拉高40~80us
		timeout = 0;
    while(!GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN) && timeout < 100) {
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

	// 等待变为低电平
	while(GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN) && timeout < 100) {
			timeout++;
			Delay_us(1);
	}
	
	// 等待变高电平
	timeout=0;
	while(!GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN) && timeout < 100){
			timeout++;
			Delay_us(1);
	}
	
	//等待40us
	Delay_us(40);
	
	return GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN);   
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

uint8_t DHT11_ReadData(uint8_t *temp, uint8_t *humi){
	uint8_t i;
	uint8_t	buf[5];
	
	// DHT11端口复位，发出起始信号
	DHT11_RST();
  // 等待DHT11回应
	if(DHT11_Check()){
		for(i = 0; i < 5; i++){
			buf[i] = DHT11_ReadByte();
		}
		if((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4]){	//数据校验
			*humi = buf[0];
			*temp = buf[2];
		}
	} else {
		return 0;
	}
	return 1;	    
}
