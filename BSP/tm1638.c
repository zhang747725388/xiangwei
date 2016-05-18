#include "tm1638.h"
#include "stm32f10x.h"	
#include "rsystem.h"
SYSTIMER Tm16033_Tim;
 u8  key_tab1[]={1,   9,    17,   25,   16,   24,  32,   40};
 //�����������ʾ����
unsigned char ledtab[]={0x00,0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                           0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
KeyStaEnum Key1603_Check(u8 flag)
{
	static BOOLEAN TimStart = bFALSE;
	if( TimStart == bFALSE ){
		if(GPIO_ReadInputDataBit(KEY1_PORT,KEY1_PIN) == RESET){
			TimStart = bTRUE;
			Timer_Reset(&Tm16033_Tim);
		}
	}else{
		if(GPIO_ReadInputDataBit(KEY1_PORT,KEY1_PIN) == SET){
			TimStart = bFALSE;			
			if(Timer_GetElapse(&Tm16033_Tim) < 1000){
				return (Short);
			}else if(Timer_GetElapse(&Tm16033_Tim) > 3000){
				return (Long);
			}
		}		
	}
	
	return (NoPut);

}
 
void TM1638GPIO_Config(void)
{
  

     GPIO_InitTypeDef GPIO_InitStructure; 
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5| GPIO_Pin_6|GPIO_Pin_7; 
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
     GPIO_Init(GPIOA, &GPIO_InitStructure); 
} 
void TM1638_Write(unsigned char	DATA)			//д���ݺ���
{
  unsigned char i;
  for(i=0;i<8;i++)
  {    
    RESET_CLK;
    if(DATA&0X01)
      SET_DIO;
    else
      RESET_DIO;
    DATA>>=1;
    SET_CLK;
  }
}
unsigned char TM1638_Read(void)					//�����ݺ���
{
	unsigned char i;
	unsigned char temp=0;
  SET_DIO;	//����Ϊ����
	for(i=0;i<8;i++)
	{
		temp>>=1;
		RESET_CLK;
		if(GPIO_ReadInputDataBit(DIO_PORT,DIO_PIN) == SET)
			temp|=0x80;
		SET_CLK;
	}
	return temp;
}	
void Write_COM(unsigned char cmd)		//����������
{
  RESET_STB;
  TM1638_Write(cmd);
  SET_STB;
}

void Write_DATA(unsigned char add,unsigned char DATA)//ָ����ַд������
{  
  Write_COM(0x44);       /*�����������ã���̶���ַ��д����������*/  
  RESET_STB;
  TM1638_Write(0xc0|add);/*��ַ�������ã�����Ҫд�����ݵļĴ�����ַ*/
  TM1638_Write(DATA);
  SET_STB;
}
/*k3������8����*/
unsigned char Read_key(void)
{
  unsigned char c[4],i,key_value=0;
  RESET_STB;
  TM1638_Write(0x42);/*�����������ã���ȡ��ֵ����*/
  for(i=0;i<4;i++)
    c[i]=TM1638_Read();/*������ȡ�ĸ��ֽ�*/
  SET_STB;	
  for(i=0;i<4;i++)
    key_value|=c[i];
  for(i=0;i<4;i++)
    if(c[i]==key_value)
      break;
  return (i*8+key_value);  
}
void Write_oneLED(unsigned char num,unsigned char flag)	//��������һ��LED������numΪ��Ҫ���Ƶ�led��ţ�flagΪ0ʱϨ�𣬲�Ϊ0ʱ����
{
  if(flag)
    Write_DATA(2*num+1,1);
  else
    Write_DATA(2*num+1,0);
} 	 
void Write_allLED(unsigned char LED_flag)					//����ȫ��LED������LED_flag��ʾ����LED״̬
{
  unsigned char i;
  for(i=0;i<8;i++)
  {
    if(LED_flag&(1<<i))
      Write_DATA(2*i+1,3);
    else
      Write_DATA(2*i+1,0);
		}
}
void init_TM1638(void)
{
  unsigned char i;
  TM1638GPIO_Config();
  Write_COM(0x8F); /*��ʾ�����������ã������������ƺ���ʾ��������*/
  Write_COM(0x40); /*д�����������ã�����ʾ�Ĵ���д�����ҵ�ַ�Զ�����*/

	TM1638_Write(0xc0);//д��ַ����
	for(i=0;i<16;i++)
		TM1638_Write(ledtab[0]);	
	SET_STB;

}
//============================================================================//
void key_scan(void)
{
  u8 i=0,keyvalue=0,keytemp=0;  
  keyvalue=Read_key();
  if(keyvalue!=0)
  {
  for(i=0;i<8;i++)
  {
    if( keyvalue==key_tab1[i])
    {keytemp=i;break;}
  } 
  switch(keytemp)
  {
    case 0: 
//				   if(ModeMainFlag<2){
//           
//    
// 		    ModeMainFlag=3;
//          }
					
          
           break;
    case 1: 
  		
			LCD_Clear();  LCD_WriteString_en(30,0,"2"); 
 
	 
          break;
    case 2:  		 	LCD_Clear(); 
              		LCD_WriteString_en(30,0,"3");
					        Write_oneLED(0,0);
           break;
    case 3: 	LCD_Clear();
             	LCD_WriteString_en(30,0,"4");
           break;
    case 4: 	LCD_Clear();
			  	LCD_WriteString_en(30,0,"5");
           break;
    case 5:  
			LCD_Clear();
			LCD_WriteString_en(30,0,"6");
			break;
    case 6:  	LCD_WriteString_en(30,0,"7");
			break;
    case 7:  	LCD_WriteString_en(30,0,"8");
			break;    
    default:break;
  }
  }  
}
