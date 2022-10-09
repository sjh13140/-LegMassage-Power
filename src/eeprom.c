#include "eeprom.h"


// 偶地址有效 一共128字节 
unsigned char xdata eeprom_address[256]  _at_   0XEE00;             //eeprom指定地址  eeprom_address[256]


/**********************************************************************************************************
**函数名称 ：iap_eeprom_write
**函数描述 ：iap写
**输    入 ：地址、数据地址、长度
**输    出 ：None
**********************************************************************************************************/
void iap_eeprom_write(unsigned char addr, unsigned char *buf, unsigned char len)  //epprom写     
{
	unsigned char i=0,temp_ea=0,temp_lvrpd=0;
	EA = 0;
  IAPTE_2P8_MS; 
  temp_lvrpd = LVRPD;
  //  LVRPD = 1;         //关闭LVR
	for(i = 0;i<len;i++)
	{
	  IAPWE_SFR=0XE2;      //使能iap
		eeprom_address[addr+i*2] = *buf;
		_nop_();
		buf++;
		IAPWE_SFR = 0x00;    //关闭iap
	}
	//LVRPD = 0;           //还原LVR
	IAPTE_DISABLE;
	EA = 1;	
}
/**********************************************************************************************************
**函数名称 ：iap_eeprom_read
**函数描述 ：iap读数据
**输    入 ：None
**输    出 ：None
**********************************************************************************************************/
void iap_eeprom_read(unsigned char addr, unsigned char *buf, unsigned char len)    //eeprom读
{
  unsigned char i=0;
	EA = 0;

	for(i = 0;i<len;i++)
	{
		*buf = eeprom_address[addr+i*2];
		buf++;
	}	
	EA = 1;
}


