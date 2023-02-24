#include "timer.h"
#include "ct1642.h"
#include "output.h"
#define FRC_HZ				14745600
#define FRC_DIV				2
#define CLK_US              2000                     //2000us
#define CLK_US1     	  50
#define TIME_RELOAD        (unsigned int)(65536-(((FRC_HZ/FRC_DIV)/2/1000)*CLK_US/1000))   //���ȸ���
#define TIME_RELOAD1        (unsigned int)(65536-(((FRC_HZ/FRC_DIV)/2/1000)*CLK_US1/1000))   //���ȸ���




static u32 s_u32systimescnt;
static u16 s_alarmsec;
static u8  s_stepsec;
static u16  s_500ms;
extern u8 xdata runstate;
u8 xdata pwmval;
u8 xdata pwmcnt;
/**********************************************************************************************************
**�������� ��tim0_mode1_init
**�������� ����ʱ��timer0 MODE1 ��ʼ������
**��    �� ��None
**��    �� ��None
**********************************************************************************************************/
void tim0_mode1_init(void)           
{               
  // 16λ��ʱ��/������
	TMOD = (TMOD &~ TMOD_TMOD0_MASK)|1<<TMOD_TMOD0_POS;//Timer0ģʽѡ��  16λ��ʱ��

  TH0 = (TIME_RELOAD) / 256; // timer0 ���ֽ�����
  TL0 = (TIME_RELOAD) % 256; // timer0 ���ֽ�����            
  ET0 = 1;                   // timer0 �ж�ʹ��
  TR0 = 1;                   // timer0 ���п���  
}

/**********************************************************************************************************
**�������� ��timer0_irq
**�������� ��timer0�ж����
**��    �� ��None
**��    �� ��None
**********************************************************************************************************/
void timer0_irq() interrupt 1          
{ 
	//����Ҫ���־λ��mcu�����ж�ʱ�Զ����
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
  // 16λ��ʱ��/������
	TMOD = (TMOD &~ TMOD_TMOD1_MASK)|1<<TMOD_TMOD1_POS;//Timer0ģʽѡ��  16λ��ʱ��

  TH1 = (TIME_RELOAD1) / 256; // timer0 ���ֽ�����
  TL1 = (TIME_RELOAD1) % 256; // timer0 ���ֽ�����            
  ET1 = 1;                   // timer0 �ж�ʹ��
  TR1 = 1;                   // timer0 ���п���  
}
void timer1_irq() interrupt 3          
{ 
	//����Ҫ���־λ��mcu�����ж�ʱ�Զ����
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