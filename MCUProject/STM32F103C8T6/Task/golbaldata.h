#ifndef __GOLBALDATA_H
#define __GOLBALDATA_H

#include "DataTypedef.h"


//--定义全局变量-----
#define EXT extern


#define FALSE 0
#define TRUE 1
	
	
#define VERSION 1.00
//---------------配置参数---------------
EXT ConfigTypedef CfgData;

//---------------传感数据---------------
EXT ICDCntTypedef Tim2ICD;//脉冲宽度采集
EXT SsdataTypedef chA,chB;//传感器输出数据
EXT int8_t DataMap[200];	//数据映射表

//---------------通信端口---------------
	
#define TX2EN HAL_GPIO_WritePin(RS485TXDEN_GPIO_Port,RS485TXDEN_Pin,GPIO_PIN_SET)
#define RX2EN HAL_GPIO_WritePin(RS485TXDEN_GPIO_Port,RS485TXDEN_Pin,GPIO_PIN_RESET)

EXT int8_t Tx2Buf[200];	
EXT int8_t Tx2Num; //发送个数
EXT int8_t Tx2Cnt;//发送个数计数

EXT int8_t Rx2Buf[200];		
EXT int8_t Rx2Num; //接收个数
EXT int8_t Rx2OverTime;//接收超时计数器


	
#endif /*__GOLBALDATA_H*/
