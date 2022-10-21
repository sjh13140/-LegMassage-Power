#include "ct1642.h"

//上电时CLK为低，DATA为高
//1、数据移位：从DATA端输入数据，在CLK上升沿作用下，一次传输18个数据位，分别对应C1--C4、6位空、Q2--Q9
//2、数据锁存：CLK置1，DATA端上升沿
//3、数据输出：CLK置0，DATA端上升沿
//4、C1--C4位0选中，Q2--Q9位1点亮

//#define DAT P1_4
//#define CLK P1_5
sbit DAT=P1^4;
sbit CLK=P1^5;

typedef struct AIP1642_TAG{
  u8 pos;                        
  u8 n;   
  u8 buf[2];           
}AIP1642_T;

u8  code table[]={0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};	
AIP1642_T t_aip1642;

void ct1642_gpio_init(void)
{
	//p14
  P1MODH = (P1MODH&~P1MODH_P1MOD4_MASK)|1<<P1MODH_P1MOD4_POS;//配置coms推挽输出
	P1_4 = 1;//输出高
	
		//p15
  P1MODH = (P1MODH&~P1MODH_P1MOD5_MASK)|1<<P1MODH_P1MOD5_POS;//配置coms推挽输出
	P1_5 = 1;//输出高

	t_aip1642.pos=1;
	t_aip1642.n=0;
}
void ct1642_send_data(unsigned char ct_dis_data, unsigned char ct_com)
{
		unsigned char ct_addr;                   //存储数码管位置
		unsigned char i;
		switch(ct_com){
			case 0: {ct_addr=0xfe; ;break;}//显示C1位数据 数码管为共阴极，将要点亮的COM置0以显示该COM
			case 1: {ct_addr=0xfd; break;} //显示C2位数据  
			case 2: {ct_addr=0xfb; break;} //显示C3位数据  
			case 3: {ct_addr=0xf7; break;} //显示C4位数据     
			case 4: {ct_addr=0xff; break;}  //扫描键盘,关闭COM1  
			default:{ct_addr=0xff; ct_dis_data=0x00;break;}   
		}
		for(i=0;i<8;i++) {                  //发送8位地址
			CLK=0 ;
			if( (ct_addr>>i)&0x01){
				DAT=1;
			}
			else{
				DAT=0;
			}
			CLK=1;//上升沿输出一位
		}
		DAT=0;      //发送两个空位，补足要发送的18位
		CLK=0 ;
		_nop_();//此处根据单片机的指令周期而定
		CLK=1;
		DAT=0;
		CLK=0 ;
		_nop_();
		CLK=1;
		for(i=0;i<8;i++){  //发送8位数据
			CLK=0 ;
			if( (ct_dis_data>>i)&0x01)
			{
				DAT=1;
			}
			else
			{
				DAT=0;
			}
			CLK=1;
		}
		CLK=1; //输出数据
		DAT=0;
		_nop_();
		DAT=1;
		CLK=0 ;
		DAT=0;
		_nop_();
		DAT=1;
		CLK=0;
}
void aip1642_process(void)
{
		 ct1642_send_data( table[t_aip1642.buf[t_aip1642.pos]],t_aip1642.pos);
		t_aip1642.pos++;
		if(t_aip1642.pos>1)t_aip1642.pos=0;
}


void show_aip1642(u8 para1,u8 para2)
{
	t_aip1642.buf[0]=para1;
	t_aip1642.buf[1]=para2;

}
