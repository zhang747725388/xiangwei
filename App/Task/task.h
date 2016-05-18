
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
	   	System     = 0,				// ϵͳ
	    Send 	     = 1,				     // ������
	    Get        = 3, 			     	// ������
    	PepleFlow  = 4, 				// ������
	   	Alarm      = 5 				//  ����
}ModeStruct;
extern void KeyTask(void);
extern void SendGetSNConnet(void);
extern void SendConnet(void);
extern void  Getdatatask(void);
#endif

