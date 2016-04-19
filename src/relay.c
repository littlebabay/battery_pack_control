#include "../inc/relay.h"
#include "../inc/beep.h"

const unsigned char OUT_48V[16]={1,3,2,4,6,8,7,9,11,13,12,14,16,18,17,19};
const unsigned char OUT_96V[24]={5,8,1,5,9,2,10,13,6,10,14,7,15,18,11,15,19,12,20,3,16,20,4,17};
const unsigned char OUT_144V[32]={5,10,13,1,5,10,14,2,10,15,18,6,10,15,19,7,15,20,3,11,15,20,4,12,20,5,8,16,20,5,9,17};
const unsigned char OUT_192V[40]={3,20,15,10,6,4,20,15,10,7,8,5,20,15,11,9,5,20,15,12,13,10,5,20,16,14,10,5,20,17,18,15,10,5,1,19,15,10,5,2}; 

void relay_delay(void){

	unsigned int i,j;

	for(i = 0; i <1000; i++ )
		
		for(j = 0; j <300; j++);


}
/*********************************************************************
*
*			关掉所有继电器
*
*********************************************************************/
void relay_all_off(void){
	
	 relay_1 = OFF;
	 relay_2 = OFF;
	 relay_3 = OFF;
	 relay_4 = OFF;
	 relay_5 = OFF;
	 relay_6 = OFF;
	 relay_7 = OFF;
	 relay_8 = OFF;
	 relay_9 = OFF;
	 relay_10 = OFF;
	 relay_11 =	OFF;
	 relay_12 =	OFF;
	 relay_13 =	OFF;
	 relay_14 =	OFF;
	 relay_15 =	OFF;
	 relay_16 = OFF;
	 relay_17 =	OFF;
	 relay_18 =	OFF;
	 relay_19 =	OFF;
	 relay_20 =	OFF;
	 relay_delay();
}
/*********************************************************************
*
*			继电器引脚输出模式设置以及关闭所有继电器
*
*********************************************************************/
void relay_init(void){


	//将所有继电器复位，关掉
	relay_all_off();
	// 将P4特殊功能引脚设置为普通IO
	P4SW = (0x01<<4) + (0x01<<5) + (0x01<<6);
	//将所有继电器使用到的IO全都设置为强推挽输出模式
	P0M1 &=~(0xff); 
	P0M0 |= (0xff);
	P2M1 &=~(0xff);
	P2M0 |= (0xff);
	P4M1 &=~((0x01<<0)+(0x01<<1)+(0x01<<4)+(0x01<<5));
	P4M0 |= ((0x01<<0)+(0x01<<1)+(0x01<<4)+(0x01<<5));

}



/*********************************************************************
*
*			逐个测试继电器，根据声音判断继电器的工作状态
*
*********************************************************************/
void relay_test_all(void){
	  	
		beep(1);
		beep(1);
		beep(1);
		relay_1=(ON);   
	 	beep(1);
		relay_1=(OFF);
		
		beep(1);
		relay_2=(ON);
	 	beep(1);
		relay_2=(OFF);

		beep(1);
		relay_3=(ON);
	 	beep(1);
		relay_3=(OFF);

		beep(1);
		relay_4=(ON);
	 	beep(1);
		relay_4=(OFF);

		beep(1);
		relay_5=(ON);
	 	beep(1);
		relay_5=(OFF);

		beep(1);
		relay_6=(ON);
	 	beep(1);
		relay_6=(OFF);

		beep(1);
		relay_7=(ON);
	 	beep(1);
		relay_7=(OFF);

		beep(1);
		relay_8=(ON);
	 	beep(1);
		relay_8=(OFF);

		beep(1);
		relay_9=(ON);
	 	beep(1);
		relay_9=(OFF);

		beep(1);
		relay_10=(ON);
	 	beep(1);
		relay_10=(OFF);

		beep(1);
		relay_11=(ON);
	 	beep(1);
		relay_11=(OFF);

		beep(1);
		relay_12=(ON);
	 	beep(1);
		relay_12=(OFF);

		beep(1);
		relay_13=(ON);
	 	beep(1);
		relay_13=(OFF);

		beep(1);
		relay_14=(ON);
	 	beep(1);
		relay_14=(OFF);

		beep(1);
		relay_15=(ON);
	 	beep(1);
		relay_15=(OFF);

		beep(1);
		relay_16=(ON);
	 	beep(1);
		relay_16=(OFF);

		beep(1);
		relay_17=(ON);
	 	beep(1);
		relay_17=(OFF);

		beep(1);
		relay_18=(ON);
	 	beep(1);
		relay_18=(OFF);

		beep(1);
		relay_19=(ON);
	 	beep(1);
		relay_19=(OFF);

		beep(1);
		relay_20=(ON);
	 	beep(1);
		relay_20=(OFF);


}


/*********************************************************************
*
*			设置对应继电器的状态
*
*********************************************************************/
static void relay_set( const unsigned char  relay, const unsigned char  state){

	 switch(relay){
	 
	 	case 1: relay_1 = state;break;
	 	case 2: relay_2 = state;break;
		case 3: relay_3 = state;break;
		case 4: relay_4 = state;break;
		case 5: relay_5 = state;break;
		case 6: relay_6 = state;break;
		case 7: relay_7 = state;break;
		case 8: relay_8 = state;break;
		case 9: relay_9 = state;break;
		case 10: relay_10 = state;break;
		case 11: relay_11 = state;break;
		case 12: relay_12 = state;break;
		case 13: relay_13 = state;break;
		case 14: relay_14 = state;break;
		case 15: relay_15 = state;break;
		case 16: relay_16 = state;break;
	 	case 17: relay_17 = state;break;
		case 18: relay_18 = state;break;
		case 19: relay_19 = state;break;
		case 20: relay_20 = state;break;
	 
	 }

}
/*********************************************************************
*
*			输出不同电压
*     参数： 
			 voltage=V_48V,V_96V,V_144,V_192V。
			 m= 0,1,2,3 表示使用哪组蓄电池对外输出
*			 polar= POSITVIE,NEGATIVE 表示输出极性
*
*********************************************************************/
void relay_voltage_OUT( const unsigned char voltage,const unsigned char polar ,const unsigned char m){

	 relay_all_off();
	 /*******************************48V***************************************/
	 if(voltage == V_48V){
	 
		 if(polar == POSITIVE){ //使用第m组蓄电池对外输出+48V
		 	
			relay_set( OUT_48V[4*m],ON);
			relay_delay();
		 	relay_set( OUT_48V[4*m+1],ON);
			relay_delay();
		 
		 }else if(polar == NEGATIVE){  //使用第m组蓄电池对外输出-48V
		 
		 	relay_set(OUT_48V[4*m+2],ON);
			relay_delay();
		 	relay_set(OUT_48V[4*m+3],ON);
			relay_delay();
		 
		 }

	 /******************************96V*****************************************/ 

	 }else if(voltage == V_96V){
	 
		 if(polar == POSITIVE){ //使用第m组蓄电池对外输出+96V
		 	
			relay_set( OUT_96V[6*m],ON);
			relay_delay();
		 	relay_set( OUT_96V[6*m+1],ON);
			relay_delay();
			relay_set( OUT_96V[6*m+2],ON);
			relay_delay();
		 
		 }else if(polar == NEGATIVE){  //使用第m组蓄电池对外输出-96V
		 
		 	relay_set(OUT_96V[6*m+3],ON);
			relay_delay();
		 	relay_set(OUT_96V[6*m+4],ON);
			relay_delay();
		 	relay_set(OUT_96V[6*m+5],ON);
			relay_delay();
		 }

	 /******************************144V*****************************************/
	   
	 }else if(voltage == V_144V){ //输出144V
	 
		 if(polar == POSITIVE){ //使用第m组蓄电池对外输出+144V
		 	
			relay_set( OUT_144V[8*m],ON);
			relay_delay();
		 	relay_set( OUT_144V[8*m+1],ON);
			relay_delay();
			relay_set( OUT_144V[8*m+2],ON);
			relay_delay();
		 	relay_set( OUT_144V[8*m+3],ON);
			relay_delay();
		 
		 }else if(polar == NEGATIVE){  //使用第m组蓄电池对外输出-144V
		 
		 	relay_set( OUT_144V[8*m+4],ON);
			relay_delay();
		 	relay_set( OUT_144V[8*m+5],ON);
			relay_delay();
			relay_set( OUT_144V[8*m+6],ON);
			relay_delay();
		 	relay_set( OUT_144V[8*m+7],ON);
			relay_delay();
		 
		 }

	 /******************************192V*****************************************/ 

	 }else if(voltage == V_192V){//输出192V
	 
		 if(polar == POSITIVE){ //使用第m组蓄电池对外输出+192V
		 	
			relay_set( OUT_192V[10*m],ON);
			relay_delay();
		 	relay_set( OUT_192V[10*m+1],ON);
			relay_delay();
			relay_set( OUT_192V[10*m+2],ON);
			relay_delay();
		 	relay_set( OUT_192V[10*m+3],ON);
			relay_delay();
			relay_set( OUT_192V[10*m+4],ON);
			relay_delay();
		 
		 }else if(polar == NEGATIVE){ //使用第m组蓄电池对外输出-192V
		 
		 	relay_set( OUT_192V[10*m+5],ON);
			relay_delay();
		 	relay_set( OUT_192V[10*m+6],ON);
			relay_delay();
			relay_set( OUT_192V[10*m+7],ON);
			relay_delay();
		 	relay_set( OUT_192V[10*m+8],ON);
			relay_delay();
			relay_set( OUT_192V[10*m+9],ON);
			relay_delay();
		 
		 }
	  
	 }
	 
}
/***********************************************************************************
*
*
*
*
************************************************************************************/
void relay_out(void){

   unsigned i=0;

   for(i=0 ; i <4 ;i++)	{
   	   
	    relay_all_off();
	    relay_voltage_OUT(V_48V,POSITIVE,i);
		beep(3);
	    relay_all_off();
		relay_voltage_OUT(V_48V,NEGATIVE,i);
   		beep(3);
   
   }

   for(i=0 ; i <4 ;i++)	{
   
   		 relay_all_off();
		 relay_voltage_OUT(V_96V,POSITIVE,i);
		 beep(3);
	 	 relay_all_off();
		 relay_voltage_OUT(V_96V,NEGATIVE,i);
   		 beep(3);
   }

   for(i=0 ; i <4 ;i++)	{
   		 
		 relay_all_off();
	 	 relay_voltage_OUT(V_144V,POSITIVE,i);
		 beep(3);
		 relay_all_off();
		 relay_voltage_OUT(V_144V,NEGATIVE,i);
   		 beep(3);
   
   }

    for(i=0 ; i <4 ;i++){
   		 
		 relay_all_off();
		 relay_voltage_OUT(V_192V,POSITIVE,i);
		 beep(3);
		 relay_all_off();
	 	 relay_voltage_OUT(V_192V,NEGATIVE,i);
   		 beep(3);

   }
   relay_all_off();
}




