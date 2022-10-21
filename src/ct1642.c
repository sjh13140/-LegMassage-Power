#include "ct1642.h"

//�ϵ�ʱCLKΪ�ͣ�DATAΪ��
//1��������λ����DATA���������ݣ���CLK�����������£�һ�δ���18������λ���ֱ��ӦC1--C4��6λ�ա�Q2--Q9
//2���������棺CLK��1��DATA��������
//3�����������CLK��0��DATA��������
//4��C1--C4λ0ѡ�У�Q2--Q9λ1����

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
  P1MODH = (P1MODH&~P1MODH_P1MOD4_MASK)|1<<P1MODH_P1MOD4_POS;//����coms�������
	P1_4 = 1;//�����
	
		//p15
  P1MODH = (P1MODH&~P1MODH_P1MOD5_MASK)|1<<P1MODH_P1MOD5_POS;//����coms�������
	P1_5 = 1;//�����

	t_aip1642.pos=1;
	t_aip1642.n=0;
}
void ct1642_send_data(unsigned char ct_dis_data, unsigned char ct_com)
{
		unsigned char ct_addr;                   //�洢�����λ��
		unsigned char i;
		switch(ct_com){
			case 0: {ct_addr=0xfe; ;break;}//��ʾC1λ���� �����Ϊ����������Ҫ������COM��0����ʾ��COM
			case 1: {ct_addr=0xfd; break;} //��ʾC2λ����  
			case 2: {ct_addr=0xfb; break;} //��ʾC3λ����  
			case 3: {ct_addr=0xf7; break;} //��ʾC4λ����     
			case 4: {ct_addr=0xff; break;}  //ɨ�����,�ر�COM1  
			default:{ct_addr=0xff; ct_dis_data=0x00;break;}   
		}
		for(i=0;i<8;i++) {                  //����8λ��ַ
			CLK=0 ;
			if( (ct_addr>>i)&0x01){
				DAT=1;
			}
			else{
				DAT=0;
			}
			CLK=1;//���������һλ
		}
		DAT=0;      //����������λ������Ҫ���͵�18λ
		CLK=0 ;
		_nop_();//�˴����ݵ�Ƭ����ָ�����ڶ���
		CLK=1;
		DAT=0;
		CLK=0 ;
		_nop_();
		CLK=1;
		for(i=0;i<8;i++){  //����8λ����
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
		CLK=1; //�������
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
