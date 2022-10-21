/***********************************************************************************************************
  显示效果：
	通过USB将开发板与电脑，打开电脑中的串口助手，设置对应端口，
	9600波特率，8位数据位，无校验位，1位停止位。向学习板发送任
	意1个字节数据，学习板会回传1个相同字节数据。
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
u8 xdata  mode=0;   //按摩模式 
u8 xdata modelove=0;
u8 xdata eepromflag=0;
u8 xdata eeprombuf[2];
//u8 xdata chrgstate=0;  //0表示拔掉 1表示充电   2表示充满
//u8 xdata powerstate=0;  //电量状态  0:表示电量不足 1:表示电量充足2:表示电量不足
u16 xdata temp=0;  //串口接收存放校验和
u8 xdata alarmtime=15;  //定时时间
u8 xdata alarmflag=1;
u32 xdata firsttime=0;  //获取定时时间的首次计算时间戳
//u8 xdata pushbuf[20]; //发送数组
//u32 xdata ledtime;  //低电量闪烁时间的首次计算时间戳
u8 xdata runstate=0;  // 0:停止  1:运行 2:暂停 3:充电
u8 xdata step=0xff; //模式运行步骤
u32 xdata steptimes=0; //模式运行时间计算
u8 xdata kneehot;
u8 xdata feethot=0; //加热片参数
u8 xdata kneelast;
u8 xdata feetlast=0; //加热片参数
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
	tempbuf[0] = headpara; //协议头
       tempbuf[1] = a;   //功能字
	tempbuf[2] = len;  //数据长度
	for(i=0;i<len;i++){
		sum=sum+buf[i];
		tempbuf[3+i] =buf[i];
	}
	tempbuf[3+len] = sum/256;  //校验位
	tempbuf[3+len+1] = sum%256;
	tempbuf[3+len+2] = endpara;  //#  协议尾
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


//按键扫描
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

//按键执行

void key_process(void)
{
  u8 key;
//  u8 i;
	key = key_scan();
	if(key==0)return;
	if(key==KEY1SHORT){  //自动
		mode++;
		if(mode>5)mode=1;
		mode_process();

	}
	else if(key==KEY2SHORT){//局部
		if(mode<=5)mode=6;
		else {
                     mode++;
			if(mode>8)mode=6;
		}
		mode_process();
	}
	else if(key==KEY3LONG){  //开关
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
	else if(key==KEY3SHORT){ //开关
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
	else if(key==KEY4SHORT){   //强度 
		strengthflag++;
		if(strengthflag>4)strengthflag=1;
	}
	else if(key==KEY5SHORT){  //加热 
               if(hotflag==0) {
			kneehot=kneelast;   //膝盖加热
			feethot=feetlast;  //足底加热
			hotflag=5;     //加热状态
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
//蓝牙传输数据处理
void ble_process(void)
{
		u8 i;
	   
      if(USART_RX_STA&0x80)           //  0                     1                   2                       3                4                     5
	  {
	    //先处理数据校验    协议头    功能字   数据长度      数据     校验位    协议尾
	       bsp_delay_ms(200);
		USART_RX_STA= USART_RX_STA&0x7f;
		if( USART_RX_BUF[0]==headpara){
				if(USART_RX_BUF[2]==USART_RX_STA-4)  //先判断数据长度对不对
				{
					for(i=0;i<(USART_RX_STA-4);i++)
					{
						temp =temp+USART_RX_BUF[3+i];
					}
					if(temp==USART_RX_BUF[USART_RX_STA-1]) //再判断校验位对不对
					{
					       temp=0;
						if(USART_RX_BUF[1]==SET_RUNSTATE)  //运行状态
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
						else if(USART_RX_BUF[1]==GET_RUNSTATE){  //获取运行状态
								t_data.len=0;
								t_data.buf[t_data.len++]=runstate;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_RUNSTATE,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==SET_MODE)  //模式
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
						else if(USART_RX_BUF[1]==GET_MODE){  //获取模式状态
								t_data.len=0;
								t_data.buf[t_data.len++]=mode;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_MODE,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==SET_LOVEMODE)  //添加心动模式
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
						else if(USART_RX_BUF[1]==GET_LOVEMODE){  //获取收藏
                                                    					t_data.len=0;
								t_data.buf[t_data.len++]=modelove;
			
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_LOVEMODE,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==CLR_LOVEMODE)  //删除心动模式
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
						else if(USART_RX_BUF[1]==SET_HEAT){  //设置加热
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
						else if(USART_RX_BUF[1]==GET_HEAT){  //获取获取加热状态
                                          						t_data.len=0;
								t_data.buf[t_data.len++]= hotflag;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_HEAT,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==SET_STRENGTH){  //设置强度
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
						else if(USART_RX_BUF[1]==GET_STRENGTH){  //获取震动状态
                               						t_data.len=0;
								t_data.buf[t_data.len++]= strengthflag;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_STRENGTH,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==GET_RUNTIME)  //定时设置
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
						else if(USART_RX_BUF[1]==GET_RUNTIME){  //获取定时值
								t_data.len=0;
								t_data.buf[t_data.len++]=alarmflag;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_RUNTIME,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==GET_RUNSTAMP)  //获取时间戳
						{
                                                     // putchar(get_alarmsec());  //发送时间戳
                        					t_data.len=0;
								t_data.buf[t_data.len++]=get_alarmsec()/256;
								t_data.buf[t_data.len++]=get_alarmsec()%256;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_RUNSTAMP,t_data.buf,t_data.len);	    						
						}
						else if(USART_RX_BUF[1]==RST_SYS){  //重启
								t_data.len=0;
								t_data.buf[t_data.len++]=0x01;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(RST_SYS,t_data.buf,t_data.len);
							   while(1);
						}
						else if(USART_RX_BUF[1]==GET_VER){  //获取程序版本
								t_data.len=0;
								t_data.buf[t_data.len++]= codeverion;
								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(RST_SYS,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==GET_ALLSTATE){  //获取多种状态
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
					else{  //校验和不对
							temp=0;
							for(i=0;i< USART_RX_STA;i++)USART_RX_BUF[i]=0;
							USART_RX_STA=0;
         						t_data.len=0;
  								t_data.buf[t_data.len++]=0X01;
  								for(i=0;i<6-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
  								pushlongdata(ERR_DATA,t_data.buf,t_data.len);
					}
				} 
				else{   //数据长度不对
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
	if(runstate==0){   //关机
		PUMP=0;
		valve_process(0,0,0,0); 
		step=0xff;
		ui_show(0, 0);
		FOOTHEAT(0);
		KNEEHEAT(0);
	}
	else if(runstate==1){  //开机
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
              case FOOT:           //脚底
			PUMP=1;
			valve_process(1,0,0,0); // FOOT ANKLE SLEG BLEG
			//twogasbagrun=0;
			break;
		case ANKLE:         //脚踝
			//t_mode.time = t_downgas.gotime;
			PUMP=1;
			valve_process(0,1,0,0); 
			//twogasbagrun=0;
			break;
              case SLEG:           //小腿
			//t_mode.time = t_upgas.gotime;
			PUMP=1;
			valve_process(0,0,1,0); 
			//twogasbagrun=0;
			break;
		case BLEG:         //大腿
			//t_mode.time = t_downgas.gotime;
			PUMP=1;
			valve_process(0,0,0,1); 
			//twogasbagrun=0;
			break;
              case FOOT_ANKLE:           //脚底+ 脚踝
			//t_mode.time = t_upgas.gotime;
			PUMP=1;
			valve_process(1,1,0,0); 
			//twogasbagrun=0;
			break;
              case FOOT_SLEG:           //脚底+ 小腿
			//t_mode.time = t_upgas.gotime;
			PUMP=1;
			valve_process(1,0,1,0); 
			//twogasbagrun=0;
			break;
		 case FOOT_BLEG:           //脚底+ 大腿
			//t_mode.time = t_upgas.gotime;
			PUMP=1;
			valve_process(1,0,0,1); 
			//twogasbagrun=0;
			break;
              case ANKLE_SLEG:           //脚踝+ 小腿
			//t_mode.time = t_upgas.gotime;
			PUMP=1;
			valve_process(0,1,1,0); 
			//twogasbagrun=0;
			break;
		 case ANKLE_BLEG:           //脚踝+ 大腿
			//t_mode.time = t_upgas.gotime;
			PUMP=1;
			valve_process(0,1,0,1); 
			//twogasbagrun=0;
			break;
		 case SLEG_BLEG:           //小腿+ 大腿
			//t_mode.time = t_upgas.gotime;
			PUMP=1;
			valve_process(0,0,1,1); 
			//twogasbagrun=0;
			break;
		case FOOT_ANKLE_SLEG:         //脚底+ 脚踝+小腿
			//t_mode.time = t_downgas.gotime;
			PUMP=1;
			valve_process(1,1,1,0); 
			//twogasbagrun=0;
			break;
              case FOOT_ANKLE_SLEG_BLEG:            //脚底+ 脚踝+小腿+大腿
			//t_mode.time = t_upgas.gotime;
			PUMP=1;
			valve_process(1,1,1,1); 
			//twogasbagrun=0;
			break;	
              case ALL_OUTGAS:            //脚底+ 脚踝+小腿+大腿
			//t_mode.time = t_upgas.gotime;
			PUMP=0;
			valve_process(0,0,0,0); 
			again=1;
			//twogasbagrun=0;
			break;			
		}		
	}
	else if(runstate==2) { //暂停
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
**函数名称 ：main
**函数描述 ：主函数
**输    入 ：None
**输    出 ：None
**********************************************************************************************************/
void main(void)
{

	bsp_clock_init();     //系统快钟14.7456M div 2
	uart1_timer2_init();  //uart1_timer2初始化
	tim0_mode1_init();
	tim1_mode1_init(); 
	pwm0_init();
	pwm1_init();
	gpio_output_init();
	input_init();
	ct1642_gpio_init();
	EA = 1;               //总中断允许
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
		//按键设置处理
		key_process();
//		//蓝牙接收处理
		ble_process();

//		//输出控制
	control_process();
//		数码管显示
       	show_aip1642(SHOW1,SHOW2);
//		运行定时
//		alarmtime_process();
		cleardog(1);
	}
}



