#ifndef __RED_H
#define __RED_H    
//////////////////////////////////////////////////////////////////////////////////	 
 
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
  
#define RDATA 	PAin(1)	 	//�������������
#include "rsystem.h"
//����ң��ʶ����(ID),ÿ��ң�����ĸ�ֵ��������һ��,��Ҳ��һ����.
//����ѡ�õ�ң����ʶ����Ϊ0
#define REMOTE_ID 0      		   
extern  u8* str; 

typedef enum //����һ�����岻ͬ���ǣ��˴��ı��DAYʡ�ԣ���������ġ�
{
  Code_UP    =0   ,
  Code_DOWN  =162 ,
  Code_PSW   =98  ,
  Code_EX    =2   ,
  Code_A     =226 ,
  Code_B     =194 ,
  Code_C     =34  ,
  Code_D     =224 ,
  Code_E     =168 ,
  Code_S     =144 ,
  Code_CON   =104 ,
  Code_T1    =152 ,
  Code_T2    =176 ,
  Code_T3    =48  ,
  Code_T4    =24  ,
  Code_T5    =122 ,
  Code_T6    =16  ,
  Code_T7    =56  ,
  Code_T8    =90  ,
  Code_T9    =66  ,
  Code_T10   =82
} Remotecode;
extern u8 RmtCnt;			//�������µĴ���

void Remote_Init(void);    	//���⴫��������ͷ���ų�ʼ��
u8 Remote_Scan(void);	  
extern void Remote_check(void);
#endif















