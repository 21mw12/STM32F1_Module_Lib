#include "MotorEncoder.h"

void MotorEncoder_Init(void) {
	RCC_APB2PeriphClockCmd(Control_Periph, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = Control_PIN_1 | Control_PIN_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Control_PORT, &GPIO_InitStructure);
	
	TIM3_Encoder_Init();
	TIM2_PWM_Init(1000, 576, 0);
}

void MotorEncoder_SetState(enum MotorState state) {
	if (state == ForwardTurn) {
		GPIO_SetBits(Control_PORT, GPIO_Pin_2);
		GPIO_ResetBits(Control_PORT, GPIO_Pin_3);
	}
	else if (state == ReverseTurn) {
		GPIO_ResetBits(Control_PORT, GPIO_Pin_2);
		GPIO_SetBits(Control_PORT, GPIO_Pin_3);
	}
	else if (state == Stop) {
		GPIO_ResetBits(Control_PORT, GPIO_Pin_2);
		GPIO_ResetBits(Control_PORT, GPIO_Pin_3);
	}
}

void MotorEncoder_SetDutyCycle(int8_t DutyCycle) {
	TIM2_PWM2_SetCompare(DutyCycle);
}

float MotorEncoder_CalculateSpeed(void) {
	int16_t EncoderCount = TIM3_Encoder_GetClear();
	// 轮胎转了的圈数 = 当前计数值 / (齿轮比 * 转一圈的数值)
	// 速度 = 轮胎转了的圈数 * 轮胎周长 / 计算间隔时间
	float speed = (EncoderCount / (float) (Gear_Ratio * HoareEncoder_Circle_Count)) * Tyre_Perimeter / Calculate_Time;	// 计算轮胎转了几圈
	return speed;
}

