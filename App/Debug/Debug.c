
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

//��д�ն˺�
void Debug_WriteDeviceID(const uint8_t *terminalid)
{
	UpdateDeviceID(terminalid);	
}


//��дӲ���汾��
void Debug_WriteHardVer(const uint8_t *hardware)
{
	UpdateHardWareVer(hardware);	
}


//��д��Ʒ�ͺ�
void Debug_WriteProductID(const uint8_t *productid)
{
	UpdateProductID(productid);	
}


//��ȡ�ն˲���
void Debug_GetConstParam(uint8_t *productid , uint8_t *version , uint8_t *hardware , uint8_t *terminalid)						
{
	BYTE * Address = (BYTE *)FLASHADD_SECTION(127);
	
	/* ����汾 */
	*version++ =FirmWare_Ver[0];
	*version++ =FirmWare_Ver[1];
	
 	/* �ն˱�� */
	*terminalid++ = *Address++;
	*terminalid++ = *Address++;
	*terminalid++ = *Address++;
	*terminalid   = *Address++;	
	
	/* Ӳ���汾  */
	*hardware++ = *Address++;
	*hardware++ = *Address++;
	*hardware++ = *Address++;
	*hardware   = *Address++;

	/* ��Ʒ�ͺ�  */
	*productid++ = *Address++;
	*productid   = *Address++;
}


//��ȡ��ѹֵ����
uint16_t Debug_GetVol(void)
{
	INT16U VolTmp;
	VolTmp = GetVoltage() * 10;
	return (VolTmp);
}


//��ȡ���ٶȴ�����״̬
uint8_t Debug_GetMemsSta(void)
{
	if(MEMS_GetMEMSSta() == MEMS_Error)	return (0x01);
	if(MEMS_GetMEMSSta() == MEMS_OK)	return (0x02);
	return (0x00);
}


//��ȡflash״̬
uint8_t Debug_GetEFlashSta(void)
{
	if( SPI_Flash_ReadID() == 0xEF14 ){
		return (0x02);
	}else{
		return (0x01);
	}
}


//��ȡGPS״̬
void Debug_GetGPSInfo(uint8_t *data, uint16_t *size)
{
	if(GetGPSTestDataStatus()){
		RStrncpy( (char *)GetGPSTestDataInfo() , (char *)data , GetGPSTestDataLen());	         // ��������
		*size = GetGPSTestDataLen();
		GPSTestData_Init();
	}else{
		*size = 0;
	}
}


//��ȡ����ͨѶ״̬
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


//��ȡOBDͨѶ״̬
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


//TTS����
void Debug_TTSTest(void)
{
	LKClient_TestTTS();
}


//�𶯻��Ѳ���
void Debug_WakeUpTest(void)
{
	SleepSta = Sleep;
}


//��������λ��
void Debug_SetStartMode(uint8_t position)
{
	if(position == 0x00){
		DebugMode = DebugHard;
	}else if(position == 0x01){
		DebugMode = DebugSoft;
	}
}


//������дFlash���׵�ַ������С
void Debug_GetFlashAddr(uint32_t *StartAddr, uint32_t *FlashSize)
{
	*StartAddr = UPD_PROGRAM_ADDR;
    *FlashSize = (1024 * 80);
}


//����SuperBlock
void Debug_WriteSuperBlock(uint16_t Space ,uint16_t CheckByte)
{
	SUPER_BLOCK Sb_Temp;
	Sb_Temp.bNewUpdateRequest = 0x01;				    // ���������־  App   -> Rboot
	Sb_Temp.bUpdateOK = 0x00;						    // ���³ɹ���־  Rboot -> App
	Sb_Temp.reserved = 0x00;						    // ����
	Sb_Temp.FW_StartAddr = UPD_PROGRAM_ADDR;			// �̼��Ŀ�ʼ��ַ(Ext Flash)0x08018000
	Sb_Temp.FW_Size = Space;				    		// �̼��ܴ�С
	Sb_Temp.FW_VerifyWord = CheckByte;			  		// �̼�У����
	Sb_Temp.LockWord = 0x5599;						    // 0x5599
	Flash_WriteSuperBlock(&Sb_Temp);
}


//��ȡ����ģʽ
DebugModeEnum Debug_GetMode(void)
{
	return (DebugMode);
}


//��ղ���ģʽ
void Debug_ClrMode(void)
{
	DebugMode = DebugDefault;
}

