#include "output.h"




void gpio_output_init()
{
  //p05
 	  P0OE = (P0OE&~P0OE_P0OE0_MASK)|1<<P0OE_P0OE0_POS;          //VALVE1
	P0_0 = 0;//输出高	
 	 P0OE = (P0OE&~P0OE_P0OE1_MASK)|1<<P0OE_P0OE1_POS;            //VALVE2
	P0_1 = 0;//输出高

 
 	  P0OE = (P0OE&~P0OE_P0OE4_MASK)|1<<P0OE_P0OE4_POS;          //VALVE1
	P0_4 = 0;//输出高	
 	 P0OE = (P0OE&~P0OE_P0OE5_MASK)|1<<P0OE_P0OE5_POS;            //VALVE2
	P0_5 = 0;//输出高

	  P0OE = (P0OE&~P0OE_P0OE6_MASK)|1<<P0OE_P0OE6_POS;           //VALVE3
	P0_6 = 0;//输出高
	
	  P0OE = (P0OE&~P0OE_P0OE7_MASK)|1<<P0OE_P0OE7_POS;           //VALVE4
	P0_7 = 0;//输出高	

	
//	P3MODL = (P3MODL&~P3MODL_P3MOD3_MASK)|2<<P3MODL_P3MOD3_POS;//LED2配置coms推挽输出
//	P3_3 = 1;//输出高

//	P3MODL = (P3MODL&~P3MODL_P3MOD2_MASK)|2<<P3MODL_P3MOD2_POS;//LED2配置coms推挽输出
//	P3_2 = 1;//输出高

	P1MODL = (P1MODL&~P1MODL_P1MOD1_MASK)|2<<P1MODL_P1MOD1_POS;//PUMP
	P1_1 = 1;//输出高

//	P1MODL = (P1MODL&~P1MODL_P1MOD2_MASK)|2<<P1MODL_P1MOD2_POS;//PUMP
//	P1_2 = 0;//输出高
//	P1MODL = (P1MODL&~P1MODL_P1MOD3_MASK)|2<<P1MODL_P1MOD3_POS;//PUMP
//	P1_3=0;//输出高
}