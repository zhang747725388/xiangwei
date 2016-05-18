
#ifndef __VOLTAGE_H_
#define __VOLTAGE_H_

/*--- File Includes ------------------------------------------------------*/
#include "stdtype.h"

/*--- Macro Defination ---------------------------------------------------*/

/*--- Data Struct Defination ---------------------------------------------*/
typedef enum _VoltageStaEnum{
	Vol_Default = 0,
	Vol_Error   = 1,
	Vol_OK      = 2
}VoltageStaEnum;

/*--- Variables Export ---------------------------------------------------*/

/*--- Function Export ----------------------------------------------------*/

extern void VoltageSampleInit(void);
extern void VoltageSampleTask(void);
extern double GetVoltage(void);
extern VoltageStaEnum GetVoltageSta(void);
extern INT8U GetRealVoltage(void);

#endif

