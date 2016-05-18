
#include "stm32f10x_it.h"
#include "bsp.h"
#include "atc30.h"
#include "systest.h" 
 
//extern void USB_Istr(void);


//gql_debug_uart_20140916
/*----------------------------------------------------------------------
* º¯ÊýÃû³Æ£ºUSART1_IRQHandler()
* Èë¿Ú²ÎÊý£ºÎÞ
* ³ö¿Ú²ÎÊý£ºÎÞ
* ·µ»Ø²ÎÊý£ºÎÞ
* º¯Êý°æ±¾£º
* º¯ÊýËµÃ÷£º´®¿ÚDebug¡£
------------------------------------------------------------------------
* º¯ÊýÐÞ¶©£º
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
* º¯ÊýÃû³Æ£ºUSART2_IRQHandler()
* Èë¿Ú²ÎÊý£ºÎÞ
* ³ö¿Ú²ÎÊý£ºÎÞ
* ·µ»Ø²ÎÊý£ºÎÞ
* º¯Êý°æ±¾£º
* º¯ÊýËµÃ÷£º 
------------------------------------------------------------------------
* º¯ÊýÐÞ¶©£º
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
* º¯ÊýÃû³Æ£ºUSART3_IRQHandler()
* Èë¿Ú²ÎÊý£ºÎÞ
* ³ö¿Ú²ÎÊý£ºÎÞ
* ·µ»Ø²ÎÊý£ºÎÞ
* º¯Êý°æ±¾£º
* º¯ÊýËµÃ÷£   ½ÓÊÕÖÐ¶Ï
------------------------------------------------------------------------
* º¯ÊýÐÞ¶©£º
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
* º¯ÊýÃû³Æ£ºUART4_IRQHandler()
* Èë¿Ú²ÎÊý£ºÎÞ
* ³ö¿Ú²ÎÊý£ºÎÞ
* ·µ»Ø²ÎÊý£ºÎÞ
* º¯Êý°æ±¾£º
* º¯ÊýËµÃ÷:
------------------------------------------------------------------------
* º¯ÊýÐÞ¶©£º
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
* º¯ÊýÃû³Æ£ºUART5_IRQHandler()
* Èë¿Ú²ÎÊý£ºÎÞ
* ³ö¿Ú²ÎÊý£ºÎÞ
* ·µ»Ø²ÎÊý£ºÎÞ
* º¯Êý°æ±¾£º
* º¯ÊýËµÃ÷£ 
------------------------------------------------------------------------
* º¯ÊýÐÞ¶©£º
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

