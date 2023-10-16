#include <STC89C5xRC.H>

#ifndef	__OLED_H
#define	__OLED_H

typedef unsigned int u16;
typedef unsigned char u8;


#define high 1
#define low 0 
/*************Pin Define***************/
sbit SCL=P0^7;
sbit SDA=P0^6;


void Initial_M096128x64_ssd1306();
void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
void fill_picture(unsigned char fill_Data);
//void Picture();
void IIC_Start();
void IIC_Stop();
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);
void Set_add(unsigned char x, unsigned char y);
void OLED_Clear(void);
void Xianshi_Tupian(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void Xianshi_16X16(unsigned char x, y, N);
void Xianshi_8X16(unsigned char x, y,unsigned char ch[]);


#endif