
#include "rsystem.h"
/*******���ų�ʼ���ײ�ӿ�*****************/
/**********************************
** ��1��GPIO_Mode_AIN            ģ������
** ��2��GPIO_Mode_IN_FLOATING    ��������
** ��3��GPIO_Mode_IPD            ��������
** ��4��GPIO_Mode_IPU?           ��������
** ��5��GPIO_Mode_Out_OD         ��©���
** ��6��GPIO_Mode_Out_PP         �������
** ��7��GPIO_Mode_AF_OD          ���ÿ�©���
** ��8��GPIO_Mode_AF_PP          �����������
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