#include "STC/stc12c5a.h"
#include "../inc/main.h"	 
#include "../inc/beep.h"
#include "../inc/relay.h"
#include "../inc/uart.h"
#include "../inc/hide_box.h"
#include "../inc/i2c.h"
#include "../inc/batt.h"
#include "../inc/key.h"
#include "../inc/ina226.h"
#include "../inc/smg.h"
#include "../inc/schedule.h"
#include "../inc/ad.h"

#include "stdio.h"

int main(void){
	

	unsigned char dat=0;
	unsigned int dat_buf=0;
	unsigned int bus[4]={0};
	unsigned char key_value=255;

	unsigned long int a=0,b=1;
   

	/**********************************Power Hold*******************************************/
		
		POWER_HOLD_ENABLE;//程序启动后维持出5V电源
		while(POWER_KEY == ENABLE);
		beep(1);

	/***************************************************************************************/

	smg_write(SMG_IN,123);
    smg_write(SMG_OUT,234);
	smg_write(SMG_BATT_1,345);
	smg_write(SMG_BATT_2,456);
	smg_write(SMG_BATT_3,567);
	smg_write(SMG_BATT_4,678);

	smg_write_led(0xffff);


	/**********************************Module Initial***************************************/

		relay_init();
		serial_init();
		i2c_init();
		smg_init();
		ad_init();

	/***************************************************************************************/
	    //relay_test_all();

		DISCHARGE_ENABLE;

	
		ina226_set_reg();
		ina226_set_reg();
		ina226_set_reg();

		//i2c_change_reg_addr(I2C_ADDR_BATT_3,REG_BUS_ADDR);//修改

		//relay_voltage_OUT(V_192V,POSITIVE,0);

	/*************************************main**********************************************/

		while(1){
			
			/*******************************Power OFF function******************************/
			
				if( POWER_KEY == ENABLE ){
					beep(1);
					while(POWER_KEY == ENABLE);
					POWER_HOLD_DISABLE;
					
				}
			/******************************************************************************/




			//beep(1);
			/*	
			if(I2C_ALERT == 0){
			  
			  // ina226_read_all(I2C_ADDR_CHARGE);
			   //ina226_read_all(I2C_ADDR_DISCHARGE);
			   //ina226_read_all(I2C_ADDR_BATT_1);
			   //ina226_read_all(I2C_ADDR_BATT_2);
			   ina226_read_all(I2C_ADDR_BATT_3);
			   //ina226_read_all(I2C_ADDR_BATT_4); 
			   
			   //beep(1);

			} 
			 */

			 ina226_read_all(I2C_ADDR_BATT_1);
			 ina226_read_all(I2C_ADDR_BATT_2);
			 ina226_read_all(I2C_ADDR_BATT_3);
			 ina226_read_all(I2C_ADDR_BATT_4);
	   		 /*
			i2c_read( I2C_ADDR_BATT_1, REG_CONFIG_ADDR, bus); 
			i2c_read( I2C_ADDR_BATT_2, REG_CONFIG_ADDR, bus+1); 
			//i2c_read( I2C_ADDR_BATT_3, REG_CONFIG_ADDR, bus+2); 
			//i2c_read( I2C_ADDR_BATT_4, REG_CONFIG_ADDR, bus+3); 
			if(bus == 0x4f27 ){
			   a++;
			}		
			printf("\r\n %x %x",*bus, *(bus+1));
			b++;

			*/

		

			schedule_run();//start one time schedule module
			
			/**********************************hide_box* **************************************/
	
				if(hide_box_enter == TRUE ) hide_box();//进入hide_box模式
			
			/*********************************************************************************/
	
		}
	/*************************************************************************************/
}
