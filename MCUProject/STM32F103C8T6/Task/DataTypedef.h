#ifndef __DATATYPEDEF_H
#define __DATATYPEDEF_H

#include "main.h"
#include "cmsis_os.h"

typedef struct  
{
	float 		offset;		//����ƫ��
	float 		scale;		//����ϵ��
	uint16_t	empty_A;	//�������4mA��Ӧ�� ��Χ0-10000 ��λ��KG
	uint16_t	full_A;		//�������20mA��Ӧ�� ��Χ0-50000 ��λ��KG
	uint16_t	empty_V;	//��ѹ���0V��Ӧ�� ��Χ0-10000 ��λ��KG
	uint16_t	full_V;		//��ѹ���10V��Ӧ�� ��Χ0-50000 ��λ��KG
	float			speed;		//�����ٶ�
	float			pdeath;		//ѹ������
	
}SscfgTypedef;//����������


typedef struct  
{
	uint8_t 				addr;		//�豸ID ��Χ1-100 Ĭ��1
	uint16_t 				bps; 		//֧�ֲ����ʣ�4800��9600��19200��38400
	SscfgTypedef 		ssA;		//������A
	SscfgTypedef 		ssB;		//������B
	uint8_t					update;  //�����¼�
	
}ConfigTypedef;//�豸����


typedef struct 
{
	uint16_t cnt1;
	uint16_t cnt2;
	uint16_t cnt3;
	uint16_t cnt4;
	
}ICDCntTypedef;//�����������

typedef struct 
{
	float kg;			//kg
	float	sum;		//�ۻ���
	float mV;			//��ѹ�ٷֱ�
	float mA;			//�����ٷֱ�
}SsdataTypedef;//����������


#endif /*__DATATYPEDEF_H*/
