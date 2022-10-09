#ifndef __TM52FE8276_BSP_LCD_H__
#define __TM52FE8276_BSP_LCD_H__

#define COM_MAX	4
#define SEG_MAX 6



#define SEG0		P0_6
#define SEG1		P0_7
#define SEG2		P1_2
#define SEG3		P1_3
#define SEG4		P1_6
#define SEG5		P1_7



void lcd_reflush(unsigned char com_idx);

void lcd_wirte_seg(unsigned char seg_idx,unsigned char content_mask,unsigned char content);

void lcd_display_special(unsigned char contenx);

void lcd_display_number(unsigned char hundred,unsigned char ten,unsigned char one);
void lcd_display_number2(unsigned char hundred,unsigned char ten,unsigned char one);
#endif
