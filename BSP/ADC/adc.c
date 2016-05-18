 

#include "rsystem.h"
 

void ADC_InitChannel(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
	
	/* Configure PA.01 (ADC Channel 1) as analog input -------------------------*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);   
	
	/* ADC1 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	                /* 独立模式 */
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;			            /* 连续多通道模式 */
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	                /* 连续转换 */
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; /* 转换不受外界决定 */
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;		        /* 右对齐 */
	ADC_InitStructure.ADC_NbrOfChannel = 11;					            /* 扫描通道数 */
	ADC_Init(ADC1, &ADC_InitStructure);
	
	/* ADC1 regular channel 1 configuration */ 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5);
	ADC_Cmd(ADC1, ENABLE);                                                /* Enable ADC1 */
	
	/* Enable ADC1 reset calibaration register */   
	ADC_ResetCalibration(ADC1);
	/* Check the end of ADC1 reset calibration register */
	while(ADC_GetResetCalibrationStatus(ADC1));
	
	/* Start ADC1 calibaration */
	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration */
	while(ADC_GetCalibrationStatus(ADC1));
                        
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);                                /* 使能转换开始 */
}


INT32U ADC_GetValue(void)
{
	if ( ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == SET )
	{
		return ADC_GetConversionValue(ADC1);
	}
	else
	{
		return ADC_NOT_READY;
	}
}

