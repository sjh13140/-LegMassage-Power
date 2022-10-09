#ifndef __ADC_H
#define __ADC_H
#include "config.h"
void  adc_init();                  //adc初始化
unsigned int adc_get_average(unsigned char ch);   
unsigned int adc_get_value(unsigned char ch);                // ADC 值获取函数
#endif