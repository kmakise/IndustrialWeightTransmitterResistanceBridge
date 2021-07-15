/**
  ******************************************************************************
  * File Name          : Task05.c
  * Description        : Code for freeRTOS Task05 Application
  ******************************************************************************
  * @author  kmakise
  * @version V1.0.0
  * @date    2021-2-4
  * @brief   ���ò������ݴ洢����
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
#include "Task05.h"

#include "golbaldata.h"
#include "string.h"
#include "crc.h"
#include "ModBusProtocol.h"
#include "usart.h"

/*Golbal data space ----------------------------------------------------------*/

#define FLASH_START_ADDR 		0x0800E000
#define FLASH_BUFFER_SIZE 	100
uint8_t datatfbuf[FLASH_BUFFER_SIZE];


void ReadBufFromFlash(void)
{
	uint32_t Robot_Num_Flash_Add = FLASH_START_ADDR; 
	
	for(int i = 0;i < FLASH_BUFFER_SIZE/2;i++)
	{
		uint16_t readdata = *(__IO uint16_t*)( Robot_Num_Flash_Add );
		datatfbuf[i * 2 + 1	] = readdata >> 8;
		datatfbuf[i * 2 		] = readdata & 0xFF;
		Robot_Num_Flash_Add+=2;
	}
}

void WriteBufToFlash(void)
{
	
	uint32_t Robot_Num_Flash_Add = FLASH_START_ADDR; 

	vTaskSuspendAll();
	
	FLASH_EraseInitTypeDef My_Flash;  //���� FLASH_EraseInitTypeDef �ṹ��Ϊ My_Flash
	HAL_FLASH_Unlock();               //����Flash
			
	My_Flash.TypeErase = FLASH_TYPEERASE_PAGES;  //����Flashִ��ҳ��ֻ����������
	My_Flash.PageAddress = Robot_Num_Flash_Add;  //����Ҫ�����ĵ�ַ
	My_Flash.NbPages = 1;                        //˵��Ҫ������ҳ�����˲���������Min_Data = 1��Max_Data =(���ҳ��-��ʼҳ��ֵ)֮���ֵ
			
	uint32_t PageError = 0;                    //����PageError,������ִ�����������ᱻ����Ϊ�����FLASH��ַ
	HAL_FLASHEx_Erase(&My_Flash, &PageError);  //���ò�����������
	
	for(int i = 0;i < FLASH_BUFFER_SIZE/2;i++)
	{
		uint16_t Write_Flash_Data = datatfbuf[i * 2 + 1] << 8 | datatfbuf[i * 2];
		 //��Flash������д��FLASH_TYPEPROGRAM_HALFWORD ����������Flash��ַ��16λ
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,Robot_Num_Flash_Add, Write_Flash_Data);
		Robot_Num_Flash_Add+=2;
	}
	HAL_FLASH_Lock(); //��סFlash
	
	xTaskResumeAll();
}

void Usart2BaudRate(uint16_t bps)
{
	switch(bps)
	{
		case 4800: 	bps = 4800;  	break;
		case 9600: 	bps = 9600;  	break;
		case 19200:	bps = 19200; 	break;
		case 38400:	bps = 38400; 	break;
		default:		bps = 9600;		break;
	}
  huart2.Init.BaudRate = bps;
  HAL_UART_Init(&huart2);
}


//����Ĭ�ϲ������ò�д��flash
void DefultParam(void)
{
	//ͨ������
	CfgData.addr = 1;
	CfgData.bps = 9600;
	
	//����������A
	CfgData.ssA.empty_A = 0;
	CfgData.ssA.full_A	= 500;
	CfgData.ssA.empty_V = 0;
	CfgData.ssA.full_V	= 500;
	CfgData.ssA.offset	= 507;
	CfgData.ssA.scale		= 0.01324192 * 3;//40000-500kg
	CfgData.ssA.speed		= 0.5;
	CfgData.ssA.pdeath	= 1.5;
	
	//����������B
	CfgData.ssB.empty_A = 0;
	CfgData.ssB.full_A	= 500;
	CfgData.ssB.empty_V = 0;
	CfgData.ssB.full_V	= 500;
	CfgData.ssB.offset	= 507;
	CfgData.ssB.scale		= 0.01324192 * 3;//40000-500kg
	CfgData.ssB.speed		= 0.5;
	CfgData.ssB.pdeath	= 1.5;
	
	//��������
	CfgData.update = 255;
}


//�������ò����浽flash
void ConfigUpdate(void)
{
	if(CfgData.update != 0)
	{
		//copy to buf
		uint8_t len = sizeof(CfgData);
		
		vTaskSuspendAll();
		datatfbuf[0] = 0;
		while(datatfbuf[0] == 0)
		{
			memcpy(datatfbuf,&CfgData,len);
		}
		xTaskResumeAll();
		
		uint16_t SendCrc = CalCRC16(datatfbuf,len);
		INT16ToCh(&datatfbuf[len],SendCrc);
		
		//�������ô���
		Usart2BaudRate(CfgData.bps);
		
		//save to flash
		WriteBufToFlash();
		CfgData.update = 0;
	}
}

//��flash�������ò�У��
void LoadParam(void)
{
	ReadBufFromFlash();
	//У�����
	if((CalCRC16(datatfbuf,sizeof(CfgData)+2)==0))
	{
		memcpy(&CfgData,datatfbuf,sizeof(CfgData));
		Usart2BaudRate(CfgData.bps);
	}
	else //ʧ��
	{
		DefultParam();
		CfgData.update = 255;
		ConfigUpdate();
	}
}

void Task05Main(void)
{
	LoadParam();
	for(;;)
	{
		ConfigUpdate();
		osDelay(100);
	}
}



