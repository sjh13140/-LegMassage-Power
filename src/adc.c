#include "adc.h"



/**********************************************************************************************************
**�������� ��adc_init
**�������� ��ADC ���ó�ʼ��
**��    �� ��None
**��    �� ��None
**********************************************************************************************************/
void  adc_init()                  //adc��ʼ��
{
	OPTION = (OPTION&~OPTION_ADCKS_MASK)|2<<OPTION_ADCKS_POS;        // ADC ʱ��Ƶ��ѡ�� 8��Ƶ
	AUX3 = (AUX3&~AUX3_ADCVREFS_MASK)|0<<AUX3_ADCVREFS_POS;          // ADC�ο���ѹ(VREFS)ѡ�� 5V
	//p07	ad10
	P0ADIE = (P0ADIE&~P0ADIE_P0ADIE_MASK)|8<< P0ADIE_P0ADIE_POS;     // ADC ����ͨ��ʹ�ܿ���
}
/**********************************************************************************************************
**�������� ��adc_get_value
**�������� ��ADC����ֵ adc_temp
**��    �� ��adc�ɼ�ͨ��
**��    �� ��ADC��ֵ
**********************************************************************************************************/
unsigned int adc_get_value(unsigned char ch)                // ADC ֵ��ȡ����
{
	unsigned int adc_temp = 0;
	unsigned int  temph = 0;
	unsigned int  templ = 0;
	ADCHS = (ADCHS&~ADCHS_ADCHS_MASK)|ch<<ADCHS_ADCHS_POS;    // ADC ͨ��ѡ��
	ADSOC = 1;                                                // ADC����ת��     
	while(ADSOC);           

	templ = ADTKDT;
	temph = ADCDH;         
	adc_temp  = (temph<<4) &0xff0;
	adc_temp |= (templ>>4);
	return adc_temp ;	
}
/**********************************************************************************************************
**�������� ��adc_get_average
**�������� ��ADC��ȡadc_tempȡƽ��ֵ
**��    �� ��adc�ɼ�ͨ��
**��    �� ��ADC�ɼ�ƽ����ֵ
**********************************************************************************************************/
unsigned int adc_get_average(unsigned char ch)            
{
	unsigned int adc_value_max = 0;
	unsigned int adc_value_min = 0xffff;
	unsigned int adc_sum = 0;
	unsigned int adc_current = 0;
	unsigned char i;
	for(i = 0;i<10;i++)    //�ɼ�ƽ��ֵ
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

