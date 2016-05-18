#include "rsystem.h"
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Set the Vector Table base address at 0x08000000 */
	//NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x00000);
	
	/* 设置中断优先级为1位抢占式优先级，3位子优先级 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    /* 设置串口1中断 */	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;			 //将串口5的抢占优先级设为最高
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					 //将串口5的响应优先级设为2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the TIM2 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel     = TIM2_IRQn; //定时器2
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 	     = 10;
	NVIC_InitStructure.NVIC_IRQChannelCmd                    = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	 
}

