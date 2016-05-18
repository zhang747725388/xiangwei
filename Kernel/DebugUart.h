 
#ifndef _DEBUG_UART_H_
#define _DEBUG_UART_H_

#include "stm32f10x.h"
//#include "port.h"

/*
 *   调试定义
 */
#define DEBUG_UART_SWITCH 1  //是否启用调试

#if DEBUG_UART_SWITCH

#define COM_SYSTEMTEST	USART1

//打印调试位置

#define DEBUG_LOCATION() \
do				\
{  \
	uint16_t line = __LINE__;  \
	DebugUart_Putstr("[File:");  \
	DebugUart_Putstr(__FILE__);  \
	DebugUart_Putstr("  ");   \
	DebugUart_Putstr("line:");   \
	DebugUart_Putchar((char)(line / 1000 % 10) + '0'); \
	DebugUart_Putchar((char)(line / 100 % 10) + '0');  \
	DebugUart_Putchar((char)(line / 10 % 10) + '0');   \
	DebugUart_Putchar((char)(line % 10) + '0');   \
	DebugUart_Putstr("]\r\n");   \
}while(0);


void DebugUart_Interrupt(void);                     //调试口中断函数
 

/*调试串口*/
void DebugUart_Putchar(uint8_t c);
void DebugUart_Putstr(const char *str);
u16 DebugUart_Getchar(void);
void DebugUart_Putdata(const uint8_t *buf, uint16_t size);

#endif


#endif
