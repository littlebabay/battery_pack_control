#include "../inc/smg.h"
#include "../inc/beep.h"

unsigned char m=0;
unsigned int led_state =LED_ALL_OFF;//all led state indicate
unsigned char smg_buf[32];//smg reflash buf
unsigned char smg_module[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};// character die define

void smg_init(void)		//40毫秒@16MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xAB;		//设置定时初值
	TH0 = 0x2F;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	ET0 = 1;
	EA=1;
	TR0 = 1;		//定时器0开始计时
}

/***********************************************************************************
*
*
*				  更新显示内容
*
*
************************************************************************************/
void smg_write(unsigned char which,unsigned int dat){

	 smg_buf[which*4]   = smg_module[dat%10];
	 smg_buf[which*4+1] = smg_module[dat%100/10];
	 smg_buf[which*4+2] = smg_module[dat%1000/100];
	 smg_buf[which*4+3] = smg_module[dat%10000/1000];
}

/***********************************************************************************
*
*
*				  更新LED状态
*
*
************************************************************************************/
void smg_write_led( unsigned int dat){

	 led_state = dat;
	 smg_buf[SMG_LED_VOL_SEL*4]   = dat & 0x00ff;
	 smg_buf[SMG_LED_VOL_SEL*4+1] = dat & 0x00ff;
	 smg_buf[SMG_LED_VOL_SEL*4+2] = dat & 0x00ff;
	 smg_buf[SMG_LED_VOL_SEL*4+3] = dat & 0x00ff;

	 smg_buf[SMG_LED_BATT*4]   =  dat>>8;
	 smg_buf[SMG_LED_BATT*4+1] =  dat>>8;
	 smg_buf[SMG_LED_BATT*4+2] =  dat>>8;
	 smg_buf[SMG_LED_BATT*4+3] =  dat>>8;
}

/***********************************************************************************
*
*
*				  数码管刷新函数
*
*
************************************************************************************/
void smg_flush(void) interrupt 1
{

	unsigned char n,k;

    ET0 = 0;
	TR0 = 0;	
   
	SMG_1_OFF;
	SMG_2_OFF;
	SMG_3_OFF;
	SMG_4_OFF;

	for( n = 0; n < 8; n++){
	
		for( k = 0; k < 8; k++ ){
		
			if( (smg_buf[4*n+m] << k) & 0x80){
				
				SMG_DATA_H;
			
			}else{

				SMG_DATA_L;
			
			}
			SMG_CLK_L;
			SMG_CLK_H;
			SMG_CLK_L;
		
		}
		
	}

	SMG_RCLK_L;
	SMG_RCLK_H;
	SMG_RCLK_L;

	switch(m){

		case 0: SMG_1_ON;break;
		case 1: SMG_2_ON;break;
		case 2: SMG_3_ON;break;
		case 3: SMG_4_ON;break;		
   }		
	
    if( m == 3) m=0;
	else m++;

   TL0 = 0xAB;		//设置定时初值
   TH0 = 0x2F;		//设置定时初值

   ET0 = 1;
   TR0 = 1;

}


