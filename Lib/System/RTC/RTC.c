#include "RTC.h"
#include "BKP.h"
#include <time.h>

struct tm RTC_Time_Date;

void RTC_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);	
	
	PWR_BackupAccessCmd(ENABLE);
	
	/* 如果没有完全断电就不初始化RTC配置 */
	if (BKP_Read(RTC_Sign_BPKDR) != 0x5A5A) {
		RCC_LSEConfig(RCC_LSE_ON);
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) != SET)
		
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);
		
		RTC_WaitForSynchro();		// 等待同部署
		RTC_WaitForLastTask();	// 等待上一次写操作完成
		
		/* 配置预分频器 */
		RTC_SetPrescaler(32768 - 1);
		RTC_WaitForLastTask();
		
		/* 配置计数器的默认值 */
		RTC_SetCounter(RTC_Count_Default);
		RTC_WaitForLastTask();
		
		BKP_Write(RTC_Sign_BPKDR, 0x5A5A);
	} else {
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
	}
	
}

void RTC_SetTime(uint16_t Year, uint8_t Month, uint8_t Day, uint8_t Hour, uint8_t Minute, uint8_t Second) {
	time_t time_cnt;
	
	RTC_Time_Date.tm_year = Year - 1900;
	RTC_Time_Date.tm_mon = Month - 1;
	RTC_Time_Date.tm_mday = Day;
	RTC_Time_Date.tm_hour = Hour;
	RTC_Time_Date.tm_min = Minute;
	RTC_Time_Date.tm_sec = Second;
	
	time_cnt = mktime(&RTC_Time_Date);
	
	RTC_SetCounter(time_cnt);
	RTC_WaitForLastTask();
}

void RTC_RefreshTime(int8_t TimeZone) {
	time_t time_cnt;
	
	time_cnt = RTC_GetCounter() + TimeZone * 60 * 60;
	
	RTC_Time_Date = *localtime(&time_cnt);
}

uint16_t RTC_GetYear(void) {
	return RTC_Time_Date.tm_year + 1900;
}

uint8_t RTC_GetMonth(void) {
	return RTC_Time_Date.tm_mon;
}

uint8_t RTC_GetDay(void) {
	return RTC_Time_Date.tm_mday;
}

uint8_t RTC_GetHour(void) {
	return RTC_Time_Date.tm_hour;
}

uint8_t RTC_GetMinute(void) {
	return RTC_Time_Date.tm_min;
}

uint8_t RTC_GetSecond(void) {
	return RTC_Time_Date.tm_sec;
}

uint16_t RTC_GetMiliSecond(void) {
	return (32767 - RTC_GetDivider()) / 32767.0 * 999;
}

void RTC_SetAlarmCountDown(uint32_t AlarmValue) {
	RTC_SetAlarm(RTC_GetCounter() + AlarmValue);
	RTC_WaitForLastTask();
}

uint8_t RTC_CheckAlarm(void) {
	return RTC_GetFlagStatus(RTC_FLAG_ALR);
}
