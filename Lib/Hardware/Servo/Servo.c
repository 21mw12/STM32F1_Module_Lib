#include "Servo.h"
#include "TIM2PWM.h"

void Servo_Init(void) {
	TIM2_PWM_Init(7200, 200, 0);
}

void Servo_SetAngle(float Angle) {
	/**
	  * 舵机角度0~180对应电平反转比较值0~960
	  * 的倍数关系为5.333...
	  */
	TIM2_PWM1_SetCompare(Angle * 5.333);
}