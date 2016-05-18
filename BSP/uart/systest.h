
#ifndef __SYSTEST_H
#define __SYSTEST_H

#include "stdtype.h"

 
#define COM_SYSTEMTEST			(USART2)			//µ÷ÊÔÄ£¿éCOM¿Ú
#define COM_SYSTEMTEST_INIT(x)	(UART2_Init(x))
#define GetDATA_BUFFER_SIZE 150
extern BYTE    SysTest_RcvData[GetDATA_BUFFER_SIZE];
extern BYTE    Mart_RcvData[GetDATA_BUFFER_SIZE];
extern INT8U   SysTest_RcvDataLen;
extern void SysTest_Bsp_Init(void);
extern void SysTest_RcvDataInit(void);
extern void SysTest_GetUartData(BYTE UsartData);
extern void SysTest_SendData(BYTE * Cmd , INT8U CmdLen);
extern void SysTest_Disable_RcvIT(void);
extern void SysTest_Putstr(const BYTE *str);

extern void  SysTest_Putchar1(unsigned char c);
extern BOOLEAN IsSysTestDataRcved(void);
extern void SysTest_Putstr1(const BYTE str);

#endif

