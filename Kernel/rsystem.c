/*--- SOURCE FILE DESCRIPTOR ---------------------------------------------------
Project : Realtime Micro Library
File    : rsystem.c
Author  : automatic.dai
E-mail  : automatic.dai@gmail.com
Data    : 2013/01/16
Version : V1.0(alpha)
Note    : 
------------------------------------------------------------------------------*/

#include "rsystem.h"

INT32U	r_nIntNest = 0;

/*--- FUNCTION DESCRIPTOR ------------------------------------------------------
Function : RInit()
Input    : 
Output   : 
Return   : 
Version  : 
Note     : 
------------------------------------------------------------------------------*/
void RInit(void)
{
	Systick_Init();
	return;
}

