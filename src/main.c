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
#define buflen 10
#define KEYTIME 1000

#define foot_gogas_L1 9                                      /*    脚底    */
#define foot_gogas_L2 11
#define foot_gogas_L3 15
#define foot_gogas_L4 17

#define foot_again_gogas_L1 5                            /*    脚底泄气后充气    */
#define foot_again_gogas_L2 10
#define foot_again_gogas_L3 15
#define foot_again_gogas_L4 20

#define ankle_gogas_L1 9						   /*    脚踝    */
#define ankle_gogas_L2 11
#define ankle_gogas_L3 15
#define ankle_gogas_L4 17

#define ankle_again_gogas_L1 5				  /*    脚踝泄气后充气    */
#define ankle_again_gogas_L2 10
#define ankle_again_gogas_L3 15
#define ankle_again_gogas_L4 20

#define sleg_gogas_L1 11						 /*   小腿    */
#define sleg_gogas_L2 23
#define sleg_gogas_L3 26
#define sleg_gogas_L4 28

#define sleg_again_gogas_L1 5				 /*    小腿   泄气后充气    */
#define sleg_again_gogas_L2 10
#define sleg_again_gogas_L3 15
#define sleg_again_gogas_L4 20

#define bleg_gogas_L1 14						 /*   大腿    */
#define bleg_gogas_L2 17
#define bleg_gogas_L3 20
#define bleg_gogas_L4 22

#define bleg_again_gogas_L1 5				 /*    大腿   泄气后充气    */
#define bleg_again_gogas_L2 10
#define bleg_again_gogas_L3 15
#define bleg_again_gogas_L4 20

#define foot_ankle_gogas_L1 11				/*    脚底   脚踝 */
#define foot_ankle_gogas_L2 17
#define foot_ankle_gogas_L3 21
#define foot_ankle_gogas_L4 23

#define foot_sleg_gogas_L1 18				/*    脚底   小腿 */
#define foot_sleg_gogas_L2 20
#define foot_sleg_gogas_L3 22
#define foot_sleg_gogas_L4 26

#define foot_bleg_gogas_L1 17				/*    脚底   大腿 */
#define foot_bleg_gogas_L2 27
#define foot_bleg_gogas_L3 32
#define foot_bleg_gogas_L4 34

#define ankle_sleg_gogas_L1 11				   /*    脚踝   小腿   */
#define ankle_sleg_gogas_L2 16
#define ankle_sleg_gogas_L3 20
#define ankle_sleg_gogas_L4 23

#define ankle_bleg_gogas_L1 18				  /*    脚踝    大腿   */
#define ankle_bleg_gogas_L2 27
#define ankle_bleg_gogas_L3 35
#define ankle_bleg_gogas_L4 40

#define sleg_bleg_gogas_L1 21				 /*   小腿   大腿     */
#define sleg_bleg_gogas_L2 27
#define sleg_bleg_gogas_L3 36
#define sleg_bleg_gogas_L4 41

#define foot_ankle_sleg_gogas_L1 10
#define foot_ankle_sleg_gogas_L2 15
#define foot_ankle_sleg_gogas_L3 20
#define foot_ankle_sleg_gogas_L4 25

#define foot_ankle_sleg_bleg_gogas_L1 23       /*    脚底   脚踝小腿   大腿*/
#define foot_ankle_sleg_bleg_gogas_L2 35
#define foot_ankle_sleg_bleg_gogas_L3 40
#define foot_ankle_sleg_bleg_gogas_L4 47

#define foot_ankle_sleg_bleg_again_gogas_L1 5      	/*    脚底   脚踝小腿   大腿泄气后二次充气*/
#define foot_ankle_sleg_bleg_again_gogas_L2 10
#define foot_ankle_sleg_bleg_again_gogas_L3 15
#define foot_ankle_sleg_bleg_again_gogas_L4 20

#define foot_ankle_sleg_bleg_outgas_L1 4                /*    脚底   脚踝小腿   大腿泄气*/
#define foot_ankle_sleg_bleg_outgas_L2 4
#define foot_ankle_sleg_bleg_outgas_L3 4
#define foot_ankle_sleg_bleg_outgas_L4 4


#define tempL3 255
#define tempL2 230
#define tempL1 200
u8 code gastime[16][5]={
	{0,foot_ankle_sleg_bleg_outgas_L1, foot_ankle_sleg_bleg_outgas_L2, foot_ankle_sleg_bleg_outgas_L3, foot_ankle_sleg_bleg_outgas_L4},
	{1,foot_gogas_L1, foot_gogas_L2, foot_gogas_L3, foot_gogas_L4},                
	{2,ankle_gogas_L1, ankle_gogas_L2, ankle_gogas_L3, ankle_gogas_L4},
	{3,foot_ankle_gogas_L1, foot_ankle_gogas_L2, foot_ankle_gogas_L3, foot_ankle_gogas_L4},
	{4,sleg_gogas_L1, sleg_gogas_L2, sleg_gogas_L3, sleg_gogas_L4},
	{5,foot_sleg_gogas_L1,  foot_sleg_gogas_L2,  foot_sleg_gogas_L3,  foot_sleg_gogas_L4},
	{6,ankle_sleg_gogas_L1, ankle_sleg_gogas_L2, ankle_sleg_gogas_L3, ankle_sleg_gogas_L4},
	{7,foot_ankle_sleg_gogas_L1, foot_ankle_sleg_gogas_L2, foot_ankle_sleg_gogas_L3, foot_ankle_sleg_gogas_L4},
	{8,bleg_gogas_L1, bleg_gogas_L2, bleg_gogas_L3,bleg_gogas_L4},
	{9,foot_bleg_gogas_L1, foot_bleg_gogas_L2, foot_bleg_gogas_L3,foot_bleg_gogas_L4},
	{10,ankle_bleg_gogas_L1, ankle_bleg_gogas_L2, ankle_bleg_gogas_L3, ankle_bleg_gogas_L4},
	{11,0,0,0,0},
	{12,sleg_bleg_gogas_L1, sleg_bleg_gogas_L2, sleg_bleg_gogas_L3, sleg_bleg_gogas_L4},
	{13,0,0,0,0},
	{14,0,0,0,0},
	{15,foot_ankle_sleg_bleg_gogas_L1, foot_ankle_sleg_bleg_gogas_L2, foot_ankle_sleg_bleg_gogas_L3, foot_ankle_sleg_bleg_gogas_L4},     		
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
	u8 buf[buflen];
}DATA_T;
typedef enum TIME_ENUM{
   	SET_RUNSTATE=1,
	  GET_RUNSTATE,
	  SET_MODE,
	  GET_MODE,
	  SET_LOVEMODE,
	  GET_LOVEMODE,
	  CLR_LOVEMODE,
	  SET_FOOTHOT,
	  GET_FOOTHOT,
	  SET_KNEEHOT,
	  GET_KNEEHOT,
	  SET_STRENGTH,
	  GET_STRENGTH,
	  SET_RUNTIME,
	  GET_RUNTIME,
	  GET_RUNSTAMP,
	  RST_SYS,
	  GET_VER,
	  GET_ALLSTATE,
	  SET_CUSTOM,
		GET_CUSTOM,
	  GET_GASSTATE,
	  ERR_DATA=0XEF
}TIME_E;

typedef enum BODY_ENUM{
	ALL_OUTGAS=0,
	FOOT=1,   
	ANKLE=2,    
	FOOT_ANKLE=3, 
	SLEG=4,
	FOOT_SLEG=5,  
	ANKLE_SLEG=6,
	FOOT_ANKLE_SLEG=7,
	BLEG=8,                                                   
	FOOT_BLEG=9,						 
	ANKLE_BLEG=10,				
	SLEG_BLEG=12,				
	FOOT_ANKLE_SLEG_BLEG=15  		
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
u8 xdata alarmflag=3;
u32 xdata firsttime=0;  //获取定时时间的首次计算时间戳
u32 xdata alarmtimetemp;
//u8 xdata pushbuf[20]; //发送数组
//u32 xdata ledtime;  //低电量闪烁时间的首次计算时间戳
u8 xdata runstate=0;  // 0:停止  1:运行 2:暂停 3:充电
u8 xdata runstate_temp=0;
u8 xdata step=0x80; //模式运行步骤
u32 xdata steptimes=0; //模式运行时间计算
u8 xdata kneepara;
u8 xdata footpara=0; //加热片参数
//u8 xdata kneelast;
//u8 xdata feetlast=0; //加热片参数
u8 xdata footflag=0;
u8 xdata kneeflag=0;
u8 xdata footlastflag=2;
u8 xdata kneelastflag=2;

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
u8 xdata custombuf[10]={FOOT,ANKLE,SLEG,BLEG,FOOT_ANKLE,ANKLE_SLEG,SLEG_BLEG,FOOT_SLEG,ANKLE_BLEG,FOOT_BLEG};
u8 xdata foot_3min_flag=0;
u8 xdata knee_3min_flag=0;
u8 xdata foot_step=0;
u8 xdata knee_step=0;
u32 xdata end_foottimes;
u32 xdata end_kneetimes;
u32 xdata head_foottimes;
u32 xdata head_kneetimes;
void ui_show(u8 para1,u8 para2)
{
	SHOW1=para1;
	SHOW2=para2;
}
void pushlongdata(u8 a,u8 *buf,u8 len) 
{
      u8 i=0;
	u16 sum=0;
	u8 tempbuf[16];
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
	if(para1==0){
		FOOTHEAT=0;	
	}
	else if(para1==1||para1==2) {
		if(foot_3min_flag==0) {
			end_foottimes = 180; //180
		}
		switch(foot_step) {
			case 0:
				FOOTHEAT=1;
				if(get_footsec()-head_foottimes>=end_foottimes) {
					if(foot_3min_flag==0){
						foot_3min_flag=1;		
					}
					end_foottimes = 5;
					head_foottimes=get_footsec();
					foot_step = 1;
				}
			break;
			case 1:
				FOOTHEAT=0;
				if(get_footsec()-head_foottimes>=end_foottimes) {
					if(para1==1)end_foottimes= 5;
					else if(para1==2)end_foottimes= 10;
					head_foottimes=get_footsec();
					foot_step = 0;
					
				}
			break;
		}
	}
	else if(para1==3){
		FOOTHEAT=1;
	}
	
	if(para2==0){
		KNEEHEAT=0;	
	}
	else if(para2==1||para2==2) {
		if(knee_3min_flag==0) {
			end_kneetimes = 180; // 3*60*500 
		}
		switch(knee_step) {
			case 0:
				KNEEHEAT=1;
				if(get_kneesec()-head_kneetimes>=end_kneetimes) {
					if(knee_3min_flag==0){
						knee_3min_flag=1;		
					}
					end_kneetimes = 5;
					head_kneetimes=get_kneesec();
					knee_step = 1;
				}
			break;
			case 1:
				KNEEHEAT=0;
				if(get_kneesec()-head_kneetimes>=end_kneetimes)  {
					if(para2==1)end_kneetimes=5;
					else if(para2==2)end_kneetimes=10;
					head_kneetimes=get_kneesec();
					knee_step = 0;
					
				}
			break;
		}
	}
	else {
		KNEEHEAT=1;
	}
}
void mode_process()
{
	u8 i;
	switch(mode){
	case 1:
		t_mode.buf[0] = FOOT;
		t_mode.buf[1] = ANKLE;
		t_mode.buf[2] = SLEG;
		t_mode.buf[3] = BLEG;
		t_mode.num = 4;
		//heat_process(tempL4,tempL4);
		//t_mode.p = 0;
		strengthflag = 2;   //力度2档
//		footpara = tempL2;   //温度2档
//		kneepara=tempL2;     //温度2档
		footflag = 2;
		kneeflag=2;
		footlastflag =footflag;
		kneelastflag = kneeflag;
		break;
	case 2:
		t_mode.buf[0] = FOOT;
		t_mode.buf[1] = FOOT_ANKLE;
		t_mode.buf[2] = ANKLE_SLEG;
		t_mode.buf[3] = SLEG_BLEG;
		t_mode.num = 4;
		//heat_process(tempL4,tempL4);
		//t_mode.p = 0;
		strengthflag = 2;   //力度2档
//		footpara = tempL2;   //温度2档
//		kneepara=tempL2;     //温度2档
		footflag = 2;
		kneeflag=2;
		footlastflag =footflag;
		kneelastflag = kneeflag;
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
		strengthflag = 2;   //力度2档
//		footpara = tempL2;   //温度2档
//		kneepara=tempL2;     //温度2档
		footflag = 2;
		kneeflag=2;
		footlastflag =footflag;
		kneelastflag = kneeflag;
		break;
	case 4:
		t_mode.buf[0]=FOOT_ANKLE_SLEG_BLEG;
		t_mode.buf[1]=ALL_OUTGAS;
		t_mode.num = 2;
		strengthflag = 2;   //力度2档
//		footpara = tempL2;   //温度2档
//		kneepara=tempL2;     //温度2档
		footflag = 2;
		kneeflag=2;
		footlastflag =footflag;
		kneelastflag = kneeflag;
		//heat_process(tempL4,tempL4);
		//t_mode.p = 0;
		break;
	case 5:
		for(i=0;i<10;i++)
		t_mode.buf[i]=custombuf[i];
		t_mode.num = 10;
		
		strengthflag = 2;   //力度2档
//		footpara = tempL2;   //温度2档
//		kneepara=tempL2;     //温度2档
		footflag = 2;
		kneeflag=2;
		footlastflag =footflag;
		kneelastflag = kneeflag;
		break;
	case 6:
		t_mode.buf[0]=FOOT_ANKLE;
		t_mode.buf[1]=ALL_OUTGAS;
		t_mode.num = 2;
		//heat_process(tempL4,tempL4);
		//t_mode.p = 0;
		strengthflag = 2;   //力度2档
//		footpara = 0;   //温度2档
//		kneepara=0;     //温度2档
		footflag = 0;
		kneeflag=0;
		break;
	case 7:
		t_mode.buf[0]=SLEG;
		t_mode.buf[1]=ALL_OUTGAS;
		t_mode.num = 2;
		//t_mode.p = 0;
//		footpara = 0;   //温度2档
//		kneepara=0;     //温度2档
		footflag = 0;
		kneeflag=0;
		break;
	case 8:
		t_mode.buf[0]=BLEG;
		t_mode.buf[1]=ALL_OUTGAS;
		t_mode.num = 2;
		//heat_process(tempL4,tempL4);
		//t_mode.p = 0;
//		footpara = 0;   //温度2档
//		kneepara=0;     //温度2档
		footflag = 0;
		kneeflag=0;
		break;
	}

		again=0;  //非充放标志
		if(step&t_mode.buf[0]==0)clear_stepsec();
		t_mode.p=0;
		step=t_mode.buf[t_mode.p];
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
 u8 i;
	key = key_scan();
	if(key==0)return;
	if(key==KEY1SHORT){  //自动
		mode++;
		if(mode>5)mode=1;
		mode_process();
		t_data.len=0;
		t_data.buf[t_data.len++]=runstate;
		t_data.buf[t_data.len++]=mode;
		for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
		pushlongdata(SET_MODE,t_data.buf,t_data.len);
	}
	else if(key==KEY2SHORT){//局部
		if(mode<=5)mode=6;
		else {
                     mode++;
			if(mode>8)mode=6;
		}
		mode_process();
		t_data.len=0;
		t_data.buf[t_data.len++]=runstate;
		t_data.buf[t_data.len++]=mode;
		for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
		pushlongdata(SET_MODE,t_data.buf,t_data.len);
	}
	else if(key==KEY3LONG){  //开关
			if(runstate==0){   //关机的时候进行开机
				runstate=1;
				mode = modelove;
				clear_stepsec();  //开机清0 ，不能删除  不然开机后模式1会直接运行脚踝
				mode_process();
				firsttime=0;
				clear_alarmsec();
				foot_3min_flag=0;
				knee_3min_flag=0;
				set_footsec(0);
				set_kneesec(0);
				head_foottimes=get_footsec();
				head_kneetimes=get_kneesec();
				foot_step=0;
				knee_step=0;
			}
			else if(runstate==1||runstate==2){
				runstate=0;
				footflag = 0;
				kneeflag=0;
				strengthflag=0;
				mode=0;
			}
			runstate_temp = runstate;
		      t_data.len=0;
			t_data.buf[t_data.len++]= runstate;
			t_data.buf[t_data.len++]= mode;
			t_data.buf[t_data.len++]= modelove;
			t_data.buf[t_data.len++]= alarmflag;
			t_data.buf[t_data.len++]= strengthflag;
			t_data.buf[t_data.len++]= footflag;	
			t_data.buf[t_data.len++]= kneeflag;
			for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
			pushlongdata(GET_ALLSTATE,t_data.buf,t_data.len);	
	}
	else if(key==KEY3SHORT){ //开关
		if(runstate==1){
			runstate=2;
			stoptime=getsystimes();
	      t_data.len=0;
		t_data.buf[t_data.len++]= runstate;
		t_data.buf[t_data.len++]= mode;
		t_data.buf[t_data.len++]= modelove;
		t_data.buf[t_data.len++]= alarmflag;
		t_data.buf[t_data.len++]= 0;
		t_data.buf[t_data.len++]= 0;	
		t_data.buf[t_data.len++]= 0;
		}
		else if(runstate==2){  //
			runstate = 1;
		      t_data.len=0;
		t_data.buf[t_data.len++]= runstate;
		t_data.buf[t_data.len++]= mode;
		t_data.buf[t_data.len++]= modelove;
		t_data.buf[t_data.len++]= alarmflag;
		t_data.buf[t_data.len++]= strengthflag;
		t_data.buf[t_data.len++]= footflag;	
		t_data.buf[t_data.len++]= kneeflag;
		}
		runstate_temp = runstate;

		for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
		pushlongdata(GET_ALLSTATE,t_data.buf,t_data.len);	
	}
	else if(key==KEY4SHORT){   //强度 
		strengthflag++;
		if(strengthflag>4)strengthflag=1;
			t_data.len=0;
					t_data.buf[t_data.len++]=strengthflag;
					for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
					pushlongdata(SET_STRENGTH,t_data.buf,t_data.len);
	}
	else if(key==KEY5SHORT){  //加热 
               if(footflag==0&&kneeflag==0){   //如果当前状态是关加热 则开启加热
			 footflag = 	footlastflag;
			kneeflag = kneelastflag ;
			foot_3min_flag=0;
			knee_3min_flag=0;
			set_footsec(0);
			set_kneesec(0);
			head_foottimes=get_footsec();
			head_kneetimes=get_kneesec();
			foot_step=0;
			knee_step=0;
			t_data.len=0;
			t_data.buf[t_data.len++]=footflag;
			for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
			pushlongdata(SET_FOOTHOT,t_data.buf,t_data.len);
			t_data.len=0;
			t_data.buf[t_data.len++]=kneeflag;
			for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
			pushlongdata(SET_KNEEHOT,t_data.buf,t_data.len);
			
	        }
	        else {   //如果当前状态是开加热 则关闭加热
			footlastflag = footflag ;
			kneelastflag = kneeflag ;
			footflag =0;
			kneeflag =0;
			t_data.len=0;
			t_data.buf[t_data.len++]=footflag;
			for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
			pushlongdata(SET_FOOTHOT,t_data.buf,t_data.len);
			t_data.len=0;
			t_data.buf[t_data.len++]=kneeflag;
			for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
			pushlongdata(SET_KNEEHOT,t_data.buf,t_data.len);
		}
	}
	ui_show(mode,strengthflag); 
	POWERLED=runstate;
	HEATLED=footflag|kneeflag;
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

									runstate=USART_RX_BUF[3];
									if(runstate_temp==0) {
										clear_alarmsec();
										firsttime = get_alarmsec();
										mode =modelove;
										mode_process();
										foot_3min_flag=0;
										knee_3min_flag=0;
										set_footsec(0);
										set_kneesec(0);
										head_foottimes=get_footsec();
										head_kneetimes=get_kneesec();
										foot_step=0;
										knee_step=0;
									}
									runstate_temp = runstate;
									t_data.len=0;
									t_data.buf[t_data.len++]=runstate;
									for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
									pushlongdata(SET_RUNSTATE,t_data.buf,t_data.len);
		
							
						} 
						else if(USART_RX_BUF[1]==GET_RUNSTATE){  //获取运行状态
								t_data.len=0;
								t_data.buf[t_data.len++]=runstate;
								for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_RUNSTATE,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==SET_MODE)  //模式
						{
									mode=USART_RX_BUF[3];
									mode_process();
									t_data.len=0;
									t_data.buf[t_data.len++]=runstate;
									t_data.buf[t_data.len++]=mode;
									for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
									pushlongdata(SET_MODE,t_data.buf,t_data.len);
		
							
						} 
						else if(USART_RX_BUF[1]==GET_MODE){  //获取模式状态
								t_data.len=0;
								t_data.buf[t_data.len++]=mode;
								for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
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
								for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(SET_LOVEMODE,t_data.buf,t_data.len);
							 
						}
						else if(USART_RX_BUF[1]==GET_LOVEMODE){  //获取收藏
                                                    					t_data.len=0;
								t_data.buf[t_data.len++]=modelove;
			
								for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
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
								for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(CLR_LOVEMODE,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==SET_FOOTHOT){  //设置加热
								footlastflag = footflag;
						             footflag = USART_RX_BUF[3];
								if(footlastflag==0) {
									foot_3min_flag=0;
									head_foottimes=get_footsec();
									foot_step=0;
								}
                                          			t_data.len=0;
  								t_data.buf[t_data.len++]= footflag;
  								for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
  								pushlongdata(SET_FOOTHOT,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==GET_FOOTHOT){  //获取获取加热状态
                                          						t_data.len=0;
								t_data.buf[t_data.len++]= footflag;
								for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_FOOTHOT,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==SET_KNEEHOT){  //设置加热
								kneelastflag=kneeflag;
						             kneeflag = USART_RX_BUF[3];
							if(kneelastflag==0) {
								knee_3min_flag=0;
								head_kneetimes=get_kneesec();						
								knee_step=0;
							}
                                      			t_data.len=0;
								t_data.buf[t_data.len++]= kneeflag;
								for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(SET_KNEEHOT,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==GET_KNEEHOT){  //获取获取加热状态
                                          		t_data.len=0;
								t_data.buf[t_data.len++]= kneeflag;
								for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_KNEEHOT,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==SET_STRENGTH){  //设置强度
						             strengthflag = USART_RX_BUF[3];
                                          		t_data.len=0;
  								t_data.buf[t_data.len++]= strengthflag;
  								for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
  								pushlongdata(SET_STRENGTH,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==GET_STRENGTH){  //获取强度状态
                               				t_data.len=0;
								t_data.buf[t_data.len++]= strengthflag;
								for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_STRENGTH,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==SET_RUNTIME)  //定时设置
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
							for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
							pushlongdata(SET_RUNTIME,t_data.buf,t_data.len);
									
						}
						else if(USART_RX_BUF[1]==GET_RUNTIME){  //获取定时值
							t_data.len=0;
							t_data.buf[t_data.len++]=alarmflag;
							for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
							pushlongdata(GET_RUNTIME,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==GET_RUNSTAMP)  //获取时间戳
						{
                                                     // putchar(get_alarmsec());  //发送时间戳
                    					t_data.len=0;
							t_data.buf[t_data.len++]=get_alarmsec()/256;
							t_data.buf[t_data.len++]=get_alarmsec()%256;
							for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
							pushlongdata(GET_RUNSTAMP,t_data.buf,t_data.len);	    						
						}
						else if(USART_RX_BUF[1]==RST_SYS){  //重启
							t_data.len=0;
							t_data.buf[t_data.len++]=0x01;
							for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
							pushlongdata(RST_SYS,t_data.buf,t_data.len);
						   while(1);
						}
						else if(USART_RX_BUF[1]==GET_VER){  //获取程序版本
								t_data.len=0;
								t_data.buf[t_data.len++]= codeversion;
								for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(RST_SYS,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==GET_ALLSTATE){  //获取多种状态 
                                                    	t_data.len=0;
								t_data.buf[t_data.len++]= runstate;
								t_data.buf[t_data.len++]= mode;
								t_data.buf[t_data.len++]= modelove;
								t_data.buf[t_data.len++]= alarmflag;
								t_data.buf[t_data.len++]= strengthflag;
								t_data.buf[t_data.len++]= footflag;	
								t_data.buf[t_data.len++]= kneeflag;
								for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_ALLSTATE,t_data.buf,t_data.len);
						}
						else if(USART_RX_BUF[1]==SET_CUSTOM){
								for(i=0;i<10;i++) {
									custombuf[i]= USART_RX_BUF[3+i];
								}
								t_data.len=0;
								t_data.buf[t_data.len++]= 1;
								for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(SET_CUSTOM,t_data.buf,t_data.len);		
						}
						else if(USART_RX_BUF[1]==GET_CUSTOM) {
								t_data.len=0;
								for(i=0;i<sizeof(custombuf);i++){
									t_data.buf[i]=custombuf[i];
								}
								t_data.len = sizeof(custombuf);
								for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
								pushlongdata(GET_CUSTOM,t_data.buf,t_data.len);							
					
						}
						else if(USART_RX_BUF[1]==GET_GASSTATE) {
								t_data.len=0;
  								t_data.buf[t_data.len++]=t_mode.buf[t_mode.p];
  								for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
  								pushlongdata(GET_GASSTATE,t_data.buf,t_data.len);


						}
						for(i=0;i< USART_RX_STA;i++)USART_RX_BUF[i]=0;
						USART_RX_STA=0;
							ui_show(mode,strengthflag); 
							POWERLED=runstate;
							HEATLED=(footflag|kneeflag);
					}
					else{  //校验和不对
							temp=0;
							for(i=0;i< USART_RX_STA;i++)USART_RX_BUF[i]=0;
							USART_RX_STA=0;
         						t_data.len=0;
  								t_data.buf[t_data.len++]=0X01;
  								for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
  								pushlongdata(ERR_DATA,t_data.buf,t_data.len);
					}
				} 
				else{   //数据长度不对
						temp=0;
						for(i=0;i< USART_RX_STA;i++)USART_RX_BUF[i]=0;
						USART_RX_STA=0;
								t_data.len=0;
  								t_data.buf[t_data.len++]=0X00;
  								for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
  								pushlongdata(ERR_DATA,t_data.buf,t_data.len);   
				}
		}
		else 	{
              	                temp=0;
						for(i=0;i< USART_RX_STA;i++)USART_RX_BUF[i]=0;
						USART_RX_STA=0;     
								t_data.len=0;
  								t_data.buf[t_data.len++]=0X02;
  								for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
  								pushlongdata(ERR_DATA,t_data.buf,t_data.len);
		}

		
	  }

}
 #endif
void control_process(void)
{
u8 i;
	if(runstate==0){   //关机
		PUMP=0;                  //关闭气泵
		HEATLED=0;		//关闭加热指示灯
		POWERLED=0;	//关闭运行指示灯
		valve_process(0,0,0,0); //关闭全部气阀
		step=0x80;
		ui_show(0, 0);  //关闭模式和力度指示灯
		heat_process(0, 0);
	}
	else if(runstate==1){  //开机
		heat_process(footflag, kneeflag);
		if(again==0){  //非单独充放气囊标志
			if(mode==2||mode==3||mode==5) {     //双气囊打气状态下减少打气时间
				if(step==FOOT_ANKLE||step==FOOT_SLEG||step==ANKLE_SLEG) {    //不含大腿的双气囊打气
					t_mode.time = gastime[step][strengthflag]-4;
				}
				else if(step==FOOT_BLEG||step==ANKLE_BLEG||step==SLEG_BLEG){  //含大腿的双气囊打气 减少时间应该更多
					t_mode.time = gastime[step][strengthflag]-7;

				}
				else if(step==FOOT||step==ANKLE||step==SLEG||step==BLEG){   //单气囊打气 按正常时间
					t_mode.time = gastime[step][strengthflag];
				}	
			}   
			else {  //MODE = 1 4 6 7 8   该模式下按正常打气时间
				t_mode.time = gastime[step][strengthflag];  //  10
			}
		}
		else {    //again =1    //单独充放气囊标志 泄气完后再次充气时间需要减少
			
			if(step==ALL_OUTGAS) { 
				if(t_mode.buf[0]==BLEG)t_mode.time = gastime[step][strengthflag]+4;  //  大腿泄气8秒  
				else if(t_mode.buf[0]==FOOT_ANKLE_SLEG_BLEG)t_mode.time = gastime[step][strengthflag]+2;   //泄气6秒
				else t_mode.time = gastime[step][strengthflag];   //其他泄气4秒

			}
			else {
				if(step==BLEG)t_mode.time = gastime[step][strengthflag]-8;  //大腿泄完气后少打气6秒
				else t_mode.time = gastime[step][strengthflag]-4;   //其他泄完气后少打气6秒

			}
		}		

		if(get_stepsec()>=t_mode.time){  //  大于10  判断运行步骤的时间是否结束，如果结束则运行下一个步骤
			clear_stepsec();  //0
			t_mode.p++; //  1
			if(t_mode.p>=t_mode.num)t_mode.p=0;
			t_data.len=0;
			t_data.buf[t_data.len++]=t_mode.buf[t_mode.p];
			for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
			pushlongdata(GET_GASSTATE,t_data.buf,t_data.len);
		}
		
		step = t_mode.buf[t_mode.p];  //  12     //获取运行的步骤

           switch(step)
           	{
              case FOOT:           //脚底
			PUMP=1;
			valve_process(1,0,0,0); // FOOT ANKLE SLEG BLEG
			break;
		case ANKLE:         //脚踝

			PUMP=1;
			valve_process(0,1,0,0); 
	
			break;
              case SLEG:           //小腿
			
			PUMP=1;
			valve_process(0,0,1,0); 
			
			break;
		case BLEG:         //大腿
	
			PUMP=1;
			valve_process(0,0,0,1); 
		
			break;
              case FOOT_ANKLE:           //脚底+ 脚踝
		
			PUMP=1;
			valve_process(1,1,0,0); 
		
			break;
              case FOOT_SLEG:           //脚底+ 小腿
			
			PUMP=1;
			valve_process(1,0,1,0); 
			
			break;
		 case FOOT_BLEG:           //脚底+ 大腿
			
			PUMP=1;
			valve_process(1,0,0,1); 
		
			break;
              case ANKLE_SLEG:           //脚踝+ 小腿
		
			PUMP=1;
			valve_process(0,1,1,0); 
		
			break;
		 case ANKLE_BLEG:           //脚踝+ 大腿
		
			PUMP=1;
			valve_process(0,1,0,1); 
		
			break;
		 case SLEG_BLEG:           //小腿+ 大腿
			
			PUMP=1;
			valve_process(0,0,1,1); 
		
			break;
		case FOOT_ANKLE_SLEG:         //脚底+ 脚踝+小腿
		
			PUMP=1;
			valve_process(1,1,1,0); 
		
			break;
              case FOOT_ANKLE_SLEG_BLEG:            //脚底+ 脚踝+小腿+大腿
		
			PUMP=1;
			valve_process(1,1,1,1); 
			
			break;	
              case ALL_OUTGAS:            //脚底+ 脚踝+小腿+大腿
		
			PUMP=0;
			valve_process(0,0,0,0); 
			again=1;
			
			break;			
		}		
	}
	else if(runstate==2) { //暂停
              PUMP=0;
		heat_process(0, 0);
		ui_show(0, 0);
		HEATLED=0;
		if(getsystimes()-stoptime>=500){
			stoptime=getsystimes();
			POWERLED=~POWERLED;
		}		
	}


}

void alarmtime_process(void)
{
  u8 i;
    if(runstate!=0)
      	{
		if(get_alarmsec()-firsttime>=(alarmtime*60)){
			runstate=0;
			t_data.len=0;
			t_data.buf[t_data.len++]=runstate;
			for(i=0;i<buflen-t_data.len;i++)t_data.buf[t_data.len+i]=0;	
			pushlongdata(GET_RUNSTATE,t_data.buf,t_data.len);			
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
	gpio_output_init();
	input_init();
	ct1642_gpio_init();
	EA = 1;               //总中断允许
	iap_eeprom_read(0,eeprombuf,2);
	eepromflag = eeprombuf[0];
	modelove = eeprombuf[1]; 
	if(eepromflag!=0x03){
		eeprombuf[0]=0x03; 
		eeprombuf[1]=0x01; //  0X01
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
	FOOTHEAT=0;
	KNEEHEAT=0;
	wdg_init();
  while(1)
	{

		key_process();
		ble_process();
		control_process();
       	show_aip1642(SHOW1,SHOW2);
		alarmtime_process();
		cleardog(1);
	}
}



