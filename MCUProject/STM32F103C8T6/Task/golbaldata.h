#ifndef __GOLBALDATA_H
#define __GOLBALDATA_H

#include "DataTypedef.h"


//--����ȫ�ֱ���-----
#define EXT extern


#define FALSE 0
#define TRUE 1
	
	
#define VERSION 1.00
//---------------���ò���---------------
EXT ConfigTypedef CfgData;

//---------------��������---------------
EXT ICDCntTypedef Tim2ICD;//�����Ȳɼ�
EXT SsdataTypedef chA,chB;//�������������
EXT int8_t DataMap[200];	//����ӳ���

//---------------ͨ�Ŷ˿�---------------
	
#define TX2EN HAL_GPIO_WritePin(RS485TXDEN_GPIO_Port,RS485TXDEN_Pin,GPIO_PIN_SET)
#define RX2EN HAL_GPIO_WritePin(RS485TXDEN_GPIO_Port,RS485TXDEN_Pin,GPIO_PIN_RESET)

EXT int8_t Tx2Buf[200];	
EXT int8_t Tx2Num; //���͸���
EXT int8_t Tx2Cnt;//���͸�������

EXT int8_t Rx2Buf[200];		
EXT int8_t Rx2Num; //���ո���
EXT int8_t Rx2OverTime;//���ճ�ʱ������


	
#endif /*__GOLBALDATA_H*/
