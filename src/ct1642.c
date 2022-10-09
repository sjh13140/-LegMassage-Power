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
  u8 buf[4];           
}AIP1642_T;
//D1 D2(16) =0X03  D8D6(17)=0XA0  D5D7(18)=0X50 D3D4(19)=0X0C   D1(20)=0X01   D2(21)=0X02 D3(22)=0X04  L(23)  暗24
u8  code table[]={0x00,0x01,0x02,0x04,0x08,0x10};	 //D1 D2    D8 D6    D5D7   D3D4
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
/*
Pos位：1、2、4、8对应C1--C4
Val段：对应8个段Q2--Q9
*/
void CT1642_Write(unsigned char Pos, unsigned char Val)
{
    unsigned char i,Posn;
    // 1、移18位：对应C1--C4、6位空、Q2--Q9
    Posn=~Pos;
    for(i=0; i<4; i++)//C1--C4
    {
        DAT=Posn & 0x01;
        Posn >>= 1;
        CLK=0;    CLK=1;
    }
    for(i=0; i<6; i++)//6位空
    {
        DAT=1;
        CLK=0;    CLK=1;
    }
    for(i=0; i<8; i++)//Q2--Q9
    {
        DAT=Val & 0x01;
        Val >>= 1;
        CLK=0;    CLK=1;
    }
    // 2、锁存
    CLK=1;    DAT=0;    DAT=1;
    // 3、输出
    CLK=0;    DAT=0;    DAT=1;
}

void aip1642_process(void)
{
		CT1642_Write(0, 0xff);
		if(t_aip1642.pos==1){t_aip1642.n=t_aip1642.buf[0];}
		else if(t_aip1642.pos==2){t_aip1642.n=t_aip1642.buf[1];}
		else if(t_aip1642.pos==4){t_aip1642.n=t_aip1642.buf[2];}
		else if(t_aip1642.pos==8){t_aip1642.n=t_aip1642.buf[3];}
		CT1642_Write(t_aip1642.pos, table[t_aip1642.n]);
		t_aip1642.pos=t_aip1642.pos<<1;
		if(t_aip1642.pos>8)t_aip1642.pos=1;

		

		
}

void show_aip1642(u8 para1,u8 para2,u8 para3,u8 para4)
{
	t_aip1642.buf[0]=para1;
	t_aip1642.buf[1]=para2;
	t_aip1642.buf[2]=para3;
	t_aip1642.buf[3]=para4;
}