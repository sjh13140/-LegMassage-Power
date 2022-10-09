#include <REGtenxTM52FN8276.h>
#include <intrins.h>

#include "tm52fn8276_bsp_lcd.h"



unsigned char code BIT_MAP[8] = {0x01,0x02,0x04,0x08,0x01,0x02,0x04,0x08};       //��ʾȡģ

unsigned char code TABLE_XFGE[15] = {0x0A,0x00,0x0C,0x04,0x06,0x06,0x0E,0x00,0x0E,0x06,0x00,0x04};
unsigned char code TABLE_ABCD[15] = {0x0F,0x06,0x0B,0x0F,0x06,0x0D,0x0D,0x07,0x0F,0x0F,0x00,0x00};

unsigned char code TABLE_XFGE2[15] = {0x0b,0x01,0x0d,0x05,0x07,0x07,0x0f,0x01,0x0f,0x07,0x01,0x05};
unsigned char code TABLE_ABCD2[15] = {0x0F,0x06,0x0B,0x0F,0x06,0x0D,0x0D,0x07,0x0F,0x0F,0x00,0x00};

unsigned char com_seg_buf[SEG_MAX];

/* LCD seg 0-3����ˢ������*/
void lcd_set_seg1(unsigned char com_idx)
{
	unsigned char bit_seat = BIT_MAP[com_idx];
	
	if(com_seg_buf[0]&bit_seat)        //seg0�ڵ�ƽ�ж�
		SEG0 = 1;
	else
		SEG0 = 0;

	if(com_seg_buf[1]&bit_seat)        //seg1�ڵ�ƽ�ж�
		SEG1 = 1;
	else
		SEG1 = 0;
	
	if(com_seg_buf[2]&bit_seat)        //seg2�ڵ�ƽ�ж�
		SEG2 = 1;
	else
		SEG2 = 0;

	if(com_seg_buf[3]&bit_seat)
		SEG3 = 1;
	else
		SEG3 = 0;

	if(com_seg_buf[4]&bit_seat)
		SEG4 = 1;
	else
		SEG4 = 0;

	if(com_seg_buf[5]&bit_seat)        //seg5�ڵ�ƽ�ж�
		SEG5 = 1;
	else
		SEG5 = 0;
}
/* LED seg4-7����ˢ������*/
void lcd_set_seg2(unsigned char com_idx)
{
	unsigned char bit_seat = BIT_MAP[com_idx];
	
	if(com_seg_buf[0]&bit_seat)         //seg0�ڵ�ƽ�ж�
		SEG0 = 0;
	else
		SEG0 = 1;

	if(com_seg_buf[1]&bit_seat)
		SEG1 = 0;
	else
		SEG1 = 1;
	
	if(com_seg_buf[2]&bit_seat)
		SEG2 = 0;
	else
		SEG2 = 1;

	if(com_seg_buf[3]&bit_seat)
		SEG3 = 0;
	else
		SEG3 = 1;

	if(com_seg_buf[4]&bit_seat)
		SEG4 = 0;
	else
		SEG4 = 1;

	if(com_seg_buf[5]&bit_seat)       //seg5�ڵ�ƽ�ж�
		SEG5 = 0;
	else
		SEG5 = 1;
}

/* LCD com��ˢ��*/
void lcd_set_com(unsigned char com)
{
	switch(com)             //ѡ��ˢ������0-7
	{
		case 0:
			P0_0 = 0;
			P0_1 = 1;
			P0_2 = 1;
			P0_3 = 1;
			P0LOE = 0xe;       //LCD1/2ƫѹ���ʹ��
			break;
		case 1:
			P0_0 = 1;
			P0_1 = 0;
			P0_2 = 1;
			P0_3 = 1;
			P0LOE = 0xd;      //LCD1/2ƫѹ���ʹ��
			break;
		case 2:
			P0_0 = 1;
			P0_1 = 1;
			P0_2 = 0;
			P0_3 = 1;
			P0LOE = 0xb;     //LCD1/2ƫѹ���ʹ��
			break;
		case 3:
			P0_0 = 1;
			P0_1 = 1;
			P0_2 = 1;
			P0_3 = 0;
			P0LOE = 0x7;     //LCD1/2ƫѹ���ʹ��
			break;
		case 4:
			P0_0 = 1;
			P0_1 = 1;
			P0_2 = 1;
			P0_3 = 1;
			P0LOE = 0xe;     //LCD1/2ƫѹ���ʹ��
			break;
		case 5:
			P0_0 = 1;
			P0_1 = 1;
			P0_2 = 1;
			P0_3 = 1;
			P0LOE = 0xd;     //LCD1/2ƫѹ���ʹ��
			break;
		case 6:
			P0_0 = 1;
			P0_1 = 1;
			P0_2 = 1;
			P0_3 = 1;
			P0LOE = 0xb;    //LCD1/2ƫѹ���ʹ��
			break;
		case 7:
			P0_0 = 1;
			P0_1 = 1;
			P0_2 = 1;
			P0_3 = 1;
			P0LOE = 0x7;    //LCD1/2ƫѹ���ʹ��
			break;
		default:
			break;			
	}
}

/*LCDˢ�º���*/
void lcd_reflush(unsigned char com_idx)
{
	lcd_set_com(com_idx);
	if(com_idx <4)                // ����0-3
	{
		lcd_set_seg1(com_idx);
	}
	else                          // ����4-7
	{
		lcd_set_seg2(com_idx);
	}
}

void lcd_wirte_seg(unsigned char seg_idx,unsigned char content_mask,unsigned char content)
{
	unsigned char temp_contenx;

	temp_contenx = com_seg_buf[seg_idx]&(~content_mask);
	content = content & content_mask;
	com_seg_buf[seg_idx] = temp_contenx | content;	
}

/*LCD display*/
void lcd_display_special(unsigned char contenx)
{
	lcd_wirte_seg(0,0xff,contenx);
	lcd_wirte_seg(1,0xff,contenx);
	lcd_wirte_seg(2,0xff,contenx);
	lcd_wirte_seg(3,0xff,contenx);
	lcd_wirte_seg(4,0xff,contenx);
	lcd_wirte_seg(5,0xff,contenx);
}


/**********************************************************************************************************
**�������� ��lcd_display_number
**�������� ����ֱֵ����ʾ
**��    �� ��hundred��ten��one
**��    �� ��None
**********************************************************************************************************/
void lcd_display_number(unsigned char hundred,unsigned char ten,unsigned char one)
{
	lcd_wirte_seg(0,0xff,TABLE_XFGE[hundred]);
	lcd_wirte_seg(1,0xff,TABLE_ABCD[hundred]);
	lcd_wirte_seg(2,0xff,TABLE_XFGE[ten]);
	lcd_wirte_seg(3,0xff,TABLE_ABCD[ten]);
	lcd_wirte_seg(4,0xff,TABLE_XFGE[one]);
	lcd_wirte_seg(5,0xff,TABLE_ABCD[one]);
}


/**********************************************************************************************************
**�������� ��lcd_display_number2
**�������� ���¶���ʾ����
**��    �� ��hundred��ten��one
**��    �� ��None
**********************************************************************************************************/
void lcd_display_number2(unsigned char hundred,unsigned char ten,unsigned char one)
{
	lcd_wirte_seg(0,0xff,TABLE_XFGE[hundred]);
	lcd_wirte_seg(1,0xff,TABLE_ABCD[hundred]);
	lcd_wirte_seg(2,0xff,TABLE_XFGE2[ten]);
	lcd_wirte_seg(3,0xff,TABLE_ABCD2[ten]);
	lcd_wirte_seg(4,0xff,TABLE_XFGE2[one]);
	lcd_wirte_seg(5,0xff,TABLE_ABCD2[one]);
}





