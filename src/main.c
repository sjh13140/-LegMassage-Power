/***********************************************************************************************************
  ��ʾЧ����
	ͨ��USB������������ԣ��򿪵����еĴ������֣����ö�Ӧ�˿ڣ�
	9600�����ʣ�8λ����λ����У��λ��1λֹͣλ����ѧϰ�巢����
	��1���ֽ����ݣ�ѧϰ���ش�1����ͬ�ֽ����ݡ�
	ROM=16K  EEPROM=128b IRAM=256b  XRAM = 768b
***********************************************************************************************************/
#include "config.h"
#include "uart1.h"
#include "timer.h"
#include "adc.h"
#include "pwm.h"                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
#include "output.h"
#include "touch.h"
#include "eeprom.h"
#include "ct1642.h"
#include "wdg.h"
#include "input.h"

#define KEYTIME 1000

#define upgasbag_gogas_hightime     45          // 36
#define upgasbag_gogas_midtime      40           // 31
#define upgasbag_gogas_lowtime       33            //24

#define downgasbag_gogas_hightime    34//30
#define downgasbag_gogas_midtime     31 //27 
#define downgasbag_gogas_lowtime      25  //21

#define twogasbag_gogas_hightime          45//41
#define twogasbag_outgas_hightime         2
#define twogasbag_gogas_midtime          39//35
#define twogasbag_outgas_midtime        2
#define twogasbag_gogas_lowtime           30//26
#define twogasbag_outgas_lowtime         2

#define bat_lowpower 800   //   3.7v
#define bat_nonepower 750  //  3.5v

typedef struct KEY_TAG{
  u32 time;                        
  u8 state;   
  u8 over;           
}KEY_TAG_T;

typedef enum KEY_ENUM{
   TK1LONG=1,
	 TK1SHORT,
	  TK2SHORT,
	   TK3SHORT,
	    TK4SHORT,
	    KEYSHORT
}KEY_E;
typedef struct MODE_TAG{         
  u8 num;                        
  u8 p;   
  u8 time;
  u8 temptime;
  u8 buf[10];
}MODE_T;
typedef enum MODE_ENUM{
		GENTLE,
		RELAX,
		VIGOROUS,
		EXERCISE 
}MODE_E;
typedef enum AIP1642_ENUM{
		UI_NONE,
		UI_L1,
		UI_L2,
		UI_L3,
		UI_L4,
		UI_L5
}AIP1642_E;
typedef struct GASAG_TAG{         
     u8 gotime;
	u8 outtime;
}GASAG_T;
typedef struct DATA_TAG{         
     	u8 len;
	u8 buf[6];
}DATA_T;
typedef enum TIME_ENUM{
   	SET_MODE=1,
	 SET_MODELOVE,
	  CLR_MODELOVE,
	  SET_ALARMTIME,
	  GET_RUNTIME,
	  GET_MODELOVE,
	  GET_POWERSTATE,
	  GET_CHARGSTATE,
	  GET_MODE,
	  GET_ALARMTIME,
	  RST_SYS,
	  GET_VER,
	  GET_SHOCKSTATE,
	  GET_HOTSTATE,
	  GET_RUNSTATE,
	  GET_RUNSTATE_MODE,
	  GET_RUNSTATE_MODE_MODELOVE_ALARMTIME_SHOCK_HOT,
	  GET_RUNSTATE_CHARGSTATE,
	  GET_RUNSTATE_POWERSTATE,
	  SET_SHOCK,
	  SET_HOT,
	  ERR_DATA=0XEF

}TIME_E;
KEY_TAG_T xdata tk1;
KEY_TAG_T xdata tk2;
KEY_TAG_T xdata tk3;
KEY_TAG_T xdata tk4;
KEY_TAG_T xdata key;
MODE_T xdata t_mode;
GASAG_T xdata t_upgas;
GASAG_T xdata t_downgas;
GASAG_T xdata t_twogas;
DATA_T xdata t_data;
u8 xdata  mode=0;   //��Ħģʽ 
u8 xdata modelove=0;
u8 xdata eepromflag=0;
u8 xdata eeprombuf[2];
u8 xdata chrgstate=0;  //0��ʾ�ε� 1��ʾ���   2��ʾ����
u8 xdata powerstate=0;  //����״̬  0:��ʾ�������� 1:��ʾ��������2:��ʾ��������
u16 xdata temp=0;  //���ڽ��մ��У���
u8 xdata alarmtime=15;  //��ʱʱ��
u32 xdata firsttime=0;  //��ȡ��ʱʱ����״μ���ʱ���
u8 xdata pushbuf[20]; //��������
u32 xdata ledtime;  //�͵�����˸ʱ����״μ���ʱ���
u8 xdata runstate=0;  // 0:ֹͣ  1:���� 2:��ͣ 3:���
u8 xdata step=0xff; //ģʽ���в���
u32 xdata steptimes=0; //ģʽ����ʱ�����
u8 xdata temppara=0; //����Ƭ����
u8 xdata shockpara=0; //��������
u32 xdata shocktime;//��ʱ����״μ���ʱ���
u8 xdata lockflag=0; //������־
u32 xdata beeptime;
u8 xdata beepflag;
u8 xdata SHOW1=UI_NONE;
u8 xdata SHOW2=UI_NONE;
u8 xdata SHOW3=UI_NONE;
u8 xdata SHOW4=UI_NONE;
u8 xdata dir;
u8 xdata cnt;
u8 xdata twogasbagrun;
u8 xdata databuf[10];
void pushlongdata(u8 a,u8 *buf,u8 len) 
{
      u8 i=0;
	u16 sum=0;
	u8 tempbuf[15];
	tempbuf[0] = headpara; //Э��ͷ
       tempbuf[1] = a;   //������
	tempbuf[2] = len;  //���ݳ���
	for(i=0;i<len;i++){
		sum=sum+buf[i];
		tempbuf[3+i] =buf[i];
	}
	tempbuf[3+len] = sum/256;  //У��λ
	tempbuf[3+len+1] = sum%256;
	tempbuf[3+len+2] = 0xff;  //#  Э��β
		for(i=0;i<6+len;i++)
			{
	            putchar(tempbuf[i]);

		}	  


}
//void pushdata(u8 a,u16 b)  	//	������   ����
//{
//		u8 i;
//		pushbuf[0] = headpara; //Э��ͷ
//	       pushbuf[1] = a;   //������
//		pushbuf[2] = 1;  //���ݳ���
//		pushbuf[3] = b;  //����λ
//		pushbuf[4] = pushbuf[3];  //У��λ
//		pushbuf[5] = 0xff;  //#  Э��β
//			for(i=0;i<6;i++)
//				{
//		            putchar(pushbuf[i]);

//			}
//	
//	
//}
//void pushtime(u8 a,u16 b)
//{
//		u8 i;
//		pushbuf[0] = headpara; //Э��ͷ
//	       pushbuf[1] = a;   //������
//		pushbuf[2] = 2;  //���ݳ���
//		pushbuf[3] = b/256;  //����λ
//		pushbuf[4] = b%256;  //����λ
//		pushbuf[5] = 0xff;  //#  Э��β
//		for(i=0;i<6;i++)
//			{
//		        putchar(pushbuf[i]);

//		}
//}


//����ɨ��
u8 key_scan(void)
{
   if(tk1.state==0){
		if(KEY1==0){
			tk1.time = getsystimes();
			tk1.state=1;
			tk1.over=0;
		}
	}
	else {
		if(tk1.over==0){
			if(getsystimes()-tk1.time>=KEYTIME){
				tk1.over=1;
				return TK1LONG;
				
			}
			else if(KEY1==1)
				{
					if(getsystimes()-tk1.time>=15){
							tk1.over=1;
							return TK1SHORT;
						}
					else {
							tk1.over=1;
							return 0;

					}
			}
		}
		else 
			{
                    if(KEY1==1) tk1.state=0;

		}

	}

   if(tk2.state==0){
		if(KEY2==0){
			tk2.time = getsystimes();
			tk2.state=1;
			tk2.over=0;
		}
	}
	else {
		if(tk2.over==0){
			if(getsystimes()-tk2.time>=KEYTIME){
				tk2.over=1;
				return 0;
				
			}
			else if(KEY2==1)
				{
					if(getsystimes()-tk2.time>=15){
							tk2.over=1;
							return TK2SHORT;
						}
					else {
							tk2.over=1;
							return 0;

					}
			}
		}
		else 
			{
                    if(KEY2==1) tk2.state=0;

		}

	}

   if(tk3.state==0){
		if(KEY3==0){
			tk3.time = getsystimes();
			tk3.state=1;
			tk3.over=0;
		}
	}
	else {
		if(tk3.over==0){
			if(getsystimes()-tk3.time>=KEYTIME){
				tk3.over=1;
				return 0;
				
			}
			else if(KEY3==1)
				{
					if(getsystimes()-tk3.time>=15){
							tk3.over=1;
					
							return TK3SHORT;
						}
					else {
							tk3.over=1;
							return 0;

					}
			}
		}
		else 
			{
                    if(KEY3==1) tk3.state=0;

		}

	}

   if(tk4.state==0){
		if(KEY4==0){
			tk4.time = getsystimes();
			tk4.state=1;
			tk4.over=0;
		}
	}
	else {
		if(tk4.over==0){
			if(getsystimes()-tk4.time>=KEYTIME){
				tk4.over=1;
				return 0;
				
			}
			else if(KEY4==1)
				{
					if(getsystimes()-tk4.time>=15){
							tk4.over=1;
			
							return TK4SHORT;
						}
					else {
							tk4.over=1;
							return 0;

					}
			}
		}
		else 
			{
                    if(KEY4==1) tk4.state=0;

		}

	}

   if(key.state==0){
		if(KEY5==0){
			key.time = getsystimes();
			key.state=1;
			key.over=0;
		}
	}
	else {
		if(key.over==0){
			if(getsystimes()-key.time>=KEYTIME){
				key.over=1;
				return 0;
				
			}
			else if(KEY5==1)
				{
					if(getsystimes()-key.time>=15){
							key.over=1;
					
							return KEYSHORT;
						}
					else {
							key.over=1;
							return 0;

					}
			}
		}
		else 
			{
                    if(KEY5==1) key.state=0;

		}

	}
	return 0;
}

//����ִ��

void key_process(void)
{
  u8 key;
  u8 i;
	key = key_scan();
	if(key==0)return;
	

}


 #if 0
//�����������ݴ���
void ble_process(void)
{
		u8 i;
	   
      if(USART_RX_STA&0x80)           //  0                     1                   2                       3                4                     5
	  {
	    //�ȴ�������У��    Э��ͷ    ������   ���ݳ���      ����     У��λ    Э��β
	       bsp_delay_ms(200);
		USART_RX_STA= USART_RX_STA&0x7f;
		if( USART_RX_BUF[0]==headpara){
				if(USART_RX_BUF[2]==USART_RX_STA-4)  //���ж����ݳ��ȶԲ���
				{
					for(i=0;i<(USART_RX_STA-4);i++)
					{
						temp =temp+USART_RX_BUF[3+i];
					}
					if(temp==USART_RX_BUF[USART_RX_STA-1]) //���ж�У��λ�Բ���
					{
					       temp=0;
						if(USART_RX_BUF[1]==SET_MODE)  //ģʽ
						{
		 					       if(runstate==0){ 
//								        adc_value = adc_get_average(10);
//									if(adc_value>bat_lowpower)powerstate=1;
//									else if(adc_value<=bat_lowpower&&adc_value>bat_nonepower)powerstate=2;
//									else powerstate=0;
								}
						   
							       if(runstate!=3&&powerstate!=0){
									clear_alarmsec();
									firsttime = get_alarmsec();
									runstate=1;
									mode=USART_RX_BUF[3];
									if(mode==0){
										t_upgas.gotime = upgasbag_gogas_lowtime;
										t_downgas.gotime = downgasbag_gogas_lowtime;
										t_twogas.gotime=twogasbag_gogas_lowtime;
										t_twogas.outtime=twogasbag_outgas_lowtime;
										t_mode.buf[0]=0;
										t_mode.buf[1]=1;
										t_mode.num=2;
										t_mode.time = t_upgas.gotime;
										shockpara = 1;
										temppara=128;
										SHOW1=UI_GENTLE;
										SHOW2=3;
										SHOW3=0;
										SHOW4=UI_L1;
									}
									else if(mode==1){
										t_upgas.gotime = upgasbag_gogas_midtime;
										t_downgas.gotime = downgasbag_gogas_midtime;
										t_twogas.gotime=twogasbag_gogas_midtime;
										t_twogas.outtime=twogasbag_outgas_midtime;
										t_mode.buf[0]=0;
										t_mode.buf[1]=1;
										t_mode.num=2;
										t_mode.time = t_upgas.gotime;
										shockpara = 2;
										temppara=128;
										SHOW1=UI_RELAX;
										SHOW2=3;
										SHOW3=0;
										SHOW4=UI_L2;
									}
									else if(mode==2){
										t_upgas.gotime = upgasbag_gogas_hightime;
										t_downgas.gotime = downgasbag_gogas_hightime;
										t_twogas.gotime=twogasbag_gogas_hightime;
										t_twogas.outtime=twogasbag_outgas_hightime;
										t_mode.buf[0]=2;
										t_mode.buf[1]=3;
										t_mode.num=2;
										t_mode.time = t_twogas.gotime;
										shockpara = 3;
										temppara=255;
										SHOW1=UI_VIGOROUS;
										SHOW2=5;
										SHOW3=0;
										SHOW4=UI_L3;
									}
									else if(mode==3){
										t_upgas.gotime = upgasbag_gogas_midtime;
										t_downgas.gotime = downgasbag_gogas_midtime;
										t_twogas.gotime=twogasbag_gogas_midtime;
										t_twogas.outtime=twogasbag_outgas_midtime;
										t_mode.buf[0]=0;
										t_mode.buf[1]=1;
										t_mode.buf[2]=2;
										t_mode.buf[3]=3;
										t_mode.num=4;
										t_mode.time =t_upgas.gotime;
										shockpara = 2;
										temppara=255;
										SHOW1=UI_EXERCISE;
										SHOW2=5;
										SHOW3=0;
										SHOW4=UI_L2;
									}
									if(step!=t_mode.buf[0])clear_stepsec();
									t_mode.p=0;
									t_data.len=0;
									t_data.buf[t_data.len++]=mode;
									for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
									pushlongdata(SET_MODE,t_data.buf,t_data.len);
								} else{
								     if(runstate==2){
										t_data.len=0;
										t_data.buf[t_data.len++]=chrgstate;
										for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
										pushlongdata(GET_CHARGSTATE,t_data.buf,t_data.len);
									 }
								     if(powerstate==0){
										t_data.len=0;
										t_data.buf[t_data.len++]=powerstate;
										for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
										pushlongdata(GET_POWERSTATE,t_data.buf,t_data.len);

									 }

								}
							
						} 
						else if(USART_RX_BUF[1]==SET_MODELOVE)  //����Ķ�ģʽ
						{
                                                    	modelove=USART_RX_BUF[3]; 
								eeprombuf[0]=1; 
								eeprombuf[1]=modelove; 
								iap_eeprom_write(0,eeprombuf,2); 
								t_data.len=0;
								t_data.buf[t_data.len++]=modelove;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(SET_MODELOVE,t_data.buf,t_data.len);
							 
						}
						else if(USART_RX_BUF[1]==CLR_MODELOVE)  //ɾ���Ķ�ģʽ
						{
                                                      	modelove = 0;
								eeprombuf[0]=1; 
								eeprombuf[1]=modelove; 
								iap_eeprom_write(0,eeprombuf,2); 
								t_data.len=0;
								t_data.buf[t_data.len++]=modelove;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(CLR_MODELOVE,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==SET_ALARMTIME)  //��ʱ����
						{

						                       clear_alarmsec();
											   firsttime=0;
									if(USART_RX_BUF[3]==1)  //5
									{
		                                                         alarmtime = 5;
																 
															                
									}
									else if(USART_RX_BUF[3]==2)  //10
										{
		                                             alarmtime = 10;
														 
										
									}
									else if(USART_RX_BUF[3]==3) //15
										{
										alarmtime = 15;
											
										

									}
									else if(USART_RX_BUF[3]==4)  //20
										{
		                                             alarmtime = 20;
													 
										
									}
									else if(USART_RX_BUF[3]==5)  //25
										{
		                                             alarmtime = 25;
										
									}
									else if(USART_RX_BUF[3]==6)  //30
										{
		                                             alarmtime = 30;
										
									}
								t_data.len=0;
								t_data.buf[t_data.len++]=alarmtime;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(SET_ALARMTIME,t_data.buf,t_data.len);
									
						}
						else if(USART_RX_BUF[1]==GET_RUNTIME)  //��ȡʱ���
						{
                                                     // putchar(get_alarmsec());  //����ʱ���
                        					t_data.len=0;
								t_data.buf[t_data.len++]=get_alarmsec()/256;
								t_data.buf[t_data.len++]=get_alarmsec()%256;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_RUNTIME,t_data.buf,t_data.len);
							    						 

						}
						else if(USART_RX_BUF[1]==GET_MODELOVE){  //��ȡ�ղ�
                                                    					t_data.len=0;
								t_data.buf[t_data.len++]=modelove;
			
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_MODELOVE,t_data.buf,t_data.len);
						}

						else if(USART_RX_BUF[1]==GET_POWERSTATE){  //��ȡ����״̬
//						       	        adc_value = adc_get_average(10);
//								if(adc_value>bat_lowpower)powerstate=1;
//								else if(adc_value<=bat_lowpower&&adc_value>bat_nonepower)powerstate=2;
//								else powerstate=0;
                                                 					t_data.len=0;
								t_data.buf[t_data.len++]=powerstate;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_POWERSTATE,t_data.buf,t_data.len);
						}

						else if(USART_RX_BUF[1]==GET_CHARGSTATE){  //��ȡ���״̬
                                                                            					t_data.len=0;
								t_data.buf[t_data.len++]=chrgstate;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_CHARGSTATE,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==GET_MODE){  //��ȡģʽ״̬
						t_data.len=0;
								t_data.buf[t_data.len++]=mode;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_MODE,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==GET_ALARMTIME){  //��ȡ��ʱֵ
						t_data.len=0;
								t_data.buf[t_data.len++]=alarmtime;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_ALARMTIME,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==RST_SYS){  //����
						t_data.len=0;
								t_data.buf[t_data.len++]=0x01;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(RST_SYS,t_data.buf,t_data.len);
							   while(1);
						}
						else if(USART_RX_BUF[1]==GET_VER){  //��ȡ����汾
						t_data.len=0;
								t_data.buf[t_data.len++]= codeverion;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(RST_SYS,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==GET_SHOCKSTATE){  //��ȡ��״̬
                               						t_data.len=0;
								t_data.buf[t_data.len++]= shockpara;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_SHOCKSTATE,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==GET_HOTSTATE){  //��ȡ��ȡ����״̬
                                          						t_data.len=0;
								t_data.buf[t_data.len++]= temppara;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_HOTSTATE,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==GET_RUNSTATE){  //��ȡ����״̬
                                          						t_data.len=0;
  								t_data.buf[t_data.len++]= runstate;
  								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
  								pushlongdata(GET_SHOCKSTATE,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==GET_RUNSTATE_MODE){  //��ȡ������ģʽ״̬
                                                    						t_data.len=0;
								t_data.buf[t_data.len++]= runstate;
								t_data.buf[t_data.len++]= mode;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_RUNSTATE_MODE,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==GET_RUNSTATE_MODE_MODELOVE_ALARMTIME_SHOCK_HOT){  //��ȡ����״̬
                                                    	t_data.len=0;
								t_data.buf[t_data.len++]= runstate;
								t_data.buf[t_data.len++]= mode;
								t_data.buf[t_data.len++]= modelove;
								t_data.buf[t_data.len++]= alarmtime;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_RUNSTATE_MODE_MODELOVE_ALARMTIME_SHOCK_HOT,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==SET_SHOCK){  //������
						             shockpara = USART_RX_BUF[3];
								if(shockpara==0){
									SHOW4=UI_NONE;
								}
								else if(shockpara==1){
									SHOW4=UI_L1;
								}
								else if(shockpara==2){
									SHOW4=UI_L2;
								}
								else if(shockpara==3){
									SHOW4=UI_L3;
								}
                                          		t_data.len=0;
  								t_data.buf[t_data.len++]= shockpara;
  								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
  								pushlongdata(SET_SHOCK,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==SET_HOT){  //���ü���
						             temppara = USART_RX_BUF[3];
								if(temppara==0) {
									SHOW2=0;
									SHOW3=0;
								}
								else if(temppara==128){
									SHOW2=3;
									SHOW3=0;

								}
								else if(temppara==255){
									SHOW2=5;
									SHOW3=0;

								}
                                          			t_data.len=0;
  								t_data.buf[t_data.len++]= temppara;
  								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
  								pushlongdata(SET_HOT,t_data.buf,t_data.len);
						}
						for(i=0;i< USART_RX_STA;i++)USART_RX_BUF[i]=0;
						USART_RX_STA=0;
						
					}
					else{  //У��Ͳ���
							temp=0;
							for(i=0;i< USART_RX_STA;i++)USART_RX_BUF[i]=0;
							USART_RX_STA=0;
         						t_data.len=0;
  								t_data.buf[t_data.len++]=0X01;
  								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
  								pushlongdata(ERR_DATA,t_data.buf,t_data.len);
					}
				} 
				else{   //���ݳ��Ȳ���
						temp=0;
						for(i=0;i< USART_RX_STA;i++)USART_RX_BUF[i]=0;
						USART_RX_STA=0;
								t_data.len=0;
  								t_data.buf[t_data.len++]=0X00;
  								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
  								pushlongdata(ERR_DATA,t_data.buf,t_data.len);   
				}
		}
		else 	{
              	                temp=0;
						for(i=0;i< USART_RX_STA;i++)USART_RX_BUF[i]=0;
						USART_RX_STA=0;     
								t_data.len=0;
  								t_data.buf[t_data.len++]=0X02;
  								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
  								pushlongdata(ERR_DATA,t_data.buf,t_data.len);
		}

		
	  }

}
 #endif
void control_process(void)
{
	if(runstate==0){   //�ػ�
		PUMP=0;
		VALVE1=0;
		VALVE2=0;
		HEATSLICE(0);
	
		step=0xff;
		 SHOW1=UI_NONE;
		 SHOW2=UI_NONE;
		 SHOW3=UI_NONE;
		 SHOW4=UI_NONE;		
	}
	else if(runstate==1){  //����
	
		//HEATSLICE(temppara);

		if(get_stepsec()==t_mode.time){
			clear_stepsec();
			t_mode.p++;
			if(t_mode.p>=t_mode.num)t_mode.p=0;
		}
		step = t_mode.buf[t_mode.p];
           switch(step)
           	{
              case 0:           //������
			t_mode.time = t_upgas.gotime;
			PUMP=1;
			VALVE1=1;
			VALVE2=0;
			twogasbagrun=0;
			break;
		case 1:         //������
			t_mode.time = t_downgas.gotime;
			PUMP=1;
			VALVE1=0;
			VALVE2=1;
			twogasbagrun=0;
			break;
              case 2:   //˫���Ҵ���
              	if(twogasbagrun==1){
				if(mode==2)t_mode.time=17;
				else if(mode==3)t_mode.time=15;
			}
			else {
				t_mode.time = t_twogas.gotime;
			} 
			PUMP=1;
			VALVE1=1;
			VALVE2=1;
			break;
		case 3:   //˫����й��
		       t_mode.time = t_twogas.outtime;
			PUMP=0;
			VALVE1=0;
			VALVE2=0;
			twogasbagrun=1;
			break;
		}		
	}
	else if(runstate==2) { //��ͣ
                 PUMP=0;

	}


}

void alarmtime_process(void)
{
  u8 i;
    if(runstate!=0&&runstate!=3)
      	{
		if(get_alarmsec()-firsttime>=(alarmtime*60)){
			runstate=0;
			//pushdata(0x01,(u16)mode);
			t_data.len=0;
			t_data.buf[t_data.len++]=runstate;
			for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
			pushlongdata(0x0f,t_data.buf,t_data.len);			
		}
	}


}

/**********************************************************************************************************
**�������� ��main
**�������� ��������
**��    �� ��None
**��    �� ��None
**********************************************************************************************************/
void main(void)
{

	bsp_clock_init();     //ϵͳ����14.7456M div 2
	uart1_timer2_init();  //uart1_timer2��ʼ��
	tim0_mode1_init();
	tim1_mode1_init(); 
	pwm0_init();
	pwm1_init();
	gpio_output_init();
	input_init();
	ct1642_gpio_init();
	EA = 1;               //���ж�����
	iap_eeprom_read(0,eeprombuf,2);
	eepromflag = eeprombuf[0];
	modelove = eeprombuf[1]; 
	if(eepromflag!=0x02){
		eeprombuf[0]=0x02; 
		eeprombuf[1]=0x00; 
		iap_eeprom_write(0,eeprombuf,2);
		
	}
	else{
		iap_eeprom_read(0,eeprombuf,2);
		eepromflag = eeprombuf[0];
		modelove= eeprombuf[1];
		
	}
	EA = 1;
SHOW1=5;
SHOW2=2;
SHOW3=1;
SHOW4=2;
	wdg_init();
  while(1)
	{
		//�������ô���
//		key_process();
//		//�������մ���
		//ble_process();
//		//�������������
	//	power_process();     //������ᵼ����ʱ��׼
//		//�������
//		control_process();
//		�������ʾ
       show_aip1642(SHOW1,SHOW2,SHOW3,SHOW4);
//		���ж�ʱ
//		alarmtime_process();
		cleardog(1);
	}
}



