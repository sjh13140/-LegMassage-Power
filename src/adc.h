#ifndef __ADC_H
#define __ADC_H
#include "config.h"
void  adc_init();                  //adc��ʼ��
unsigned int adc_get_average(unsigned char ch);   
unsigned int adc_get_value(unsigned char ch);                // ADC ֵ��ȡ����
#endif