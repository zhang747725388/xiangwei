/*--- HEADER FILE DESCRIPTOR --------------------------------------------------
Project : Realtime Micro Library
File    : string.h
Author  : automatic.dai
E-mail  : automatic.dai@gmail.com
Data    : 2013/01/16
Version : V1.0(alpha)
Note    : 
-----------------------------------------------------------------------------*/

#ifndef __RSTRING_H_
#define __RSTRING_H_

/*--- Header Includes -------------------------------------------------------*/
#include "stdtype.h"

/*--- Macro Defination ------------------------------------------------------*/
#define  STRING_DECLAR(X,Y)		char X[Y+1]
#define  STRING					      char*
#define  STRING_NULL			(STRING)(R_NULL)

#define  STRING_CHAR_NOT_FOUND	(0xFFFFFFFF)

/*--- Data Struct Defination ------------------------------------------------*/

/*--- Variables Export ------------------------------------------------------*/

/*--- Function Declaration --------------------------------------------------*/
R_EXT STRING 	 RStrncpy(STRING src, STRING dst, INT32U num);
R_EXT BOOLEAN 	 RStrncmp(STRING src, STRING dst, INT32U num);
R_EXT STRING	 RStrcat(STRING dst, STRING src);
R_EXT INT32U	 RStrFind(STRING src, CHAR chDst, INT32U nStrLength, INT32U nStartPos);

R_EXT STRING 	 RHexToStr(BYTE hex, STRING dst);
R_EXT STRING 	 RIntToStr(INT32U num, STRING dst);

R_EXT void 		 RMemset(void *src, INT8U bSetValue, INT32U length);

extern int     RMLStrcmp(BYTE *dpDst ,BYTE *dpSour ,INT32U u32length);
extern void    RMLStrcpy(BYTE *dpDst ,BYTE *dpSour ,INT32U u32length);

extern void 	 HexToStr(INT32U Hex, BYTE * Str , INT8U * Length);

extern void 	 ByteToStr(BYTE Src , BYTE * Dst);
extern BYTE * CharToStr(BYTE n);
extern void float_to_string( unsigned char data,  unsigned char *str);
extern BOOLEAN FindDstInArray(BYTE *Src , INT32U SrcLen , BYTE *Dst , INT32U DstLen);

#endif
