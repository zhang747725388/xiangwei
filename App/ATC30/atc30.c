
/*   ATC30�ն�-Ӧ�ó����ʼ������   */

/*--- File Includes ------------------------------------------------------*/
#include "rsystem.h"
#include "bsp.h"
#include "pbdata.h"
#include "GPSTask.h"
#include "OBDTask.h"
#include "mems.h"
#include "voltage.h"
#include "paramlist.h"

#include "crc8.h"
#include "superblock.h"
#include "CQueue.h"
#include "LKClient.h"
#include "ManageInfo.h"
#include "sleep.h"
#include "selfcheck.h"
#include "debug.h"
#include "USBTest.h"
#include "BlueTooth.h"
#include "atc30.h"

#include "gps.h"
#include "gSensor.h"
/*--- Macro Defination ---------------------------------------------------*/
#define ATC30_IWDG_OPEN    (0)             // Ϊ1ʱ�رտ��Ź���Ϊ0ʱ�������Ź�
#define ATC30_TESTUSE_MODE (1)             // Ϊ1ʱ�޷��������ܲ��ԣ�Ϊ0ʱ���ݱ�־λ�������ܲ���
#define ATC30_NOSLEEP_MODE (0)             // ��1ʱ�ն���Զ������

#define RTC_WAKEUP_TIME    (1800)

#define SYSTEM_TESTFLAG    (BKP_DR3)

/*--- Data Struct Defination ---------------------------------------------*/

/*--- Variable Declaration -----------------------------------------------*/

/*--- Variable Defination ------------------------------------------------*/
ATC30ModeEnum NowATC30Mode  = Default;		   // ATC30�Ĺ���״̬

/*--- Functions Declearation ---------------------------------------------*/
extern void ATC30_Mode_Exchange(void);

/*--- Functions Defination -----------------------------------------------*/

/*----------------------------TestOne Period -------------------------------*/
void ATC30_GoTo_TestModeOne(void)
{
	NowATC30Mode = TestOne;
	if(BKP_ReadBackupRegister(SYSTEM_TESTFLAG) == 0xABCD)//	   gql_test_code
	{	
			BKP_WriteBackupRegister(SYSTEM_TESTFLAG,0x0000);
			Led_PortInit();              						// Led
			Led_GPS_On();
			//Led_OBD_On();
			Led_GSM_On();	
			 
			Open_OBDPower();		     						// ��OBD��Դ
			Open_GPSPower();
		 // BT_POWER_ON(); 
		//Open_CANDrivePower();				
			NVIC_Configuration();        // NVIC		
			LKClient_GoTo_Test();
	}
	else
	{
			SleepSta = Sleep;
			BKP_WriteBackupRegister(SYSTEM_TESTFLAG,0xABCD);		
			RTC_SetCounter(0x00000000);
			RTC_WaitForLastTask();
			RTC_SetAlarm(5);
			RTC_WaitForLastTask();
			PWR_EnterSTANDBYMode();
	}
}


void ATC30_TestModeOne_Run(void)
{
	LKClient_TestRun();
	IWDG_ReloadCounter();			    // ι��
	USBTest_Task();
	ATC30_Mode_Exchange();
}


/*----------------------------TestOne Period -------------------------------*/
void ATC30_GoTo_TestModeTwo(void)
{
	NowATC30Mode = TestTwo;

	/* Bsp Init	*/
	NVIC_Configuration();        // NVIC
	Led_PortInit();              // Led
	ADC_InitChannel();	         // ADC
 
 		
 gSensor_Init();
	 
	SPI_Flash_Init();	           // Flash
	GPS_BSP_Init();              // GPS
BT_INIT();
	/* App Init */
	VoltageSampleInit();         
	MEMS_SampleInit();
	 OBD_PreToDiagnose();
	LKClient_GoTo_Test();	
	
	//OBD_ClrTestError();
	//OBD_GoToRestart();
	
	Sleep_TaskForTest_Init();
	
	SelfCheck_SoftTest_Init();
}


void ATC30_TestModeTwo_Run(void)
{
	VoltageSampleTask();		   // Voltage���  
//	MEMS_SampleTask();			   // MEMS���  
		gSensor_Task();	

		OBDTask();	
	LKClient_TestRun();
  //OBDTaskForTest();			     // OBD   		
	Sleep_TaskForTest();       // Sleep
	SelfCheck_SoftTestTask();

	USBTest_Task();
	ATC30_Mode_Exchange();
}


/*-------------------------Bogus Wake Period -------------------------------*/
void ATC30_GoTo_BogusWakeMode(void)
{
	NowATC30Mode = BogusWake;
	ADC_InitChannel();	  	    	// ADC
	VoltageSampleInit();  
	Sleep_InitOne();	
}


void ATC30_BogusWakeMode_Run(void)
{
	VoltageSampleTask();
	Sleep_TaskOne();	
	IWDG_ReloadCounter();			    // ι��
}


/*------------------------ Wake Up Period ----------------------------------*/
void ATC30_GoTo_WakeUpMode(void)
{
	NowATC30Mode = WakeUp;

	/* Bsp Init	*/
	NVIC_Configuration();        // NVIC
	Led_PortInit();              // Led
	ADC_InitChannel();	         // ADC
 
  
  gSensor_Init(); 
  BT_INIT();
	SPI_Flash_Init();	           // Flash
	GPS_BSP_Init();              // GPS
	
	/* App Init */
	VoltageSampleInit();         // ADC
	MEMS_SampleInit();
   OBD_PreToDiagnose();	       // OBD
	GPSTask_Init();
	
	LKClient_GoTo_Start();
	LKClient_ManageInfoTaskInit();
	Sleep_InitTwo();
	SelfCheckInit();
}


void ATC30_WakeUpMode_Run(void)
{
	VoltageSampleTask();		   // Voltage���  
  gSensor_Task();	
	OBDTask();					       // OBD   	
	GPSTask();					       // GPS    
  
	BT_Task();
	LKClientTask();				     // LKClient
	LKClient_ManageInfoTask(); // MsgTask
#if (!ATC30_NOSLEEP_MODE)
	Sleep_TaskTwo();			     // ��������
#endif 

	SelfCheckTask();      	   // ϵͳ�Բ�
	
	USBTest_Task();
	ATC30_Mode_Exchange();
	
}


/*--------------------------- ATC30 ---------------------------------*/
void ATC30_Confirm_Mode(void)
{  
	/* �����û����� */	
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_BKP | RCC_APB1Periph_PWR , ENABLE );	  	 
	PWR_BackupAccessCmd(ENABLE);
	RCC_LSICmd(ENABLE);
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
	RCC_RTCCLKCmd(ENABLE);
	RTC_WaitForSynchro();
	RTC_WaitForLastTask();
	RTC_SetPrescaler(39999);
	RTC_WaitForLastTask();
	
	
	            
	/* ����Ҫ���� */
	if(BKP_ReadBackupRegister(SYSTEM_SLEEPFLAG) == 0xABCD)//
	{
		  Led_PortInit();
		  Led_GSM_On();
		
		
		
			RTC_WaitForLastTask();
			RTC_SetCounter(0x00000000);
			RTC_WaitForLastTask();
			
			BKP_WriteBackupRegister(SYSTEM_SLEEPFLAG,0x0000);
			RTC_SetAlarm(RTC_WAKEUP_TIME);
			RTC_WaitForLastTask();
 
		 										        		                      // ��ʼ��MEMS
   	  gSensor_Init(); 
		 
		  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);                   //�ر�jtag������swd��
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);                     	//ʹ��PWR����ʱ��
 		  Reset_Sim900_PowerPin();        		                                      // ʹ��WakeUp����
      Close_OBDPower();
		  Close_GPSPower();
			
			
			RCC_ClearFlag();                                                          // �����λ��־
			
			

			NowATC30Mode = GotoSleep;													
  
	}
	/* ������Ҫ���� */
	else
	{
		INT32U RTCCounter = 0;

#if (!ATC30_IWDG_OPEN)
		Init_IWDG(); 				                                                    // ���Ź�
#endif
		
		/* ����Ǹ��¹̼����һ�θ�λ	*/
		if(Is_ATC30UpdateOK() == bTRUE)
		{															
				Flash_EraseSuperBlock();		    // ����������
		}

		ConstParam_Backup();                // �����ն˱�š�Ӳ���汾����Ʒ�ͺš����Ա�־λ
		Param_Init();  		                  // ����Paramlist
		LKConAddr_Init();                   // ����AddressList
		LKConAddr_Change(MAIN_IP);
		
		/* ��ʼ��USB 
		USBTest_Init(Debug_GetConstParam,Debug_GetVol,Debug_GetMemsSta,
					 Debug_GetEFlashSta,Debug_GetLKClientSta,Debug_GetGPSInfo,
					 Debug_GetOBDSta,Debug_TTSTest,Debug_WakeUpTest,Debug_SetStartMode,
					 Debug_WriteDeviceID,Debug_WriteHardVer,Debug_WriteProductID,
					 Debug_GetFlashAddr,Debug_WriteSuperBlock);
*/

#if (!ATC30_TESTUSE_MODE)
		/* �������ܲ��Գ��� */
		if( (TestFlag[0] == 0xFF) && (TestFlag[1] == 0xFF))
		{
				ATC30_GoTo_TestModeOne();
				return;
		}	
#endif
 
 		  gSensor_Init(); 
		 
		RTCCounter = RTC_GetCounter();

		if( (RTCCounter > RTC_WAKEUP_TIME) && (RCC_GetFlagStatus(RCC_FLAG_PORRST) == RESET) )
		{   
				ATC30_GoTo_BogusWakeMode();				                                      // ����RTC���Ӹ�λ 
		}
		else
		{
				ATC30_GoTo_WakeUpMode();				                                        // �����𶯻��� �������ϵ�
		}			
	}
}


void ATC30_Mode_Run(void)
{
		switch(NowATC30Mode)
		{
				case (GotoSleep): 		  	  PWR_EnterSTANDBYMode();	         break;		                   
				case (BogusWake):           ATC30_BogusWakeMode_Run();       break;
				case (WakeUp): 	            ATC30_WakeUpMode_Run();          break;
				case (TestOne):            	ATC30_TestModeOne_Run();		     break;
				case (TestTwo):             ATC30_TestModeTwo_Run();         break;
				default:                                                     break;
		}
}


/*---------------------------- Period Update -------------------------------*/
void ATC30_Mode_Exchange(void)
{
		switch (NowATC30Mode)
		{
			case (TestOne):
				if(Debug_GetMode() == DebugSoft)
				{
						Debug_ClrMode();
						ATC30_GoTo_TestModeTwo();
						UpdateTestFlag(0xAA,0xBB);
				}
				break;
			
			case (TestTwo):
				if(Debug_GetMode() == DebugHard)
				{
						Debug_ClrMode();
						UpdateTestFlag(0xFF,0xFF);	
						ATC30_GoTo_TestModeOne();			
				}
				else if(Debug_GetMode() == DebugSoft)
				{
						Debug_ClrMode();
						ATC30_GoTo_TestModeTwo();
				}
				break;
			
			case (WakeUp):
				if(Debug_GetMode() == DebugHard)
				{
						Debug_ClrMode();
						UpdateTestFlag(0xFF,0xFF);	
						ATC30_GoTo_TestModeOne();
				}
				else if(Debug_GetMode() == DebugSoft)
				{
						Debug_ClrMode();
						ATC30_GoTo_TestModeTwo();
				}
				break;
			
			default:
				break;

		}
	
}

