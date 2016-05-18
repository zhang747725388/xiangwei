#include "rsystem.h"
//////////////////////////////////////////////////////////////////////////////////	 
//����ң�س�ʼ��
//����IO�Լ���ʱ��4�����벶��
 INT32U IR_Key;
 u8* str=0; 
void Remote_Init(void)    			  
{  

	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;  
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //ʹ��PORTBʱ�� 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);	//TIM5 ʱ��ʹ�� 
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //PA1 ���� 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		//�������� 
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOA,GPIO_Pin_1);	//��ʼ��GPIOA1
	
						  
 	TIM_TimeBaseStructure.TIM_Period = 10000; //�趨�������Զ���װֵ ���10ms���  
	TIM_TimeBaseStructure.TIM_Prescaler =(72-1); 	//Ԥ��Ƶ��,1M�ļ���Ƶ��,1us��1.	   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ

	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;  // ѡ������� IC2ӳ�䵽TI5��
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  TIM_ICInitStructure.TIM_ICFilter = 0x03;//IC4F=0011 ���������˲��� 8����ʱ��ʱ�������˲�
  TIM_ICInit(TIM5, &TIM_ICInitStructure);//��ʼ����ʱ�����벶��ͨ��

  TIM_Cmd(TIM5,ENABLE ); 	//ʹ�ܶ�ʱ��5
 
 						
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM5�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���	
 
 	TIM_ITConfig( TIM5,TIM_IT_Update|TIM_IT_CC2,ENABLE);//��������ж� ,����CC2IE�����ж�	
}

 
//ң��������״̬
//[7]:�յ����������־
//[6]:�õ���һ��������������Ϣ
//[5]:����	
//[4]:����������Ƿ��Ѿ�������								   
//[3:0]:�����ʱ��
u8 	RmtSta=0;	  	  
u16 Dval;		//�½���ʱ��������ֵ
u32 RmtRec=0;	//������յ�������	   		    
u8  RmtCnt=0;	//�������µĴ���	  
//��ʱ��5�жϷ������	 
void TIM5_IRQHandler(void)
{ 		    	 
    if(TIM_GetITStatus(TIM5,TIM_IT_Update)!=RESET)
	{
		if(RmtSta&0x80)//�ϴ������ݱ����յ���
		{	
			RmtSta&=~0X10;						//ȡ���������Ѿ���������
			if((RmtSta&0X0F)==0X00)RmtSta|=1<<6;//����Ѿ����һ�ΰ����ļ�ֵ��Ϣ�ɼ�
			if((RmtSta&0X0F)<14)RmtSta++;
			else
			{
				RmtSta&=~(1<<7);//���������ʶ
				RmtSta&=0XF0;	//��ռ�����	
			}						 	   	
		}							    
	}
 	if(TIM_GetITStatus(TIM5,TIM_IT_CC2)!=RESET)
	{	  
		if(RDATA)//�����ز���
		{

			TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���				
	    	TIM_SetCounter(TIM5,0);	   	//��ն�ʱ��ֵ
			RmtSta|=0X10;					//����������Ѿ�������
		}else //�½��ز���
		{			
  			 Dval=TIM_GetCapture2(TIM5);//��ȡCCR1Ҳ������CC1IF��־λ
			 TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC4P=0	����Ϊ�����ز���
 			
			if(RmtSta&0X10)					//���һ�θߵ�ƽ���� 
			{
 				if(RmtSta&0X80)//���յ���������
				{
					
					if(Dval>300&&Dval<800)			//560Ϊ��׼ֵ,560us
					{
						RmtRec<<=1;	//����һλ.
						RmtRec|=0;	//���յ�0	   
					}else if(Dval>1400&&Dval<1800)	//1680Ϊ��׼ֵ,1680us
					{
						RmtRec<<=1;	//����һλ.
						RmtRec|=1;	//���յ�1
					}else if(Dval>2200&&Dval<2600)	//�õ�������ֵ���ӵ���Ϣ 2500Ϊ��׼ֵ2.5ms
					{
						RmtCnt++; 		//������������1��
						RmtSta&=0XF0;	//��ռ�ʱ��		
					}
 				}else if(Dval>4200&&Dval<4700)		//4500Ϊ��׼ֵ4.5ms
				{
					RmtSta|=1<<7;	//��ǳɹ����յ���������
					RmtCnt=0;		//�����������������
				}						 
			}
			RmtSta&=~(1<<4);
		}				 		     	    					   
	}
 TIM_ClearFlag(TIM5,TIM_IT_Update|TIM_IT_CC2);	    
}

//����������
//����ֵ:
//	 0,û���κΰ�������
//����,���µİ�����ֵ.
/*
;================================
;******  ����ң������ֵ��  ******
;  4c     0e      4d      0d
;  0f     4f      4e      0c
;  0b     4b      4a      08
;  48     12      16      4C
;  40     48      04      00
;  02     05      54      4D
;  0A     1E      0E      1A
;  1C     14      0F      0C
;================================  */
u8 Remote_Scan(void)
{        
	u8 sta=0;       
    u8 t1,t2;  
	if(RmtSta&(1<<6))//�õ�һ��������������Ϣ��
	{ 
	    t1=RmtRec>>24;			//�õ���ַ��
	    t2=(RmtRec>>16)&0xff;	//�õ���ַ���� 
 	    if((t1==(u8)~t2)&&t1==REMOTE_ID)//����ң��ʶ����(ID)����ַ 
	    { 
	        t1=RmtRec>>8;
	        t2=RmtRec; 	
	        if(t1==(u8)~t2)sta=t1;//��ֵ��ȷ	 
		}   
		if((sta==0)||((RmtSta&0X80)==0))//�������ݴ���/ң���Ѿ�û�а�����
		{
		 	RmtSta&=~(1<<6);//������յ���Ч������ʶ
			RmtCnt=0;		//�����������������
		}
	}  
    return sta;
}


void TIM2_IRQHandler( void )
{
	static INT16U IR_LastPluse = 0;
	static INT8U  IR_Sta         = 0;
	static INT32U IR_Code      = 0;
	static INT8U  IR_PluseCnt  = 0;
	static INT8U  IR_Up          = 0;
	INT16U IR_ThisPluse;
	INT16U IR_PluseSub;
	

	if ( TIM_GetITStatus( TIM2, TIM_IT_CC2 ) == SET )
	{
		TIM_ClearFlag( TIM2, TIM_IT_CC2 );
		IR_Up = 0;
		IR_ThisPluse = TIM_GetCapture2( TIM2 );
		
		if ( IR_ThisPluse > IR_LastPluse )
		{
			IR_PluseSub = IR_ThisPluse - IR_LastPluse;
		}
		else {
			IR_PluseSub = 0xffff - IR_LastPluse + IR_ThisPluse;
		}
		
		IR_LastPluse = IR_ThisPluse;
		IR_PluseCnt++;
		
		if ( IR_PluseCnt == 2 )
		{
			if (( IR_PluseSub > 5000 ) && ( IR_PluseSub < 8000 ))
			{
				IR_Sta = 0x01;
			}
		}
		else if ( IR_Sta & 0x01 )	// ��������ɹ�����ʼ����
		{
			if (( IR_PluseSub < 450 ) || ( IR_PluseSub > 1300 ))
			{
				IR_Sta      = 0;
				IR_PluseCnt = 0;
				IR_Code     = 0;
			}
			else
			{
				IR_Code <<= 1;
				if (( IR_PluseSub > 900 ) && ( IR_PluseSub < 1300 ))
				{
					IR_Code |= 0x01;
				}
				if ( IR_PluseCnt == 34 )
				{
					IR_Key = IR_Code;
					IR_Sta = 0x02;
				//	printf( "IR Down is : 0x%8x\n\n", IR_Key );
				}
			}
		}
		else if ( IR_Sta & 0x02 )
		{
			switch ( IR_PluseCnt )
			{
				case 35:
				{
					if ( ( IR_PluseSub < 4500 ) || ( IR_PluseSub > 7000 ) )
					{
						IR_PluseCnt--;
					}
					break;
				}
				case 36:
				{
					IR_PluseCnt = 34;
					if ( ( IR_PluseSub > 45000) && ( IR_PluseSub < 60000 ) )
					{	
						IR_Key = IR_Code;
						//printf( "IR continue is : 0x%8x\n\n", IR_Key );
					}
					break;
				}
			}
		}
	}
	
	if ( TIM_GetITStatus( TIM2, TIM_IT_Update ) == SET )
	{
		TIM_ClearFlag( TIM2, TIM_IT_Update );	
		if ( GPIO_ReadInputDataBit( GPIOA, GPIO_Pin_1 ) == SET )
		{
			IR_Up++;
			if ( IR_Up >= 2 )
			{
				IR_Code     = 0;
				IR_Sta      = 0;
				IR_PluseCnt = 0;
			}
		}
	} 
}
void Remote_check(void){

  u8 key; 
  Remotecode remotecode;
	key=Remote_Scan();	
		if(key)
		{	 
		 
			switch(key)
			{

	case Code_UP    :
		             str="ERROR";
		             break;
	case Code_DOWN  :
		             str="POWER";
		             break;
	case Code_PSW   :
		             str="UP";
		             break;
	case Code_EX    :
		             str="PLAY";
		             break;
	case Code_A     :
		             str="ALIENTEK";
		             break;
	case Code_B     :
		             str="RIGHT";
		             break;
	case Code_C     :
		             str="LEFT";
		             break;
	case Code_D     :
		             str="VOL-";
		             break;
	case Code_E     :
		             str="DOWN";
		             break;
	case Code_S     :
		             str="VOL+";
		             break;
	case Code_CON   :
		             str="1";
		             break;
	case Code_T1    :
		             str="2";
		             break;
	case Code_T2    :
		             str="3";
		             break;
	case Code_T3    :
		             str="4";
		             break;
	case Code_T4    :
		             str="5";
		             break;
	case Code_T5    :
		             str="6";
		             break;
	case Code_T6    :
		             str="7";
		             break;
	case Code_T7    :
		             str="8";
		             break;
	case Code_T8    :
		             str="9";
		             break;
	case Code_T9    :
		             str="0";
		             break;
	case Code_T10   :
		             str="DELETE";
		             break;		 
			}
		 
		}


}