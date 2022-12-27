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
u8 get_footsec();
u8 get_kneesec();
void set_footsec(u8 para);
void set_kneesec(u8 para);
#endif