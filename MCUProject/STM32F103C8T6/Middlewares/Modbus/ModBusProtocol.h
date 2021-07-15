#ifndef __MODBUSPROTOCOL_H
#define __MODBUSPROTOCOL_H

#include "stm32f1xx_hal.h"

void Rx2RecToBuf(void);//����2����
void ModBusProtocol(void);//ModBusЭ����մ���
//float
void FloatToCh(void *p,float f);//--��������ת��ΪModBus��ʽ���ַ�
float ChToFloat(void *p);//--��ModBus��ʽ���ַ�ת��Ϊ������
//int16
void INT16ToCh(void *p,int16_t Int);//--������ת��ΪModBus��ʽ���ַ�
int16_t ChToINT16(void *p);//--ModBus��ʽ���ַ�ת��Ϊ������
//int32
int32_t ChToLong(void *p);//--��ModBus��ʽ���ַ�ת��Ϊ������
void LongToCh(void *p,int32_t l);//--��long������ת��ΪModBus��ʽ���ַ�

#endif /*__MODBUSPROTOCOL_H*/
