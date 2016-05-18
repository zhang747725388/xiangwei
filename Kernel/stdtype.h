/*--- HEADER FILE DESCRIPTOR --------------------------------------------------
Project : Realtime Micro Library
File    : stdtype.h
Author  : automatic.dai
E-mail  : automatic.dai@gmail.com
Data    : 2013/01/16
Version : V1.0(alpha)
Note    : 
-----------------------------------------------------------------------------*/

#ifndef __STDTYPE_H_
#define __STDTYPE_H_

/*--- Header Includes -------------------------------------------------------*/

/*--- Macro Defination ------------------------------------------------------*/
/* Bit Manipulate */
#define BIT_SET(byte,bit)			( (byte) |=  (1<<(bit)) )
#define BIT_CLR(byte,bit)			( (byte) &= ~(1<<(bit)) )
#define BIT_CPL(byte,bit)			( (byte) ^=  (1<<(bit)) )
#define BIT_GET(byte,bit)			( (byte) &   (1<<(bit)) )

#define BIT_0						(0x01)
#define BIT_1						(0x02)
#define BIT_2						(0x04)
#define BIT_3						(0x08)
#define BIT_4						(0x10)
#define BIT_5						(0x20)
#define BIT_6						(0x40)
#define BIT_7						(0x80)

/* NULL Pointer */
#define	R_NULL						((void *)0)

/* Attributes */
#define R_IO						volatile
#define R_I							volatile const
#define R_O							volatile

#define R_EXT						extern
#define R_STATIC					static

#define R_COUNTER_TYPE				0x01
#define R_TIMER_TYPE				0x02
#define ISTYPE(x,y)					(x->type == y)
		
/*--- Data Struct Defination ------------------------------------------------*/
/* signed */
typedef  signed char				CHAR;
typedef  signed char				INT8S;
typedef  signed short int			INT16S;
typedef  signed int					INT32S;
typedef  signed long long int		INT64S;

/* unsigned */
typedef  unsigned char				BYTE;
typedef  unsigned char				UCHAR;
typedef  unsigned char				uchar;
typedef  unsigned char				INT8U;
typedef  unsigned short int			INT16U;
typedef  unsigned int				INT32U;
typedef  unsigned long long int 	INT64U;


#define RCCA			    (RCC_APB2Periph_GPIOA)
#define RCCB			    (RCC_APB2Periph_GPIOB)
#define RCCC			    (RCC_APB2Periph_GPIOC)
#define RCCD			    (RCC_APB2Periph_GPIOD)
#define RCCE			    (RCC_APB2Periph_GPIOE)
#define RCCF			    (RCC_APB2Periph_GPIOF)
#define PORTA		      (GPIOA)
#define PORTB		      (GPIOB)
#define PORTC		      (GPIOC)
#define PORTD		      (GPIOD)
#define PORTE		      (GPIOE)
#define PORTF		      (GPIOF)
#define PIN0			    (GPIO_Pin_0)
#define PIN1			    (GPIO_Pin_1)
#define PIN2			    (GPIO_Pin_2)
#define PIN3			    (GPIO_Pin_3)
#define PIN4			    (GPIO_Pin_4)
#define PIN5			    (GPIO_Pin_5)
#define PIN6			    (GPIO_Pin_6)
#define PIN7			    (GPIO_Pin_7)
 



/* float */
typedef  float						FLOAT32;
typedef  double						FLOAT64;

/* boolean */
typedef  enum _BOOLEAN
{
	bFALSE = 0,
	bTRUE  = 1
}BOOLEAN;

/* function pointer */
typedef void 						(*CALLBACK)(INT32U param);

/* mem address */
typedef R_IO INT32U 				*MEMADDR;

/*--- Variables Export ------------------------------------------------------*/

/*--- Function Declaration --------------------------------------------------*/
#define SYSTEM_SUPPORT_OS		0		// 
																	    
	 
 
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO?迆米??﹞車3谷?
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO?迆2迄℅¯,????米ㄓ辰?米?IO?迆!
//豕﹞㊣㏒n米??米D?車迆16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //那?3? 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //那?豕? 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //那?3? 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //那?豕? 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //那?3? 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //那?豕? 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //那?3? 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //那?豕? 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //那?3? 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //那?豕?

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //那?3? 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //那?豕?

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //那?3? 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //那?豕?
#endif
