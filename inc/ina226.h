#ifndef __INA226_H
#define __INA226_H

#include "STC/STC12C5A.h"
#include "../inc/uart.h"

#define  I2C_ADDR_CHARGE		0x40
#define  I2C_ADDR_DISCHARGE		0x41
#define  I2C_ADDR_BATT_1		0x42
#define  I2C_ADDR_BATT_2		0x43
#define  I2C_ADDR_BATT_3		0x44
#define  I2C_ADDR_BATT_4		0x45

#define  REG_CONFIG_ADDR 		0x00
#define  REG_SHUNT_ADDR 		0x01
#define  REG_BUS_ADDR 			0x02
#define  REG_POWER_ADDR 		0x03
#define  REG_CURRENT_ADDR 		0x04
#define  REG_CALIBRATION_ADDR 	0x05
#define  REG_MASK_ENABLE_ADDR 	0x06
#define  REG_ALERT_LIMIT_ADDR 	0x07

typedef struct {

	union{
	
		struct{

			unsigned int RST 		:1;
			unsigned int NC  		:3;
			unsigned int AVG 		:3;
			unsigned int VBUS_CT	:3;
			unsigned int VSHT_CT    :3;
			unsigned int MODE		:3;
		
		}bits;

		unsigned int word;
	
	}config;	

	unsigned int shunt_voltage;

	unsigned int bus_voltage;

	unsigned int power;

	unsigned int current;

	unsigned int calibration;

	union{
	
		struct{
		  	
			unsigned int SOL		:1;
			unsigned int SUL 		:1;
			unsigned int BOL		:1;
			unsigned int BUL		:1;
			unsigned int POL		:1;
			unsigned int CNVR		:1;
			unsigned int NC 		:5;
			unsigned int AFF		:1;
			unsigned int CVRF		:1;
			unsigned int OVF		:1;
			unsigned int APOL		:1;
			unsigned int LEN		:1;

		
		}bits;
		
		unsigned int word;
	
	}mask_enable;

	unsigned int alert_limit;

}ina226_typedef;


extern void  ina226_set_reg(void);
extern void  ina226_read_all(unsigned char i2c_addr);
extern void  ina226_print_all_reg(unsigned char i2c_addr);

#endif