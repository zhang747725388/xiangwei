/*--- HEADER FILE DESCRIPTOR --------------------------------------------------
Project : Realtime Micro Library
File    : rsystem.h
Author  : automatic.dai
E-mail  : automatic.dai@gmail.com
Data    : 2013/01/16
Version : V1.0(alpha)
Note    : 
-----------------------------------------------------------------------------*/
#ifndef __RSYSTEM_H_
#define __RSYSTEM_H_
/*--- Header Includes -------------------------------------------------------*/
#include "string.h"
#include "math.h"
#include "key.h"
#include "stdtype.h"
#include "rtime.h"
#include "rstring.h"
#include "rdelay.h"
#include "task.h"
#include "stm32f10x.h"
#include "5110LCD.h"
#include "LCD.h"
#include "remote.h"
#include "74hc595.h"
#include "systest.h"
#include "led.h"
#include "MODE.h"
#include "bsp.h"
#include "nvic.h"
#include "GPIO.h"
#include "stmflash.h"
#include "systest.h"

R_EXT INT32U 	r_nIntNest;

/*--- Function Declaration --------------------------------------------------*/
R_EXT void 		RInit(void);
R_EXT void 		RStart(void);
R_EXT void 		REnterInt(void);
R_EXT void 		RExitInt(void);

#endif
