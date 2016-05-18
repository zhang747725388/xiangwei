/*--- File Includes ------------------------------------------------------*/
#include "rsystem.h"

uint8_t seg_table_p[]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6,0xee,0x3e,0x9c,0x7a,0x9e,0x8e};
uint8_t seg_table_n[]={0x03,0x9F,0x25,0x0D,0x99,0x49,0x41,0x1F,0x01,0x09};

uint8_t hc595data[8]={0,0,0,0,0,0,0,0};
void hc595_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

  GPIO_InitStructure.GPIO_Pin = HC595_DATA;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(HC595_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = HC595_SCLK;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(HC595_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = HC595_RCLK;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(HC595_PORT, &GPIO_InitStructure);

  GPIO_ResetBits(HC595_PORT, HC595_DATA);
  GPIO_ResetBits(HC595_PORT, HC595_SCLK);
  GPIO_ResetBits(HC595_PORT, HC595_RCLK);

}

void hc595_write_byte(uint8_t byte)
{
  uint8_t i, num;
  num = byte;
  for (i=0; i<8; i++)
  {
    GPIO_ResetBits(HC595_PORT, HC595_SCLK);
    if ((num&0x01)==0x01)
      GPIO_SetBits(HC595_PORT, HC595_DATA);
    else
      GPIO_ResetBits(HC595_PORT, HC595_DATA);
    GPIO_SetBits(HC595_PORT, HC595_SCLK);
    num = num>>1;
  }
}

void hc595_latch(void)
{
  GPIO_ResetBits(HC595_PORT, HC595_RCLK);
  GPIO_SetBits(HC595_PORT, HC595_RCLK);
  GPIO_ResetBits(HC595_PORT, HC595_RCLK);
}

void hc595_display(uint8_t data[])
{
  hc595_write_byte(0x01);
  hc595_write_byte(seg_table_n[data[7]]);
  hc595_latch();
//HC595_DELAY
  hc595_write_byte(0x02);
  hc595_write_byte(seg_table_n[data[6]]);
  hc595_latch();
//HC595_DELAY
  hc595_write_byte(0x04);
  hc595_write_byte(seg_table_n[data[5]]);
  hc595_latch();
//HC595_DELAY
  hc595_write_byte(0x08);
  hc595_write_byte(seg_table_n[data[4]]);
  hc595_latch();
//HC595_DELAY
  hc595_write_byte(0x10);
  hc595_write_byte(seg_table_n[data[3]]);
  hc595_latch();
//HC595_DELAY
  hc595_write_byte(0x20);
  hc595_write_byte(seg_table_n[data[2]]);
  hc595_latch();
//HC595_DELAY
  hc595_write_byte(0x40);
  hc595_write_byte(seg_table_n[data[1]]);
  hc595_latch();
//HC595_DELAY
  hc595_write_byte(0x80);
  hc595_write_byte(seg_table_n[data[0]]);
  hc595_latch();
//HC595_DELAY
}

void SetHCMode(u8 type){

switch(type){
case open://打开
//	LCD_Write_cn(0, 3, 13);
// 	LCD_Write_cn(15, 3, 14);
// 	LCD_WriteString_en(30,3,value); //
   hc595data[0]=1;
   hc595data[1]=0;
   hc595data[2]=0;
   hc595data[3]=0;
   hc595data[4]=0;
   hc595data[5]=0;
   hc595data[6]=0;
   hc595data[7]=0;
	break;
case close://关闭
 
	break;
case strong://增益
 
	break;
case door://门槛
	 
	break;
case start://开始
	  
	break;
case stop://停止
	  
	break;
case mode://模式
	  
	break;
case OPENCMD://指令
	 
	break;
case CLOSECMD://指令
	  
	  
	break;
case Delay://延时
	  
	  
	break;
case AutoConnect:
   hc595data[0]=1;
   hc595data[1]=1;
   hc595data[2]=1;
   hc595data[3]=1;
   hc595data[4]=1;
   hc595data[5]=1;
   hc595data[6]=1;
   hc595data[7]=1;
   
	break;
}

}

void setMainMode(u8 value){
 
 

   hc595data[0]=value;
   hc595data[1]=0;
   hc595data[2]=0;
   hc595data[3]=0;
   hc595data[4]=0;
   hc595data[5]=0;
   hc595data[6]=0;
   hc595data[7]=0;



}

void setMainValue(u8 mode1, u8 value){
   u8 temp[3]={0,0,0};
 
   
   temp[0]=value/100;
   temp[1]=(value%100)/10;
   temp[2]=value%10;
  

   hc595data[0]=mode1;
   hc595data[1]=0;
   hc595data[2]=0;
   hc595data[3]=0;
   hc595data[4]=0;
   hc595data[5]= temp[0];
   hc595data[6]= temp[1];
   hc595data[7]= temp[2];



}
void setOpenclose(u8 mode1,u8 type1){
switch(type1){
case open:
	 hc595data[0]=mode1;
   hc595data[1]=0;
   hc595data[2]=0;
   hc595data[3]=0;
   hc595data[4]=0;
   hc595data[5]= 1;
   hc595data[6]= 1;
   hc595data[7]= 1;

	break;

case close:
	 hc595data[0]=mode1;
   hc595data[1]=0;
   hc595data[2]=0;
   hc595data[3]=0;
   hc595data[4]=0;
   hc595data[5]= 2;
   hc595data[6]= 2;
   hc595data[7]= 2;
	break;

}



}