#include "oled.h"
#include "picture.h"	



/**********************************************
//IIC Start
**********************************************/
void IIC_Start()
{
   SCL = high;		
   SDA = high;
   SDA = low;
   SCL = low;
}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{
   SCL = low;
   SDA = low;
   SCL = high;
   SDA = high;
}
/**********************************************
// IIC Write byte
**********************************************/
void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)		
	{
		if(IIC_Byte & 0x80)
		SDA=high;
		else
		SDA=low;
		SCL=high;
		SCL=low;
		IIC_Byte<<=1;
	}
	SDA=1;
	SCL=1;
	SCL=0;
}
/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   Write_IIC_Byte(0x78);            //Slave address,SA0=0
   Write_IIC_Byte(0x00);			//write command
   Write_IIC_Byte(IIC_Command); 
   IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
   IIC_Start();
   Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
   Write_IIC_Byte(0x40);			//write data
   Write_IIC_Byte(IIC_Data);
   IIC_Stop();
}
/********************************************
// fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		Write_IIC_Command(0xb0+m);		//page0-page1
		Write_IIC_Command(0x00);		//low column start address
		Write_IIC_Command(0x10);		//high column start address
		for(n=0;n<132;n++)
			{
				Write_IIC_Data(fill_Data);
			}
	}
}
///******************************************
//// picture显示一张图片
//******************************************/
//void Picture()
//{
//  unsigned char x,y;
//  unsigned int i=0;
//  for(y=0;y<8;y++)
//    {
//      Write_IIC_Command(0xb0+y);
//      Write_IIC_Command(0x0);
//      Write_IIC_Command(0x10);
//      for(x=0;x<132;x++)
//        {
//          Write_IIC_Data(BMP[i++]);
//        }
//    }
//}

/***********************Delay****************************************/
void Delay_50ms(unsigned int Del_50ms)
{
	unsigned int m;
	for(;Del_50ms>0;Del_50ms--)
		for(m=6245;m>0;m--);
}

void Delay_1ms(unsigned int Del_1ms)
{
	unsigned char j;
	while(Del_1ms--)
	{	
		for(j=0;j<123;j++);
	}
}



//坐标设置
void Set_add(unsigned char x, unsigned char y) //x表示列（0~127），y表示页（0~7）
{ 	
	Write_IIC_Command(0xb0+y);                        //设置页地址（0~7）
	Write_IIC_Command(((x&0xf0)>>4)|0x10);             //设置显示位置—列高地址
	Write_IIC_Command((x&0x0f));                        //设置显示位置—列低地址
}   

void Initial_M096128x64_ssd1306()
{
	Delay_1ms(5);
	Write_IIC_Command(0xAE);   //display off
	Write_IIC_Command(0x20);	//Set Memory Addressing Mode	
	Write_IIC_Command(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	Write_IIC_Command(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	Write_IIC_Command(0xc8);	//Set COM Output Scan Direction
	Write_IIC_Command(0x00);//---set low column address
	Write_IIC_Command(0x10);//---set high column address
	Write_IIC_Command(0x40);//--set start line address
	Write_IIC_Command(0x81);//--set contrast control register
	Write_IIC_Command(0xdf);
	Write_IIC_Command(0xa1);//--set segment re-map 0 to 127
	Write_IIC_Command(0xa6);//--set normal display
	Write_IIC_Command(0xa8);//--set multiplex ratio(1 to 64)
	Write_IIC_Command(0x3F);//
	Write_IIC_Command(0xa4);//0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	Write_IIC_Command(0xd3);//-set display offset
	Write_IIC_Command(0x00);//-not offset
	Write_IIC_Command(0xd5);//--set display clock divide ratio/oscillator frequency
	Write_IIC_Command(0xf0);//--set divide ratio
	Write_IIC_Command(0xd9);//--set pre-charge period
	Write_IIC_Command(0x22); //
	Write_IIC_Command(0xda);//--set com pins hardware configuration
	Write_IIC_Command(0x12);
	Write_IIC_Command(0xdb);//--set vcomh
	Write_IIC_Command(0x20);//0x20,0.77xVcc
	Write_IIC_Command(0x8d);//--set DC-DC enable
	Write_IIC_Command(0x14);//
	Write_IIC_Command(0xaf);//--turn on oled panel 
}


//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!
//先选中页，初始位置，然后128列全部清零
void OLED_Clear(void)  
{  
	unsigned char i,n;		    
	for(i=0;i<8;i++)  
	{  
		Write_IIC_Command (0xb0+i); //选中页地址（0~7）
		Write_IIC_Command (0x00);   //选中显示位置—列低地址
		Write_IIC_Command (0x10);   //选中显示位置—列高地址   
		for(n=0;n<128;n++)  //选中所有像素点
		    Write_IIC_Data(0);   //关闭像素点
	} //更新显示
}
 
 
//图片显示函数，显示BMP图片128×64起始点坐标
 
/*  x0、x1:显示数据的列位置；
      x0：数据的初始位置          刚开始在哪一列打印出来
			x1：数据的最后的位置        在哪一列打印结束
		y0、y1：显示的页位置
		  y0：数据的初始页位置（行）；刚开始在哪一行打印出来
			y1:数据的最后的位置（行）   在哪一行打印结束
 
		BMP[]:需要打印的数据
*/
void Xianshi_Tupian(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) 
		y=y1/8;      
  else 
		y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
			Set_add(x0,y);
			for(x=x0;x<x1;x++)
			{      
					Write_IIC_Data(BMP[j++]);	    	
			}
	}
}
 
//16x16显示函数
/***功能描述：显示16*16点阵  显示的坐标（x,y），y为页范围0～7****************************/
void Xianshi_16X16(unsigned char x, y, N)
{
	unsigned char wm=0;
	unsigned int adder=32*N;
	Set_add(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		Write_IIC_Data(F16x16[adder]);
		adder += 1;
	}
	
	Set_add(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		Write_IIC_Data(F16x16[adder]);
		adder += 1;
	} 	  	
}


/* 8X16显示 */
//可以自己找出来数据对应的数组
/*******************功能描述：显示8*16一组标准ASCII字符串	 显示的坐标（x,y），y为页范围0～7****************/
//ch[]:想要输入的数据，会自动在F8X16[]中寻找出来并发送给OLED
void Xianshi_8X16(unsigned char x, y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>120){x=0;y++;}
		
		Set_add(x,y);     //一共两页，第一页
		for(i=0;i<8;i++)
		Write_IIC_Data(F8X16[c*16+i]);
		 
		Set_add(x,y+1);   //一共两页，第二页
		for(i=0;i<8;i++)     
		Write_IIC_Data(F8X16[c*16+i+8]);
		
		x+=8;
		j++;
	}
}






