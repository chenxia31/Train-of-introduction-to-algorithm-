/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         app_linewalking.c	
* @author       liusen
* @version      V1.0
* @date         2017.07.17
* @brief        Ѳ��ģʽ�˶�
* @details      
* @par History  ������˵��
*                 
* version:		liusen_20170717
*/
#include "app_linewalking.h"
#include "bsp_linewalking.h"
#include "sys.h"
#include "app_motor.h"
#include "delay.h"

int Status=0;
/**
* Function       app_LineWalking
* @author        liusen
* @date          2017.07.20    
* @brief         Ѳ��ģʽ�˶�
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   ��
*/

extern int adc_value;
void app_LineWalking(void)
{
	int LineL1 = 1, LineL2 = 1, LineR1 = 1, LineR2 = 1;

	bsp_GetLineWalking(&LineL1, &LineL2, &LineR1, &LineR2);	//��ȡ���߼��״̬	

	if( (LineL1 == LOW || LineL2 == LOW) && LineR2 == LOW&& (adc_value<1500 || adc_value>1700)) //�Ҵ���
    {
      	Car_SpinRight(3600, 3600);
		    delay_ms(266);
	  Status=1;
	
    } 
			else if ( LineL1 == LOW && (LineR1 == LOW || LineR2 == LOW)&& (adc_value<1500 || adc_value>1700)) //�����
		{ 
					Car_SpinLeft(3600, 3600);
			    delay_ms(266);
			Status=1;

			}  
					else if( LineL1 == LOW&& (adc_value<1500 || adc_value>1700) ) //���������
								{  
									Car_SpinLeft(3000, 3000);
									delay_ms(20);
									Status=1;
								}
								else if ( LineR2 == LOW&& (adc_value<1500 || adc_value>1700)) //���������
												{  
													Car_SpinRight(3000,3000);
													delay_ms(20);
													Status=1;
													}
												else if (LineL2 == LOW && LineR1 == HIGH && (adc_value<1500 || adc_value>1700)) //�м�����ϵĴ�����΢������ת
															{   
																Car_Left(3000); 
																Status=0;
																}
																else if (LineL2 == HIGH && LineR1 == LOW && (adc_value<1500 || adc_value>1700)) //�м�����ϵĴ�����΢������ת
																					{   
																							Car_Right(3000);  
																							Status=0;
																						}
																				else if(LineL2 == LOW && LineR1 == LOW) // ���Ǻ�ɫ, ����ǰ��
																						{  
																								Car_Run(3000);
																							  Status=0;
																							
																							}	
																								else{
																								//	if (flag==0)
																											//{
																									//Car_Back(1000);
																													//}
                                                     }
}
