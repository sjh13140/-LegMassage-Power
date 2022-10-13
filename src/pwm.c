#include "pwm.h"

/**********************************************************************************************************
**�������� ��pwm0_init
**�������� ��pwm0 ��ʼ������
**��    �� ��None
**��    �� ��None
**********************************************************************************************************/
void pwm0_init()    //����Ƭ
{
	//����GPIO���� p12
	P1MODL = (P1MODL&~P1MODL_P1MOD2_MASK)|2<<P1MODL_P1MOD2_POS;	
	PINMOD = (PINMOD&~PINMOD_PWM0OE_MASK)|1<<PINMOD_PWM0OE_POS;       // ����pwm0�ź������p12
	PWMCON = (PWMCON&~PWMCON_PWM0CKS_MASK)|2<<PWMCON_PWM0CKS_POS;     // ����Ƶ pwm0ʱ��Դ
	PWM0PRD = 255;
}
/**********************************************************************************************************
**�������� ��pwm1_init
**�������� ��pwm1 ��ʼ����
**��    �� ��None
**��    �� ��None
**********************************************************************************************************/
void pwm1_init()   //���ȵ�
{
	//����GPIO���� p13
	P1MODL = (P1MODL&~P1MODL_P1MOD3_MASK)|2<<P1MODL_P1MOD3_POS;
	PINMOD = (PINMOD&~PINMOD_PWM1OE_MASK)|1<<PINMOD_PWM1OE_POS;       // pwm1����ź�ʹ��
	PWMCON = (PWMCON&~PWMCON_PWM1CKS_MASK)|2<<PWMCON_PWM1CKS_POS;     // ����Ƶ
	PWM1PRD = 255;
}

//void pwm2_init()  //LED1
//{
//	//����GPIO���� p16
//	P1MODH = (P1MODH&~P1MODH_P1MOD6_MASK)|2<<P1MODH_P1MOD6_POS;
//	PWMCON2 = (PWMCON2&~PWMCON2_PWM2OE_MASK)|1<<PWMCON2_PWM2OE_POS;    // pwm2���ʹ��
//	PWMCON2 = (PWMCON2&~PWMCON2_PWM2CKS_MASK)|2<<PWMCON2_PWM2CKS_POS;  // ����Ƶ
//	PWM2PRD = 255;
//}
/**********************************************************************************************************
//**�������� ��pwm_set_prd
//**�������� ��pwm�������ú���
//**��    �� ��pwm1-3����
//**��    �� ��None
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
**�������� ��pwm_set_duty
**�������� ��pwm1-pwm3 pwmռ�ձ����ú���
**��    �� ��pwm1-3ռ�ձ�
**��    �� ��None
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

