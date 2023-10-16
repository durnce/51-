#include <STC89C5xRC.H>
  
sbit DA=P2^3;  

float humidity=0.0;
float temperature=0.0;
unsigned char flag=0;
//float old_humidity=0.0;
//float old_temperature=0.0;
  
void delay(unsigned int x_ms)         
{  
    unsigned char i, j;  
  while(x_ms)  
    {   i = 2;  
    j = 239;  
    do  
    {  
        while (--j);  
    } while (--i);  
			x_ms--;  
    }  
}  
  
unsigned char  DHT22_init()  
{  
    unsigned char i;  
    DA=1;  
    DA=0;  
    delay(20);                              //delay 1ms  
    DA=1;  
    while(DA==1);  
    i = 27;while (--i);     //delay 60us  
    if(DA==1) return 1;  
    i = 37;while (--i);         //delay 80us  
    if(DA==0) return 1;  
    while(DA==1); 

		return 0;
}  
  
unsigned char ReadHH()      //读湿度高八位  
{  
    unsigned char i,n,HH=0x00;  
    for(n=0;n<8;n++)  
    {  
        while(DA==0);  
          
        while (DA==1)  
        {  
            i = 17;while (--i); //delau 40us  
            if(DA==1)  
            HH=HH|(0X01<<(7-n));  
        }  
    }     
    return HH;  
}  
      
unsigned char ReadHL()          //读湿度低八位  
{  
    unsigned char i,n,HL=0x00;  
    for(n=0;n<8;n++)  
    {  
        while(DA==0);  
          
        while (DA==1)  
        {  
            i = 17;while (--i); //delau 40us  
            if(DA==1)  
            HL=HL|(0X01<<(7-n));  
        }  
    }     
    return HL;    
}  
  
unsigned char ReadTH()              //读温度高八位  
{  
    unsigned char i,n,TH=0x00;  
    for(n=0;n<8;n++)  
    {  
        while(DA==0);  
          
        while (DA==1)  
        {  
            i = 17;while (--i); //delau 40us  
            if(DA==1)  
            TH=TH|(0X01<<(7-n));  
        }  
    }     
    return TH;    
}  
  
unsigned char ReadTL()          //读温度低八位  
{  
    unsigned char i,n,TL=0x00;  
    for(n=0;n<8;n++)  
    {  
        while(DA==0);  
          
        while (DA==1)  
        {  
            i = 17;while (--i); //delau 40us  
            if(DA==1)  
            TL=TL|(0X01<<(7-n));  
        }  
    }     
    return TL;  
}

unsigned char Read_Lcd()
{
	unsigned char TH;										//温度高8位
	unsigned char TL;										//温度低8位
	unsigned char RH_H;									//湿度高8位
	unsigned char RH_L;									//湿度低8位
	
	DHT22_init();												//初始化
//	old_humidity=humidity;
//	old_temperature=temperature;
	
	RH_H=ReadHH();      //读湿度高八位
	RH_L=ReadHL();      //读湿度高八位
	TH=ReadTH();      //读温度高八位
	TL=ReadTL();      //读温度高八位
	
	
	if(TH & 0x80)												//温度高位判断正负同时置0
  {
      flag = 1;
      TH &= 0x7F;
  }else
	{
		flag=0;
	}	
	humidity=RH_H<<8|RH_L;								//合并16位二进制
	temperature=TH<<8|TL;
	
	humidity/=10;													//转化10进制
	temperature/=10;
	
	
	
//	if((humidity<=25))
//	{
//		humidity=old_humidity;
//	}
//	if(temperature>=80)
//	{
//		temperature=old_temperature;
//	}
	
}


