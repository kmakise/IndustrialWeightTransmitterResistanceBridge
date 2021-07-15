/**
  ******************************************************************************
  * File Name          : Task02.c
  * Description        : Code for freeRTOS Task02 Application
  ******************************************************************************
  * @author  kmakise
  * @version V1.0.0
  * @date    2021-2-4
  * @brief   传感器数据计算更新
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
#include "Task02.h"

#include "golbaldata.h"
#include "VAOutput.h"

/*Golbal data space ----------------------------------------------------------*/

void CntToKGCalc(void)
{
	float cntA = Tim2ICD.cnt1;
	float cntB = Tim2ICD.cnt2;
	
	chA.kg = (cntA - CfgData.ssA.offset) * CfgData.ssA.scale;
	chB.kg = (cntB - CfgData.ssB.offset) * CfgData.ssB.scale;
}

void OutputVASignal(void)
{	
	//chA 电流
	chA.mA = (chA.kg			 				- CfgData.ssA.empty_A)/
					 (CfgData.ssA.full_A - CfgData.ssA.empty_A);
	//chA 电压
	chA.mV = (chA.kg							- CfgData.ssA.empty_V)/
					 (CfgData.ssA.full_V - CfgData.ssA.empty_V);
	
	
	//chB 电流
	chB.mA = (chB.kg			 				- CfgData.ssB.empty_A)/
					 (CfgData.ssB.full_A - CfgData.ssB.empty_A);
	//chB 电压
	chB.mV = (chB.kg			 			  - CfgData.ssB.empty_V)/
					 (CfgData.ssB.full_V - CfgData.ssB.empty_V);
	
	chA.mV = (chA.mV < 0) ? 0 : chA.mV;
	chA.mV = (chA.mV > 1) ? 1 : chA.mV;
	
	chA.mA = (chA.mA < 0) ? 0 : chA.mA;
	chA.mA = (chA.mA > 1) ? 1 : chA.mA;
	
	chB.mV = (chB.mV < 0) ? 0 : chB.mV;
	chB.mV = (chB.mV > 1) ? 1 : chB.mV;
	
	chB.mA = (chB.mA < 0) ? 0 : chB.mA;
	chB.mA = (chB.mA > 1) ? 1 : chB.mA;
	
	
	//CHA
	VoltageOutput(0,chA.mV);
	CurrentOutput(0,chA.mA);
	//CHB
	VoltageOutput(1,chB.mV);
	CurrentOutput(1,chB.mA);
}

//计算累积量
void sumCalc(void)
{
	//0.02 50Hz
	if(chA.kg > CfgData.ssA.pdeath)
	{
		chA.sum += chA.kg * CfgData.ssA.speed * 0.02;
	}
	if(chB.kg > CfgData.ssB.pdeath)
	{
		chB.sum += chB.kg * CfgData.ssB.speed * 0.02;
	}
}

void Task02Main(void)
{
	chA.kg = 0;
	chB.kg = 0;
	chA.sum = 0;
	chB.sum = 0;
	
	VoltageOutput(0,0);
	VoltageOutput(1,0);
	CurrentOutput(0,0);
	CurrentOutput(1,0);
	
	for(;;)
	{
		CntToKGCalc();
		sumCalc();
		OutputVASignal();
		
		osDelay(20);
	}
}



