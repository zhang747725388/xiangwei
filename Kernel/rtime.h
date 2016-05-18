/*--- HEADER FILE DESCRIPTOR --------------------------------------------------
Project : Realtime Micro Library
File    : rtime.h
Author  : automatic.dai
E-mail  : automatic.dai@gmail.com
Data    : 2013/01/16
Version : V1.0(alpha)
Note    : 
-----------------------------------------------------------------------------*/

#ifndef __RTIME_H_
#define __RTIME_H_

#include "stm32f10x.h"
/*--- Header Includes -------------------------------------------------------*/
#include "stdtype.h" 

/*--- Macro Defination ------------------------------------------------------*/
#define RML_SYSCLK_FREQ			(72000000UL)	// System frequency
#define RML_SYSTICK_TIME		(10UL)			// System schedule time(ms)

/*--- Data Struct Defination ------------------------------------------------*/
typedef struct systimer_t
{
	INT32U		start_cnt;
	INT32U		alarm_time;
}SYSTIMER;

/*--- Variables Export ------------------------------------------------------*/

/*--- Function Declaration --------------------------------------------------*/
R_EXT void 		Systick_Init(void);
R_EXT void 		Timer_TickISR(void);
R_EXT void 		Timer_Set(SYSTIMER *timer, INT32U alarm_time);
R_EXT void 		Timer_Reset(SYSTIMER *timer);
R_EXT INT32U 	Timer_GetElapse(SYSTIMER *timer);
R_EXT BOOLEAN 	Timer_GetReached(SYSTIMER *timer);
void             Timer_Delayms(u32 ms);
extern void InputCaptureInit( void );
extern void DelayUs(unsigned long nus);
#endif
