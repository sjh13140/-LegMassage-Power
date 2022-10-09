#include "uart1.h"

u8 xdata USART_RX_BUF[50];
u8  USART_RX_STA;
u8 xdata head;
u8 xdata recvstart=0;
/**********************************************************************************************************
**函数名称 ：uart_gpio_init
**函数描述 ：uart RXD TXD 管脚配置
**输    入 ：None
**输    出 ：None
**********************************************************************************************************/
void uart_gpio_init()
{
	//RXD   p30
	P3MODL = (P3MODL&~P3MODL_P3MOD0_MASK)|0<<P3MODL_P3MOD0_POS;
	P3_0 = 1;//使能上拉
	//TXD   p31
	P3MODL = (P3MODL&~P3MODL_P3MOD1_MASK)|2<<P3MODL_P3MOD1_POS;
	P3_1 = 1;//输出高		
}
/**********************************************************************************************************
**函数名称 ：uart1_timer2_init
**函数描述 ：uart1在定时器timer2下工作配置
**输    入 ：None
**输    出 ：None
**********************************************************************************************************/
void uart1_timer2_init()
{
	uart_gpio_init();
	SM0 = 0;
	SM1 = 1;	        //SM0\SM1=01   UART mode=1;8位数据传送  
	SM2 = 0;		   	  //Mode 1, 3    波特率采用9600 = (SMOD+1) x Fsysclk / (32 x 2 x (256-TH1)) --- 若使用Timer1 自动重载模式
	PCON = (PCON & ~PCON_SMOD_MASK) | 1<<PCON_SMOD_POS;//SMOD=1 允许双波特率控制位
	OPTION = (OPTION & ~OPTION_UART1W_MASK)|0<<OPTION_UART1W_POS;//禁止一线UART模式
  //Mode 1    波特率采用9600 =  Fsysclk / (32 x (65536-TH1)) --- 若使用Timer1 自动重载模式
  //假如我用7.3728MHZ晶体通过计算 65536-TH1应等于24,
	CT2 = 0;
	TCLK = 1;
	RCLK = 1;
	TL2 = (65536-24)%256;
	TH2 = (65536-24)/256;
	RCP2L = (65536-24)%256;
	RCP2H = (65536-24)/256;
	TR2 = 1;          //timer2运行
	REN = 1;		      //UART1接收收据使能
	ES = 1;           //允许串口Uart1中断
}

char putchar(char c)  //串口printf 打印重定义
{
	SBUF = c;
	while(TI == 0);
	TI = 0;
	return c;
}

/**********************************************************************************************************
**函数名称 ：uart1_irq
**函数描述 ：uart1中断
**输    入 ：None
**输    出 ：None
**********************************************************************************************************/
void uart1_irq() interrupt 4
{
unsigned char res;
	if(RI)
	{    
	       
		res = SBUF;
		if(USART_RX_STA==0&&res==headpara) 
		{
			recvstart=1;
		}
		if(recvstart==1){
			if(res==0xff)  //#
			{
	                    USART_RX_STA = USART_RX_STA  | 0x80;
				recvstart=0;
			}
			else {
				USART_RX_BUF[USART_RX_STA++]=res;
				if(USART_RX_STA>49)USART_RX_STA=0;

			}
		}
		RI = 0;
	}
	
}