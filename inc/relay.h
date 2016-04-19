#ifndef __RELAY_H
#define __RELAY_H

#include "STC/stc12c5a.h"

/********************************************************************/
					
				//继电器控制引脚定义

/********************************************************************/
#define ON    1
#define OFF	  0

#define POSITIVE 0
#define NEGATIVE 1

#define V_0V	  0
#define V_48V     48
#define V_96V     96
#define V_144V    144
#define V_192V    192

#define relay_1   P40
#define relay_2   P20
#define relay_3   P21
#define relay_4   P22
#define relay_5   P23
#define relay_6   P24
#define relay_7   P25
#define relay_8   P26
#define relay_9   P27
#define relay_10  P44
#define relay_11  P45
#define relay_12  P41
#define relay_13  P07
#define relay_14  P06
#define relay_15  P05
#define relay_16  P04
#define relay_17  P03
#define relay_18  P02
#define relay_19  P01
#define relay_20  P00

#define CHARGE_ENABLE  P13 = 0  //充电打开
#define CHARGE_DISABLE  P13 = 1	//充电关闭
#define DISCHARGE_ENABLE  P14 = 0 //放电打开
#define DISCHARGE_DISABLE  P14 = 1//放电关闭


//不同输出电压时，寄存器配置
extern const unsigned char OUT_48V[];
extern const unsigned char OUT_96V[];
extern const unsigned char OUT_144V[];
extern const unsigned char OUT_192V[];



/******************************************************************/

extern void relay_init();
extern void relay_test_all();
extern void relay_all_off();
extern const void relay_voltage_OUT( const unsigned char voltage,const unsigned char polar ,const unsigned char m);
extern void relay_out(void);

#endif