#include "../inc/uart.h"
#include "../inc/beep.h"
#include "stdio.h"
#include "stdarg.h"
#define uchar unsigned char
#define uint unsigned int

unsigned char receive_buf[20];
unsigned char i=0;
unsigned char buf=0;


/***********************************************
串行口初始化波特率9600，定时器1，工作方式2  *************************************************/
void serial_init(void)
{ 
PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xCC;		//设定定时初值
	TH1 = 0xCC;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	ES = 1; //打开串口中断
	EA=1;
	TR1 = 1;		//启动定时器1
}
/********************* **************************	   
串行口传送数据	
        传送显示数组各字符给计算机	
*************************************************/	  

void send_byte(unsigned char byte){
		ES=0;
		SBUF =byte;
		while(!TI);
		TI=0;
		ES =1;	
}

void uart_printf(unsigned char *s){
	
	while(*s){

		send_byte(*s++);
	}
}

char putchar(char c){

	send_byte( (unsigned char) c);	
	return (c);

}

/***********************************************
串行中断服务函数	
单片机接收数据，存入table数组	
*************************************************/
void serial() interrupt 4
{

 ES=0;	//关串口中断
 buf = SBUF;

 if( buf == 0x0d ){	//判断是否接收到回车键

 	 receive_buf[i] = '\0';//如果收到回车键，在接收到的字符串末尾加结束符'\0';
	 i = 0;//接收缓存清空
	 //uart_printf(receive_buf);
	 //uart_printf("\n");
	 //send_byte(0x0d); //换行符
	 send_byte(0x0d); //换行符
	 send_byte(0x0a);
	 send_byte('#');
	 //send_byte(hide_box_compare_str(receive_buf,"hide_box"));
	 cmd_update = 1;//标志位：表示接收到新命令

	 if( (hide_box_compare_str(receive_buf,"hide_box")) == TRUE ){	//判断接收到的命令是否是hide_box

		  hide_box_enter = TRUE; //允许进入hide_box模式

	 }else if( (hide_box_compare_str( receive_buf,"hide_box_exit")) == TRUE ){	//判断接收到的命令是否是hide_box_exit

		  hide_box_enter = FALSE;//退出hide_box模式
	 }

 }else if(buf != 0x0a){

 	 receive_buf[i++] = buf;//将接收到的数据存到接收缓冲
	 send_byte(buf); //换行符
 }

 //uart_printf("\r\nRecive is OK!\r\n");
 
 //beep(1);
 RI=0; //软件清除接收中断
 ES=1;//开串口中断

 }