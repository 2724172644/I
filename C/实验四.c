#include<reg51.h>
typedef unsigned char u8;
typedef unsigned int u16;
u8 D[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//显示0~9的值
u8 a,b,b1,b2;
sbit p22=P2^2;
sbit p23=P2^3;
sbit p24=P2^4;

void delay(u16 x)
{
	u16 m,n;
	for(;x>0;x--)
		for(m=12;m>0;m--)
			for(n=1000;n>0;n--);
}
void smg(u8 x,u8 y)
{
	P1=D[x];p22=0;p22=1;p22=0;
	P1=D[y];p23=0;p23=1;p23=0;
}
void traffic(u8 y)
{
	switch(y)
	{
		case 0:P1=0x09;p24=0;p24=1;p24=0;break;
		case 1:P1=0x12;p24=0;p24=1;p24=0;break;
		case 2:P1=0x24;p24=0;p24=1;p24=0;break;
		case 3:P1=0x00;p24=0;p24=1;p24=0;break;
	}
}
void main()
{
	EA=1;	 //全局中断开
	EX0=1;	 //外部中断0开
	IT0=1;	 //跳沿触发中断
	while(1)
	{	
		for(a=10;a>=0;a--)
		{
			smg((a/10),(a%10));
			traffic(0);
			delay(10);
			if(a==0)break;
		}
		for(a=5;a>=0;a--)
		{

			smg((a/10),(a%10));
			traffic(1);
			delay(5);
			traffic(3);
			delay(5);
			if(a==0)break;
		}
		for(a=10;a>=0;a--)
		{
			smg((a/10),(a%10));
			traffic(2);
			delay(10);
			if(a==0)break;
		}
		for(a=5;a>=0;a--)
		{
			smg((a/10),(a%10));
			traffic(1);
			delay(5);
			traffic(3);
			delay(5);
			if(a==0)break;
		}
	}
}
void Int0() interrupt 0
{
	for(a=10;a>=0;a--)
		{
			smg((a/10),(a%10));
			traffic(1);
			delay(5);
			traffic(3);
			delay(5);
			if(a==0)break;
		}	
}
