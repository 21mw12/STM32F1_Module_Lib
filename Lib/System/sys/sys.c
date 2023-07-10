/*
//杜洋工作室出品
//洋桃系列开发板应用程序
//关注微信公众号：洋桃电子
//洋桃开发板资料下载 www.DoYoung.net/YT 
//即可免费看所有教学视频，下载技术资料，技术疑难提问
//更多内容尽在 杜洋工作室主页 www.doyoung.net
*/

/*
《修改日志》
1-201708221422 加入RCC时钟的设置函数。

*/

#include "sys.h"

void NVIC_Configuration(void) {
	// 设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}

void RCC_Configuration(void) {  
	ErrorStatus HSEStartUpStatus;   
	RCC_DeInit();              		// RCC寄存器恢复初始化值 
	RCC_HSEConfig(RCC_HSE_ON); 		// 使能外部高速晶振 
	HSEStartUpStatus = RCC_WaitForHSEStartUp(); // 等待外部高速晶振使能完成
	
	if(HSEStartUpStatus == SUCCESS){   
		/* 设置PLL时钟源及倍频系数 */
		// RCC_PLLMul_x（枚举2~16）是倍频值。
		// 当HSE=8MHz, RCC_PLLMul_9时 PLLCLK=72MHz
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
		
		/* 设置AHB时钟（HCLK） */   
		// AHB时钟 = 系统时钟(SYSCLK) = 72MHz（外部晶振8HMZ）
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		
		/* 注意此处的设置，如果使用SYSTICK做延时程序，此时SYSTICK(Cortex System timer)=HCLK/8=9MHz */   
		RCC_PCLK1Config(RCC_HCLK_Div2); 	// 设置低速AHB时钟（PCLK1）, APB1时钟 = HCLK/2 = 36MHz（外部晶振8HMZ）   
		RCC_PCLK2Config(RCC_HCLK_Div1); 	// 设置高速AHB时钟（PCLK2）, APB2时钟 = HCLK = 72MHz（外部晶振8HMZ）
		
		/* 注：AHB主要负责外部存储器时钟。APB2负责AD，I/O，高级TIM，串口1。APB1负责DA，USB，SPI，I2C，CAN，串口2，3，4，5，普通TIM */  
		FLASH_SetLatency(FLASH_Latency_2); 	// 设置FLASH存储器延时时钟周期数
		
		
		/* FLASH时序延迟几个周期，等待总线同步操作 */
		// 推荐按照单片机系统运行频率：
		//							0~24MHz时，取Latency_0 
		//							24~48MHz时，取Latency_1   
		//							48~72MHz时，取Latency_2 
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);	 //选择FLASH预取指缓存的模式，预取指缓存使能  
		
		RCC_PLLCmd(ENABLE);		// 使能PLL
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET); // 等待PLL输出稳定   
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); 		// 选择SYSCLK时钟源为PLL
		while(RCC_GetSYSCLKSource() != 0x08);		 // 等待PLL成为SYSCLK时钟源   
	}
}

/*********************************************************************************************
 * 杜洋工作室 www.DoYoung.net
 * 洋桃电子 www.DoYoung.net/YT 
*********************************************************************************************/
