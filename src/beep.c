#include "../inc/beep.h"

#define BEEP  P43 

void beep_delay(unsigned int);
/******************************************************************************************

				   ·äÃùÆ÷º¯Êı count=·äÃùÆ÷Ãù½Ğ´ÎÊı

******************************************************************************************/
void beep(unsigned char count){
	
	unsigned int i=0;
	unsigned int interval=500;
	unsigned int repeat = 250000/interval;

	while(count--){

		for(i=0 ;i < 500; i++){

			BEEP = 1;
		 	beep_delay(interval);
		 	BEEP = 0;
		 	beep_delay(interval);
		}

		for(i=0 ;i < 500; i++){
			BEEP = 0;
		 	beep_delay(interval);
		 	BEEP = 0;
		 	beep_delay(interval);
		}
		
	}										 

}

void beep_delay(unsigned int interval){
 	
	 while(interval--);
}