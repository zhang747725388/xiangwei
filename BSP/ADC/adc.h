
#ifndef __ADC_H_
#define __ADC_H_

#include "stdtype.h"

#define ADC_NOT_READY		(0xFFFFFFFF) 

extern void 	ADC_InitChannel(void);
extern INT32U 	ADC_GetValue(void);

#endif
