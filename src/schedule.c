#include "../inc/schedule.h"
#include "../inc/key.h"
#include "../inc/uart.h"
#include "../inc/relay.h"
#include "../inc/smg.h"
#include "stdio.h"
#include "../inc/main.h"

bit schedule_out_state = OFF;
bit schedule_relay_state = OFF;// inter out voltage state 
/**************************************************************************************
*
*						
*						output the request voltage
*
*
***************************************************************************************/

void schedule_out_vol_sel(unsigned char voltage){
	
	 
	 switch(voltage){
	 
	 	case V_48V:

			if(schedule_relay_state == OFF){
			
				relay_voltage_OUT(V_48V,POSITIVE,0);
				schedule_relay_state = ON;
				smg_write_led(led_state | 0x00f0);//close voltage led
				smg_write_led(led_state & (~LED_48V));//open the voltage led
			}
			
			else if(schedule_relay_state == ON){
			 	
				DISCHARGE_DISABLE;
				smg_write_led(led_state | LED_DISCHARGE ); //close the corresponding led
				relay_all_off();
				schedule_relay_state = OFF;
				smg_write_led(led_state | 0x00f0);//close voltage led
			}

			break;

		case V_96V:
			
			if(schedule_relay_state == OFF){
			
				relay_voltage_OUT(V_96V,POSITIVE,0);
				schedule_relay_state = ON;
				smg_write_led(led_state | 0x00f0);//close voltage led
				smg_write_led(led_state & (~LED_96V));//open the voltage led
			}
			
			else if(schedule_relay_state == ON){

				smg_write_led(led_state | LED_DISCHARGE ); //close the corresponding led
				DISCHARGE_DISABLE;
				relay_all_off();
				schedule_relay_state = OFF;
				smg_write_led(led_state | 0x00f0);//close voltage led
			}


			break;

		case V_144V:
			
			if(schedule_relay_state == OFF){
			
				relay_voltage_OUT(V_144V,POSITIVE,0);
				schedule_relay_state = ON;
				smg_write_led(led_state | 0x00f0);//close voltage led
				smg_write_led(led_state & (~LED_144V));//open the voltage led
			}
			
			else if(schedule_relay_state == ON){
			   	
				smg_write_led(led_state | LED_DISCHARGE ); //close the corresponding led
				DISCHARGE_DISABLE;
				relay_all_off();
				schedule_relay_state = OFF;
				smg_write_led(led_state | 0x00f0);//close voltage led
			}

			
			break;

		case V_192V:
			
				if(schedule_relay_state == OFF){
			
				relay_voltage_OUT(V_192V,POSITIVE,0);
				schedule_relay_state = ON;
				smg_write_led(led_state | 0x00f0);//close voltage led
				smg_write_led(led_state & (~LED_192V));//open the voltage led
			}
			
			else if(schedule_relay_state == ON){
			    
				smg_write_led(led_state | LED_DISCHARGE ); //close the corresponding led
				DISCHARGE_DISABLE;
				relay_all_off();
				schedule_relay_state = OFF;
				smg_write_led(led_state | 0x00f0);//close voltage led
			}

			
			break;
	 
	 }
	 
}

/**************************************************************************************
*
*						
*						output enbale or disable
*
*
***************************************************************************************/
void schedule_out_en(void){
	
	schedule_out_state = !schedule_out_state;
	
	if(schedule_out_state == ON){
		
		DISCHARGE_ENABLE;//open output
		smg_write_led(led_state & (~LED_DISCHARGE));//open the corresponding led	

	}else{
	
		DISCHARGE_DISABLE;//close ouput
		smg_write_led(led_state | LED_DISCHARGE ); //close the corresponding led
	}	

}
/***************************************************************************************************
*
*
*				   schedule entry
*
*
***************************************************************************************************/
void schedule_run(void){

	 unsigned char key_value=KEY_NONE;

	 key_value = key_scan(); //read key value

	 switch(key_value){
	 
	 	  case KEY_NONE:  		break;
		  case KEY_OUT_EN: 
		  	while( ( key_scan()) != KEY_NONE);
			schedule_out_en();
		  	printf("KEY_OUT_EN Press!\r\n");	
			break;
		  case KEY_OUT_48V:
		  	while( ( key_scan()) != KEY_NONE);
			schedule_out_vol_sel(V_48V);
		   	printf("KEY_OUT_48V Press!\r\n"); 
			break;
		  case KEY_OUT_96V: 
		  	while( ( key_scan()) != KEY_NONE);
			schedule_out_vol_sel(V_96V);
			printf("KEY_OUT_96V Press!\r\n"); 
			break;
		  case KEY_OUT_144V:
		  	while( ( key_scan()) != KEY_NONE);
			schedule_out_vol_sel(V_144V);
		  	printf("KEY_OUT_144V Press!\r\n"); 	
			break;
		  case KEY_OUT_192V:
		  	while( ( key_scan()) != KEY_NONE);
			schedule_out_vol_sel(V_192V);
		  	printf("KEY_OUT_192V Press!\r\n"); 	
			break;
			
	 }

}



