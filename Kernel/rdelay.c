
/* C���Լ�Ƕ��ʽ������س��ú�������ϵͳ������ʱ����
                                    �ַ�����������
									�ַ����ȽϺ���*/

#include "stdtype.h"

/* Functions:   HXZ_SoftDelay()
   Description: ��ͨ��ʱ����,40000000Լ����2�� 
                             20000000ԼΪ1��
							 2000000ԼΪ100ms
							 200000ԼΪ10ms
							 20000ԼΪ1ms         
							 10000ԼΪ0.5ms */
void HXZ_SoftDelay(INT32U u32Count)				  
{
	while ( u32Count-- );
}

