#include "pwm.h"

/**********************************************************************************************************
**函数名称 ：pwm0_init
**函数描述 ：pwm0 初始化配置
**输    入 ：None
**输    出 ：None
**********************************************************************************************************/
void pwm0_init()    //加热片
{
	//设置GPIO属性 p12
	P1MODL = (P1MODL&~P1MODL_P1MOD2_MASK)|2<<P1MODL_P1MOD2_POS;	
	PINMOD = (PINMOD&~PINMOD_PWM0OE_MASK)|1<<PINMOD_PWM0OE_POS;       // 允许pwm0信号输出到p12
	PWMCON = (PWMCON&~PWMCON_PWM0CKS_MASK)|2<<PWMCON_PWM0CKS_POS;     // 不分频 pwm0时钟源
	PWM0PRD = 255;
}
/**********************************************************************************************************
**函数名称 ：pwm1_init
**函数描述 ：pwm1 初始化配
**输    入 ：None
**输    出 ：None
**********************************************************************************************************/
void pwm1_init()   //加热灯
{
	//设置GPIO属性 p13
	P1MODL = (P1MODL&~P1MODL_P1MOD3_MASK)|2<<P1MODL_P1MOD3_POS;
	PINMOD = (PINMOD&~PINMOD_PWM1OE_MASK)|1<<PINMOD_PWM1OE_POS;       // pwm1输出信号使能
	PWMCON = (PWMCON&~PWMCON_PWM1CKS_MASK)|2<<PWMCON_PWM1CKS_POS;     // 不分频
	PWM1PRD = 255;
}

//void pwm2_init()  //LED1
//{
//	//设置GPIO属性 p16
//	P1MODH = (P1MODH&~P1MODH_P1MOD6_MASK)|2<<P1MODH_P1MOD6_POS;
//	PWMCON2 = (PWMCON2&~PWMCON2_PWM2OE_MASK)|1<<PWMCON2_PWM2OE_POS;    // pwm2输出使能
//	PWMCON2 = (PWMCON2&~PWMCON2_PWM2CKS_MASK)|2<<PWMCON2_PWM2CKS_POS;  // 不分频
//	PWM2PRD = 255;
//}
/**********************************************************************************************************
//**函数名称 ：pwm_set_prd
//**函数描述 ：pwm周期设置函数
//**输    入 ：pwm1-3周期
//**输    出 ：None
//**********************************************************************************************************/
//void pwm_set_prd(unsigned char r_prd,unsigned char g_prd,unsigned char b_prd)
//{
//	PWM0PRD = b_prd;
//	PWM1PRD = g_prd;
//	//PWM2PRD = r_prd;
//}
/*
B	1.2 PWM0
G	1.3 PWM1
R	1.6	PWM2
*/
/**********************************************************************************************************
**函数名称 ：pwm_set_duty
**函数描述 ：pwm1-pwm3 pwm占空比设置函数
**输    入 ：pwm1-3占空比
**输    出 ：None
**********************************************************************************************************/
//void pwm_set_duty(unsigned char r_duty,unsigned char g_duty,unsigned char b_duty) 
//{
//	PWM0DH = b_duty;
//	PWM1DH = g_duty;
//	PWM2DH = r_duty;
//}

//void FMQ(u8 para)
//{
//    PWM2DH=para;
//}

void FOOTHEAT(u8 para)
{
    PWM0DH=para;
}
void KNEEHEAT(u8 para)
{
    PWM1DH=para;
}

