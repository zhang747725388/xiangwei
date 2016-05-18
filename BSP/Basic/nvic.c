#include "rsystem.h"
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Set the Vector Table base address at 0x08000000 */
	//NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x00000);
	
	/* �����ж����ȼ�Ϊ1λ��ռʽ���ȼ���3λ�����ȼ� */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    /* ���ô���1�ж� */	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;			 //������5����ռ���ȼ���Ϊ���
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					 //������5����Ӧ���ȼ���Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the TIM2 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel     = TIM2_IRQn; //��ʱ��2
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 	     = 10;
	NVIC_InitStructure.NVIC_IRQChannelCmd                    = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	 
}

