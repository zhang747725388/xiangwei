 /*
 *   ����ϵͳ����ʹ�õĴ���
 */
#include <string.h>
 
#include "DebugUart.h"
 
 /*
 *   ���ڵ��Ժ���
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
 *   �������ƣ�void DebugUart_Putchar(uint8_t c)
 *   ���������c    �����͵�����
 *   ���ز�������
 *   �������ܣ�����1�ֽ����� ���ڵ���
 */
void 
DebugUart_Putchar(uint8_t c)
{
	while(USART_GetFlagStatus(COM_SYSTEMTEST, USART_FLAG_TXE) == RESET)  //�ȴ����ͳɹ�
	{
	}
	USART_SendData(COM_SYSTEMTEST, c);	  //��������
}

/*
 *   �������ƣ�void DebugUart_Putstr(const u8 *str)
 *   ���������str      �������ַ����׵�ַ
 *   ���ز�������
 *   �������ܣ������ַ���str   ���ڵ���
 */
void 
DebugUart_Putstr(const char *str)
{
	if(!str)  return;   
	while(*str)
	{
		while(USART_GetFlagStatus(COM_SYSTEMTEST, USART_FLAG_TXE) == RESET)  //�ȴ����ͳɹ�
		{
		}
		USART_SendData(COM_SYSTEMTEST, (uint16_t)(*str++));	  //��������
	}
}



/*
 *   �������ƣ�void DebugUart_Putdata(const uint8_t *buf, uint16_t size)
 *   ���������str      �������ַ����׵�ַ
 *             size     �������ݳ���
 *   ���ز�������
 *   �������ܣ����Ͷ�������   ���ڵ���
 */
void 
DebugUart_Putdata(const uint8_t *buf, uint16_t size)
{
	if(!buf)  return;   
	while(size-- > 0)
	{
		while(USART_GetFlagStatus(COM_SYSTEMTEST, USART_FLAG_TXE) == RESET)  //�ȴ����ͳɹ�
		{
		}
		USART_SendData(COM_SYSTEMTEST, *buf++);	  //��������
	}
}



/*
 *   �������ƣ�static u16 DebugUart_Getchar(void)
 *   �����������
 *   ���ز��������յ����ֽ�
 *   �������ܣ��Ӵ��ڽ���һ���ֽ�����  ���ڵ���
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
 *   �������ƣ����Կ��жϺ���
 *   �����������
 *   �����������
 *   �������ܣ���ɵ��Դ��ڽ����жϹ���
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
			#if 0   /*����ʹ��*/
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







