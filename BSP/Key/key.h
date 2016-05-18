#ifndef __KEY_H_
#define __KEY_H_
#include "rtime.h"
#include "rsystem.h"
typedef enum _KeyStaEnum{
 	NoPut     = 0,				// 默认
	Short 	  = 1,				// 短按
	Long      = 2 				// 长按
}KeyStaEnum;
#define KEY0_RCC			    (RCC_APB2Periph_GPIOC)
#define KEY0_PORT		      (GPIOC)
#define KEY0_PIN			    (GPIO_Pin_1)

#define KEY1_RCC			    (RCC_APB2Periph_GPIOC)
#define KEY1_PORT		      (GPIOC)
#define KEY1_PIN			    (GPIO_Pin_2)

#define KEY2_RCC			    (RCC_APB2Periph_GPIOC)
#define KEY2_PORT		      (GPIOC)
#define KEY2_PIN			    (GPIO_Pin_3)

#define KEY3_RCC			    (RCC_APB2Periph_GPIOC)
#define KEY3_PORT		      (GPIOC)
#define KEY3_PIN			    (GPIO_Pin_4)

#define KEY4_RCC			     (RCC_APB2Periph_GPIOC)
#define KEY4_PORT		       (GPIOC)
#define KEY4_PIN			    (GPIO_Pin_5)

#define KEY5_RCC			    (RCC_APB2Periph_GPIOC)
#define KEY5_PORT		    (GPIOC)
#define KEY5_PIN			    (GPIO_Pin_6)

#define KEY6_RCC			    (RCC_APB2Periph_GPIOC)
#define KEY6_PORT		    (GPIOC)
#define KEY6_PIN			    (GPIO_Pin_7)

#define KEY7_RCC			    (RCC_APB2Periph_GPIOC)
#define KEY7_PORT		      (GPIOC)
#define KEY7_PIN			    (GPIO_Pin_8)

#define KEY0_STATUS     GPIO_ReadInputDataBit(KEY0_PORT,KEY0_PIN)
#define KEY1_STATUS     GPIO_ReadInputDataBit(KEY1_PORT,KEY1_PIN)
#define KEY2_STATUS     GPIO_ReadInputDataBit(KEY2_PORT,KEY2_PIN)
#define KEY3_STATUS     GPIO_ReadInputDataBit(KEY3_PORT,KEY3_PIN)
#define KEY4_STATUS     GPIO_ReadInputDataBit(KEY4_PORT,KEY4_PIN)
#define KEY5_STATUS     GPIO_ReadInputDataBit(KEY5_PORT,KEY5_PIN)
#define KEY6_STATUS     GPIO_ReadInputDataBit(KEY6_PORT,KEY6_PIN)
#define KEY7_STATUS     GPIO_ReadInputDataBit(KEY7_PORT,KEY7_PIN)


#define KEY_SERIES_FLAG    100       //按键连发开始所需时间长度
#define KEY_SERIES_DELAY    50       //按键连发的时间间隔长度

//按键属性
#define KEY_DOWN        0xA0
#define KEY_LONG        0xB0
#define KEY_LIAN        0xC0
#define KEY_UP          0xD0
#define KEY_SHORT       0xE0

 
#define KEY0_DOWN        0xA1
#define KEY0_LONG        0xB1
#define KEY0_LIAN        0xC1
#define KEY0_UP          0xD1

#define KEY1_DOWN        0xA2
#define KEY1_LONG        0xB2
#define KEY1_LIAN        0xC2
#define KEY1_UP          0xD2

#define KEY2_DOWN        0xA3
#define KEY2_LONG        0xB3
#define KEY2_LIAN        0xC3
#define KEY2_UP          0xD3

#define KEY3_DOWN        0xA4
#define KEY3_LONG        0xB4
#define KEY3_LIAN        0xC4
#define KEY3_UP          0xD4

#define KEY4_DOWN        0xA5
#define KEY4_LONG        0xB5
#define KEY4_LIAN        0xC5
#define KEY4_UP          0xD5

#define KEY5_DOWN        0xA6
#define KEY5_LONG        0xB6
#define KEY5_LIAN        0xC6
#define KEY5_UP          0xD6



#define KEY6_DOWN        0xA7
#define KEY6_LONG        0xB7
#define KEY6_LIAN        0xC7
#define KEY6_UP          0xD7


#define KEY7_DOWN        0xA8
#define KEY7_LONG        0xB8
#define KEY7_LIAN        0xC8
#define KEY7_UP          0xD8








#define NO_KEY          0x00

#define KEY_DOWN1       0X01
#define KEY_DOWN2       0X02
#define KEY_DOWN3       0X03
#define KEY_DOWN4       0X04
#define KEY_DOWN5       0X05
#define KEY_DOWN6       0X06
#define KEY_DOWN7       0X07
#define KEY_DOWN8       0X08



#define KEY0_PRESS      (KEY_DOWN|KEY0_DOWN)
#define KEY1_PRESS      (KEY_DOWN|KEY1_DOWN)
#define KEY2_PRESS      (KEY_DOWN|KEY2_DOWN)
#define KEY3_PRESS      (KEY_DOWN|KEY3_DOWN)
#define KEY4_PRESS      (KEY_DOWN|KEY4_DOWN)
#define KEY5_PRESS      (KEY_DOWN|KEY5_DOWN)
#define KEY6_PRESS      (KEY_DOWN|KEY6_DOWN)
#define KEY7_PRESS      (KEY_DOWN|KEY7_DOWN)
void Key_Init(void);
uchar Key_Scan(void);
void KeyAction(u8 flag);
void MainKeytask(void);

#endif
