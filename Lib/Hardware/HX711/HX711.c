#include "HX711.h"
#include "Delay.h"

/* 初始重量 */
uint32_t originalData = 0;

void HX711_Init(void) {
	RCC_APB2PeriphClockCmd(HX711_Periph, ENABLE);
 
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = HX711_Pin_DT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(HX711_Port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = HX711_Pin_SCK;
	GPIO_Init(HX711_Port, &GPIO_InitStructure);  
	
	GPIO_SetBits(HX711_Port, HX711_Pin_SCK);
	
	Delay_ms(2000);
	originalData = HX711_ReadData();		// 获取初始重量（皮重）
}

void HX711_Reset(void) {
	GPIO_SetBits(HX711_Port, HX711_Pin_SCK);
	Delay_us(60);
}

uint32_t HX711_ReadData(void) {
	uint32_t result = 0;
	
	GPIO_SetBits(HX711_Port, HX711_Pin_DT);
	Delay_us(1);
	GPIO_ResetBits(HX711_Port, HX711_Pin_SCK);
	
	while(GPIO_ReadInputDataBit(HX711_Port, HX711_Pin_DT));
	
  for (uint8_t i = 0; i < 24; i++) {
		GPIO_SetBits(HX711_Port, HX711_Pin_SCK);
		result <<= 1;
		Delay_us(1);
		GPIO_ResetBits(HX711_Port, HX711_Pin_SCK);
		
		if (GPIO_ReadInputDataBit(HX711_Port, HX711_Pin_DT)) {
			result++;
		}
		Delay_us(1);
	}
	
	GPIO_SetBits(HX711_Port, HX711_Pin_SCK);
  result ^= 0x800000;		// 第25个脉冲下降沿时转换数据
	Delay_us(1);
	GPIO_ResetBits(HX711_Port, HX711_Pin_SCK);
	
	return result;
}

uint32_t HX711_GetWeight(void) {
	uint32_t weight = HX711_ReadData();
	
	if (weight > originalData) {	
		weight = (uint32_t)((float)(weight - originalData) / HX711_coefficient);
		return weight;
	}
	
	return 0;
}
