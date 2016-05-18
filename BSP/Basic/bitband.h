
#ifndef __BITBAND_H_
#define __BITBAND_H_

#include "stm32f10x.h"

///////////////////////////////////////////////////////////////
//位带操作宏定义
#define BIT_BAND(add, bitnum) 	((add & 0xF0000000)+0x2000000+((add & 0xFFFFF)<<5)+(bitnum<<2)) 
#define BIT_ADDR(add, bitnum)	*((volatile unsigned long *)BIT_BAND(add, bitnum)) 

//IO口地址映射
#define GPIOA_IDR_ADDR    	(GPIOA_BASE+8) // 0x40010808 
#define GPIOB_IDR_ADDR    	(GPIOB_BASE+8) // 0x40010C08 
#define GPIOC_IDR_ADDR    	(GPIOC_BASE+8) // 0x40011008 
#define GPIOD_IDR_ADDR    	(GPIOD_BASE+8) // 0x40011408 
#define GPIOE_IDR_ADDR    	(GPIOE_BASE+8) // 0x40011808 
#define GPIOF_IDR_ADDR    	(GPIOF_BASE+8) // 0x40011A08 
#define GPIOG_IDR_ADDR    	(GPIOG_BASE+8) // 0x40011E08 

#define GPIOA_ODR_ADDR    	(GPIOA_BASE+12) // 0x4001080C 
#define GPIOB_ODR_ADDR    	(GPIOB_BASE+12) // 0x40010C0C 
#define GPIOC_ODR_ADDR    	(GPIOC_BASE+12) // 0x4001100C 
#define GPIOD_ODR_ADDR    	(GPIOD_BASE+12) // 0x4001140C 
#define GPIOE_ODR_ADDR    	(GPIOE_BASE+12) // 0x4001180C 
#define GPIOF_ODR_ADDR    	(GPIOF_BASE+12) // 0x40011A0C    
#define GPIOG_ODR_ADDR    	(GPIOG_BASE+12) // 0x40011E0C    

#define PORTA_OUT(n)   		BIT_ADDR(GPIOA_ODR_ADDR, n%16) 
#define PORTA_IN(n)    		BIT_ADDR(GPIOA_IDR_ADDR, n%16) 

#define PORTB_OUT(n)   		BIT_ADDR(GPIOB_ODR_ADDR, n%16) 
#define PORTB_IN(n)    		BIT_ADDR(GPIOB_IDR_ADDR, n%16) 

#define PORTC_OUT(n)   		BIT_ADDR(GPIOC_ODR_ADDR, n%16) 
#define PORTC_IN(n)    		BIT_ADDR(GPIOC_IDR_ADDR, n%16) 

#define PORTD_OUT(n)   		BIT_ADDR(GPIOD_ODR_ADDR, n%16) 
#define PORTD_IN(n)    		BIT_ADDR(GPIOD_IDR_ADDR, n%16) 

#define PORTE_OUT(n)   		BIT_ADDR(GPIOE_ODR_ADDR, n%16) 
#define PORTE_IN(n)    		BIT_ADDR(GPIOE_IDR_ADDR, n%16)

#define PORTF_OUT(n)   		BIT_ADDR(GPIOF_ODR_ADDR, n%16) 
#define PORTF_IN(n)    		BIT_ADDR(GPIOF_IDR_ADDR, n%16)

#define PORTG_OUT(n)   		BIT_ADDR(GPIOG_ODR_ADDR, n%16) 
#define PORTG_In(n)    		BIT_ADDR(GPIOG_IDR_ADDR, n%16)

#endif
