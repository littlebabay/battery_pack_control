#ifndef __SMG_H
#define __SMG_H

#include "STC/stc12c5a.h"

#define SMG_CLK_H		P37=1
#define SMG_CLK_L		P37=0
#define SMG_RCLK_H		P36=1
#define SMG_RCLK_L		P36=0
#define SMG_DATA_H		P35=1
#define SMG_DATA_L		P35=0
#define	SMG_1_ON		P42=0
#define	SMG_1_OFF		P42=1
#define	SMG_2_ON		P10=0
#define	SMG_2_OFF		P10=1
#define	SMG_3_ON		P11=0
#define	SMG_3_OFF		P11=1
#define	SMG_4_ON		P12=0
#define	SMG_4_OFF		P12=1

#define SMG_IN			0
#define SMG_OUT			1
#define SMG_BATT_1		2
#define SMG_BATT_2		3
#define SMG_BATT_3		4
#define SMG_BATT_4		5
#define SMG_LED_VOL_SEL	6
#define SMG_LED_BATT	7

//LED bit define
#define LED_ALL_OFF		0xffff
#define LED_IN			(0x0001<<8)
#define LED_OUT			(0x0001<<9)
#define LED_BATT_1		(0x0001<<10)
#define LED_BATT_2		(0x0001<<11)
#define LED_BATT_3		(0x0001<<12)
#define LED_BATT_4		(0x0001<<13)
#define LED_CHARGE		(0x0001<<0)
#define LED_DISCHARGE	(0x0001<<1)
#define LED_ERROR		(0x0001<<2)
#define LED_LOWVOL		(0x0001<<3)
#define	LED_48V			(0x0001<<4)
#define	LED_96V			(0x0001<<5)
#define	LED_144V		(0x0001<<6)
#define	LED_192V		(0x0001<<7)






extern unsigned char smg_buf[];
extern unsigned int led_state;

extern void smg_init(void);
extern void smg_write(unsigned char which,unsigned int dat);
extern void smg_write_led( unsigned int dat);
#endif