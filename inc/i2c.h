#ifndef __I2C_H
#define __I2C_H
#include "STC/STC12C5A.h"
#include "../inc/uart.h"
#include "intrins.h"

#define I2C_SCL   P34
#define I2C_SDA   P33
#define I2C_ALERT P32

extern void i2c_init(void);
extern unsigned char i2c_write(unsigned char i2c_addr,unsigned char reg_addr,unsigned int dat);
extern unsigned char i2c_read(unsigned char i2c_addr,unsigned char reg_addr,unsigned int *dat);
extern unsigned char i2c_change_reg_addr(unsigned char i2c_addr , unsigned char reg_addr);

#endif