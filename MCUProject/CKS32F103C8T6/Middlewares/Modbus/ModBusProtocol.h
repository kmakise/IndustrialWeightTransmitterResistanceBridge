#ifndef __MODBUSPROTOCOL_H
#define __MODBUSPROTOCOL_H

#include "stm32f1xx_hal.h"

void Rx2RecToBuf(void);//串口2接收
void ModBusProtocol(void);//ModBus协议接收处理
//float
void FloatToCh(void *p,float f);//--将浮点数转换为ModBus格式的字符
float ChToFloat(void *p);//--将ModBus格式的字符转换为浮点数
//int16
void INT16ToCh(void *p,int16_t Int);//--整型数转换为ModBus格式的字符
int16_t ChToINT16(void *p);//--ModBus格式的字符转换为整型数
//int32
int32_t ChToLong(void *p);//--将ModBus格式的字符转换为浮点数
void LongToCh(void *p,int32_t l);//--将long型数据转换为ModBus格式的字符

#endif /*__MODBUSPROTOCOL_H*/
