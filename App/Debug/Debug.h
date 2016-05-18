

#ifndef __DEBUG_H_
#define __DEBUG_H_

/*--- File Includes ------------------------------------------------------*/
#include "stm32f10x.h"

/*--- Macro Defination ---------------------------------------------------*/

/*--- Data Struct Defination ---------------------------------------------*/
typedef enum _DebugModeEnum{
	DebugDefault   = 0,
	DebugHard      = 1,
	DebugSoft      = 2
}DebugModeEnum;


/*--- Variables Export ---------------------------------------------------*/

/*--- Function Export ----------------------------------------------------*/
extern void Debug_WriteDeviceID(const uint8_t *terminalid);
extern void Debug_WriteHardVer(const uint8_t *hardware);
extern void Debug_WriteProductID(const uint8_t *productid);
extern void Debug_GetConstParam(uint8_t *productid , uint8_t *version , uint8_t *hardware , uint8_t *terminalid);
extern uint16_t Debug_GetVol(void);
extern uint8_t Debug_GetMemsSta(void);
extern uint8_t Debug_GetEFlashSta(void);
extern void Debug_GetGPSInfo(uint8_t *data, uint16_t *size);
extern void Debug_GetLKClientSta(uint8_t *status, uint8_t *errid);
extern void Debug_GetOBDSta(uint8_t *status, uint8_t *errid);
extern void Debug_TTSTest(void);
extern void Debug_WakeUpTest(void);
extern void Debug_SetStartMode(uint8_t position);
extern void Debug_GetFlashAddr(uint32_t *StartAddr, uint32_t *FlashSize);
extern void Debug_WriteSuperBlock(uint16_t Space ,uint16_t CheckByte);


extern DebugModeEnum Debug_GetMode(void);
extern void Debug_ClrMode(void);


#endif

