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
  
unsigned char ReadHH()      //��ʪ�ȸ߰�λ  
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
      
unsigned char ReadHL()          //��ʪ�ȵͰ�λ  
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
  
unsigned char ReadTH()              //���¶ȸ߰�λ  
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
  
unsigned char ReadTL()          //���¶ȵͰ�λ  
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
	unsigned char TH;										//�¶ȸ�8λ
	unsigned char TL;										//�¶ȵ�8λ
	unsigned char RH_H;									//ʪ�ȸ�8λ
	unsigned char RH_L;									//ʪ�ȵ�8λ
	
	DHT22_init();												//��ʼ��
//	old_humidity=humidity;
//	old_temperature=temperature;
	
	RH_H=ReadHH();      //��ʪ�ȸ߰�λ
	RH_L=ReadHL();      //��ʪ�ȸ߰�λ
	TH=ReadTH();      //���¶ȸ߰�λ
	TL=ReadTL();      //���¶ȸ߰�λ
	
	
	if(TH & 0x80)												//�¶ȸ�λ�ж�����ͬʱ��0
  {
      flag = 1;
      TH &= 0x7F;
  }else
	{
		flag=0;
	}	
	humidity=RH_H<<8|RH_L;								//�ϲ�16λ������
	temperature=TH<<8|TL;
	
	humidity/=10;													//ת��10����
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


