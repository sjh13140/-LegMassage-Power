#include "touch.h"


void touch_gpio_init()
{
	// p11
	P1MODL = (P1MODL&~P1MODL_P1MOD0_MASK)|0<<P1MODL_P1MOD0_POS;//����SW3 ��������
	P1_0 = 1; //ʹ������
	P1MODL = (P1MODL&~P1MODL_P1MOD1_MASK)|0<<P1MODL_P1MOD1_POS;//����SW3 ��������
	P1_1 = 1; //ʹ������
	
	// p10
	P1MODH = (P1MODL&~P1MODH_P1MOD7_MASK)|0<<P1MODH_P1MOD7_POS;//����SW3 ��������
	P1_7= 1; //ʹ������
	P3MODH = (P3MODH&~P3MODH_P3MOD4_MASK)|0<<P3MODH_P3MOD4_POS;//����SW3 ��������
	P3_4 = 1; //ʹ������
	P3MODH = (P3MODH&~P3MODH_P3MOD5_MASK)|0<<P3MODH_P3MOD5_POS;//����SW3 ��������
	P3_5 = 1; //ʹ������	
	P3MODH = (P3MODH&~P3MODH_P3MOD6_MASK)|0<<P3MODH_P3MOD6_POS;//����SW3 ��������
	P3_6 = 1; //ʹ������	
	P3MODH = (P3MODH&~P3MODH_P3MOD7_MASK)|0<<P3MODH_P3MOD7_POS;//����SW3 ��������
	P3_7 = 1; //ʹ������			
}

