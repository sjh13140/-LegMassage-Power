#ifndef __WDG_H
#define __WDG_H
#include "config.h"
#define cleardog(x) CLRWDT = x;
void wdg_init();
#endif