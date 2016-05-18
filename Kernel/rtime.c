/*--- SOURCE FILE DESCRIPTOR ---------------------------------------------------
Project : Realtime Micro Library
File    : rtime.c
Author  : automatic.dai
E-mail  : automatic.dai@gmail.com
Data    : 2013/01/16
Version : V1.0(alpha)
Note    : 
------------------------------------------------------------------------------*/

#include "stm32f10x.h"
#include "rtime.h"


INT32U		r_tickcnt;			// used for calculate time(* SYSTICK_TIME)


void Systick_Init(void)
{
	INT16U systick_fac_ms = RML_SYSCLK_FREQ / 8 / 1000; 		// 1ms interval    

	/* Set reload register */
	SysTick->LOAD  = (systick_fac_ms & SysTick_LOAD_RELOAD_Msk) - 1;
	
	/* Set priority for Cortex-M3 System Interrupts */
	NVIC_SetPriority(SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
	
	/* Load the SysTick Counter Value */  
	SysTick->VAL   = 0; 
	
	/* Enable SysTick IRQ and SysTick Timer */                                         
	SysTick->CTRL  = //SysTick_CTRL_CLKSOURCE_Msk | 
	               SysTick_CTRL_TICKINT_Msk   | 
	               SysTick_CTRL_ENABLE_Msk;                   

}


/*--- FUNCTION DESCRIPTOR ------------------------------------------------------
Function : SysTick_Handler()
Input    : 
Output   : 
Return   : 
Version  : 
Note     :
------------------------------------------------------------------------------*/
void SysTick_Handler(void)
{
	static INT32U tickcnt = 0;
	if ( ++tickcnt >= RML_SYSTICK_TIME )
	{
		tickcnt = 0;
		Timer_TickISR();
	}
}		
void InputCaptureInit( void )
{
	TIM_ICInitTypeDef 		TIM_ICInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
   RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE );
	
	TIM_TimeBaseInitStructure.TIM_Period             = 0xffff; // 16位计数
	TIM_TimeBaseInitStructure.TIM_Prescaler          = 72*2-1;   // 144分频 2us
	TIM_TimeBaseInitStructure.TIM_ClockDivision     = 0;      // 不分割
	TIM_TimeBaseInitStructure.TIM_CounterMode   = TIM_CounterMode_Up; // 上升计数
	TIM_TimeBaseInit( TIM2, &TIM_TimeBaseInitStructure );
	TIM_ITConfig( TIM2, TIM_IT_Update, DISABLE );
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	
	TIM_ICInitStructure.TIM_Channel       = TIM_Channel_2;				// 选择通道2
	TIM_ICInitStructure.TIM_ICPolarity     = TIM_ICPolarity_Falling;		       // 下降沿触发
	TIM_ICInitStructure.TIM_ICPrescaler   = TIM_ICPSC_DIV1;				//
	TIM_ICInitStructure.TIM_ICSelection  = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICFilter        = 0x0;	
	TIM_ICInit( TIM2, &TIM_ICInitStructure );
	TIM_ITConfig( TIM2, TIM_IT_CC2, DISABLE );
	TIM_ClearFlag( TIM2, TIM_FLAG_CC2 );	
	TIM_Cmd( TIM2, ENABLE );
	TIM_ITConfig( TIM2, TIM_IT_CC2 | TIM_IT_Update, ENABLE );
}

/*--- FUNCTION DESCRIPTOR ------------------------------------------------------
Function : Timer_TickISR()
Input    : 
Output   : 
Return   : 
Version  : 
Note     : 
------------------------------------------------------------------------------*/
void Timer_TickISR(void)
{
	++r_tickcnt;
}


/*--- FUNCTION DESCRIPTOR ------------------------------------------------------
Function : Timer_Set()
Input    : 
Output   : 
Return   : 
Version  : 
Note     : 
------------------------------------------------------------------------------*/
void Timer_Set(SYSTIMER *timer, INT32U alarm_time)
{
	timer->start_cnt = r_tickcnt;
	timer->alarm_time = alarm_time;	
}


/*--- FUNCTION DESCRIPTOR ------------------------------------------------------
Function : Timer_Reset()
Input    : 
Output   : 
Return   : 
Version  : 
Note     : 
------------------------------------------------------------------------------*/
void Timer_Reset(SYSTIMER *timer)
{
	timer->start_cnt = r_tickcnt;
}


/*--- FUNCTION DESCRIPTOR ------------------------------------------------------
Function : Timer_GetElapse()
Input    : 
Output   : 
Return   : 
Version  : 
Note     : 
------------------------------------------------------------------------------*/
INT32U Timer_GetElapse(SYSTIMER *timer)
{
	return	(r_tickcnt - timer->start_cnt) * RML_SYSTICK_TIME; 
}


/*--- FUNCTION DESCRIPTOR ------------------------------------------------------
Function : Timer_GetReached()
Input    : 
Output   : 
Return   : 
Version  : 
Note     : 
------------------------------------------------------------------------------*/
BOOLEAN Timer_GetReached(SYSTIMER *timer)
{
	if((timer -> alarm_time) != 0){
		return ( Timer_GetElapse(timer) >= timer->alarm_time ) ? bTRUE : bFALSE;
	}
	return (bFALSE);
}
void Timer_Delayms(u32 ms)
{
	SYSTIMER time;
	
	Timer_Set(&time, ms);
	while(!Timer_GetReached(&time))
	{}
}
