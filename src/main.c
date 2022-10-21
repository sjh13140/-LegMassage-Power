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

#define foot_gogas_L1 10
#define foot_gogas_L2 15
#define foot_gogas_L3 20
#define foot_gogas_L4 25

#define foot_again_gogas_L1 5
#define foot_again_gogas_L2 10
#define foot_again_gogas_L3 15
#define foot_again_gogas_L4 20

#define ankle_gogas_L1 10
#define ankle_gogas_L2 15
#define ankle_gogas_L3 20
#define ankle_gogas_L4 25

#define ankle_again_gogas_L1 5
#define ankle_again_gogas_L2 10
#define ankle_again_gogas_L3 15
#define ankle_again_gogas_L4 20

#define sleg_gogas_L1 10
#define sleg_gogas_L2 15
#define sleg_gogas_L3 20
#define sleg_gogas_L4 25

#define sleg_again_gogas_L1 5
#define sleg_again_gogas_L2 10
#define sleg_again_gogas_L3 15
#define sleg_again_gogas_L4 20

#define bleg_gogas_L1 10
#define bleg_gogas_L2 15
#define bleg_gogas_L3 20
#define bleg_gogas_L4 25

#define bleg_again_gogas_L1 5
#define bleg_again_gogas_L2 10
#define bleg_again_gogas_L3 15
#define bleg_again_gogas_L4 20

#define foot_ankle_gogas_L1 10
#define foot_ankle_gogas_L2 15
#define foot_ankle_gogas_L3 20
#define foot_ankle_gogas_L4 25

#define foot_sleg_gogas_L1 10
#define foot_sleg_gogas_L2 15
#define foot_sleg_gogas_L3 20
#define foot_sleg_gogas_L4 25

#define foot_bleg_gogas_L1 10
#define foot_bleg_gogas_L2 15
#define foot_bleg_gogas_L3 20
#define foot_bleg_gogas_L4 25

#define ankle_sleg_gogas_L1 10
#define ankle_sleg_gogas_L2 15
#define ankle_sleg_gogas_L3 20
#define ankle_sleg_gogas_L4 25

#define ankle_bleg_gogas_L1 10
#define ankle_bleg_gogas_L2 15
#define ankle_bleg_gogas_L3 20
#define ankle_bleg_gogas_L4 25

#define sleg_bleg_gogas_L1 10
#define sleg_bleg_gogas_L2 15
#define sleg_bleg_gogas_L3 20
#define sleg_bleg_gogas_L4 25

#define foot_ankle_sleg_gogas_L1 10
#define foot_ankle_sleg_gogas_L2 15
#define foot_ankle_sleg_gogas_L3 20
#define foot_ankle_sleg_gogas_L4 25

#define foot_ankle_sleg_bleg_gogas_L1 10
#define foot_ankle_sleg_bleg_gogas_L2 15
#define foot_ankle_sleg_bleg_gogas_L3 20
#define foot_ankle_sleg_bleg_gogas_L4 25

#define foot_ankle_sleg_bleg_again_gogas_L1 5
#define foot_ankle_sleg_bleg_again_gogas_L2 10
#define foot_ankle_sleg_bleg_again_gogas_L3 15
#define foot_ankle_sleg_bleg_again_gogas_L4 20

#define foot_ankle_sleg_bleg_outgas_L1 4
#define foot_ankle_sleg_bleg_outgas_L2 4
#define foot_ankle_sleg_bleg_outgas_L3 4
#define foot_ankle_sleg_bleg_outgas_L4 4


#define tempL3 255
#define tempL2 230
#define tempL1 200
u8 code gastime[13][5]={
	{0,foot_gogas_L1, foot_gogas_L2, foot_gogas_L3, foot_gogas_L4},
	{0,ankle_gogas_L1, ankle_gogas_L2, ankle_gogas_L3, ankle_gogas_L4},
	{0,sleg_gogas_L1, sleg_gogas_L2, sleg_gogas_L3, sleg_gogas_L4},
	{0,bleg_gogas_L1, bleg_gogas_L2, bleg_gogas_L3,bleg_gogas_L4},
	{0,foot_ankle_gogas_L1, foot_ankle_gogas_L2, foot_ankle_gogas_L3, foot_ankle_gogas_L4},
	{0,foot_sleg_gogas_L1,  foot_sleg_gogas_L2,  foot_sleg_gogas_L3,  foot_sleg_gogas_L4},
	{0,foot_bleg_gogas_L1, foot_bleg_gogas_L2, foot_bleg_gogas_L3,foot_bleg_gogas_L4},
	{0,ankle_sleg_gogas_L1, ankle_sleg_gogas_L2, ankle_sleg_gogas_L3, ankle_sleg_gogas_L4},
	{0,ankle_bleg_gogas_L1, ankle_bleg_gogas_L2, ankle_bleg_gogas_L3, ankle_bleg_gogas_L4},
	{0,sleg_bleg_gogas_L1, sleg_bleg_gogas_L2, sleg_bleg_gogas_L3, sleg_bleg_gogas_L4},
	{0,foot_ankle_sleg_gogas_L1, foot_ankle_sleg_gogas_L2, foot_ankle_sleg_gogas_L3, foot_ankle_sleg_gogas_L4},
	{0,foot_ankle_sleg_bleg_gogas_L1, foot_ankle_sleg_bleg_gogas_L2, foot_ankle_sleg_bleg_gogas_L3, foot_ankle_sleg_bleg_gogas_L4},
	{0,foot_ankle_sleg_bleg_outgas_L1, foot_ankle_sleg_bleg_outgas_L2, foot_ankle_sleg_bleg_outgas_L3, foot_ankle_sleg_bleg_outgas_L4}	
};
u8 code agastime[13][5]={
	{0,foot_again_gogas_L1, foot_again_gogas_L2, foot_again_gogas_L3, foot_again_gogas_L4},
	{0,ankle_gogas_L1, ankle_gogas_L2, ankle_gogas_L3, ankle_gogas_L4},
	{0,sleg_again_gogas_L1, sleg_again_gogas_L2, sleg_again_gogas_L3, sleg_again_gogas_L4},
	{0,bleg_again_gogas_L1, bleg_again_gogas_L2, bleg_again_gogas_L3,bleg_again_gogas_L4},
	{0,foot_ankle_gogas_L1, foot_ankle_gogas_L2, foot_ankle_gogas_L3, foot_ankle_gogas_L4},
	{0,foot_sleg_gogas_L1,  foot_sleg_gogas_L2,  foot_sleg_gogas_L3,  foot_sleg_gogas_L4},
	{0,foot_bleg_gogas_L1, foot_bleg_gogas_L2, foot_bleg_gogas_L3,foot_bleg_gogas_L4},
	{0,ankle_sleg_gogas_L1, ankle_sleg_gogas_L2, ankle_sleg_gogas_L3, ankle_sleg_gogas_L4},
	{0,ankle_bleg_gogas_L1, ankle_bleg_gogas_L2, ankle_bleg_gogas_L3, ankle_bleg_gogas_L4},
	{0,sleg_bleg_gogas_L1, sleg_bleg_gogas_L2, sleg_bleg_gogas_L3, sleg_bleg_gogas_L4},
	{0,foot_ankle_sleg_gogas_L1, foot_ankle_sleg_gogas_L2, foot_ankle_sleg_gogas_L3, foot_ankle_sleg_gogas_L4},
	{0,foot_ankle_sleg_bleg_again_gogas_L1, foot_ankle_sleg_bleg_again_gogas_L2, foot_ankle_sleg_bleg_again_gogas_L3, foot_ankle_sleg_bleg_again_gogas_L4},
	{0,foot_ankle_sleg_bleg_outgas_L1, foot_ankle_sleg_bleg_outgas_L2, foot_ankle_sleg_bleg_outgas_L3, foot_ankle_sleg_bleg_outgas_L4}	
};
typedef struct KEY_TAG{
  u32 time;                        
  u8 state;   
  u8 over;           
}KEY_TAG_T;

typedef enum KEY_ENUM{
	
	KEY1SHORT=1,
	KEY2SHORT,
	KEY3LONG,
	KEY3SHORT,
	KEY4SHORT,
	KEY5SHORT
}KEY_E;
typedef struct MODE_TAG{         
  u8 num;                        
  u8 p;   
  u8 time;
  u8 temptime;
  u8 buf[10];
}MODE_T;
//typedef enum MODE_ENUM{
//		GENTLE,
//		RELAX,
//		VIGOROUS,
//		EXERCISE 
//}MODE_E;
typedef enum AIP1642_ENUM{
		UI_NONE,
		UI_L1,
		UI_L2,
		UI_L3,
		UI_L4,
		UI_L5,
		UI_L1L2
}AIP1642_E;
//typedef struct GASAG_TAG{         
//     u8 gotime;
//	u8 outtime;
//}GASAG_T;
typedef struct DATA_TAG{         
     	u8 len;
	u8 buf[6];
}DATA_T;
typedef enum TIME_ENUM{
   	SET_RUNSTATE=1,
	 GET_RUNSTATE,
	  SET_MODE,
	  GET_MODE,
	  SET_LOVEMODE,
	  GET_LOVEMODE,
	  CLR_LOVEMODE,
	  SET_HEAT,
	  GET_HEAT,
	  SET_STRENGTH,
	  GET_STRENGTH,
	  SET_RUNTIME,
	  GET_RUNTIME,
	  GET_RUNSTAMP,
	  RST_SYS,
	  GET_VER,
	  GET_ALLSTATE,
	  ERR_DATA=0XEF
}TIME_E;

typedef enum BODY_ENUM{
	FOOT,
	ANKLE,
	SLEG,
	BLEG,
	FOOT_ANKLE,
	FOOT_SLEG,
	FOOT_BLEG,
	ANKLE_SLEG,
	ANKLE_BLEG,
	SLEG_BLEG,
	FOOT_ANKLE_SLEG,
	FOOT_ANKLE_SLEG_BLEG,
	ALL_OUTGAS
}BODY_E;


KEY_TAG_T xdata key1;
KEY_TAG_T xdata key2;
KEY_TAG_T xdata key3;
KEY_TAG_T xdata key4;
KEY_TAG_T xdata key5;
MODE_T xdata t_mode;
//GASAG_T xdata t_upgas;
//GASAG_T xdata t_downgas;
//GASAG_T xdata t_twogas;
DATA_T xdata t_data;
u8 xdata  mode=0;   //��Ħģʽ 
u8 xdata modelove=0;
u8 xdata eepromflag=0;
u8 xdata eeprombuf[2];
//u8 xdata chrgstate=0;  //0��ʾ�ε� 1��ʾ���   2��ʾ����
//u8 xdata powerstate=0;  //����״̬  0:��ʾ�������� 1:��ʾ��������2:��ʾ��������
u16 xdata temp=0;  //���ڽ��մ��У���
u8 xdata alarmtime=15;  //��ʱʱ��
u8 xdata alarmflag=1;
u32 xdata firsttime=0;  //��ȡ��ʱʱ����״μ���ʱ���
//u8 xdata pushbuf[20]; //��������
//u32 xdata ledtime;  //�͵�����˸ʱ����״μ���ʱ���
u8 xdata runstate=0;  // 0:ֹͣ  1:���� 2:��ͣ 3:���
u8 xdata step=0xff; //ģʽ���в���
u32 xdata steptimes=0; //ģʽ����ʱ�����
u8 xdata kneehot;
u8 xdata feethot=0; //����Ƭ����
u8 xdata kneelast;
u8 xdata feetlast=0; //����Ƭ����
u8 xdata hotflag=0;

u8 xdata SHOW1=UI_NONE;
u8 xdata SHOW2=UI_NONE;

//u8 xdata dir;
//u8 xdata cnt;
//u8 xdata twogasbagrun;
//u8 xdata databuf[10];
u8 xdata strengthflag=1;
//u8 xdata strengthpara=1;
u32 xdata stoptime;
//u8 xdata stopflag;
u8 xdata again=0;
void ui_show(u8 para1,u8 para2)
{
	SHOW1=para1;
	SHOW2=para2;
}
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
	tempbuf[3+len+2] = endpara;  //#  Э��β
		for(i=0;i<6+len;i++)
			{
	            putchar(tempbuf[i]);

		}	  


}
void valve_process(u8 para1,u8 para2,u8 para3,u8 para4)
{
		VALVE1=para1;
		VALVE2=para2;
		VALVE3=para3;
		VALVE4=para4;

}
void heat_process(u8 para1,u8 para2)
{
		FOOTHEAT(para1);
		KNEEHEAT( para2);
}
void mode_process()
{
	switch(mode){
	case 1:
		t_mode.buf[0] = FOOT;
		t_mode.buf[1] = ANKLE;
		t_mode.buf[2] = SLEG;
		t_mode.buf[3] = BLEG;
		t_mode.num = 4;
		//heat_process(tempL4,tempL4);
		//t_mode.p = 0;

		break;
	case 2:
		t_mode.buf[0] = FOOT;
		t_mode.buf[1] = FOOT_ANKLE;
		t_mode.buf[2] = ANKLE_SLEG;
		t_mode.buf[3] = SLEG_BLEG;
		t_mode.num = 4;
		//heat_process(tempL4,tempL4);
		//t_mode.p = 0;
		break;
	case 3:
		t_mode.buf[0]=FOOT_ANKLE;
		t_mode.buf[1]=SLEG_BLEG;
		t_mode.buf[2]=FOOT_SLEG;
		t_mode.buf[3]=FOOT_BLEG;
		t_mode.buf[4]=ANKLE_SLEG;
		t_mode.buf[5]=ANKLE_BLEG;
		t_mode.num = 6;
		//heat_process(tempL4,tempL4);
		//t_mode.p = 0;
		break;
	case 4:
		t_mode.buf[0]=FOOT_ANKLE_SLEG_BLEG;
		t_mode.buf[1]=ALL_OUTGAS;
		t_mode.num = 2;
		//heat_process(tempL4,tempL4);
		//t_mode.p = 0;
		break;
	case 5:
		break;
	case 6:
		t_mode.buf[0]=FOOT;
		t_mode.buf[1]=ALL_OUTGAS;
		t_mode.num = 2;
		//heat_process(tempL4,tempL4);
		//t_mode.p = 0;
		break;
	case 7:
		t_mode.buf[0]=SLEG;
		t_mode.buf[1]=ALL_OUTGAS;
		t_mode.num = 2;
		//t_mode.p = 0;
		break;
	case 8:
		t_mode.buf[0]=BLEG;
		t_mode.buf[1]=ALL_OUTGAS;
		t_mode.num = 2;
		//heat_process(tempL4,tempL4);
		//t_mode.p = 0;
		break;
	}
		strengthflag = 2;
		feethot = tempL3;
		kneehot=tempL3;
		hotflag=5;
		kneelast = kneehot;
		feetlast = feethot;
		again=0;
		if(step!=t_mode.buf[0])clear_stepsec();
		t_mode.p=0;
}


//����ɨ��
u8 key_scan(void)
{
   if(key1.state==0){
		if(KEY1==0){
			key1.time = getsystimes();
			key1.state=1;
			key1.over=0;
		}
	}
	else {
		if(key1.over==0){
			if(getsystimes()-key1.time>=KEYTIME){
				key1.over=1;
				return 0;
				
			}
			else if(KEY1==1)
				{
					if(getsystimes()-key1.time>=15){
							key1.over=1;
							return KEY1SHORT;
						}
					else {
							key1.over=1;
							return 0;

					}
			}
		}
		else 
			{
                    if(KEY1==1) key1.state=0;

		}

	}

   if(key2.state==0){
		if(KEY2==0){
			key2.time = getsystimes();
			key2.state=1;
			key2.over=0;
		}
	}
	else {
		if(key2.over==0){
			if(getsystimes()-key2.time>=KEYTIME){
				key2.over=1;
				return 0;
				
			}
			else if(KEY2==1)
				{
					if(getsystimes()-key2.time>=15){
							key2.over=1;
							return KEY2SHORT;
						}
					else {
							key2.over=1;
							return 0;

					}
			}
		}
		else 
			{
                    if(KEY2==1) key2.state=0;

		}

	}

   if(key3.state==0){
		if(KEY3==0){
			key3.time = getsystimes();
			key3.state=1;
			key3.over=0;
		}
	}
	else {
		if(key3.over==0){
			if(getsystimes()-key3.time>=KEYTIME){
				key3.over=1;
				return KEY3LONG;
				
			}
			else if(KEY3==1)
				{
					if(getsystimes()-key3.time>=15){
							key3.over=1;
					
							return KEY3SHORT;
						}
					else {
							key3.over=1;
							return 0;

					}
			}
		}
		else 
			{
                    if(KEY3==1) key3.state=0;

		}

	}

   if(key4.state==0){
		if(KEY4==0){
			key4.time = getsystimes();
			key4.state=1;
			key4.over=0;
		}
	}
	else {
		if(key4.over==0){
			if(getsystimes()-key4.time>=KEYTIME){
				key4.over=1;
				return 0;
				
			}
			else if(KEY4==1)
				{
					if(getsystimes()-key4.time>=15){
							key4.over=1;
			
							return KEY4SHORT;
						}
					else {
							key4.over=1;
							return 0;

					}
			}
		}
		else 
			{
                    if(KEY4==1) key4.state=0;

		}

	}

   if(key5.state==0){
		if(KEY5==0){
			key5.time = getsystimes();
			key5.state=1;
			key5.over=0;
		}
	}
	else {
		if(key5.over==0){
			if(getsystimes()-key5.time>=KEYTIME){
				key5.over=1;
				return 0;
				
			}
			else if(KEY5==1)
				{
					if(getsystimes()-key5.time>=15){
							key5.over=1;
					
							return KEY5SHORT;
						}
					else {
							key5.over=1;
							return 0;

					}
			}
		}
		else 
			{
                    if(KEY5==1) key5.state=0;

		}

	}
	return 0;
}

//����ִ��

void key_process(void)
{
  u8 key;
//  u8 i;
	key = key_scan();
	if(key==0)return;
	if(key==KEY1SHORT){  //�Զ�
		mode++;
		if(mode>5)mode=1;
		mode_process();

	}
	else if(key==KEY2SHORT){//�ֲ�
		if(mode<=5)mode=6;
		else {
                     mode++;
			if(mode>8)mode=6;
		}
		mode_process();
	}
	else if(key==KEY3LONG){  //����
					if(runstate==0){
						runstate=1;
						mode = 1;
						mode_process();
	
					}
					else if(runstate==1){
						runstate=0;
						hotflag=0;
						strengthflag=0;
						mode=0;
					}
	}
	else if(key==KEY3SHORT){ //����
		if(runstate==1){
			runstate=2;
		 t_mode.temptime = get_stepsec();	
 		stoptime=getsystimes();
		//stopflag=0;
		}
		else if(runstate==2){
			runstate = 1;
			set_stepsec(t_mode.temptime);
		}
	}
	else if(key==KEY4SHORT){   //ǿ�� 
		strengthflag++;
		if(strengthflag>4)strengthflag=1;
	}
	else if(key==KEY5SHORT){  //���� 
               if(hotflag==0) {
			kneehot=kneelast;   //ϥ�Ǽ���
			feethot=feetlast;  //��׼���
			hotflag=5;     //����״̬
	        }
	        else {
			hotflag=0;
			kneelast = kneehot;
			feetlast = feethot;
			kneehot=0;
			feethot=0;
		}
	}
	//if(runstate==0)ui_show(0,0, 0, 0);
	//else if(runstate==1)ui_show((mode<6?mode:0),(mode>5?mode-5:0), strengthflag, runstate+hotflag);
	ui_show(mode,strengthflag); 
	POWERLED=runstate;
	HEATLED=hotflag;
}


 #if 1
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
						if(USART_RX_BUF[1]==SET_RUNSTATE)  //����״̬
						{
									clear_alarmsec();
									firsttime = get_alarmsec();
									runstate=USART_RX_BUF[3];
									mode = 1;
									if(step!=t_mode.buf[0])clear_stepsec();
									t_mode.p=0;
									t_data.len=0;
									t_data.buf[t_data.len++]=runstate;
									for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
									pushlongdata(SET_RUNSTATE,t_data.buf,t_data.len);
		
							
						} 
						else if(USART_RX_BUF[1]==GET_RUNSTATE){  //��ȡ����״̬
								t_data.len=0;
								t_data.buf[t_data.len++]=runstate;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_RUNSTATE,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==SET_MODE)  //ģʽ
						{
									clear_alarmsec();
									firsttime = get_alarmsec();
									runstate=1;
									mode=USART_RX_BUF[3];
									
									if(step!=t_mode.buf[0])clear_stepsec();
									t_mode.p=0;
									t_data.len=0;
									t_data.buf[t_data.len++]=runstate;
									t_data.buf[t_data.len++]=mode;
									for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
									pushlongdata(SET_MODE,t_data.buf,t_data.len);
		
							
						} 
						else if(USART_RX_BUF[1]==GET_MODE){  //��ȡģʽ״̬
								t_data.len=0;
								t_data.buf[t_data.len++]=mode;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_MODE,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==SET_LOVEMODE)  //����Ķ�ģʽ
						{
                                                    	modelove=USART_RX_BUF[3]; 
								eeprombuf[0]=1; 
								eeprombuf[1]=modelove; 
								iap_eeprom_write(0,eeprombuf,2); 
								t_data.len=0;
								t_data.buf[t_data.len++]=modelove;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(SET_LOVEMODE,t_data.buf,t_data.len);
							 
						}
						else if(USART_RX_BUF[1]==GET_LOVEMODE){  //��ȡ�ղ�
                                                    					t_data.len=0;
								t_data.buf[t_data.len++]=modelove;
			
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_LOVEMODE,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==CLR_LOVEMODE)  //ɾ���Ķ�ģʽ
						{
                                                      	modelove = 1;
								eeprombuf[0]=1; 
								eeprombuf[1]=modelove; 
								iap_eeprom_write(0,eeprombuf,2); 
								t_data.len=0;
								t_data.buf[t_data.len++]=modelove;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(CLR_LOVEMODE,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==SET_HEAT){  //���ü���
						             hotflag = USART_RX_BUF[3];
								if(hotflag==0) {
								
								}
								else if(hotflag==128){
								

								}
								else if(hotflag==255){
								

								}
                                          			t_data.len=0;
  								t_data.buf[t_data.len++]= hotflag;
  								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
  								pushlongdata(SET_HEAT,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==GET_HEAT){  //��ȡ��ȡ����״̬
                                          						t_data.len=0;
								t_data.buf[t_data.len++]= hotflag;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_HEAT,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==SET_STRENGTH){  //����ǿ��
						             strengthflag = USART_RX_BUF[3];
								if(strengthflag==0){
									
								}
								else if(strengthflag==1){
									
								}
								else if(strengthflag==2){
									
								}
								else if(strengthflag==3){
									
								}
                                          		t_data.len=0;
  								t_data.buf[t_data.len++]= strengthflag;
  								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
  								pushlongdata(SET_STRENGTH,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==GET_STRENGTH){  //��ȡ��״̬
                               						t_data.len=0;
								t_data.buf[t_data.len++]= strengthflag;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_STRENGTH,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==GET_RUNTIME)  //��ʱ����
						{

						                       clear_alarmsec();
											   firsttime=0;
											   alarmflag = USART_RX_BUF[3];
									if(alarmflag==1)  alarmtime = 5;
									else if(alarmflag==2) alarmtime = 10; 
									else if(alarmflag==3) alarmtime = 15;
									else if(alarmflag==4) alarmtime = 20;
									else if(alarmflag==5) alarmtime = 25;
									else if(alarmflag==6)  alarmtime = 30;
									t_data.len=0;
								t_data.buf[t_data.len++]=alarmflag;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_RUNTIME,t_data.buf,t_data.len);
									
						}
						else if(USART_RX_BUF[1]==GET_RUNTIME){  //��ȡ��ʱֵ
								t_data.len=0;
								t_data.buf[t_data.len++]=alarmflag;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_RUNTIME,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==GET_RUNSTAMP)  //��ȡʱ���
						{
                                                     // putchar(get_alarmsec());  //����ʱ���
                        					t_data.len=0;
								t_data.buf[t_data.len++]=get_alarmsec()/256;
								t_data.buf[t_data.len++]=get_alarmsec()%256;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_RUNSTAMP,t_data.buf,t_data.len);	    						
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
						else if(USART_RX_BUF[1]==GET_ALLSTATE){  //��ȡ����״̬
                                                    	t_data.len=0;
								t_data.buf[t_data.len++]= runstate;
								t_data.buf[t_data.len++]= mode;
								t_data.buf[t_data.len++]= modelove;
								t_data.buf[t_data.len++]= alarmflag;
								t_data.buf[t_data.len++]= strengthflag;
								t_data.buf[t_data.len++]= hotflag;								
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_ALLSTATE,t_data.buf,t_data.len);
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
		valve_process(0,0,0,0); 
		step=0xff;
		ui_show(0, 0);
		FOOTHEAT(0);
		KNEEHEAT(0);
	}
	else if(runstate==1){  //����
		FOOTHEAT(feethot);
		KNEEHEAT(kneehot);
		if(again==0){
		t_mode.time = gastime[step][strengthflag];}
		else { t_mode.time = agastime[step][strengthflag];}
		if(get_stepsec()==t_mode.time){
			clear_stepsec();
			t_mode.p++;
			if(t_mode.p>=t_mode.num)t_mode.p=0;
		}
		step = t_mode.buf[t_mode.p];
           switch(step)
           	{
              case FOOT:           //�ŵ�
			PUMP=1;
			valve_process(1,0,0,0); // FOOT ANKLE SLEG BLEG
			//twogasbagrun=0;
			break;
		case ANKLE:         //����
			//t_mode.time = t_downgas.gotime;
			PUMP=1;
			valve_process(0,1,0,0); 
			//twogasbagrun=0;
			break;
              case SLEG:           //С��
			//t_mode.time = t_upgas.gotime;
			PUMP=1;
			valve_process(0,0,1,0); 
			//twogasbagrun=0;
			break;
		case BLEG:         //����
			//t_mode.time = t_downgas.gotime;
			PUMP=1;
			valve_process(0,0,0,1); 
			//twogasbagrun=0;
			break;
              case FOOT_ANKLE:           //�ŵ�+ ����
			//t_mode.time = t_upgas.gotime;
			PUMP=1;
			valve_process(1,1,0,0); 
			//twogasbagrun=0;
			break;
              case FOOT_SLEG:           //�ŵ�+ С��
			//t_mode.time = t_upgas.gotime;
			PUMP=1;
			valve_process(1,0,1,0); 
			//twogasbagrun=0;
			break;
		 case FOOT_BLEG:           //�ŵ�+ ����
			//t_mode.time = t_upgas.gotime;
			PUMP=1;
			valve_process(1,0,0,1); 
			//twogasbagrun=0;
			break;
              case ANKLE_SLEG:           //����+ С��
			//t_mode.time = t_upgas.gotime;
			PUMP=1;
			valve_process(0,1,1,0); 
			//twogasbagrun=0;
			break;
		 case ANKLE_BLEG:           //����+ ����
			//t_mode.time = t_upgas.gotime;
			PUMP=1;
			valve_process(0,1,0,1); 
			//twogasbagrun=0;
			break;
		 case SLEG_BLEG:           //С��+ ����
			//t_mode.time = t_upgas.gotime;
			PUMP=1;
			valve_process(0,0,1,1); 
			//twogasbagrun=0;
			break;
		case FOOT_ANKLE_SLEG:         //�ŵ�+ ����+С��
			//t_mode.time = t_downgas.gotime;
			PUMP=1;
			valve_process(1,1,1,0); 
			//twogasbagrun=0;
			break;
              case FOOT_ANKLE_SLEG_BLEG:            //�ŵ�+ ����+С��+����
			//t_mode.time = t_upgas.gotime;
			PUMP=1;
			valve_process(1,1,1,1); 
			//twogasbagrun=0;
			break;	
              case ALL_OUTGAS:            //�ŵ�+ ����+С��+����
			//t_mode.time = t_upgas.gotime;
			PUMP=0;
			valve_process(0,0,0,0); 
			again=1;
			//twogasbagrun=0;
			break;			
		}		
	}
	else if(runstate==2) { //��ͣ
                 PUMP=0;
		FOOTHEAT(0);
		KNEEHEAT(0);
		ui_show(0, 0);
		HEATLED=0;
		if(getsystimes()-stoptime>=500){
			stoptime=getsystimes();
			POWERLED=~POWERLED;
//			if(stopflag==0){ 
//				stopflag=1;
//				//ui_show(0, 0, 0, 1);
//				}
//			else {
//					stopflag=0;
//				//ui_show(0, 0, 0, 0);
//			}
		}		
	}


}

void alarmtime_process(void)
{
  u8 i;
    if(runstate!=0&&runstate!=3)
      	{
		if(get_alarmsec()-firsttime>=(alarmtime*60)){
			runstate=0;
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
	PUMP=0;
	VALVE1=0;
	VALVE2=0;
	VALVE3=0;
	VALVE4=0;
	//ui_show(0,0, 0, 0);
		//ui_show(mode,strengthflag, 0, 0);  POWERLED=runstate;HEATLED=hotflag;
	wdg_init();
  while(1)
	{
		//�������ô���
		key_process();
//		//�������մ���
		ble_process();

//		//�������
	control_process();
//		�������ʾ
       	show_aip1642(SHOW1,SHOW2);
//		���ж�ʱ
//		alarmtime_process();
		cleardog(1);
	}
}



