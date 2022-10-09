#include "adc.h"



/**********************************************************************************************************
**函数名称 ：adc_init
**函数描述 ：ADC 配置初始化
**输    入 ：None
**输    出 ：None
**********************************************************************************************************/
void  adc_init()                  //adc初始化
{
	OPTION = (OPTION&~OPTION_ADCKS_MASK)|2<<OPTION_ADCKS_POS;        // ADC 时钟频率选择 8分频
	AUX3 = (AUX3&~AUX3_ADCVREFS_MASK)|0<<AUX3_ADCVREFS_POS;          // ADC参考电压(VREFS)选择 5V
	//p07	ad10
	P0ADIE = (P0ADIE&~P0ADIE_P0ADIE_MASK)|8<< P0ADIE_P0ADIE_POS;     // ADC 输入通道使能控制
}
/**********************************************************************************************************
**函数名称 ：adc_get_value
**函数描述 ：ADC返回值 adc_temp
**输    入 ：adc采集通道
**输    出 ：ADC数值
**********************************************************************************************************/
unsigned int adc_get_value(unsigned char ch)                // ADC 值获取函数
{
	unsigned int adc_temp = 0;
	unsigned int  temph = 0;
	unsigned int  templ = 0;
	ADCHS = (ADCHS&~ADCHS_ADCHS_MASK)|ch<<ADCHS_ADCHS_POS;    // ADC 通道选择
	ADSOC = 1;                                                // ADC启动转换     
	while(ADSOC);           

	templ = ADTKDT;
	temph = ADCDH;         
	adc_temp  = (temph<<4) &0xff0;
	adc_temp |= (templ>>4);
	return adc_temp ;	
}
/**********************************************************************************************************
**函数名称 ：adc_get_average
**函数描述 ：ADC获取adc_temp取平均值
**输    入 ：adc采集通道
**输    出 ：ADC采集平局数值
**********************************************************************************************************/
unsigned int adc_get_average(unsigned char ch)            
{
	unsigned int adc_value_max = 0;
	unsigned int adc_value_min = 0xffff;
	unsigned int adc_sum = 0;
	unsigned int adc_current = 0;
	unsigned char i;
	for(i = 0;i<10;i++)    //采集平均值
	{
		adc_current = adc_get_value(ch);
		if(adc_current > adc_value_max)
		{
			adc_value_max = adc_current;
		}
		if(adc_current < adc_value_min)
		{
			adc_value_min = adc_current;
		}
		adc_sum = adc_sum + adc_current;
	}
	adc_sum = adc_sum - adc_value_min;
	adc_sum = adc_sum - adc_value_max;
	adc_sum = adc_sum>>3;
	return adc_sum;
}

