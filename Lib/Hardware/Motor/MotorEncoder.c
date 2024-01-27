#include "MotorEncoder.h"
#include "TIM2PWM.h"
#include "TIM3Encoder.h"

void MotorEncoder_Init(void) {
	/* 电机控制IO口初始化 */
	RCC_APB2PeriphClockCmd(Control_Periph, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = Control_Pin_1 | Control_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Control_Port, &GPIO_InitStructure);
	
	/* 电机定时器初始化 */
	TIM3_Encoder_Init();
	TIM2_PWM_Init(1000, 576, 0);
}

void MotorEncoder_SetState(enum MotorState state) {
	if (state == ForwardTurn) {
		GPIO_SetBits(Control_Port, GPIO_Pin_2);
		GPIO_ResetBits(Control_Port, GPIO_Pin_3);
	}
	else if (state == ReverseTurn) {
		GPIO_ResetBits(Control_Port, GPIO_Pin_2);
		GPIO_SetBits(Control_Port, GPIO_Pin_3);
	}
	else if (state == Stop) {
		GPIO_ResetBits(Control_Port, GPIO_Pin_2);
		GPIO_ResetBits(Control_Port, GPIO_Pin_3);
	}
}

void MotorEncoder_SetDutyCycle(uint16_t DutyCycle) {
	TIM2_PWM2_SetCompare(DutyCycle);
}

float MotorEncoder_CalculateRPS(enum MotorState state) {
	int16_t EncoderCount = TIM3_Encoder_GetClear();
	
	/* 反转处理 */
//	if (state == ReverseTurn) {
//		EncoderCount = 0xFFFF - EncoderCount;
//		TIM3_overtime--;
//	}
	
	return (float)(EncoderCount + 0xFFFF * TIM3_overtime) / (Gear_Ratio * HoareEncoder_Circle_Count);
}

float MotorEncoder_CalculateSpeed(enum MotorState state) {
	float speed = MotorEncoder_CalculateRPS(state) * Tyre_Perimeter;
	return speed;
}

float MotorEncoder_CalculateDistance(enum MotorState state) {
	float distance = MotorEncoder_CalculateSpeed(state) * Calculate_Time;
	return distance;
}

