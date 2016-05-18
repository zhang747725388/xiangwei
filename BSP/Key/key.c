#include "key.h"
#include "rsystem.h"
 

void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //按键1
	RCC_APB2PeriphClockCmd(KEY0_RCC, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = KEY0_PIN;
	GPIO_Init(KEY0_PORT, &GPIO_InitStructure);
 
}
static uchar Get_Key(void)
{
     if (KEY0_STATUS==RESET) return KEY_DOWN1;
    return NO_KEY;
}

uchar Key_Scan(void)
{
    static uchar Key_State   = 0;        //按键状态
    static uchar Key_Prev    = 0;        //上一次按键
    static uchar Key_Delay   = 0;        //按键连发时间
    uchar Key_Press  = NO_KEY;           //按键值
    uchar Key_Return = NO_KEY;           //按键返回值

    Key_Press = Get_Key();

    switch (Key_State)
    {

    case 0://按键初始态00
        if (Key_Press !=NO_KEY)//有按键按下
        {
            Key_State = 1;//转到按键确认
            Key_Prev  = Key_Press;//保存按键状态
        }
        break;

    case 1://按键确认态01
        if ( Key_Press ==Key_Prev )//确认和上次按键相同
        {
            Key_State = 2;//判断按键长按

            //返回按键按下键值,按键按下就响应,如果想弹起来再响应
            //可以在弹起来后再返回按键值
           
            Key_Return = KEY_DOWN | Key_Prev;
        }
        else//按键抬起,是抖动,不响应按键
        {
            Key_State = 0;
        }
        break;

    case 2://按键释放态10
//        if (Key_Press == NO_KEY )//按键释放了
//        {
//            Key_State = 0;
//            Key_Delay = 0;
//            Key_Series  = FALSE;
//            Key_Return  = KEY_UP | Key_Prev;      //返回按键抬起值
//            break;
//        }
		      Key_Delay++;
		     if( (Key_Press == NO_KEY) && (Key_Delay<KEY_SERIES_DELAY))
            {
            Key_State = 0;
            Key_Delay = 0;
            Key_Return  = KEY_UP | Key_Prev;      //返回按键抬起值
            break;
            }
        if( (Key_Press == NO_KEY) && (Key_Delay>KEY_SERIES_DELAY))
            {
            Key_State = 0;
            Key_Delay = 0;
            Key_Return  = KEY_LONG | Key_Prev;      //返回按键抬起值
            break;
            }
    default :
        break;
    }

    return Key_Return;
}

 

