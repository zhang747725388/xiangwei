#include "iwdg.h"

// IWDG timeout equal to 20.0s (the timeout may varies due to LSI frequency dispersion)
void Init_IWDG(void)
{
	/* Enable write access to IWDG_PR and IWDG_RLR registers */
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	
	/* IWDG counter clock: 40KHz(LSI) / 256 = 156.25 Hz */
	IWDG_SetPrescaler(IWDG_Prescaler_256);
	
	/* Set counter reload value */
	IWDG_SetReload(1560);
	
	/* Reload IWDG counter */
	IWDG_ReloadCounter();
	
	/* Enable IWDG (the LSI oscillator will be enabled by hardware) */
	IWDG_Enable();
}

