/**
  ******************************************************************************
  * File Name          : Task04.c
  * Description        : Code for freeRTOS Task04 Application
  ******************************************************************************
  * @author  kmakise
  * @version V1.0.0
  * @date    2021-2-4
  * @brief   485 ModbusÍ¨ÐÅ
	******************************************************************************
  * @attention
  * <h2><center>&copy; Copyright (c) kmakise
  * All rights reserved.
  *
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "Task04.h"

#include "ModBusProtocol.h"
#include "golbaldata.h"

/*Golbal data space ----------------------------------------------------------*/


void ModBusComCheck(void)
{
	static int8_t lastRxnum = 0;

	if((lastRxnum == Rx2Num)&&(Rx2Num != 0))
	{
		lastRxnum = 0;
		ModBusProtocol();
	}
	else
	{
		lastRxnum = Rx2Num;
	}
}

void Task04Main(void)
{
	RX2EN;
	for(;;)
	{
		ModBusComCheck();
		osDelay(5);
	}
}



