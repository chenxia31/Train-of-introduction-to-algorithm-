#ifndef __DAC_H
#define __DAC_H	 
#include "sys.h"	    
								    
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
								    

void Dac1_Init(void);//�ػ�ģʽ��ʼ��		 	 
void Dac1_Set_Vol(u16 vol);
void Dac1_sine(u16 fre,u16 N,u16 dacval,int *Sine12bit,u8 on,u16 len);
#endif

















