
#include "rsystem.h"
/*******引脚初始化底层接口*****************/
/**********************************
** （1）GPIO_Mode_AIN            模拟输入
** （2）GPIO_Mode_IN_FLOATING    浮空输入
** （3）GPIO_Mode_IPD            下拉输入
** （4）GPIO_Mode_IPU?           上拉输入
** （5）GPIO_Mode_Out_OD         开漏输出
** （6）GPIO_Mode_Out_PP         推挽输出
** （7）GPIO_Mode_AF_OD          复用开漏输出
** （8）GPIO_Mode_AF_PP          复用推挽输出
**********************************/


void Init_gpio(u8 rcc_type,u8 pin_num,u8 type){
//  GPIO_InitTypeDef GPIO_InitStructure;
//	 switch(rcc_type){
//		   case 0:
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(PORTA, &GPIO_InitStructure);
//			 break; 
//	 	   case 1:
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(PORTB, &GPIO_InitStructure);
//			 break;
//			 case 2:
//			 break;
//			 case 3:
//			 break;
//			 case 4:
//			 break;
//	 
//	 
//	 
//	 }
}