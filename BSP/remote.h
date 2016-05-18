#ifndef __RED_H
#define __RED_H    
//////////////////////////////////////////////////////////////////////////////////	 
 
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
  
#define RDATA 	PAin(1)	 	//红外数据输入脚
#include "rsystem.h"
//红外遥控识别码(ID),每款遥控器的该值基本都不一样,但也有一样的.
//我们选用的遥控器识别码为0
#define REMOTE_ID 0      		   
extern  u8* str; 

typedef enum //跟第一个定义不同的是，此处的标号DAY省略，这是允许的。
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
extern u8 RmtCnt;			//按键按下的次数

void Remote_Init(void);    	//红外传感器接收头引脚初始化
u8 Remote_Scan(void);	  
extern void Remote_check(void);
#endif















