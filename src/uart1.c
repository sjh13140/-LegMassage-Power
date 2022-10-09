#include "uart1.h"

u8 xdata USART_RX_BUF[50];
u8  USART_RX_STA;
u8 xdata head;
u8 xdata recvstart=0;
/**********************************************************************************************************
**�������� ��uart_gpio_init
**�������� ��uart RXD TXD �ܽ�����
**��    �� ��None
**��    �� ��None
**********************************************************************************************************/
void uart_gpio_init()
{
	//RXD   p30
	P3MODL = (P3MODL&~P3MODL_P3MOD0_MASK)|0<<P3MODL_P3MOD0_POS;
	P3_0 = 1;//ʹ������
	//TXD   p31
	P3MODL = (P3MODL&~P3MODL_P3MOD1_MASK)|2<<P3MODL_P3MOD1_POS;
	P3_1 = 1;//�����		
}
/**********************************************************************************************************
**�������� ��uart1_timer2_init
**�������� ��uart1�ڶ�ʱ��timer2�¹�������
**��    �� ��None
**��    �� ��None
**********************************************************************************************************/
void uart1_timer2_init()
{
	uart_gpio_init();
	SM0 = 0;
	SM1 = 1;	        //SM0\SM1=01   UART mode=1;8λ���ݴ���  
	SM2 = 0;		   	  //Mode 1, 3    �����ʲ���9600 = (SMOD+1) x Fsysclk / (32 x 2 x (256-TH1)) --- ��ʹ��Timer1 �Զ�����ģʽ
	PCON = (PCON & ~PCON_SMOD_MASK) | 1<<PCON_SMOD_POS;//SMOD=1 ����˫�����ʿ���λ
	OPTION = (OPTION & ~OPTION_UART1W_MASK)|0<<OPTION_UART1W_POS;//��ֹһ��UARTģʽ
  //Mode 1    �����ʲ���9600 =  Fsysclk / (32 x (65536-TH1)) --- ��ʹ��Timer1 �Զ�����ģʽ
  //��������7.3728MHZ����ͨ������ 65536-TH1Ӧ����24,
	CT2 = 0;
	TCLK = 1;
	RCLK = 1;
	TL2 = (65536-24)%256;
	TH2 = (65536-24)/256;
	RCP2L = (65536-24)%256;
	RCP2H = (65536-24)/256;
	TR2 = 1;          //timer2����
	REN = 1;		      //UART1�����վ�ʹ��
	ES = 1;           //������Uart1�ж�
}

char putchar(char c)  //����printf ��ӡ�ض���
{
	SBUF = c;
	while(TI == 0);
	TI = 0;
	return c;
}

/**********************************************************************************************************
**�������� ��uart1_irq
**�������� ��uart1�ж�
**��    �� ��None
**��    �� ��None
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