/**
  ******************************************************************************
  * File Name          : Task03.c
  * Description        : Code for freeRTOS Task03 Application
  ******************************************************************************
  * @author  kmakise
  * @version V1.0.0
  * @date    2021-2-4
  * @brief   Debug
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
#include "Task03.h"


#include "golbaldata.h"

#include "stdio.h"
#include "usbd_cdc_if.h"

/*Golbal data space ----------------------------------------------------------*/



void Task03Main(void)
{

	for(;;)
	{
		osDelay(20);
	}
}



