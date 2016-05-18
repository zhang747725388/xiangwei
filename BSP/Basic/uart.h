
#ifndef __UART_H_
#define __UART_H_

#include "stm32f10x.h"
#include "stdtype.h"

/* Function Export */
extern void UART1_Init(INT32U u32BaudRate);
extern void UART2_Init(INT32U u32BaudRate);
extern void UART3_Init(INT32U u32BaudRate);
extern void UART4_Init(INT32U u32BaudRate);
extern void UART5_Init(INT32U u32BaudRate);

extern void UART_Config_RxInterrupt(USART_TypeDef *uart, FunctionalState state);
extern void UART_SendDataBlock(USART_TypeDef *USART,  BYTE *cpData, INT32U u32Count);

#endif
