#ifndef __TOUCH_H
#define __TOUCH_H
#include "config.h"

#define ETASTATE  P1_0
#define TK1 P1_1
#define TK2 P1_7  //加热
#define TK3 P3_5  //震动
#define TK4 P3_6  //模式
#define USBSTATE P3_7
#define KEY P3_4
void touch_gpio_init();
#endif