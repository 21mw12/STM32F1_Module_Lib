#include "usart.h"
 	
u8 USART1_RX_BUF[USART1_REC_LEN];	// ���ջ���,���USART_REC_LEN���ֽ�.
u16 USART1_RX_STA=0;	//����״̬���  ����״̬��bit15    ������ɱ�־
											//  										bit14		  ���յ�0x0d
											//                      bit13~0   ���յ�����Ч�ֽ���Ŀ

// ����Ĭ�ϵģ���ʹ��printf����ʱ�Զ�����
int fputc(int ch,FILE *p) {
	USART_SendData(USART1,(u8)ch);	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}

/**
  * @brief USART1��ʼ������
  * @param bound: ������
  * @return ��
  */
void USART1_Init(u32 bound) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	/* ����GPIO��ģʽ��IO�� */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;							//TX
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    	//�����������
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;						//RX
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;	//ģ������
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	/* USART1 ��ʼ������ */
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = bound;			//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;				//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;						//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;			//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART1, &USART_InitStructure);
	
	USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1
	USART_ClearFlag(USART1, USART_FLAG_TC);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	//��������ж�

	/* Usart1 NVIC ���� */
	NVIC_InitTypeDef NVIC_InitStructure;
 	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;					//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;		//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;					//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief USART1�жϺ���
  * @return ��
  */
void USART1_IRQHandler(void) {
	u8 r;
	
	// �����ж�
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)	{
		r =USART_ReceiveData(USART1);	// ��ȡ���յ�������
		
		// ����δ���
		if((USART1_RX_STA&0x8000)==0) {
			// ���յ���0x0d
			if(USART1_RX_STA&0x4000) {
				if(r!=0x0a)USART1_RX_STA=0;		// ���մ���,���¿�ʼ
				else USART1_RX_STA|=0x8000;		// ��������� 
			} 
			// ��û�յ�0X0D
			else {	
				if(r==0x0d) USART1_RX_STA|=0x4000;
				else {
					USART1_RX_BUF[USART1_RX_STA & 0X3FFF] = r;
					USART1_RX_STA++;
					if(USART1_RX_STA > (USART1_REC_LEN - 1)) USART1_RX_STA = 0;		// �������ݴ���,���¿�ʼ����	  
				}		 
			}
		}   		 
	} 
}
