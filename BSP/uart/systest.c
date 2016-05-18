
#include "rsystem.h"
#include "uart.h"

BOOLEAN GetData_bAvail;
BYTE    SysTest_RcvData[GetDATA_BUFFER_SIZE];
BYTE    Mart_RcvData[GetDATA_BUFFER_SIZE];
INT8U   SysTest_RcvDataLen;

void SysTest_UART_Init(void)
{
	COM_SYSTEMTEST_INIT(19200);
}


void SysTest_Enable_RcvIT(void)
{
	UART_Config_RxInterrupt(COM_SYSTEMTEST,ENABLE);
}


void SysTest_Disable_RcvIT(void)
{
	UART_Config_RxInterrupt(COM_SYSTEMTEST,DISABLE);
}


void SysTest_RcvDataInit(void)
{
	GetData_bAvail = bFALSE;
	memset(SysTest_RcvData,0,20);
	SysTest_RcvDataLen = 0;
}


void SysTest_GetUartData(BYTE UsartData)
{
	if( SysTest_RcvDataLen > GetDATA_BUFFER_SIZE-1){					   // ����������
		  SysTest_RcvDataLen =0;
      GetData_bAvail = bFALSE;			
	}

	
		/* ����Ƿ��յ���'!'*/
	if(UsartData == '!' ){
			GetData_bAvail = bTRUE;
	}
	if(GetData_bAvail == bTRUE){
 	  SysTest_RcvData[SysTest_RcvDataLen++] = UsartData;
		 
	} 
//  if(GetData_bAvail== bTRUE){
//	    return;
//	}

}
void RcvDataInit(void)
{
	GetData_bAvail = bFALSE;
	SysTest_RcvDataLen = 0;
	memset( SysTest_RcvData , 0 , GetDATA_BUFFER_SIZE);
}


void SysTest_SendData(BYTE * Cmd , INT8U CmdLen)
{
	INT8U i;
  RcvDataInit();
	for ( i = 0; i < CmdLen; i++ )
	{
		while ( USART_GetFlagStatus(COM_SYSTEMTEST, USART_FLAG_TXE) == RESET );
		USART_SendData(COM_SYSTEMTEST, *Cmd++);
	}
}
/*
 *   �������ƣ�void DebugUart_Putchar(uint8_t c)
 *   ���������c    �����͵�����
 *   ���ز�������
 *   �������ܣ�����1�ֽ����� ���ڵ���
 */
 
void SysTest_Bsp_Init(void)
{
	 SysTest_UART_Init();
	 SysTest_Enable_RcvIT();
//	SysTest_RcvDataInit();
}


/*
 *   �������ƣ�void DebugUart_Putdata(const uint8_t *buf, uint16_t size)
 *   ���������str      �������ַ����׵�ַ
 *             size     �������ݳ���
 *   ���ز�������
 *   �������ܣ����Ͷ�������   ���ڵ���
 */
void SysTest_Putstr(const BYTE *str)
{
	if(!str)  return;  
  RcvDataInit();	
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
void SysTest_Putstr1(const BYTE str)
{
	if(!str)  return;  
  RcvDataInit();	
	 while(USART_GetFlagStatus(COM_SYSTEMTEST, USART_FLAG_TXE) == RESET)  //�ȴ����ͳɹ�
		{
		}
		USART_SendData(COM_SYSTEMTEST, str);	  //��������
	 
}



BOOLEAN IsSysTestDataRcved(void)
{
	return (GetData_bAvail);
}

