
#include "stm32f10x_it.h"
#include "bsp.h"
#include "atc30.h"
#include "systest.h" 
 
//extern void USB_Istr(void);


//gql_debug_uart_20140916
/*----------------------------------------------------------------------
* �������ƣ�USART1_IRQHandler()
* ��ڲ�������
* ���ڲ�������
* ���ز�������
* �����汾��
* ����˵��������Debug��
------------------------------------------------------------------------
* �����޶���
----------------------------------------------------------------------*/
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){	
////	 Debug_Data_Analysis(USART_ReceiveData(USART1));
//		SysTest_GetUartData(USART_ReceiveData(USART1));
	}else{
		USART_ReceiveData(USART1);
	}
	USART_ClearFlag(USART1, USART_FLAG_RXNE);

}


/*----------------------------------------------------------------------
* �������ƣ�USART2_IRQHandler()
* ��ڲ�������
* ���ڲ�������
* ���ز�������
* �����汾��
* ����˵���� 
------------------------------------------------------------------------
* �����޶���
----------------------------------------------------------------------*/
void USART2_IRQHandler(void)       
{
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET){	
//	 Debug_Data_Analysis(USART_ReceiveData(USART1));
			SysTest_GetUartData(USART_ReceiveData(USART2));
	}else{
		USART_ReceiveData(USART2);
	}	
 	USART_ClearFlag(USART2, USART_FLAG_RXNE);
}


/*----------------------------------------------------------------------
* �������ƣ�USART3_IRQHandler()
* ��ڲ�������
* ���ڲ�������
* ���ز�������
* �����汾��
* ����˵���   �����ж�
------------------------------------------------------------------------
* �����޶���
----------------------------------------------------------------------*/
void USART3_IRQHandler(void)
{
	if (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) != RESET){	
//		GetDataFromSim900A(USART_ReceiveData(USART3));
	}else{
		USART_ReceiveData(USART3);
	}	
	USART_ClearFlag(USART3, USART_FLAG_RXNE);	
	
}


/*----------------------------------------------------------------------
* �������ƣ�UART4_IRQHandler()
* ��ڲ�������
* ���ڲ�������
* ���ز�������
* �����汾��
* ����˵��:
------------------------------------------------------------------------
* �����޶���
----------------------------------------------------------------------*/
void UART4_IRQHandler(void)
{
	if (USART_GetFlagStatus(UART4, USART_FLAG_RXNE) != RESET){	
//		Blueth_GetUsartData(USART_ReceiveData(UART4));
	}else{
		USART_ReceiveData(UART4);
	}
	USART_ClearFlag(UART4, USART_FLAG_RXNE);
	
}


/*----------------------------------------------------------------------
* �������ƣ�UART5_IRQHandler()
* ��ڲ�������
* ���ڲ�������
* ���ز�������
* �����汾��
* ����˵��� 
------------------------------------------------------------------------
* �����޶���
----------------------------------------------------------------------*/
void UART5_IRQHandler(void)
{
	if (USART_GetFlagStatus(UART5, USART_FLAG_RXNE) != RESET){	
//		OBD_GetUsartData(USART_ReceiveData(UART5));
	}else{
		USART_ReceiveData(UART5);
	}
	USART_ClearFlag(UART5, USART_FLAG_RXNE);
}


void NMI_Handler(void)
{
	while(1);
}


void HardFault_Handler(void)
{
	while(1);
}


void MemManage_Handler(void)
{
	while(1);
}


void BusFault_Handler(void)
{
	while(1);
}


void UsageFault_Handler(void)
{
	while(1);
}

