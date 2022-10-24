#ifndef __OUTPUT_H
#define __OUTPUT_H
#include "config.h"

#define PUMP  	P1_1
#define VALVE1   P0_5 //脚底
#define VALVE2   P0_6  //脚踝
#define VALVE3   P0_4 //小腿  
#define VALVE4   P0_7  //大腿
#define POWERLED   P0_1 //电源指示灯
#define HEATLED   P0_0  //加热指示灯
void gpio_output_init();
#endif