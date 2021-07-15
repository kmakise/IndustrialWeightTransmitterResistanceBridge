#ifndef __DATATYPEDEF_H
#define __DATATYPEDEF_H

#include "main.h"
#include "cmsis_os.h"

typedef struct  
{
	float 		offset;		//测量偏置
	float 		scale;		//测量系数
	uint16_t	empty_A;	//电流输出4mA对应点 范围0-10000 单位：KG
	uint16_t	full_A;		//电流输出20mA对应点 范围0-50000 单位：KG
	uint16_t	empty_V;	//电压输出0V对应点 范围0-10000 单位：KG
	uint16_t	full_V;		//电压输出10V对应点 范围0-50000 单位：KG
	float			speed;		//传送速度
	float			pdeath;		//压力死区
	
}SscfgTypedef;//传感器配置


typedef struct  
{
	uint8_t 				addr;		//设备ID 范围1-100 默认1
	uint16_t 				bps; 		//支持波特率：4800、9600、19200、38400
	SscfgTypedef 		ssA;		//传感器A
	SscfgTypedef 		ssB;		//传感器B
	uint8_t					update;  //更新事件
	
}ConfigTypedef;//设备配置


typedef struct 
{
	uint16_t cnt1;
	uint16_t cnt2;
	uint16_t cnt3;
	uint16_t cnt4;
	
}ICDCntTypedef;//脉冲输入计数

typedef struct 
{
	float kg;			//kg
	float	sum;		//累积量
	float mV;			//电压百分比
	float mA;			//电流百分比
}SsdataTypedef;//传感器数据


#endif /*__DATATYPEDEF_H*/
