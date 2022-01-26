/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp_timer.h	
* @author       liusen
* @version      V1.0
* @date         2017.07.17
* @brief        ��ʱ��
* @details      
* @par History  ������˵��
*                 
* version:		liusen_20170717
*/

#include "bsp_timer.h"
#include "bsp_colorful.h"
#include "bsp_servo.h"
# include "bsp_gs.h"
#include "app_motor.h"



/**
* Function       TIM1_Int_Init
* @author        liusen
* @date          2015.01.03    
* @brief         ��ʱ��1��ʼ���ӿ�
* @param[in]     arr���Զ���װֵ��psc��ʱ��Ԥ��Ƶ��
* @param[out]    void
* @retval        void
* @par History   ����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
*/
void TIM1_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler = (psc-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim   //36Mhz
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	//TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;    //�ظ������ر�
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE ); //ʹ��ָ����TIM1�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  //TIM1�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIMx					 
}
/**
* Function       TIM1_Int_Init
* @author        liusen
* @date          2015.01.03    
* @brief         ��ʱ��1�жϷ������: ��Ҫ����6·�������
* @param[in]     arr���Զ���װֵ��psc��ʱ��Ԥ��Ƶ��
* @param[out]    void
* @retval        void
* @par History   ����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
*/
int iGS=0;

void TIM1_UP_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  //���TIMx�����жϱ�־ 
		/*switch(num)
		{
			case 1:  Colorful_Control(1,0,0); break;
			case 2:  Colorful_Control(0,1,0); num = 0; break;
			//case 3:  Colorful_Control(0,0,1); break;
			//case 4:  Colorful_Control(0,1,1); break;
			//case 5:  Colorful_Control(1,1,0); break;
			//case 6:  Colorful_Control(1,0,1); break;
			//case 7:  Colorful_Control(1,1,1); num = 0; break;
			default: break;
		}*/
		iGS=Get_GS_Value();  //ʱ��3ms
		if (iGS>1700 && iGS<1750)
		{
			Car_Stop();
		}
		else
		{
			Car_Run(3600);
		}
	}
}
