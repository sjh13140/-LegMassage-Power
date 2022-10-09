#include "eeprom.h"


// ż��ַ��Ч һ��128�ֽ� 
unsigned char xdata eeprom_address[256]  _at_   0XEE00;             //eepromָ����ַ  eeprom_address[256]


/**********************************************************************************************************
**�������� ��iap_eeprom_write
**�������� ��iapд
**��    �� ����ַ�����ݵ�ַ������
**��    �� ��None
**********************************************************************************************************/
void iap_eeprom_write(unsigned char addr, unsigned char *buf, unsigned char len)  //eppromд     
{
	unsigned char i=0,temp_ea=0,temp_lvrpd=0;
	EA = 0;
  IAPTE_2P8_MS; 
  temp_lvrpd = LVRPD;
  //  LVRPD = 1;         //�ر�LVR
	for(i = 0;i<len;i++)
	{
	  IAPWE_SFR=0XE2;      //ʹ��iap
		eeprom_address[addr+i*2] = *buf;
		_nop_();
		buf++;
		IAPWE_SFR = 0x00;    //�ر�iap
	}
	//LVRPD = 0;           //��ԭLVR
	IAPTE_DISABLE;
	EA = 1;	
}
/**********************************************************************************************************
**�������� ��iap_eeprom_read
**�������� ��iap������
**��    �� ��None
**��    �� ��None
**********************************************************************************************************/
void iap_eeprom_read(unsigned char addr, unsigned char *buf, unsigned char len)    //eeprom��
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


