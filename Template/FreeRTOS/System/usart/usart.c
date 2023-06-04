#include "usart.h"
 	
u8 USART1_RX_BUF[USART1_REC_LEN];	// 接收缓冲,最大USART_REC_LEN个字节.
u16 USART1_RX_STA=0;	//接收状态标记  接收状态：bit15    接收完成标志
											//  										bit14		  接收到0x0d
											//                      bit13~0   接收到的有效字节数目

// 函数默认的，在使用printf函数时自动调用
int fputc(int ch,FILE *p) {
	USART_SendData(USART1,(u8)ch);	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}

/**
  * @brief USART1初始化函数
  * @param bound: 波特率
  * @return 无
  */
void USART1_Init(u32 bound) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	/* 配置GPIO的模式和IO口 */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;							//TX
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    	//复用推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;						//RX
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;	//模拟输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	/* USART1 初始化设置 */
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = bound;			//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;				//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;						//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;			//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART1, &USART_InitStructure);
	
	USART_Cmd(USART1, ENABLE);  //使能串口1
	USART_ClearFlag(USART1, USART_FLAG_TC);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	//开启相关中断

	/* Usart1 NVIC 配置 */
	NVIC_InitTypeDef NVIC_InitStructure;
 	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;					//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;		//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;					//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief USART1中断函数
  * @return 无
  */
void USART1_IRQHandler(void) {
	u8 r;
	
	// 接收中断
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)	{
		r =USART_ReceiveData(USART1);	// 读取接收到的数据
		
		// 接收未完成
		if((USART1_RX_STA&0x8000)==0) {
			// 接收到了0x0d
			if(USART1_RX_STA&0x4000) {
				if(r!=0x0a)USART1_RX_STA=0;		// 接收错误,重新开始
				else USART1_RX_STA|=0x8000;		// 接收完成了 
			} 
			// 还没收到0X0D
			else {	
				if(r==0x0d) USART1_RX_STA|=0x4000;
				else {
					USART1_RX_BUF[USART1_RX_STA & 0X3FFF] = r;
					USART1_RX_STA++;
					if(USART1_RX_STA > (USART1_REC_LEN - 1)) USART1_RX_STA = 0;		// 接收数据错误,重新开始接收	  
				}		 
			}
		}   		 
	} 
}
