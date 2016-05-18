
#ifndef __TASK_H_
#define __TASK_H_

/*--- File Includes ------------------------------------------------------*/
#include "rtime.h"
extern u8 ModeMainFlag;
extern BYTE Snum[4];
 
typedef struct _SendCMDStruct{
	BYTE*   Cmd;
	INT8U   CmdLen;
}SendCMDStruct;
typedef enum  _ModeStruct{
	   	System     = 0,				// 系统
	    Send 	     = 1,				     // 发射器
	    Get        = 3, 			     	// 接收器
    	PepleFlow  = 4, 				// 人流量
	   	Alarm      = 5 				//  报警
}ModeStruct;
extern void KeyTask(void);
extern void SendGetSNConnet(void);
extern void SendConnet(void);
extern void  Getdatatask(void);
#endif

