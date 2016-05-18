static uchar Get_Key(void)
{
    if (KEY0_STATUS==0) return KEY0_DOWN;
    if (KEY1_STATUS==0) return KEY1_DOWN;
    if (KEY2_STATUS==0) return KEY2_DOWN;
    if (KEY3_STATUS==0) return KEY3_DOWN;
    return NO_KEY;
}
uchar Key_Scan(void)
{
    static uchar Key_State   = 0;        //����״̬
    static uchar Key_Prev    = 0;        //��һ�ΰ���
    static uchar Key_Delay   = 0;        //��������ʱ��
    static uchar Key_Series  = FALSE;    //��־������ʼ

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
        if (Key_Press == NO_KEY )//�����ͷ���
        {
            Key_State = 0;
            Key_Delay = 0;
            Key_Series  = FALSE;
            Key_Return  = KEY_UP | Key_Prev;      //���ذ���̧��ֵ
            break;
        }
        if ( Key_Press ==Key_Prev )
        {
            Key_Delay++;
            if ((Key_Series==TRUE) && (Key_Delay>KEY_SERIES_DELAY))
            {
                Key_Delay  = 0;
                Key_Return = KEY_LIAN | Key_Press;  //����������ֵ
                Key_Prev   = Key_Press;      //��ס�ϴεİ���.
                break;
            }
            if (Key_Delay>KEY_SERIES_FLAG)
            {
                Key_Series = TRUE;
                Key_Delay  = 0;
                Key_Return = KEY_LONG | Key_Prev;   //���س������ֵ
                break;
            }
        }

    default :
        break;
    }

    return Key_Return;
}
