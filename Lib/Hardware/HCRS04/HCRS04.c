#include "HCRS04.h"

uint16_t TIM_Trigger_Count = 0;

void HC_SR04_Init(void) {
	/* 开启时钟 */
	RCC_APB2PeriphClockCmd(HCSR04_Trig_Periph | HCSR04_Echo_Periph, ENABLE);

	/* 配置Trig引脚 */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = HCSR04_TRIG_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(HCSR04_Trig_PORT, &GPIO_InitStructure);
	GPIO_ResetBits(HCSR04_Trig_PORT, HCSR04_TRIG_Pin);

	/* 配置Echo引脚 */
	GPIO_InitStructure.GPIO_Pin = HCSR04_Echo_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(HCSR04_Echo_PORT, &GPIO_InitStructure);

	/* 配置定时器 */
	// 设置为每1ms触发一次
	TIM2_Init(1000, 72);
	TIM2_OFF();
}

/**
  * @brief 发送10us的脉冲触发信号
  * @return 无
  */
void HC_SR04_Start(void) {   
	GPIO_ResetBits(HCSR04_Trig_PORT, HCSR04_TRIG_Pin);                           
	Delay_us(10);
	// 给一个10us的高电平用来开启超声波
	GPIO_SetBits(HCSR04_Trig_PORT, HCSR04_TRIG_Pin);
	Delay_us(10);
	GPIO_ResetBits(HCSR04_Trig_PORT, HCSR04_TRIG_Pin);
}

/**
  * @brief 获取定时器计数器值
  * @return 计数器值
  */
uint32_t GetEchoTimer(void) {
	uint32_t TIM_Count = 0;
	
	// 用定时器的触发次数乘以1000就是溢出的秒数
	TIM_Count = TIM_Trigger_Count * 1000;
	// 再加上定时器剩余的计数就是总共的时间
	TIM_Count += TIM2_GetCount();
	
	TIM2_ClearCount();
	Delay_ms(50);
	
	return TIM_Count;
}

float HC_SR04_GetLength(void) {
	float Length = 0;
	float Length_Sum = 0;
	uint32_t Time = 0;
	int i = 0;

	/* 读5次取平均值 */
	while(i != Average_CalCount)    {
		/* 发出开始信号 */
		HC_SR04_Start();
		
		/* 等待Echo变为高电平，清除计数值，开启时钟 */
		while(GPIO_ReadInputDataBit(HCSR04_Echo_PORT, HCSR04_Echo_Pin) == 0);      
		TIM2_ClearCount();
		TIM_Trigger_Count = 0;
		TIM2_ON();
		
		i++;
		
		/* 等待Echo变为低电平，读取计数值，关闭时钟 */
		while( GPIO_ReadInputDataBit(HCSR04_Echo_PORT, HCSR04_Echo_Pin) == 1);
		TIM2_OFF();
		Time = GetEchoTimer();
		
		/* 计算本次的长度 */
		Length = ((float)Time / 58.0);
		Length_Sum += Length;    
	}
	
	// 取平均值
	Length = Length_Sum / Average_CalCount;

	return Length;
}

/* 定时器中断函数 */
void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);		
		TIM_Trigger_Count++;		
	}
}
