#include "key.h"

#if Key_Interrupt
	void Key_Init(void){
		RCC_APB2PeriphClockCmd(Key_Periph, ENABLE);
		
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStructure.GPIO_Pin = Key_Pin;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(Key_Port, &GPIO_InitStructure);
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
		GPIO_EXTILineConfig(Key_PortSource, Key_PinSource);

		// 初始化EXTI边沿检测及控制
		EXTI_InitTypeDef EXTI_InitStruct;
		EXTI_InitStruct.EXTI_Line = Key_EXTI_Line;
		EXTI_InitStruct.EXTI_LineCmd = ENABLE;
		EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;//选择响应模式
		EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;	//	EXTI_Trigger_Falling：下降沿触发
																													//	EXTI_Trigger_Rising： 上升沿触发
																													//	EXTI_Trigger_Rising_Falling： 上升和下降沿均触发
		EXTI_Init(&EXTI_InitStruct);

		// 配置中断分组
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		NVIC_InitTypeDef NVIC_InitStruct;
		NVIC_InitStruct.NVIC_IRQChannel = Key_EXTI_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
		NVIC_Init(&NVIC_InitStruct);
	}
#else
	void Key_Init(void){
		RCC_APB2PeriphClockCmd(Key_Periph, ENABLE);
		
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStructure.GPIO_Pin = Key_Pin;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(Key_Port, &GPIO_InitStructure);			
	}

	uint8_t Key_Get(void) {
		if (GPIO_ReadInputDataBit(Key_Port, Key_Pin) == 0) {
			Delay_ms(20);
			while (GPIO_ReadInputDataBit(Key_Port, Key_Pin) == 0);
			Delay_ms(20);
			return 1;
		}
		return 0;
	}
#endif






