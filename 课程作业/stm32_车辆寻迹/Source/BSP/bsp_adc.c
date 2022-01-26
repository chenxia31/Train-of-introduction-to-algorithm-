/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         bsp_adc.c
* @author       liusen
* @version      V1.0
* @date         2017.08.17
* @brief        ADC
* @details      
* @par History  ������˵��
*                 
* version:		liusen_20170817
*/

#include "bsp_adc.h"
#include "stm32f10x_adc.h"
#include "delay.h"
# include "app_motor.h"

#define	ADC_x								ADC1

int ADC_Convert_Value=0;

// ADC GPIO ����
 void ADCx_GPIO_Config(void)
{  //?PA1??
	GPIO_InitTypeDef GPIO_InitStruct;
	//??GPIO??
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1 , ENABLE ); //ʹ�� ADC1 ͨ��ʱ��
		RCC_ADCCLKConfig(RCC_PCLK2_Div6); //���� ADC ��Ƶ���� 6

	//??????
	GPIO_InitStruct.GPIO_Pin =GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;//ģ������
	GPIO_Init(GPIOA, &GPIO_InitStruct); //��ʼ�� GPIOA.1
}

// ADC����
void ADCx_Config(void)
{  //ADC1  Channel_1
	ADC_InitTypeDef ADC_InitStruct;
	//??ADC??
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1 , ENABLE ); //ʹ�� ADC1 ͨ��ʱ��


	ADC_DeInit(ADC1); //��λ ADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
	
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;		// ?????ADC,?????
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;  		//��ͨ��ģʽ
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;		// �ظ�ת��ģʽ
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;// ת��������������ⲿ��������
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;	// �Ҷ���
	ADC_InitStruct.ADC_NbrOfChannel = 1;   // ˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1,&ADC_InitStruct);// ���ݲ�����ʼ������
	

	
		//����ָ�� ADC �Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_239Cycles5);
	
	// ADCת�������жϣ����жϷ�������ж�ȥת��ֵ
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);

	ADC_Cmd(ADC1, ENABLE); //ʹ��ָ���� ADC1
	ADC_ResetCalibration(ADC1); //������λУ׼
	while(ADC_GetResetCalibrationStatus(ADC1)); //�ȴ���λУ׼����
	ADC_StartCalibration(ADC1); //���� AD У׼
	while(ADC_GetCalibrationStatus(ADC1)); //�ȴ�У׼����
	
	// ����û�в����ⲿ����������ʹ���������ADCת��;ʹ�����ת������
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

void ADC_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
	// ?????
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  // ???????
  NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

int count=0;
int adc_value_temp=0;
int adc_value;
int temp;
int adc_delta=0;
void ADC1_2_IRQHandler(void)
{	
	

	if (ADC_GetITStatus(ADC_x,ADC_IT_EOC)==SET) 
	{
		 //??ADC????
		temp=ADC_Convert_Value;
  	ADC_Convert_Value =(float)ADC_GetConversionValue(ADC_x);
		
		if(count<3)
		{
			adc_value_temp+=ADC_Convert_Value;
			adc_delta=temp-ADC_Convert_Value;
			count+=1;
		}
		else
		{
			count=0;
			adc_value=adc_value_temp/3;
			adc_value_temp=0;
			adc_delta=0;
		}
		ADC_ClearITPendingBit(ADC_x,ADC_IT_EOC); //ɾ���ж�λ��
	}
}

/**
* Function       Adc_Init
* @author        liusen
* @date          2017.08.17    
* @brief         ADC��ʼ���ӿ�
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   �������ǽ��Թ���ͨ��Ϊ��	 ����Ĭ�Ͻ�����ͨ�� 0~3
*/



/*
* ADC�ж�������NVIC
*/


/**
* Function       Get_Adc
* @author        liusen
* @date          2017.08.17     
* @brief         ��� ADC ֵ
* @param[in]     ch:ͨ��ֵ 0~3
* @param[out]    void
* @retval        void
* @par History   �������ǽ��Թ���ͨ��Ϊ��	 ����Ĭ�Ͻ�����ͨ�� 0~3
*/

static u16 Get_Adc(u8 ch)
{
	//����ָ�� ADC �Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );
	//ͨ�� 1,�������˳��ֵΪ 1,����ʱ��Ϊ 239.5 ����
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); //ʹ�����ת������
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
	return ADC_GetConversionValue(ADC1); //�������һ�� ADC1 �������ת�����
}


/**
* Function       Get_Adc_Average
* @author        liusen
* @date          2017.08.17    
* @brief         ��� ADC ��β���ƽ��ֵ
* @param[in]     ch:ͨ��ֵ 0~3 ; times:��������
* @param[out]    void
* @retval        void
* @par History   
*/

static u16 Get_Adc_Average(u8 ch, u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{ 
		temp_val+=Get_Adc(ch);
		delay_ms(2);
	}
	return temp_val/times;
}

/**
* Function       Get_Measure_Volotage
* @author        liusen
* @date          2017.08.17  
* @brief         ��ò��ԭʼ��ѹֵ
* @param[in]     ch:ͨ��ֵ 0~3 ; times:��������
* @param[out]    void
* @retval        void
* @par History   
*/
float Get_Measure_Volotage(void)
{
	u16 adcx;
	float temp;

	adcx=Get_Adc_Average(ADC_Channel_0, 10);
	temp=(float)adcx*(3.3/4096);
	return temp;
}

/**
* Function       Get_Battery_Volotage
* @author        liusen
* @date          2017.08.18    
* @brief         ���ʵ�ʵ�ط�ѹǰ��ѹ
* @param[in]     void
* @param[out]    void
* @retval        float ��ѹֵ
* @par History   
*/
float Get_Battery_Volotage(void)
{
	float temp;

	temp = Get_Measure_Volotage();
	temp = temp * 2.827f; //temp*(20+10)/10;  3�������ڵ�2.827
	return temp;
}
