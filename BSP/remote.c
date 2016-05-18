#include "rsystem.h"
//////////////////////////////////////////////////////////////////////////////////	 
//红外遥控初始化
//设置IO以及定时器4的输入捕获
 INT32U IR_Key;
 u8* str=0; 
void Remote_Init(void)    			  
{  

	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;  
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //使能PORTB时钟 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);	//TIM5 时钟使能 
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //PA1 输入 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		//上拉输入 
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOA,GPIO_Pin_1);	//初始化GPIOA1
	
						  
 	TIM_TimeBaseStructure.TIM_Period = 10000; //设定计数器自动重装值 最大10ms溢出  
	TIM_TimeBaseStructure.TIM_Prescaler =(72-1); 	//预分频器,1M的计数频率,1us加1.	   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式

	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;  // 选择输入端 IC2映射到TI5上
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  TIM_ICInitStructure.TIM_ICFilter = 0x03;//IC4F=0011 配置输入滤波器 8个定时器时钟周期滤波
  TIM_ICInit(TIM5, &TIM_ICInitStructure);//初始化定时器输入捕获通道

  TIM_Cmd(TIM5,ENABLE ); 	//使能定时器5
 
 						
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM5中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器	
 
 	TIM_ITConfig( TIM5,TIM_IT_Update|TIM_IT_CC2,ENABLE);//允许更新中断 ,允许CC2IE捕获中断	
}

 
//遥控器接收状态
//[7]:收到了引导码标志
//[6]:得到了一个按键的所有信息
//[5]:保留	
//[4]:标记上升沿是否已经被捕获								   
//[3:0]:溢出计时器
u8 	RmtSta=0;	  	  
u16 Dval;		//下降沿时计数器的值
u32 RmtRec=0;	//红外接收到的数据	   		    
u8  RmtCnt=0;	//按键按下的次数	  
//定时器5中断服务程序	 
void TIM5_IRQHandler(void)
{ 		    	 
    if(TIM_GetITStatus(TIM5,TIM_IT_Update)!=RESET)
	{
		if(RmtSta&0x80)//上次有数据被接收到了
		{	
			RmtSta&=~0X10;						//取消上升沿已经被捕获标记
			if((RmtSta&0X0F)==0X00)RmtSta|=1<<6;//标记已经完成一次按键的键值信息采集
			if((RmtSta&0X0F)<14)RmtSta++;
			else
			{
				RmtSta&=~(1<<7);//清空引导标识
				RmtSta&=0XF0;	//清空计数器	
			}						 	   	
		}							    
	}
 	if(TIM_GetITStatus(TIM5,TIM_IT_CC2)!=RESET)
	{	  
		if(RDATA)//上升沿捕获
		{

			TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获				
	    	TIM_SetCounter(TIM5,0);	   	//清空定时器值
			RmtSta|=0X10;					//标记上升沿已经被捕获
		}else //下降沿捕获
		{			
  			 Dval=TIM_GetCapture2(TIM5);//读取CCR1也可以清CC1IF标志位
			 TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC4P=0	设置为上升沿捕获
 			
			if(RmtSta&0X10)					//完成一次高电平捕获 
			{
 				if(RmtSta&0X80)//接收到了引导码
				{
					
					if(Dval>300&&Dval<800)			//560为标准值,560us
					{
						RmtRec<<=1;	//左移一位.
						RmtRec|=0;	//接收到0	   
					}else if(Dval>1400&&Dval<1800)	//1680为标准值,1680us
					{
						RmtRec<<=1;	//左移一位.
						RmtRec|=1;	//接收到1
					}else if(Dval>2200&&Dval<2600)	//得到按键键值增加的信息 2500为标准值2.5ms
					{
						RmtCnt++; 		//按键次数增加1次
						RmtSta&=0XF0;	//清空计时器		
					}
 				}else if(Dval>4200&&Dval<4700)		//4500为标准值4.5ms
				{
					RmtSta|=1<<7;	//标记成功接收到了引导码
					RmtCnt=0;		//清除按键次数计数器
				}						 
			}
			RmtSta&=~(1<<4);
		}				 		     	    					   
	}
 TIM_ClearFlag(TIM5,TIM_IT_Update|TIM_IT_CC2);	    
}

//处理红外键盘
//返回值:
//	 0,没有任何按键按下
//其他,按下的按键键值.
/*
;================================
;******  红外遥控器键值表  ******
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
	if(RmtSta&(1<<6))//得到一个按键的所有信息了
	{ 
	    t1=RmtRec>>24;			//得到地址码
	    t2=(RmtRec>>16)&0xff;	//得到地址反码 
 	    if((t1==(u8)~t2)&&t1==REMOTE_ID)//检验遥控识别码(ID)及地址 
	    { 
	        t1=RmtRec>>8;
	        t2=RmtRec; 	
	        if(t1==(u8)~t2)sta=t1;//键值正确	 
		}   
		if((sta==0)||((RmtSta&0X80)==0))//按键数据错误/遥控已经没有按下了
		{
		 	RmtSta&=~(1<<6);//清除接收到有效按键标识
			RmtCnt=0;		//清除按键次数计数器
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
		else if ( IR_Sta & 0x01 )	// 如果引导成功，开始接码
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