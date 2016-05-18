#ifndef __LED_H
#define __LED_H
#include "rsystem.h"
#define LED1_RCC			    (RCC_APB2Periph_GPIOC)
#define LED1_PORT		      (GPIOC)
#define LED1_PIN			    (GPIO_Pin_0)  

#define LED2_RCC			    (RCC_APB2Periph_GPIOC)
#define LED2_PORT		      (GPIOC)
#define LED2_PIN			    (GPIO_Pin_0)  

#define LED3_RCC			    (RCC_APB2Periph_GPIOC)
#define LED3_PORT		      (GPIOC)
#define LED3_PIN			    (GPIO_Pin_0) 

#define LED4_RCC			    (RCC_APB2Periph_GPIOC)
#define LED4_PORT		      (GPIOC)
#define LED4_PIN			    (GPIO_Pin_0) 
#define CLOSE 0
#define OPEN  1

#define LED1  1
#define LED2  2
#define LED3  3
#define LED4  4

extern void Led_Init(void);
extern void Led1_PortInit(void);
extern void Led1_On(void);
extern void Led1_Off(void);
extern void Led_Contr(u8 lednum,u8 status);
#endif

