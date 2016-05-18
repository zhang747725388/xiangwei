
/*--- File Includes ------------------------------------------------------*/

#include "rsystem.h"
#include "bsp.h"

#include "paramlist.h"
#include "GPSTask.h"
#include "OBDTask.h"
#include "mems.h"
#include "voltage.h"

#include "superblock.h"
#include "lkclient.h"
#include "CQueue.h"
#include "sleep.h"
#include "Debug.h"

/*--- Macro Defination ---------------------------------------------------*/
								
/*--- Data Struct Defination ---------------------------------------------*/

/*--- Variable Declaration -----------------------------------------------*/
DebugModeEnum DebugMode;

/*--- Variable Defination ------------------------------------------------*/

/*--- Functions Declearation ---------------------------------------------*/

/*--- Functions Defination -----------------------------------------------*/

//焼写终端号
void Debug_WriteDeviceID(const uint8_t *terminalid)
{
	UpdateDeviceID(terminalid);	
}


//烧写硬件版本号
void Debug_WriteHardVer(const uint8_t *hardware)
{
	UpdateHardWareVer(hardware);	
}


//焼写产品型号
void Debug_WriteProductID(const uint8_t *productid)
{
	UpdateProductID(productid);	
}


//读取终端参数
void Debug_GetConstParam(uint8_t *productid , uint8_t *version , uint8_t *hardware , uint8_t *terminalid)						
{
	BYTE * Address = (BYTE *)FLASHADD_SECTION(127);
	
	/* 软件版本 */
	*version++ =FirmWare_Ver[0];
	*version++ =FirmWare_Ver[1];
	
 	/* 终端编号 */
	*terminalid++ = *Address++;
	*terminalid++ = *Address++;
	*terminalid++ = *Address++;
	*terminalid   = *Address++;	
	
	/* 硬件版本  */
	*hardware++ = *Address++;
	*hardware++ = *Address++;
	*hardware++ = *Address++;
	*hardware   = *Address++;

	/* 产品型号  */
	*productid++ = *Address++;
	*productid   = *Address++;
}


//读取电压值操作
uint16_t Debug_GetVol(void)
{
	INT16U VolTmp;
	VolTmp = GetVoltage() * 10;
	return (VolTmp);
}


//读取加速度传感器状态
uint8_t Debug_GetMemsSta(void)
{
	if(MEMS_GetMEMSSta() == MEMS_Error)	return (0x01);
	if(MEMS_GetMEMSSta() == MEMS_OK)	return (0x02);
	return (0x00);
}


//读取flash状态
uint8_t Debug_GetEFlashSta(void)
{
	if( SPI_Flash_ReadID() == 0xEF14 ){
		return (0x02);
	}else{
		return (0x01);
	}
}


//读取GPS状态
void Debug_GetGPSInfo(uint8_t *data, uint16_t *size)
{
	if(GetGPSTestDataStatus()){
		RStrncpy( (char *)GetGPSTestDataInfo() , (char *)data , GetGPSTestDataLen());	         // 拷贝数据
		*size = GetGPSTestDataLen();
		GPSTestData_Init();
	}else{
		*size = 0;
	}
}


//读取网络通讯状态
void Debug_GetLKClientSta(uint8_t *status, uint8_t *errid)
{
	if(Get_NowClientStatus() == Stop){
		*status = 0x00;
	}else if(Get_NowClientStatus() == Start){
		*status = 0x01;
	}else if(Get_NowClientStatus() == Connect){
		*status = 0x02;
	}else if(Get_NowClientStatus() == Loging){
		*status = 0x03;
	}else{
		*status = 0x04;	
	}

	if(Get_ClientOverSta() == LKDefault){
		*errid = 0x00;
	}else if(Get_ClientOverSta() == PowerError){
		*errid = 0x01;
	}else if(Get_ClientOverSta() == UartError){
		*errid = 0x02;
	}else if(Get_ClientOverSta() == NoSIMCard){
		*errid = 0x03;
	}

}


//读取OBD通讯状态
void Debug_GetOBDSta(uint8_t *status, uint8_t *errid)
{
	/*
	if(OBD_GetTestSta() == OBDTestRestart){
		*status = 0x00;
	}else if(OBD_GetTestSta() == OBDTestCANK){
		*status = 0x01;
	}else if(OBD_GetTestSta() == OBDTestOver){
		*status = 0x02;
	}
	
	if(OBD_GetTestError() == OBDTestDefault){
		*errid = 0x00;
	}else if(OBD_GetTestError() == OBDTest718Error){
		*errid = 0x01;
	}else if(OBD_GetTestError() == OBDTestCANError){
		*errid = 0x02;
	}else if(OBD_GetTestError() == OBDTestKError){
		*errid = 0x03;
	}
	
	*/
}


//TTS测试
void Debug_TTSTest(void)
{
	LKClient_TestTTS();
}


//震动唤醒测试
void Debug_WakeUpTest(void)
{
	SleepSta = Sleep;
}


//设置启动位置
void Debug_SetStartMode(uint8_t position)
{
	if(position == 0x00){
		DebugMode = DebugHard;
	}else if(position == 0x01){
		DebugMode = DebugSoft;
	}
}


//设置烧写Flash的首地址和区大小
void Debug_GetFlashAddr(uint32_t *StartAddr, uint32_t *FlashSize)
{
	*StartAddr = UPD_PROGRAM_ADDR;
    *FlashSize = (1024 * 80);
}


//置起SuperBlock
void Debug_WriteSuperBlock(uint16_t Space ,uint16_t CheckByte)
{
	SUPER_BLOCK Sb_Temp;
	Sb_Temp.bNewUpdateRequest = 0x01;				    // 更新请求标志  App   -> Rboot
	Sb_Temp.bUpdateOK = 0x00;						    // 更新成功标志  Rboot -> App
	Sb_Temp.reserved = 0x00;						    // 保留
	Sb_Temp.FW_StartAddr = UPD_PROGRAM_ADDR;			// 固件的开始地址(Ext Flash)0x08018000
	Sb_Temp.FW_Size = Space;				    		// 固件总大小
	Sb_Temp.FW_VerifyWord = CheckByte;			  		// 固件校验字
	Sb_Temp.LockWord = 0x5599;						    // 0x5599
	Flash_WriteSuperBlock(&Sb_Temp);
}


//获取测试模式
DebugModeEnum Debug_GetMode(void)
{
	return (DebugMode);
}


//清空测试模式
void Debug_ClrMode(void)
{
	DebugMode = DebugDefault;
}

