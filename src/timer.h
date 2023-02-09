#ifndef __TIMER_H
#define __TIMER_H
#include "config.h"
void tim0_mode1_init(void);   
void tim1_mode1_init(void);   
u32 getsystimes(void);
u16 get_alarmsec(void);
void clear_alarmsec(void);
u8 get_stepsec(void);
void clear_stepsec(void);
void set_stepsec(u8 para);
u16 set_alarmsec(u16 para);
extern u8 xdata pwmval;
extern u8 xdata pwmcnt;
#endif