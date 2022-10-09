#ifndef __OUTPUT_H
#define __OUTPUT_H
#include "config.h"

#define PUMP  	P1_1
#define VALVE1   P0_4 //上  
#define VALVE2   P0_5  //下
#define VALVE3   P0_6 //上  
#define VALVE4   P0_7  //下
void gpio_output_init();
#endif