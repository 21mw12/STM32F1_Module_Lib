#include "AlarmClock.h"

void AlarmClock_ExchangeWorkState(AlarmClock* aClock) {
	Clock_ExchangeWorkState(&aClock->cTime);
}

void Clock_SetTime(AlarmClock* aClock, uint8_t newHour, uint8_t newMinute) {
	aClock->cTime.hour = newHour;
	aClock->cTime.minute = newMinute;	
}

void AlarmClock_HeartBeat(AlarmClock* aClock) {
	if (aClock->cTime.cTimeState == cTimeState_Working) {
		if (Clock_ReduceTime(&aClock->cTime) == cTimeState_Idel) {
			aClock->cTime.cTimeState = cTimeState_Idel;
			aClock->aClockWarnState = aClockState_Warn;
		}
	}
}

void AlarmClock_Warnning(AlarmClock* aClock) {
	static uint8_t cnt = 5;
	
	if (aClock->aClockWarnState == aClockState_Warn && cnt != 0) {
		cnt--;
		aClock->warningFunction();
	}
	
	if (cnt == 0) {
		cnt = 5;
		aClock->aClockWarnState = aClockState_Idel;
	}
}
