
/* C语言及嵌入式开发相关常用函数，如系统阻塞延时函数
                                    字符串拷贝函数
									字符串比较函数*/

#include "stdtype.h"

/* Functions:   HXZ_SoftDelay()
   Description: 普通延时函数,40000000约等于2秒 
                             20000000约为1秒
							 2000000约为100ms
							 200000约为10ms
							 20000约为1ms         
							 10000约为0.5ms */
void HXZ_SoftDelay(INT32U u32Count)				  
{
	while ( u32Count-- );
}

