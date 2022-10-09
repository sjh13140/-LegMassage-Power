#include <REGtenxTM52FN8276.h>
#include <intrins.h>



#include "tm52fn8276_bsp.h"
#include "wdg.h"

/* 快时钟系统主频为 14.7456M/2 = 7.3728M 
 */
void bsp_clock_init()	     
{
	SELFCK = 0;	     //切换到慢时钟
	
	CLKCON = 0x02;   //div 2	 时钟分频
	delay_10nop();
	SELFCK = 1;			//切换到快时钟	 
}



void bsp_delay_ms(unsigned int ms)
{
	unsigned int i;
	unsigned char delay_cnt;
	for(i = 0;i<ms;i++)
	{
		delay_cnt = 200;
		while(delay_cnt--)
		{
			delay_10nop();
			cleardog(1);
		}
	}
}

















