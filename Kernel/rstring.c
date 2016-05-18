/*--- SOURCE FILE DESCRIPTOR ---------------------------------------------------
Project : Realtime Micro Library
File    : rstring.c
Author  : automatic.dai
E-mail  : automatic.dai@gmail.com
Data    : 2013/01/16
Version : V1.0(alpha)
Note    : 
------------------------------------------------------------------------------*/

#include "rstring.h"

/*--- FUNCTION DESCRIPTOR ------------------------------------------------------
Function : RStrncpy()
Input    : 
Output   : 
Return   : 
Version  : 
Note     : 
------------------------------------------------------------------------------*/
STRING RStrncpy(STRING src, STRING dst, INT32U num)
{
	
	STRING src_cpy = src;

	if ( src == STRING_NULL || dst == STRING_NULL )
	{	return STRING_NULL; }
	
	while ( num-- )
	{
		if ( *src == '\0')
		{
			break;
		}

		*dst++ = *src++;

	}

	*dst = '\0';

	return src_cpy;	    

}


/*--- FUNCTION DESCRIPTOR ------------------------------------------------------
Function : RStrncmp()
Input    : 
Output   : 
Return   : 
Version  : 
Note     : 
------------------------------------------------------------------------------*/
BOOLEAN RStrncmp(STRING src, STRING dst, INT32U num)
{

	if ( src == STRING_NULL || dst == STRING_NULL )
	{	
		return bFALSE; 
	}

	while ( num-- )
	{
		if ( *src == '\0' )
		{
			return (*dst == '\0') ? bTRUE : bFALSE;
		}
		if ( *dst++ != *src++ )
		{
			return bFALSE;
		}
	}

	return bTRUE;

}


/*--- FUNCTION DESCRIPTOR ------------------------------------------------------
Function : RStrcat()
Input    : 
Output   : 
Return   : 
Version  : 
Note     : 
------------------------------------------------------------------------------*/
STRING	RStrcat(STRING src1_dst, STRING src2)
{

	STRING src_cpy = src1_dst;

	if ( src1_dst == STRING_NULL || src2 == STRING_NULL )
	{
		return src1_dst;	
	}
	while ( *src1_dst != '\0' ) { src1_dst++; }
	while ( *src2 != '\0' )
	{
		*src1_dst++ = *src2++;
	}

	*src1_dst = '\0';

	return 	src_cpy;

}


/*--- FUNCTION DESCRIPTOR ------------------------------------------------------
Function : RStrFind()
Input    : 
Output   : 
Return   : 
Version  : 
Note     : 
------------------------------------------------------------------------------*/
INT32U	RStrFind(STRING src, CHAR chDst, INT32U nStrLength, INT32U nStartPos)
{

	INT32U nPos = nStartPos;
	INT32U nEndPos = nStrLength - 1;

	src = src + nPos;

	while ( nPos < nEndPos )
	{
		if ( *src++ == chDst )
		{
			return nPos;
		}
		nPos++;	
	}

	return STRING_CHAR_NOT_FOUND;	

}

CHAR HexTable[] = {'0','1','2','3','4','5','6','7','8','9',
					'A','B','C','D','E','F'};
/*--- FUNCTION DESCRIPTOR ------------------------------------------------------
Function : RHexToStr()
Input    : 
Output   : 
Return   : 
Version  : 
Note     : 
------------------------------------------------------------------------------*/
STRING RHexToStr(BYTE hex, STRING dst)
{
	
	STRING src_cpy = dst;

	*dst++ = HexTable[hex >> 4];
	*dst++ = HexTable[hex & 0x0F];  
	*dst = '\0';

	return src_cpy;

}


/*--- FUNCTION DESCRIPTOR ------------------------------------------------------
Function : RIntToStr()
Input    : 
Output   : 
Return   : 
Version  : 
Note     : 
------------------------------------------------------------------------------*/
STRING RIntToStr(INT32U num, STRING dst)
{
	
	STRING dst_cpy = dst;
	CHAR num_buff[11];
	INT8U i = 0;

	if ( dst == STRING_NULL )
	{
		return STRING_NULL;
	}

	if ( num == 0 )
	{
		*dst++ = '0';
		*dst = '\0';
		return dst_cpy;		
	}
	else
	{
		while (num)
		{
			num_buff[i++] = num % 10 + '0';
			num /= 10;
		}
	
		while(i--)
		{
			*dst++ = num_buff[i];
		}
		
		*dst = '\0';
	 	
		return dst_cpy;	
	
	}

}


/*--- FUNCTION DESCRIPTOR ------------------------------------------------------
Function : RMemset()
Input    : 
Output   : 
Return   : 
Version  : 
Note     : 
------------------------------------------------------------------------------*/
void RMemset(void *src, INT8U bSetValue, INT32U length)
{
	INT8U *src_cpy = (INT8U *)src;
	while ( length-- )
	{
		*src_cpy++ = bSetValue;	
	}

}


int RMLStrcmp(BYTE * dpDst , BYTE * dpSour , INT32U u32length)
{
	while( u32length-- )
	{
		if( *dpDst++ != *dpSour++ )
		{
			return 0;
		}
	}
	return 1;
}


void RMLStrcpy(BYTE *dpDst , BYTE *dpSour , INT32U u32length)
{
	while ( u32length-- )
	{
		*dpDst++ = *dpSour++;
	}
}


void HexToStr(INT32U Hex, BYTE * Str , INT8U * Length)
{
    INT8U a;
	BYTE  Data[10];
	INT8U Len = 0;
	do{
		a = (Hex % 10);
		Data[Len++] = a + 0x30;
		Hex = Hex / 10;	
	}while(Hex != 0);

	* Length = Len;
	while(Len != 0){
		*Str++ = Data[Len-1];
		Len--;	
	}
}


void ByteToStr(BYTE Src , BYTE * Dst)
{
	BYTE Src1;
	BYTE Src2;
	Src1 = ( Src >> 4 ) & 0x0F;
	Src2 = Src & 0x0F;
	if( ( Src1 >= 0x0A ) && (Src1 <= 0x0F) ){
		*Dst = Src1+0x37;
	}else if(( Src1 >= 0x01 ) && (Src1 <= 0x09)){
		*Dst = Src1+0x30;
	}else{
		*Dst = 0x30;
	}

	Dst++;

	if( ( Src2 >= 0x0A ) && (Src2 <= 0x0F) ){
		*Dst = Src2+0x37;
	}else if(( Src2 >= 0x01 ) && (Src2 <= 0x09)){
		*Dst = Src2+0x30;
	}else{
		*Dst = 0x30;
	}
}


BOOLEAN FindDstInArray(BYTE *Src , INT32U SrcLen , BYTE *Dst , INT32U DstLen)
{
	INT32U i;
	if(SrcLen < DstLen){
		return (bFALSE);
	}
	for( i = 0 ; i < (SrcLen - DstLen + 1) ; i++)
	{
		if( (RMLStrcmp( (Src+i),Dst,DstLen) ) == 1){
			return (bTRUE);
		}
	}
	
	return (bFALSE);
}
BYTE * CharToStr(BYTE num)
{                         BYTE * str;
                         unsigned char buf[11];
                         unsigned char temp,i=0,j=0;
                          temp=(num<0)?(-num):num;
                          while(temp!=0)
                          {
                               buf[i]=temp+'0';
                               temp=temp/10;
                               i++;
                          }
         
                          while((--i)>=0)
                          {
                               str[j]=buf[i];
                               j++;
                          }
													 return str;
}
void float_to_string( unsigned char data,  unsigned char *str)
{
  int i,j,k;
  long temp,tempoten;
  unsigned char intpart[20];  // 数的整数部分和小数部分
 
 
  i=0;
  tempoten=data/10;
  while(tempoten!=0)
  {
    intpart[i]=temp-10*tempoten+48; //to ascii code
    temp=tempoten;
    tempoten=temp/10;
    i++;
  }
  intpart[i]=temp+48;
  for(k=1;k<=i+1;k++) str[k]=intpart[i+1-k];
  str[i+j+3]=0x0D;
}