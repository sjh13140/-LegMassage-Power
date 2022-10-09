#ifndef __UART1_H
#define __UART1_H
#include "config.h"


extern unsigned char xdata USART_RX_BUF[50];
extern unsigned char USART_RX_STA;
extern unsigned char xdata head;
void uart1_timer2_init();
char putchar(char c) ;
void uart1_timer2_init();
#endif