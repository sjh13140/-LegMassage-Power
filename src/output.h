#ifndef __OUTPUT_H
#define __OUTPUT_H
#include "config.h"

#define PUMP  	P1_1
#define VALVE1   P0_5 //�ŵ�
#define VALVE2   P0_6  //����
#define VALVE3   P0_4 //С��  
#define VALVE4   P0_7  //����
#define POWERLED   P0_1 //��Դָʾ��
#define HEATLED   P0_0  //����ָʾ��
void gpio_output_init();
#endif