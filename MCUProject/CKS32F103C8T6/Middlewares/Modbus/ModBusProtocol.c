/**
  ******************************************************************************
  * File Name          : ModBusProtocol.c
  * Description        : Code for ModBusProtocol
  ******************************************************************************
  * @author  kmakise
  * @version V1.0.2
  * @date    2021-2-4
  * @brief   ModBusProtocol
	******************************************************************************
  * @attention
  * <h2><center>&copy; Copyright (c) kmakise
  * All rights reserved.
  *
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "ModBusProtocol.h"
#include "golbaldata.h"
#include "crc.h"
#include "usart.h"
#include <string.h>

void Rx2RecToBuf(void)
{
	if(USART2->SR&(1<<5)) 
	{
		Rx2OverTime = 0;
		Rx2Buf[Rx2Num] = (USART2->DR&(uint8_t)0x00FF);
		if(Rx2Num < sizeof(Rx2Buf)-1)
		{
				Rx2Num++;
		}
	}
}
//使串口2开始发送数据
void Tx2Send(void) 
{		   			
  TX2EN;	 
	osDelay(10);
	HAL_UART_Transmit(&huart2,(uint8_t *)Tx2Buf,Tx2Num,1000);
	RX2EN;
}	  
//串口读命令返回
void Read_Ret(void)
{
	int16_t SendCrc;
	Tx2Buf[0]=Rx2Buf[0];
	Tx2Buf[1]=Rx2Buf[1];
	SendCrc= CalCRC16(Tx2Buf,Tx2Buf[2]+3);
	INT16ToCh(&Tx2Buf[Tx2Buf[2]+3],SendCrc);
	Tx2Num = Tx2Buf[2]+5;

	Tx2Send(); //使串口1开始发送数据
}
//串口写命令返回（返回接收到的命令）
void Write_Ret(void)
{
	int16_t SendCrc;
	memcpy(Tx2Buf,Rx2Buf,6);//复制接收到的内容
	SendCrc = CalCRC16(Tx2Buf,6);
	INT16ToCh(&Tx2Buf[6],SendCrc); 
	Tx2Num = 8;//返回固定的8个字节
	Tx2Send(); //使串口1开始发送数据
}
//--将浮点数转换为ModBus格式的字符
void FloatToCh(void *p,float f)
{
	char *pch = (char *)p;
	char *pf = (char *)&f;
	pch[0] = pf[1];
	pch[1] = pf[0];
	pch[2] = pf[3];
	pch[3] = pf[2];
}          
//--将ModBus格式的字符转换为浮点数
float ChToFloat(void *p)
{
	float f;
	char *pch = (char *)p;
	char *pf = (char *)&f;
	pf[0] = pch[1];
	pf[1] = pch[0];
	pf[2] = pch[3];
	pf[3] = pch[2];
	return f;
}           

//--整型数转换为ModBus格式的字符
void INT16ToCh(void *p,int16_t Int)
{
	char *pch = p;
	pch[0] = Int>>8;
	pch[1] = Int&0xff;
}           

//--整型数转换为ModBus格式的字符
int16_t ChToINT16(void *p)
{
	char *pch = p;
	return ((int16_t)pch[0]<<8)+pch[1];
}           

//--将ModBus格式的字符转换为浮点数
int32_t ChToLong(void *p)
{
	int32_t l;
	char *pch = (char *)p;
	char *pl = (char *)&l;
	pl[0] = pch[3];
	pl[1] = pch[2];
	pl[2] = pch[1];
	pl[3] = pch[0];
	return l;
}           

//--将long型数据转换为ModBus格式的字符
void LongToCh(void *p,int32_t l)
{
	char *pch = (char *)p;
	char *pl = (char *)&l;
	pch[0] = pl[3];
	pch[1] = pl[2];
	pch[2] = pl[1];
	pch[3] = pl[0];
}      

//--ModBus读寄存器函数，将对应寄存器的数据转换成字符传入指针所指向的地址
uint8_t MbRegRead(int16_t addr,void *pp)
{
	char *p=pp;
	uint8_t fs  = 0;
	
	switch(addr)
	{
		case 1:FloatToCh(p,chA.kg								);fs = 1;	break;//Sensor Measure Value A
		case 3:FloatToCh(p,chB.kg								);fs = 1;	break;//Sensor Measure Value B
		case 5:INT16ToCh(p,chA.mV * 10000				);				break;//Voltage Output A
		case 6:INT16ToCh(p,chB.mV * 10000				);				break;//Voltage Output B
		case 7:INT16ToCh(p,chA.mA * 16000 + 4000);				break;//Current Output A
		case 8:INT16ToCh(p,chB.mA * 16000 + 4000);				break;//Current Output B
		
		case 9: FloatToCh(p,CfgData.ssA.offset	);fs = 1;	break;//Offset A
		case 11:FloatToCh(p,CfgData.ssA.scale		);fs = 1;	break;//Scale A
		case 13:INT16ToCh(p,CfgData.ssA.empty_A	);				break;//Current empty A
		case 14:INT16ToCh(p,CfgData.ssA.full_A	);				break;//Current full A
		case 15:INT16ToCh(p,CfgData.ssA.empty_V	);				break;//Voltage empty A
		case 16:INT16ToCh(p,CfgData.ssA.full_V	);				break;//Voltage full A
		
		case 17:FloatToCh(p,CfgData.ssB.offset	);fs = 1;	break;//Offset B
		case 19:FloatToCh(p,CfgData.ssB.scale		);fs = 1;	break;//Scale B
		case 21:INT16ToCh(p,CfgData.ssB.empty_A	);				break;//Current empty B
		case 22:INT16ToCh(p,CfgData.ssB.full_A	);				break;//Current full B
		case 23:INT16ToCh(p,CfgData.ssB.empty_V	);				break;//Voltage empty B
		case 24:INT16ToCh(p,CfgData.ssB.full_V	);				break;//Voltage full B
		
		case 25:INT16ToCh(p,CfgData.bps 				);				break;//Modbus RS485 Baudrate
		case 26:INT16ToCh(p,CfgData.addr 				);				break;//Modbus RS485 Address
		
		case 27:FloatToCh(p,CfgData.ssA.speed		);fs = 1;	break;//speed A 
		case 29:FloatToCh(p,CfgData.ssB.speed		);fs = 1;	break;//speed B 
		case 31:FloatToCh(p,CfgData.ssA.pdeath	);fs = 1;	break;//pdeath A 
		case 33:FloatToCh(p,CfgData.ssB.pdeath	);fs = 1;	break;//pdeath B 
		case 35:FloatToCh(p,chA.sum							);fs = 1;	break;//sum A 
		case 37:FloatToCh(p,chB.sum							);fs = 1;	break;//sum B 
		
		default:break;
	}
	return fs;
}


//--ModBus写寄存器函数，将传入指针所指向的地址的字符转换并写入对应寄存器
void MbRegWrite(int16_t addr,void *pp)
{
	char *p=pp;
	switch(addr)
	{
		//rw
		case 1:CfgData.ssA.scale *= ChToFloat(p)/chA.kg;CfgData.update = 0xff;break;//Sensor Measure Value A Fix1
		case 3:CfgData.ssB.scale *= ChToFloat(p)/chB.kg;CfgData.update = 0xff;break;//Sensor Measure Value B Fix1
		
		//ro
		case 5:break;//Voltage Output A
		case 6:break;//Voltage Output B
		case 7:break;//Current Output A
		case 8:break;//Current Output B
		
		//rw
		
		case 9:	CfgData.ssA.offset 		= ChToFloat(p); CfgData.update = 0xff; break;//Offset A
		case 11:CfgData.ssA.scale  		= ChToFloat(p); CfgData.update = 0xff; break;//Scale A
		case 13:CfgData.ssA.empty_A  	= ChToINT16(p); CfgData.update = 0xff; break;//Current empty A
		case 14:CfgData.ssA.full_A  	= ChToINT16(p); CfgData.update = 0xff; break;//Current full A
		case 15:CfgData.ssA.empty_V  	= ChToINT16(p); CfgData.update = 0xff; break;//Voltage empty A
		case 16:CfgData.ssA.full_V  	= ChToINT16(p); CfgData.update = 0xff; break;//Voltage full A
		
		case 17:CfgData.ssB.offset 		= ChToFloat(p); CfgData.update = 0xff; break;//Offset B
		case 19:CfgData.ssB.scale  		= ChToFloat(p); CfgData.update = 0xff; break;//Scale B
		case 21:CfgData.ssB.empty_A  	= ChToINT16(p); CfgData.update = 0xff; break;//Current empty B
		case 22:CfgData.ssB.full_A  	= ChToINT16(p); CfgData.update = 0xff; break;//Current full B
		case 23:CfgData.ssB.empty_V  	= ChToINT16(p); CfgData.update = 0xff; break;//Voltage empty B
		case 24:CfgData.ssB.full_V  	= ChToINT16(p); CfgData.update = 0xff; break;//Voltage full B
		
		case 25:CfgData.bps 					= ChToINT16(p); CfgData.update = 0xff; break;//Modbus RS485 Baudrate
		case 26:CfgData.addr 					= ChToINT16(p); CfgData.update = 0xff; break;//Modbus RS485 Address
		
		case 27:CfgData.ssA.speed			= ChToFloat(p);	CfgData.update = 0xff; break;//speed A
		case 29:CfgData.ssB.speed			= ChToFloat(p);	CfgData.update = 0xff; break;//speed B
		case 31:CfgData.ssA.pdeath		= ChToFloat(p); CfgData.update = 0xff; break;//pdeath A 
		case 33:CfgData.ssB.pdeath		= ChToFloat(p); CfgData.update = 0xff; break;//pdeath B 
		
		case 35:break;//read only
		case 37:break;//read only
		
		//cmd
		case 242:CfgData.ssA.offset 	= Tim2ICD.cnt1; CfgData.update = 0xff; break;//cha zero
		case 243:CfgData.ssB.offset 	= Tim2ICD.cnt2; CfgData.update = 0xff; break;//chb zero
		
		default:break;
	}
}

//寄存器连续写入
void MbNregWrite(uint16_t addr,uint16_t nreg)
{
	int8_t * pbuf = &Rx2Buf[7];
	
	while(nreg>0)
	{
		MbRegWrite(addr,pbuf);
		addr += 1;
		pbuf += 2;
		nreg--;
	}
}


void ModBusProtocol(void)//ModBus协议接收处理
{
	if((Rx2Buf[0] == CfgData.addr)&&(CalCRC16(Rx2Buf,Rx2Num)==0))//是本机的地址 且接收数据CRC正确
	{
		int16_t DataAddr;
		DataAddr = ChToINT16(&Rx2Buf[2]);
		
		switch(Rx2Buf[1])
		{
			case 3://读寄存器
			case 4://读寄存器
			{
				int16_t Reg_n;//读取寄存器的个数
        Reg_n = ChToINT16(&Rx2Buf[4]);//读取的寄存器个数
				
				if((DataAddr+Reg_n) < 40)//最多将寄存器地址读到 26
				{
						uint8_t * p = &Tx2Buf[3];
						Tx2Buf[2]=Reg_n*2;
						while(Reg_n>0)
						{
							 if(MbRegRead(DataAddr + 1,p) != 0)//32bit
							 {
								 DataAddr+=2;
								 p += 4;
							 }
							 else//16bit
							 {
								 DataAddr++;
								 p += 2;
							 }
							 Reg_n--;
						}
						Read_Ret();//串口读命令返回
				}
			}
			break;

			case 6://写单个寄存器 
			{
				MbRegWrite(DataAddr + 1,&Rx2Buf[4]);
				Write_Ret();
			}
			break;
			
			case 0x10://连续写入寄存器
			{
				int16_t nreg = ChToINT16(&Rx2Buf[4]);//写入的寄存器个数
				MbNregWrite(DataAddr + 1,nreg);
				Write_Ret();
			}
			break;
			default:break;//不支持的命令
		}
	}
	else
	{
		//00 03/04 00 65 00 01 crcH crcL 
		if((Rx2Buf[0] == 0x00)&&((Rx2Buf[1] == 0x03)||(Rx2Buf[1] == 0x04))&&//判断是否是广播方式读地址
		 (ChToINT16(&Rx2Buf[2])==101)&&(ChToINT16(&Rx2Buf[4])==1)&&(CalCRC16(Rx2Buf,Rx2Num)==0))
		{
			//回传本机地址
			int8_t *p= &Tx2Buf[3];
			Tx2Buf[2]=1*2;
			MbRegRead(101,p);
			Read_Ret();//串口读命令返回
		}
	}    
	Rx2Num=0; //接收个数
}





