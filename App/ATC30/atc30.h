
#ifndef __ATC30_H_
#define __ATC30_H_

/*--- File Includes ------------------------------------------------------*/

/*--- Macro Defination ---------------------------------------------------*/

/*--- Data Struct Defination ---------------------------------------------*/
typedef enum _ATC30ModeEnum{		// ATC30终端状态枚举类型
	Default   = 0,					// 默认状态，复位后处于默认状态
	GotoSleep = 1,					// 休眠状态。
	BogusWake = 2,					// 假醒状态一，由RTC闹钟导致进入该状态
	WakeUp    = 3,					// 唤醒状态二，进入该状态表示终端开始工作
	TestOne   = 4,                  // 测试模式一
	TestTwo   = 5                   // 测试模式二 
}ATC30ModeEnum;

/*--- Variables Export ---------------------------------------------------*/
extern ATC30ModeEnum NowATC30Mode;

/*--- Function Export ----------------------------------------------------*/
extern void ATC30_Confirm_Mode(void);
extern void ATC30_Mode_Run(void);

#endif

