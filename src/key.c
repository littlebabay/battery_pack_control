#include "../inc/key.h"
#include "../inc/ad.h"


unsigned char key_value=255;

unsigned char key_scan(void){

	key_value = ad_start();	//read ad value

	if(key_value > 220) return KEY_NONE;
	
	else if((key_value > 190)&&(key_value <210)) return KEY_OUT_EN;

	else if((key_value > 150)&&(key_value <170)) return KEY_OUT_48V;

	else if((key_value > 110)&&(key_value <130)) return KEY_OUT_96V;

	else if((key_value > 40)&&(key_value  <60)) return KEY_OUT_144V;

	else if( key_value < 20) return KEY_OUT_192V;

}
