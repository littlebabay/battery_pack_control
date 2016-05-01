#include "../inc/ina226.h"
#include "../inc/i2c.h"
#include "../inc/uart.h"
#include "../inc/smg.h"
#include "stdio.h"
#include "../inc/main.h"


/******************************************************************************************************
*
*							 写入指定INA226的全部寄存器内容
*
*
*******************************************************************************************************/

void ina226_write_all_reg(unsigned char i2c_addr, ina226_typedef ina226_reg){

	i2c_write( i2c_addr, REG_CONFIG_ADDR, 	  (ina226_reg.config.word)); 
	i2c_write( i2c_addr, REG_SHUNT_ADDR, 	  (ina226_reg.shunt_voltage));
	i2c_write( i2c_addr, REG_BUS_ADDR, 		  (ina226_reg.bus_voltage)); 
	i2c_write( i2c_addr, REG_POWER_ADDR,       (ina226_reg.power)); 
	i2c_write( i2c_addr, REG_CURRENT_ADDR, 	  (ina226_reg.current)); 
	i2c_write( i2c_addr, REG_CALIBRATION_ADDR, (ina226_reg.calibration)); 
	i2c_write( i2c_addr, REG_MASK_ENABLE_ADDR, (ina226_reg.mask_enable.word)); 
	i2c_write( i2c_addr, REG_ALERT_LIMIT_ADDR, (ina226_reg.alert_limit));  

}


void ina226_set_reg(void){
	 
	 ina226_typedef device;

	 //batt2.config.bits.AVG = 5;//256平均
	 device.config.word = 0x4f27; 
	 device.calibration = 512;//设置电池和放电采集器电流寄存器 1mA/bit
	 device.mask_enable.word = (0x01<<10);

	 ina226_write_all_reg(I2C_ADDR_BATT_1,device);
	 ina226_write_all_reg(I2C_ADDR_BATT_2,device);
	 ina226_write_all_reg(I2C_ADDR_BATT_3,device);
	 ina226_write_all_reg(I2C_ADDR_BATT_4,device);
	 ina226_write_all_reg(I2C_ADDR_DISCHARGE,device);

	 device.calibration = 1280;//设置充电采集器电流寄存器 1mA/bit
	 ina226_write_all_reg(I2C_ADDR_CHARGE,device);
}

/******************************************************************************************************
*
*					 读取指定INA226的MASK结果，判断是否转换完成
*
*
*******************************************************************************************************/

unsigned char ina226_read_conversion_flag(unsigned char i2c_addr){

	 unsigned int mask=0;

	 i2c_read( i2c_addr, REG_MASK_ENABLE_ADDR, &mask); 

	 if( mask & 0x08 )return TRUE;
	 else return FALSE;
}

/******************************************************************************************************
*
*							 读取指定INA226的全部寄存器内容
*
*
*******************************************************************************************************/

void  ina226_read_all(unsigned char i2c_addr){
	
	unsigned int config,shunt,bus,power,current,calibration,mask,alert;

	float result_shunt,result_voltage,result_current;
	

	/***********************************取得寄存器的值*************************************************/

	while( 	i2c_read( i2c_addr, REG_ALERT_LIMIT_ADDR, &mask));

	if(mask & 0x08);  else return ;	//如果数据转换成功，继续读取数据， 如果没有转换完成就停止读取数据，并返回

	//while( i2c_read( i2c_addr, REG_CONFIG_ADDR, 	  &config)); 
	//while( 	i2c_read( i2c_addr, REG_SHUNT_ADDR, 	  &shunt));
	while( 	i2c_read( i2c_addr, REG_BUS_ADDR, 		  &bus)); 
	//while( 	i2c_read( i2c_addr, REG_POWER_ADDR,       &power)); 
	//while( 	i2c_read( i2c_addr, REG_CURRENT_ADDR, 	  &current)); 
	//while( 	i2c_read( i2c_addr, REG_CALIBRATION_ADDR, &calibration)); 
	//while( 	i2c_read( i2c_addr, REG_MASK_ENABLE_ADDR, &mask)); 
	//while( 	i2c_read( i2c_addr, REG_ALERT_LIMIT_ADDR, &alert));

	/***********************************处理数据结果*************************************************/

	/*
	if(shunt & 0x8000){	//判断电流值是否是负值
	
	    result_shunt = -(((~shunt) + 1) * 2.5/1000);//换算成电压mV,并且加上负号

	}else{

	    result_shunt = result_shunt * 2.5/1000;//换算成电压mV
	}
	*/
	if( (i2c_addr == I2C_ADDR_CHARGE) |(i2c_addr == I2C_ADDR_DISCHARGE)){ //judge which ina226 the data from 

		 result_voltage = ((bus/400.0)*3);//总线电压

	}else{
		 result_voltage = bus/480.0;//总线电压
		 if(result_voltage>=55) return;
	}

	/*
	if(current & 0x8000){
	
		result_current = -(((~current) + 1)/1000.0);

	}else{

		result_current = current/1000.0 ;//实际电流 （A）
	}
	*/

	smg_write( (i2c_addr-0x40),(unsigned int)result_voltage );//数码管上显示电压值
	//printf("%d \r\n",(unsigned int)result_voltage);

}



/***********************************************************************************************
*
*						
*					打印指定INA226的全部寄存器内容
*
*
***********************************************************************************************/
void  ina226_print_all_reg(unsigned char i2c_addr){
	
	unsigned int config,shunt,bus,power,current,calibration,mask,alert;

	float result_shunt,result_voltage,result_current;
	

	/***********************************取得寄存器的值*************************************************/

	i2c_read( i2c_addr, REG_CONFIG_ADDR, 	  &config); 
	i2c_read( i2c_addr, REG_SHUNT_ADDR, 	  &shunt);
	i2c_read( i2c_addr, REG_BUS_ADDR, 		  &bus); 
	i2c_read( i2c_addr, REG_POWER_ADDR,       &power); 
	i2c_read( i2c_addr, REG_CURRENT_ADDR, 	  &current); 
	i2c_read( i2c_addr, REG_CALIBRATION_ADDR, &calibration); 
	i2c_read( i2c_addr, REG_MASK_ENABLE_ADDR, &mask); 
	i2c_read( i2c_addr, REG_ALERT_LIMIT_ADDR, &alert);

	/***********************************处理数据结果*************************************************/


	if(shunt & 0x8000){	//判断电流值是否是负值
	
	    result_shunt = -(((~shunt) + 1) * 2.5/1000);//换算成电压mV,并且加上负号

	}else{

	    result_shunt = result_shunt * 2.5/1000;//换算成电压mV
	}

	result_voltage = bus/480.0;//总线电压

	if(current & 0x8000){
	
		result_current = -(((~current) + 1)/1000.0);

	}else{

		result_current = current/1000.0 ;//实际电流 （A）
	}
	

	/**************************************打印结果***************************************************/
	 
	printf("\r\n/*********************This is reg dat @0x%2x*****************************/\r\n",i2c_addr);

	printf("\r\n0x%-0 4x		---config",config);
	printf("\r\n%3.2fmV		---shunt",result_shunt);
	printf("\r\n%3.3fV		---bus",result_voltage);
	//printf("\r\n%2x,%2x  ---power",power>>8,power&0x00ff);
	printf("\r\n%2.3fA		---current",result_current);
	printf("\r\n0x%-0 4x		---calibration",calibration);
	printf("\r\n0x%-0 4x		---mask",mask);
	printf("\r\n0x%-0 4x		---alert",alert);

	printf("\r\n/******************************END*************************************/\r\n",i2c_addr);

}








