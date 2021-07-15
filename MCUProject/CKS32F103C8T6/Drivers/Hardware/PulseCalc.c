/**
  ******************************************************************************
  * File Name          : PulseCalc.c
  * Description        : Code for ModBusProtocol
  ******************************************************************************
  * @author  kmakise
  * @version V1.0.0
  * @date    2021-2-4
  * @brief   PulseCalc
	******************************************************************************
  * @attention
  * <h2><center>&copy; Copyright (c) kmakise
  * All rights reserved.
  *
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "PulseCalc.h"
#include "main.h"
#include "tim.h"
#include "cmsis_os.h"
#include "golbaldata.h"



void TIM2ICD(void)
{
	static uint16_t temp_cnt1,temp_cnt1_2,
									temp_cnt2,temp_cnt2_2,
									temp_cnt3,temp_cnt3_2,
									temp_cnt4,temp_cnt4_2;
	
	if(TIM2->SR & TIM_IT_CC1)  /*-----------------------------------------------CH1 PA0*/
	{
		TIM2->SR = ~TIM_IT_CC1;
		TIM2->SR = ~TIM_FLAG_CC1OF;
		if(GPIOA->IDR & GPIO_PIN_0)
		{
			//���õ�ǰͨ��Ϊ�½��ش����ȴ��½���
			TIM2->CCER |= (TIM_CCER_CC1P << 0U);
			
			temp_cnt1 = TIM2->CCR1;
		}
		else
		{
			//���õ�ǰͨ��Ϊ�����ش����ȴ�������
			TIM2->CCER &= ~(TIM_CCER_CC1P << 0U);
			
			temp_cnt1_2 = TIM2->CCR1;
			if(temp_cnt1_2>=temp_cnt1)
			{
				Tim2ICD.cnt1 = temp_cnt1_2-temp_cnt1;//������-�½��ؼ�Ϊ�ߵ�ƽ��ʱ��
			}
			else
			{
				Tim2ICD.cnt1 = 0xffff-temp_cnt1+temp_cnt1_2+1;//����ǿ綨ʱ�����ڵ�	
			}
		}
	}
	
	if(TIM2->SR & TIM_IT_CC2)  /*-----------------------------------------------CH2 PA1*/
	{
		TIM2->SR = ~TIM_IT_CC2;
		TIM2->SR = ~TIM_FLAG_CC2OF;
		if(GPIOA->IDR & GPIO_PIN_1)
		{
			//���õ�ǰͨ��Ϊ�½��ش����ȴ��½���
			TIM2->CCER |= (TIM_CCER_CC1P << 4U);
			
			temp_cnt2 = TIM2->CCR2;
		}
		else
		{
			//���õ�ǰͨ��Ϊ�����ش����ȴ�������
			TIM2->CCER &= ~(TIM_CCER_CC1P << 4U);
			
			temp_cnt2_2 = TIM2->CCR2;
			if(temp_cnt2_2>=temp_cnt2)
			{
				Tim2ICD.cnt2 = temp_cnt2_2-temp_cnt2;
			}
			else
			{
				Tim2ICD.cnt2 = 0xffff-temp_cnt2+temp_cnt2_2+1;
			}	
		}		
	}
}




