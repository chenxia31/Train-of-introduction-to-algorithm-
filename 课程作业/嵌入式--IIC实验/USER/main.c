#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "usmart.h"	
#include "beep.h"
#include "24cxx.h"	
#include "string.h"
#include "stdio.h"
#include "rtc.h"

//ALIENTEKս��STM32������ʵ��22
//IIC ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾  
 
 int main(void)
 {	 
	u8 len;
	u8 k=0;
	u8 t;
	u8 q,w,e;
	u8 L=0;
	u8 size=0;
	u8 m;
	u8 j=0;
	u16 addr=0;
	u8 addrbegin=0;
	u8 addrend=0;
	u8 databegin=0;
	u8 dataend=0;
	u8 result;
	char c[200];
	u8 Data[200];
  u16 Addr=0;
	u16 time=0;
	u8 datatemp[200];
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	KEY_Init();
 	LED_Init();			     //LED�˿ڳ�ʼ��
  usmart_dev.init(SystemCoreClock/1000000);	
	RTC_Init();
  BEEP_Init();	 
 	AT24CXX_Init();			//IIC��ʼ�� 
  printf("\r\nI2C����ʵ��-AT24C02\r\n");
	printf("\r\nлԶ�衢��־��쳿����\r\n");
	printf("%d��%d��%d��%dʱ%d��%d��",calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,(calendar.min+2)%60,calendar.sec);
			
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
			if((u8)c[0]!=182)
			{
			     for(t=0;t<len;t++)
			     {
				         m=(u8)c[t];
				         if(m==32)
				         {
					         j++;
									 size++;
									 Data[size-1]=0;
				          }
				         if(j==0)
						    {   
					         Addr=Addr*10;
									Addr=Addr+((u8)c[t]-48);
				         }
				       else
								{
									Data[size-1]=Data[size-1]*16;
									if(m>=48&&m<58)
											Data[size-1]=Data[size-1]+m-48;
										if(m>=65&&m<72)
											Data[size-1]=Data[size-1]+m-55;
									}
		      }			
				  AT24CXX_Write(Addr,Data,size);
				  BEEP=1;
          delay_ms(500);		
					BEEP=0;
					memset(c,0,200);
					memset(Data,0,200);
		}
		else
		{
			q=0;
			w=0;
			e=0;
			for(t=0;t<len;t++)
			{
				m=(u8)c[t];
				if(q==0)
				{
					if(m==193)
					{
						addrbegin=t;
						q++;
					}
				}
				if(w==0)
				{
				    if(m==181)
				      {
					      addrend=t;
					      w++;
				      }
			  }
				if(e==0)
				  {
				      if(m==32)
				        {
						      databegin=t;
                  e++;
					      }
				  }
				 if(e==1)
				 {
					     if(m==32)
				       {
						    dataend=t;
				       }
			    }
			 }
			j=0;
			addr=0;
			for(t=addrbegin+1;t<addrend;t++)
			{
				addr=addr*10;
				addr=addr+((u8)c[t]-48);
			}
			size=0;
			for(t=databegin+1;t<dataend;t++)
			{
				size=size*10;
				size=size+((u8)c[t]-48);
			}
			AT24CXX_Read(addr,datatemp,size);
			for(j=0;j<size;j++)
			{
				result=(u8)datatemp[j];
					L=result%16;
					k=(result-L)/16;
					if(k!=0)
					{
					    if(k<10)
					      {
						       printf("\r\n%c",'0'+k);
					       }
					     else
					      {
						      printf("\r\n%c",'A'+k-10);
					       }  
					     if(L<10)
					       {
						       printf("%c",'0'+L);
					       }
					        else
				      	{
						      printf("%c",'A'+L-10);
					      }
				  }
		      else
					{
					   if(L<10)
					   {
						   printf("\r\n%c",'0'+L);
					    }
					   else
				   	{
						  printf("\r\n%c",'A'+L-10);
					  }
			   }
			 }
			memset(datatemp,0,200);
			memset(c,0,200);
			addr=0;
			size=0;
	}
}
		else 
			{
		      time++;
		    if(time==10)
		      {
			      printf("\r\n������Ŀ���ַ������\r\n");
		      }
		    if(time%15==0)
		      {
			      LED0=!LED0;//��ʾϵͳ��������	
		      }		   
		delay_ms(10);
				}
	}
}
