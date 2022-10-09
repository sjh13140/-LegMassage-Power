#include <REGtenxTM52FN8276.h>
#include <intrins.h>



#include "tm52fn8276_bsp.h"
#include "wdg.h"

/* ��ʱ��ϵͳ��ƵΪ 14.7456M/2 = 7.3728M 
 */
void bsp_clock_init()	     
{
	SELFCK = 0;	     //�л�����ʱ��
	
	CLKCON = 0x02;   //div 2	 ʱ�ӷ�Ƶ
	delay_10nop();
	SELFCK = 1;			//�л�����ʱ��	 
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

















