#include "timer.h"
#include "ct1642.h"
#include "output.h"
#define FRC_HZ				14745600
#define FRC_DIV				2
#define CLK_US              2000                     //2000us
#define CLK_US1     	  50
#define TIME_RELOAD        (unsigned int)(65536-(((FRC_HZ/FRC_DIV)/2/1000)*CLK_US/1000))   //精度更高
#define TIME_RELOAD1        (unsigned int)(65536-(((FRC_HZ/FRC_DIV)/2/1000)*CLK_US1/1000))   //精度更高




static u32 s_u32systimescnt;
static u16 s_alarmsec;
static u8  s_stepsec;
static u16  s_500ms;
extern u8 xdata runstate;
u8 xdata pwmval;
u8 xdata pwmcnt;
/**********************************************************************************************************
**函数名称 ：tim0_mode1_init
**函数描述 ：定时器timer0 MODE1 初始化设置
**输    入 ：None
**输    出 ：None
**********************************************************************************************************/
void tim0_mode1_init(void)           
{               
  // 16位定时器/计数器
	TMOD = (TMOD &~ TMOD_TMOD0_MASK)|1<<TMOD_TMOD0_POS;//Timer0模式选择  16位定时器

  TH0 = (TIME_RELOAD) / 256; // timer0 高字节数据
  TL0 = (TIME_RELOAD) % 256; // timer0 低字节数据            
  ET0 = 1;                   // timer0 中断使能
  TR0 = 1;                   // timer0 运行控制  
}

/**********************************************************************************************************
**函数名称 ：timer0_irq
**函数描述 ：timer0中断入口
**输    入 ：None
**输    出 ：None
**********************************************************************************************************/
void timer0_irq() interrupt 1          
{ 
	//不需要清标志位，mcu进入中断时自动清除
		  TH0=(TIME_RELOAD) / 256;
		  TL0=(TIME_RELOAD) % 256;       // 2ms++
		  	aip1642_process();
			s_u32systimescnt++;
			s_500ms++;
		if(s_500ms==500){
			s_500ms=0;
			if(runstate==1)s_alarmsec++;
			s_stepsec++;
		}
}
void tim1_mode1_init(void)           
{               
  // 16位定时器/计数器
	TMOD = (TMOD &~ TMOD_TMOD1_MASK)|1<<TMOD_TMOD1_POS;//Timer0模式选择  16位定时器

  TH1 = (TIME_RELOAD1) / 256; // timer0 高字节数据
  TL1 = (TIME_RELOAD1) % 256; // timer0 低字节数据            
  ET1 = 1;                   // timer0 中断使能
  TR1 = 1;                   // timer0 运行控制  
}
void timer1_irq() interrupt 3          
{ 
	//不需要清标志位，mcu进入中断时自动清除
		  TH1=(TIME_RELOAD1) / 256;
		  TL1=(TIME_RELOAD1) % 256;       // 2ms++
	pwmcnt++; 
	if(pwmcnt<=pwmval&&pwmcnt>0) PUMP=1; 
	else 
	{  
		PUMP=0;  
		if(pwmcnt>=100)pwmcnt=0; 
	}	
}
u32 getsystimes(void)
{
	return s_u32systimescnt;
}

u16 get_alarmsec(void)
{
         
        return s_alarmsec;

}
//u16 set_alarmsec(u16 para)
//{
//	s_alarmsec = para;
//}
void clear_alarmsec(void)
{
	s_alarmsec=0;
}
u8 get_stepsec(void)
{  
        return s_stepsec;
}
void set_stepsec(u8 para)
{
	s_stepsec = para;
}
void clear_stepsec(void)
{
	s_stepsec=0;
}