#ifndef	_TM1638_H
#define	_TM1638_H
// #include "stm32f10x.h"	
 #include "rsystem.h"
/*key1  key2  key3  key4  key5  key6 key7  key8*/

//=============TM1638通讯端口设置=====================================//
#define DIO_PORT		GPIOA        //设置DIO(数据输入输出引脚)
#define DIO_PIN		  GPIO_Pin_7
#define CLK_PORT		GPIOA        //设置时钟（CLK）引脚
#define CLK_PIN		  GPIO_Pin_6
#define STB_PORT		GPIOA        //设置使能引脚（STB）引脚
#define STB_PIN		  GPIO_Pin_5
#define SET_CLK         GPIO_SetBits(CLK_PORT, CLK_PIN)
#define RESET_CLK       GPIO_ResetBits(CLK_PORT, CLK_PIN)
#define SET_DIO         GPIO_SetBits(DIO_PORT, DIO_PIN)
#define RESET_DIO       GPIO_ResetBits(DIO_PORT, DIO_PIN)
#define SET_STB         GPIO_SetBits(STB_PORT, STB_PIN)
#define RESET_STB       GPIO_ResetBits(STB_PORT, STB_PIN)
//=================TM1638指令定义====================================//
#define Writedat  0x44 /*write data into display register*/
#define Readdat   0x42  /*read key_scan data*/
#define Autoaddrin 0x40 
void TM1638GPIO_Config(void);
void TM1638_Write(unsigned char	DATA);
unsigned char TM1638_Read(void);
void Write_COM(unsigned char cmd);
void Write_DATA(unsigned char add,unsigned char DATA);
unsigned char Read_key(void);
void Write_oneLED(unsigned char num,unsigned char flag);
void Write_allLED(unsigned char LED_flag);
void init_TM1638(void);
void key_scan(void);
#endif
