
 
/*--- File Includes ------------------------------------------------------*/
#include "rsystem.h"
/*--- Macro Defination ---------------------------------------------------*/

/*--- Data Struct Defination ---------------------------------------------*/

/*--- Variable Declaration -----------------------------------------------*/

/*--- Variable Defination ------------------------------------------------*/

/*--- Functions Declearation ---------------------------------------------*/

/*--- Functions Defination -----------------------------------------------*/

void BSP_Init(void)
{
/*************** System Init *********************/
	RInit();
/**************** NVIC Init **********************/
	NVIC_Configuration();
/***************** Bsp Init **********************/
 
  SysTest_Bsp_Init();
	LcdMainInit();
	Led_Init();
  ADC_InitChannel();
	VoltageSampleInit();// ADC
}
 
