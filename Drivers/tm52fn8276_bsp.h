#ifndef __TM52FN8276_BSP_H__
#define __TM52FN8276_BSP_H__

#include "tm52fn8276_sfr_config.h"


#define delay_10nop() \
	do{												\
		_nop_();_nop_();_nop_();_nop_();_nop_();	 \
		_nop_();_nop_();_nop_();_nop_();_nop_();	\
	}while(0)

	
/* 系统时钟使用快时钟，频率为2分频 8.294M  */
void bsp_clock_init();

void bsp_delay_ms(unsigned int ms);

#endif
