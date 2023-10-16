#ifndef __DHT22_h__
#define __DHT22_h__

extern float humidity;
extern float temperature;
extern unsigned char flag;



void delay(unsigned int x_ms)	;
unsigned char  DHT22_init();
unsigned char ReadTH();
unsigned char ReadTL();
unsigned char ReadHH();
unsigned char ReadHL();
unsigned char Read_Lcd();

 
#endif