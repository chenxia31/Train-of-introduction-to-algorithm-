#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 	 
#include "dac.h"
#include "adc.h"
#include "usmart.h"
#include "beep.h"
#include "string.h"
#include "timer.h"
//ALIENTEKս��STM32������ʵ��19
//DAC ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾  
 int main(void)
 {	 
	u8 len;
	char c[200]; 
	 u8 t;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	KEY_Init();			  //��ʼ����������
 	LED_Init();			     //LED�˿ڳ�ʼ��
	usmart_dev.init(72);	//��ʼ��USMART	
	Dac1_Init();				//DAC��ʼ��
	printf("\r\n��ʱ���ж�ʵ��\r\n");
	printf("\r\n��־�лԶ�衢�쳿�����\r\n");  
TIM3_Int_Init(999,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms  	
TIM4_Int_Init(249,1);
	while(1)
	 {
		if(USART_RX_STA&0x8000)
		     {		   
			       len=USART_RX_STA&0x3fff;
						 for(t=0;t<len;t++)
			      {
			        c[t]=USART_RX_BUF[t];
							USART_SendData(USART1, USART_RX_BUF[t]);//???1????
							while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//??????
						}
						USART_RX_STA=0;
						USART_ClearFlag(USART1, USART_FLAG_RXNE); 
						memset(c,0,200);
				}
		else
				{
					
				}
 }
}
