#include "../inc/i2c.h"
/**********************************************************************************
*
*					i2c初始化函数
*
**********************************************************************************/
void i2c_init(void){
	
	I2C_SCL   = 1;
	I2C_SDA   = 1;
	I2C_ALERT = 1;

}

void Delay1us(unsigned char cnt)		//@16MHz
{
	unsigned char i;

	while(cnt--){
	   i = 3;
	   while (--i);
	}	
	
}
/************************************************************
*
*			I2C START 信号 
*
/************************************************************/
void i2c_start(void){
	
	I2C_SDA = 1;
	Delay1us(1);
	I2C_SCL = 1;
	Delay1us(5);
	I2C_SDA = 0;
	Delay1us(5);
	I2C_SCL = 0;
	Delay1us(2);

}
/************************************************************
*
*			I2C STOP 信号 
*
/************************************************************/
void i2c_stop(void){
	
	I2C_SDA = 0;
	Delay1us(1);
	I2C_SCL = 1;
	Delay1us(5);
	I2C_SDA = 1;
	Delay1us(4);
}
/************************************************************
*
*			I2C 字节写 
*
/************************************************************/
void i2c_byte_write(unsigned char dat){

	unsigned char i =0;

	for( i = 0; i < 8; i++ ){
		
		if((dat<<i) & 0x80){
		  	I2C_SDA=1;
		}else{
			I2C_SDA=0;
		}
		Delay1us(1);
		I2C_SCL = 1;
		Delay1us(5);	
		I2C_SCL = 0;
	}


}
/************************************************************
*
*			I2C 字节读 
*
************************************************************/
unsigned char i2c_byte_read(void){
	 
	unsigned char i =0;
	unsigned char dat=0;

	//I2C_SCL = 0;
	//Delay1us(3);
	I2C_SDA  = 1;

	for( i = 0; i < 8; i++ ){
			
		Delay1us(1);
		I2C_SCL = 0;
		Delay1us(5);
		I2C_SCL = 1;
		Delay1us(3);
		if(I2C_SDA == 1 ){
			dat = (dat<<1) + 1;
		
		}else{
			dat = (dat<<1) + 0;
		}
		Delay1us(2);

	}

	I2C_SCL =0;
	Delay1us(2);

	return dat;

}
/*********************************************************************************************************
*
*			I2C读取ack的应答信号
*	  参数列表：unsigned char ack_no   表示前面几次调用ack的返回结果：0x03 表示前两次调用ack没有得到相应
*     返回列表：unsigned char ack_no   标志到这次调用ack为止，每一次ack的应答结果。
*
*********************************************************************************************************/
unsigned char i2c_ask_read(unsigned char ack_no){
		
	 
	Delay1us(2);
	I2C_SDA = 1;
	Delay1us(2);
	I2C_SCL = 1;
	Delay1us(3);
	if(I2C_SDA == 0){ 
		I2C_SCL = 0;
		Delay1us(2);
		return (ack_no<<1);//表示正常接收到应答
	}else{
		I2C_SCL = 0;
		Delay1us(2);
		return (ack_no<<1)+1 ;//表示正常接收到应答
	
	}
	
}
/********************************************************************************
*
*				 主机写应答信号
*
*
********************************************************************************/
void i2c_ask_write(void){

	//Delay1us(1);
	I2C_SDA = 0;
	Delay1us(3);
	I2C_SCL = 1;
	Delay1us(5);
	I2C_SCL = 0;
	Delay1us(2);

}
/************************************************************
*
*			I2C 写寄存器
*       参数列表：unsigned char i2c_addr 	器件地址
*				  unsigned char reg_addr 	寄存器地址
*				  unsigned int  dat      	待写入的数据
*		返回参数：unsigned char ack_result  ack应答信号标志位，
*											返回0x00表示操作成功，非0x00的从低位到高位，
*											依次代表第1，2，3，4。。调用ack的结果，
*											每一位0表示该次有应答，1表示该次没有应答 
*						
/************************************************************/
unsigned char i2c_write(unsigned char i2c_addr,unsigned char reg_addr,unsigned int dat){

	unsigned char ack_result=0;	

	i2c_addr<<=1; //左移一位，末尾补领，表示执行写操

	i2c_start();  //START信号

	i2c_byte_write(i2c_addr); //写I2C地址
	ack_result = i2c_ask_read(ack_result);

	i2c_byte_write(reg_addr); //写寄存器地址
	ack_result = i2c_ask_read(ack_result);

   	i2c_byte_write( (unsigned char)(dat>>8));//写数据高八位
	ack_result = i2c_ask_read(ack_result);

	i2c_byte_write( (unsigned char)(dat&0x00ff));//写数据低八位
	ack_result = i2c_ask_read(ack_result);

	i2c_stop();//停止

	return ack_result;

}

unsigned char i2c_change_reg_addr(unsigned char i2c_addr , unsigned char reg_addr){

	unsigned char ack_result=0;	

	i2c_addr<<=1; //左移一位，末尾补领，表示执行写操

	i2c_start();  //START信号

	i2c_byte_write(i2c_addr); //写I2C地址
	ack_result = i2c_ask_read(ack_result);

	i2c_byte_write(reg_addr); //写寄存器地址
	ack_result = i2c_ask_read(ack_result);

	i2c_stop();//停止

	return ack_result;

}
/************************************************************
*
*			I2C 读寄存器
*
/************************************************************/
unsigned char i2c_read(unsigned char i2c_addr,unsigned char reg_addr,unsigned int *dat){

	unsigned char ack_result=0;
	*dat = 0;	

	EA=0;

	//i2c_change_reg_addr(i2c_addr,reg_addr);//修改寄存器指针
	//i2c_change_reg_addr(i2c_addr,reg_addr);//修改寄存器指针
	//i2c_change_reg_addr(i2c_addr,reg_addr);//修改寄存器指针
	//i2c_change_reg_addr(i2c_addr,reg_addr);//修改寄存器指针
	//i2c_change_reg_addr(i2c_addr,reg_addr);//修改寄存器指针
	i2c_change_reg_addr(i2c_addr,reg_addr);//修改寄存器指针

	i2c_addr = (i2c_addr<<1) +1;//左移一位，末尾补一，表示读操作

	i2c_start();  //START信号

	i2c_byte_write(i2c_addr); //写I2C地址
	ack_result = i2c_ask_read(ack_result);

   	*dat = (unsigned int)(i2c_byte_read());//读数据高八位
	i2c_ask_write();

	*dat <<= 8;
	*dat |= (unsigned int)(i2c_byte_read());//读数据低八位
	i2c_ask_write();
	
	i2c_stop();//停止

	EA=1;
	return ack_result;

}
