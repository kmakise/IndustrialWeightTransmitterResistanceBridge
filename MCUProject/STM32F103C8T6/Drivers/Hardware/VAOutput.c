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
  * @brief  电压输出控制.
  *
  * @note   PWM脉冲宽度调制控制输出电压 PWM0-100%对应0-10V.
  *
  * @param  ch: 输出通道选择 0 A通道 1 B通道.
  * @param  vol: 输出电压 参数范围0-100% 对应 0-10V.
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
  * @brief  电流输出控制.
  *
  * @note   PWM脉冲宽度调制控制输出电压 PWM0-100%对应4-20mA.
  *
  * @param  ch: 输出通道选择 0 A通道 1 B通道.
  * @param  vol: 输出电流 参数范围0-100% 对应 4-20mA.
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





