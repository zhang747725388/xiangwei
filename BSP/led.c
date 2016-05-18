#include "rsystem.h"
void Led1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* LED控制 */
	RCC_APB2PeriphClockCmd(LED1_RCC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(LED1_PORT, &GPIO_InitStructure);
}
void Led2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* LED控制 */
	RCC_APB2PeriphClockCmd(LED2_RCC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED2_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(LED2_PORT, &GPIO_InitStructure);
}
void Led3_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* LED控制 */
	RCC_APB2PeriphClockCmd(LED3_RCC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED3_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(LED3_PORT, &GPIO_InitStructure);
}
void Led4_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* LED控制 */
	RCC_APB2PeriphClockCmd(LED4_RCC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED4_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(LED4_PORT, &GPIO_InitStructure);
}
void Led1_On(void)
{
		GPIO_SetBits(LED1_PORT, LED1_PIN);    
}


void Led1_Off(void)
{
	GPIO_ResetBits(LED1_PORT, LED1_PIN); 
}
void Led2_On(void)
{
		GPIO_SetBits(LED2_PORT, LED2_PIN);    
}


void Led2_Off(void)
{
	GPIO_ResetBits(LED2_PORT, LED2_PIN); 
}

void Led3_On(void)
{
		GPIO_SetBits(LED3_PORT, LED3_PIN);    
}
void Led3_Off(void)
{
	GPIO_ResetBits(LED3_PORT, LED3_PIN); 
}
 
void Led4_On(void)
{
		GPIO_SetBits(LED4_PORT, LED4_PIN);    
}
void Led4_Off(void)
{
	GPIO_ResetBits(LED4_PORT, LED4_PIN); 
}

 void Led_Init(void){
    Led1_Init();
    Led2_Init();
    Led3_Init();
	  Led4_Init();
}
 
/***LED状态控制*****
**
**lednum
***************/
void Led_Contr(u8 lednum,u8 status){
   switch(lednum){
	             case LED1:
                  switch(status)
                  {
                   case OPEN:   Led4_On();break;
                   case CLOSE:  Led4_Off(); break;
                   }break;
               case LED2:
                  switch(status)
                  {
                   case OPEN:   Led2_On();break;
                   case CLOSE:  Led2_Off(); break;
                   }break;
               case LED3:
                  switch(status)
                  {
                   case OPEN:   Led3_On();break;
                   case CLOSE:  Led3_Off(); break;
                   }break;
		            case LED4:
	              switch(status)
	                {
		           case OPEN: Led4_On();break;
		           case CLOSE:  Led4_Off(); break;
	               }break;
	 
	 }
}
