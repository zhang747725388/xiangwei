
#ifndef __ATC30_H_
#define __ATC30_H_

/*--- File Includes ------------------------------------------------------*/

/*--- Macro Defination ---------------------------------------------------*/

/*--- Data Struct Defination ---------------------------------------------*/
typedef enum _ATC30ModeEnum{		// ATC30�ն�״̬ö������
	Default   = 0,					// Ĭ��״̬����λ����Ĭ��״̬
	GotoSleep = 1,					// ����״̬��
	BogusWake = 2,					// ����״̬һ����RTC���ӵ��½����״̬
	WakeUp    = 3,					// ����״̬���������״̬��ʾ�ն˿�ʼ����
	TestOne   = 4,                  // ����ģʽһ
	TestTwo   = 5                   // ����ģʽ�� 
}ATC30ModeEnum;

/*--- Variables Export ---------------------------------------------------*/
extern ATC30ModeEnum NowATC30Mode;

/*--- Function Export ----------------------------------------------------*/
extern void ATC30_Confirm_Mode(void);
extern void ATC30_Mode_Run(void);

#endif

