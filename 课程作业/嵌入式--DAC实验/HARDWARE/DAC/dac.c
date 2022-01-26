#include "dac.h"
#include "delay.h"
#include "Beep.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//DAC ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/8
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
//DACͨ��1�����ʼ��
void Dac1_Init(void)
{
  
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //ʹ��PORTAͨ��ʱ��
   	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	  //ʹ��DACͨ��ʱ�� 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 // �˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 		 //ģ������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4)	;//PA.4 �����
					
	DAC_InitType.DAC_Trigger=DAC_Trigger_None;	//��ʹ�ô������� TEN1=0
	DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//��ʹ�ò��η���
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//���Ρ���ֵ����
	DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//DAC1�������ر� BOFF1=1
    DAC_Init(DAC_Channel_1,&DAC_InitType);	 //��ʼ��DACͨ��1

	DAC_Cmd(DAC_Channel_1, ENABLE);  //ʹ��DAC1
  
    DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12λ�Ҷ������ݸ�ʽ����DACֵ

}

//����ͨ��1�����ѹ
//vol:0~3300,����0~3.3V
void Dac1_Set_Vol(u16 vol)
{
	float temp=vol;
	temp/=1000;
	temp=temp*4096/3.3;
	DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12λ�Ҷ������ݸ�ʽ����DACֵ
}
//ʹ��dac�������ѹ����Ϊ���Ҳ�
//u16 fre�ǲ��η�����Ƶ��
//u16 N�ǹ涨���η����Ĵ���
//u 16dacval��ָ���ĳ�ʼ������㣬������Ŀ1�涨����Ϊ1.65����Ӧ��ȡ2049
//*Sine12bit�涨��Ϊһ���ڵ����Ҳ���ѹ�Ĳ���ֵ��256
void Dac1_sine(u16 fre,u16 N,u16 dacval,int *Sine12bit,u8 on,u16 len)
{
	float T;
	int i=0;
	int j=0;
	int dt;
	T=1000000/fre;//T��λΪus������õ�һ���ڵ�ʱ��
	dt=T/len;//����õ�һ������һ������ֵ���ֵ�ʱ��
		DAC->DHR12R1=dacval;//��ʼֵΪ0�
		for(i=0;i<N;i++)
		{
			for(j=0;j<len;j++)
			{
			  DAC->DHR12R1=Sine12bit[j];		//�����������ֵ��dac�Ĵ�����ʵ�ֵ�ѹ�ĸı�
				delay_us(dt);	
			}
		}	
}





















































