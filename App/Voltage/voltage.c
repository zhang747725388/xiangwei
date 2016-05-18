
/* Voltage检测应用程序 */ 

/*--- File Includes ------------------------------------------------------*/
#include "rsystem.h"
 

/*--- Macro Defination ---------------------------------------------------*/     
#define VOLATAGE_SAMPLE_INTERVEL (1000)		  // 电压采集的时间间隔(ms)			  (1000)

/*--- Data Struct Defination ---------------------------------------------*/

/*--- Variable Declaration -----------------------------------------------*/

/*--- Variable Defination ------------------------------------------------*/
VoltageStaEnum VoltageSta;

SYSTIMER CheckVolTim;

INT32U   Voltage_AD;
double   Voltage;

/*--- Functions Declearation ---------------------------------------------*/

/*--- Functions Defination -----------------------------------------------*/

void VoltageSampleInit(void)
{
	VoltageSta = Vol_Default;
	Voltage_AD = 0;
	Voltage = 0.0;
	Timer_Set(&CheckVolTim, VOLATAGE_SAMPLE_INTERVEL);
}


void VoltageSampleTask(void)
{
	if(Timer_GetReached(&CheckVolTim) == bTRUE){

		Voltage_AD = ADC_GetValue();
		Voltage = (double) Voltage_AD / 4096.0 * 3.3 * 7.2;	

		if( (Voltage > 11) && (Voltage < 15) ){
			VoltageSta = Vol_OK;			
		}else{
			VoltageSta = Vol_Error;		
		}

		Timer_Set(&CheckVolTim, VOLATAGE_SAMPLE_INTERVEL);	
	
	}
}


/*-----------------------------------------------------------------------------------------*/
double GetVoltage(void)
{
	return (Voltage);
}

/*-----------------------------------------------------------------------------------------*/
INT8U GetRealVoltage(void)
{
	return (Voltage*10);
}
VoltageStaEnum GetVoltageSta(void)
{
	return (VoltageSta);
}

