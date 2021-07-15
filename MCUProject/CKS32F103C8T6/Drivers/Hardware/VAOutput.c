/**
  ******************************************************************************
  * File Name          : VAOutput.c
  * Description        : Code for Voltage and Current Output
  ******************************************************************************
  * @author  kmakise
  * @version V1.0.0
  * @date    2021-2-4
  * @brief   0-10V 0-20mA
	******************************************************************************
  * @attention
  * <h2><center>&copy; Copyright (c) kmakise
  * All rights reserved.
  *
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "VAOutput.h"
#include "main.h"
#include "tim.h"
#include "cmsis_os.h"
#include "golbaldata.h"
#include "tim.h"

#define TIMARRVAL 20000.0


/**
  * @brief  ��ѹ�������.
  *
  * @note   PWM�����ȵ��ƿ��������ѹ PWM0-100%��Ӧ0-10V.
  *
  * @param  ch: ���ͨ��ѡ�� 0 Aͨ�� 1 Bͨ��.
  * @param  vol: �����ѹ ������Χ0-100% ��Ӧ 0-10V.
  * 
  * @retval None
  */
void VoltageOutput(int ch,float pct)
{
	pct = (pct > 1) ? 1:pct;
	pct = (pct < 0) ? 0:pct;
	uint16_t ccr = TIMARRVAL * pct;
	switch(ch)
	{
		case 0:TIM3->CCR1 = ccr;break;
		case 1:TIM3->CCR2 = ccr;break;
		default:break;
	}
}

/**
  * @brief  �����������.
  *
  * @note   PWM�����ȵ��ƿ��������ѹ PWM0-100%��Ӧ4-20mA.
  *
  * @param  ch: ���ͨ��ѡ�� 0 Aͨ�� 1 Bͨ��.
  * @param  vol: ������� ������Χ0-100% ��Ӧ 4-20mA.
  * 
  * @retval None
  */
void CurrentOutput(int ch,float pct)
{
	pct = (pct > 1) ? 1:pct;
	pct = (pct < 0) ? 0:pct;
	uint16_t ccr = TIMARRVAL * pct;
	switch(ch)
	{
		case 0:TIM3->CCR3 = ccr;break;//4- 20
		case 1:TIM3->CCR4 = ccr;break;
		default:break;
	}
}





