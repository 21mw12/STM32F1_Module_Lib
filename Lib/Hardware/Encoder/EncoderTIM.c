#include "EncoderTIM.h"

EncoderDirect Encoder_GetDirection(uint16_t* encoderCount) {
	static uint16_t lastCount;	// 记录上一次旋转值
	
	lastCount = *encoderCount;
	*encoderCount = TIM3_Encoder_Get();
	
	if (lastCount > *encoderCount) {
		return EncoderDirect_AntiClockwise;
	}
	else if (lastCount < *encoderCount) {
		return EncoderDirect_Clockwise;
	} else {
		return EncoderDirect_Idel;
	}
}
