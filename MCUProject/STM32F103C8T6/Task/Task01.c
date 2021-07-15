/**
  ******************************************************************************
  * File Name          : Task01.c
  * Description        : Code for freeRTOS Task01 Application
  ******************************************************************************
  * @author  kmakise
  * @version V1.0.0
  * @date    2021-2-4
  * @brief   ��ʼ��Ӳ��-״̬��
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
#include "Task01.h"

#include "golbaldata.h"

/*Golbal data space ----------------------------------------------------------*/

//---------------���ò���---------------
ConfigTypedef CfgData;

//---------------��������---------------
ICDCntTypedef Tim2ICD;
SsdataTypedef chA,chB;
int8_t DataMap[200];	//����ӳ���

//---------------ͨ�Ŷ˿�---------------
int8_t Tx2Buf[200];	
int8_t Tx2Num; 				//���͸���
int8_t Tx2Cnt;				//���͸�������
int8_t Rx2Buf[200];		
int8_t Rx2Num; 				//���ո���
int8_t Rx2OverTime;		//���ճ�ʱ������


void Task01Main(void)
{
	for(;;)
	{
		HAL_GPIO_WritePin(RunLED_GPIO_Port,RunLED_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(StaLED_GPIO_Port,StaLED_Pin,GPIO_PIN_RESET);
		osDelay(500);
		HAL_GPIO_WritePin(RunLED_GPIO_Port,RunLED_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(StaLED_GPIO_Port,StaLED_Pin,GPIO_PIN_SET);
		osDelay(500);
	}
}



