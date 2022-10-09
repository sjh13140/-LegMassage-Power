#ifndef __PWM_H
#define __PWM_H
#include "config.h"
void pwm0_init();
void pwm1_init();
void pwm2_init();
void pwm_set_prd(unsigned char r_prd,unsigned char g_prd,unsigned char b_prd);
void pwm_set_duty(unsigned char r_duty,unsigned char g_duty,unsigned char b_duty); 
void FMQ(u8 para);
void KEYLED(u8 para);
void HEATSLICE(u8 para);
#endif