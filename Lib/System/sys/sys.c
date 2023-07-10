/*
//�������ҳ�Ʒ
//����ϵ�п�����Ӧ�ó���
//��ע΢�Ź��ںţ����ҵ���
//���ҿ������������� www.DoYoung.net/YT 
//������ѿ����н�ѧ��Ƶ�����ؼ������ϣ�������������
//�������ݾ��� ����������ҳ www.doyoung.net
*/

/*
���޸���־��
1-201708221422 ����RCCʱ�ӵ����ú�����

*/

#include "sys.h"

void NVIC_Configuration(void) {
	// ����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}

void RCC_Configuration(void) {  
	ErrorStatus HSEStartUpStatus;   
	RCC_DeInit();              		// RCC�Ĵ����ָ���ʼ��ֵ 
	RCC_HSEConfig(RCC_HSE_ON); 		// ʹ���ⲿ���پ��� 
	HSEStartUpStatus = RCC_WaitForHSEStartUp(); // �ȴ��ⲿ���پ���ʹ�����
	
	if(HSEStartUpStatus == SUCCESS){   
		/* ����PLLʱ��Դ����Ƶϵ�� */
		// RCC_PLLMul_x��ö��2~16���Ǳ�Ƶֵ��
		// ��HSE=8MHz, RCC_PLLMul_9ʱ PLLCLK=72MHz
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
		
		/* ����AHBʱ�ӣ�HCLK�� */   
		// AHBʱ�� = ϵͳʱ��(SYSCLK) = 72MHz���ⲿ����8HMZ��
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		
		/* ע��˴������ã����ʹ��SYSTICK����ʱ���򣬴�ʱSYSTICK(Cortex System timer)=HCLK/8=9MHz */   
		RCC_PCLK1Config(RCC_HCLK_Div2); 	// ���õ���AHBʱ�ӣ�PCLK1��, APB1ʱ�� = HCLK/2 = 36MHz���ⲿ����8HMZ��   
		RCC_PCLK2Config(RCC_HCLK_Div1); 	// ���ø���AHBʱ�ӣ�PCLK2��, APB2ʱ�� = HCLK = 72MHz���ⲿ����8HMZ��
		
		/* ע��AHB��Ҫ�����ⲿ�洢��ʱ�ӡ�APB2����AD��I/O���߼�TIM������1��APB1����DA��USB��SPI��I2C��CAN������2��3��4��5����ͨTIM */  
		FLASH_SetLatency(FLASH_Latency_2); 	// ����FLASH�洢����ʱʱ��������
		
		
		/* FLASHʱ���ӳټ������ڣ��ȴ�����ͬ������ */
		// �Ƽ����յ�Ƭ��ϵͳ����Ƶ�ʣ�
		//							0~24MHzʱ��ȡLatency_0 
		//							24~48MHzʱ��ȡLatency_1   
		//							48~72MHzʱ��ȡLatency_2 
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);	 //ѡ��FLASHԤȡָ�����ģʽ��Ԥȡָ����ʹ��  
		
		RCC_PLLCmd(ENABLE);		// ʹ��PLL
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET); // �ȴ�PLL����ȶ�   
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); 		// ѡ��SYSCLKʱ��ԴΪPLL
		while(RCC_GetSYSCLKSource() != 0x08);		 // �ȴ�PLL��ΪSYSCLKʱ��Դ   
	}
}

/*********************************************************************************************
 * �������� www.DoYoung.net
 * ���ҵ��� www.DoYoung.net/YT 
*********************************************************************************************/
