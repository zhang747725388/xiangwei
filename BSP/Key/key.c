#include "key.h"
#include "rsystem.h"
 

void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //����1
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
    static uchar Key_State   = 0;        //����״̬
    static uchar Key_Prev    = 0;        //��һ�ΰ���
    static uchar Key_Delay   = 0;        //��������ʱ��
    uchar Key_Press  = NO_KEY;           //����ֵ
    uchar Key_Return = NO_KEY;           //��������ֵ

    Key_Press = Get_Key();

    switch (Key_State)
    {

    case 0://������ʼ̬00
        if (Key_Press !=NO_KEY)//�а�������
        {
            Key_State = 1;//ת������ȷ��
            Key_Prev  = Key_Press;//���水��״̬
        }
        break;

    case 1://����ȷ��̬01
        if ( Key_Press ==Key_Prev )//ȷ�Ϻ��ϴΰ�����ͬ
        {
            Key_State = 2;//�жϰ�������

            //���ذ������¼�ֵ,�������¾���Ӧ,����뵯��������Ӧ
            //�����ڵ��������ٷ��ذ���ֵ
           
            Key_Return = KEY_DOWN | Key_Prev;
        }
        else//����̧��,�Ƕ���,����Ӧ����
        {
            Key_State = 0;
        }
        break;

    case 2://�����ͷ�̬10
//        if (Key_Press == NO_KEY )//�����ͷ���
//        {
//            Key_State = 0;
//            Key_Delay = 0;
//            Key_Series  = FALSE;
//            Key_Return  = KEY_UP | Key_Prev;      //���ذ���̧��ֵ
//            break;
//        }
		      Key_Delay++;
		     if( (Key_Press == NO_KEY) && (Key_Delay<KEY_SERIES_DELAY))
            {
            Key_State = 0;
            Key_Delay = 0;
            Key_Return  = KEY_UP | Key_Prev;      //���ذ���̧��ֵ
            break;
            }
        if( (Key_Press == NO_KEY) && (Key_Delay>KEY_SERIES_DELAY))
            {
            Key_State = 0;
            Key_Delay = 0;
            Key_Return  = KEY_LONG | Key_Prev;      //���ذ���̧��ֵ
            break;
            }
    default :
        break;
    }

    return Key_Return;
}

 

