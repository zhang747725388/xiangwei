
/* 按键指令发送程序*/ 

/*--- File Includes ------------------------------------------------------*/
#include "rsystem.h"
#include "task.h"
#include "systest.h"
#include "74hc595.h"
#define DelaynumMax    199    //延迟数量标志
#define DelaynumMin     0    //延迟数量标志
#define StrongMax       6    //增益数量标志
#define StrongMin       0    //增益数量标志
#define DoorMax         5    //门槛数量标志
#define Doormin         0    //门槛数量标志
#define Strong1Max      6   //增益1数量标志
#define Strong1Min      0   //增益1数量标志
#define Door1Max        5   //门槛1数量标志
#define Door1min        0   //门槛1数量标志
#define Strong2Max      6   //增益2数量标志
#define Strong2Min      0   //增益2数量标志
#define Door2Max        5   //门槛2数量标志
#define Door2min        0   //门槛2数量标志
#define open  1
#define close 2
#define start  3
#define stop   4
#define strong  5
#define door  6
#define mode  7
#define OPENCMD  8
 #define CLOSECMD  9
  #define Delay  10
	  #define AutoConnect  11
 /******************模式状态位******************************* 
 **0 默认断开状态
 **1 连接串口 获取密码
 **2 输入访问密码
 **3 
 **
 **
 **
 **
 **
 **
 **
******************模式状态位*******************************/ 
u8 ModeMainFlag=0;
BYTE  Snum[4];//产品序列号
u8 CheckFlag=0;//串口数据接收判断标志位
BYTE * temp;
u8 showFlag=0;
const u8 TEXT_Buffer[]={"0c06"};
u8 datatemp[4];
//
SYSTIMER KEY_Tim;
u8 keyflag=0;
u8 keyflag1=0;
u8 keyflag2=0;
 __align(4) u8 comdata[10] ;
 __align(4) u8 deyshowdata[10] ;  
int Delayflag=0;//延迟标志
 char* DelayStr=" ";//延迟标志
 
//
#define SIZE sizeof(TEXT_Buffer)	 	//数组长度
#define FLASH_SAVE_ADDR  0X08020000 	//设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)
 


void  Getdatatask(void){
 if((RMLStrcmp(SysTest_RcvData,(BYTE *)"!S08",4) == 1))
 {
    
 }
 	    
}
 
 
void SetValueEn(unsigned char *value){

	 LCD_WriteString_en(0,0,value); //
}


void KeyAction(u8 flag){

  switch(flag){

            case KEY0_LONG:
				    
					break;
		        case KEY1_LONG:
							break;
		        case KEY2_LONG:
							break;
		        case KEY3_LONG:
							break;
		        case KEY4_LONG:
							break;
				case KEY0_UP:
					 
					break;
	            case KEY1_UP:
					  
					  //SendMode5(2);
		            break;
			    case KEY2_UP:
					 
					break;
			    case KEY3_UP:
					  
					break;
			    case KEY4_UP:
					 
					  break;
			   case KEY5_UP:
			 		 
					break;
				 
		  case KEY7_UP: 
			 		  
					break;
				 
    }
}

void MainKeytask(void){

 			if(Timer_GetElapse(&KEY_Tim) >10){

          keyflag =Key_Scan();
				  KeyAction(keyflag);

      	Timer_Reset(&KEY_Tim);
    }

}



























