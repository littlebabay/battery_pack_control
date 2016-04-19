#include "../inc/ad.h"
#include "../inc/smg.h"
#include "intrins.h"

/*----------------------------
Software delay function
----------------------------*/
void Delay(unsigned int n)
{
    unsigned int x;

    while (n--)
    {
        x = 5000;
        while (x--);
    }
}


/**************************************************************
*
*
*						 adc   init  
*
***************************************************************/

void  ad_init(void){

	P1ASF = (0x01<<5);//set  p1.5 as input port
	ADC_RES =0;//Clear pervious result	
	AUXR |= ADRJ;//set data format
	Delay(2);
}

unsigned char ad_start(void){
	
	ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | 5; //start one time ad conversation

	_nop_();                        //Must wait before inquiry
    _nop_();
    _nop_();
    _nop_();

	while(!(ADC_CONTR & ADC_FLAG)); //wait for conversation ready
	
	ADC_CONTR &= !ADC_FLAG;         //Clear ADC interrupt flag

	return 	ADC_RES;
}


