#ifndef __CT1642_H
#define __CT1642_H
#include "config.h"
void ct1642_gpio_init(void);
void CT1642_Write(unsigned char Pos, unsigned char Val);
void aip1642_process(void);
void show_aip1642(u8 para1,u8 para2);
#endif