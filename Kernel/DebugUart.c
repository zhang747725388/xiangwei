 /*
 *   用于系统调试使用的串口
 */
#include <string.h>
 
#include "DebugUart.h"
 
 /*
 *   用于调试函数
 */
#if DEBUG_UART_SWITCH 

#if 0
extern BOOLEAN Debug_GetOBDStatusNum;
#endif

#if 0
extern BOOLEAN Debug_SPECIALALARM;
#endif

static char *cmdBuf[] = 
{
	"status_up",
	"alarm",
	(char*)0
};

static uint32_t rcvNum;
static uint8_t  rcvBuf[100];



/*
 *   函数名称：void DebugUart_Putchar(uint8_t c)
 *   输入参数：c    待发送的数据
 *   返回参数：无
 *   函数功能：发送1字节数据 用于调试
 */
void 
DebugUart_Putchar(uint8_t c)
{
	while(USART_GetFlagStatus(COM_SYSTEMTEST, USART_FLAG_TXE) == RESET)  //等待发送成功
	{
	}
	USART_SendData(COM_SYSTEMTEST, c);	  //发送数据
}

/*
 *   函数名称：void DebugUart_Putstr(const u8 *str)
 *   输入参数：str      待发送字符串首地址
 *   返回参数：无
 *   函数功能：发送字符串str   用于调试
 */
void 
DebugUart_Putstr(const char *str)
{
	if(!str)  return;   
	while(*str)
	{
		while(USART_GetFlagStatus(COM_SYSTEMTEST, USART_FLAG_TXE) == RESET)  //等待发送成功
		{
		}
		USART_SendData(COM_SYSTEMTEST, (uint16_t)(*str++));	  //发送数据
	}
}



/*
 *   函数名称：void DebugUart_Putdata(const uint8_t *buf, uint16_t size)
 *   输入参数：str      待发送字符串首地址
 *             size     发送数据长度
 *   返回参数：无
 *   函数功能：发送定长数据   用于调试
 */
void 
DebugUart_Putdata(const uint8_t *buf, uint16_t size)
{
	if(!buf)  return;   
	while(size-- > 0)
	{
		while(USART_GetFlagStatus(COM_SYSTEMTEST, USART_FLAG_TXE) == RESET)  //等待发送成功
		{
		}
		USART_SendData(COM_SYSTEMTEST, *buf++);	  //发送数据
	}
}



/*
 *   函数名称：static u16 DebugUart_Getchar(void)
 *   输入参数：无
 *   返回参数：接收到的字节
 *   函数功能：从串口接收一个字节数据  用于调试
 */
u16 
DebugUart_Getchar(void)
{
	while(USART_GetFlagStatus(COM_SYSTEMTEST, USART_FLAG_RXNE) == RESET)  
	{
	}
	return USART_ReceiveData(COM_SYSTEMTEST);	
}


/*
 *   函数名称：调试口中断函数
 *   输出参数：无
 *   输出参数：无
 *   函数功能：完成调试串口接收中断功能
 */
void DebugUart_Interrupt(void)
{
	u8 c;
	c = (uint8_t)DebugUart_Getchar();

	DebugUart_Putchar(c);
	
	if(c == '>')
	{
		rcvNum = 0;
	}
	else if(c == '\r')
	{
		rcvBuf[rcvNum] = '\0';
		if(!strncmp((char*)rcvBuf, cmdBuf[0], strlen(cmdBuf[0])))
		{
#if 0
			Debug_GetOBDStatusNum = bTRUE;
#endif		
			DebugUart_Putstr("\r\n*******Status_up********\r\n");
			
		}
		else if(!strncmp((char*)rcvBuf, cmdBuf[1], strlen(cmdBuf[0])))
		{
			#if 0   /*调试使用*/
			Debug_SPECIALALARM = bTRUE;
			#endif
			
			DebugUart_Putstr("\r\n*******alarm********\r\n");
		}

	}
	else 
	{
		rcvBuf[rcvNum++] = c;
	}

}


#endif    //DEBUG_UART*******************************************************







