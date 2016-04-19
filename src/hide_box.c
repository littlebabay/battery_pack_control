#include "../inc/hide_box.h"
#include "../inc/ina226.h"
#include "../inc/relay.h"

unsigned char hide_box_enter = 0; //1：进入hide_box模式，0：在正常模式运行
unsigned char cmd_update = 0; //标志位： 1.接收到新命令 0.表示没有接收到新命令
/*************************************************************************************
*
* 			字符串比较函数，如果两个字符串完全相同，返回TRUE，反之，返回FALSE
*
**************************************************************************************/
unsigned char hide_box_compare_str(unsigned char *s1,unsigned char *s2){

	while( (*s1 != '\0') && (*s2 !='\0') ){
		
		if( (*s1++) != (*s2++) )
			return FALSE;			

	}

	if( ( *s1 == '\0') && ( *s2 == '\0') )
		return TRUE;
	else 
		return FALSE;

}

/***************************************************************************************
*
*						黑盒测试
*
****************************************************************************************/
void hide_box(){
	
	
	uart_printf("Entering hide box mode\n\r#");

	ET0=0; //关掉LED刷新
	
	while(hide_box_enter == TRUE){
		
		if(cmd_update == TRUE ){ //如果新接收到了命令，就逐个对比，解析并执行命令内容
		
			/****************************所有可执行的测试命令*************************/
			
			if( (hide_box_compare_str( receive_buf ,"beep")) == TRUE) beep(2);

			if( (hide_box_compare_str( receive_buf ,"relay_test")) == TRUE) relay_test_all();

			if( (hide_box_compare_str( receive_buf ,"relay_out")) == TRUE) relay_out();
			
			if( (hide_box_compare_str( receive_buf ,"print_ina226_charge")) == TRUE){ 
				
				ina226_print_all_reg(I2C_ADDR_CHARGE);
			}

			if( (hide_box_compare_str( receive_buf ,"print_ina226_discharge")) == TRUE){ 
				
		
				ina226_print_all_reg(I2C_ADDR_DISCHARGE);
			}
			
			if( (hide_box_compare_str( receive_buf ,"print_ina226_batt_1")) == TRUE){ 
				
			
				ina226_print_all_reg(I2C_ADDR_BATT_1);
			}
			if( (hide_box_compare_str( receive_buf ,"print_ina226_batt_2")) == TRUE){ 
				
			
				ina226_print_all_reg(I2C_ADDR_BATT_2);
			}
			if( (hide_box_compare_str( receive_buf ,"print_ina226_batt_3")) == TRUE){ 
				
				
				ina226_print_all_reg(I2C_ADDR_BATT_3);
			}
			if( (hide_box_compare_str( receive_buf ,"print_ina226_batt_4")) == TRUE){ 
				
			
				ina226_print_all_reg(I2C_ADDR_BATT_4);
			}
			if( (hide_box_compare_str( receive_buf ,"print_ina226")) == TRUE){ 
				

				ina226_print_all_reg(I2C_ADDR_CHARGE);
		
				ina226_print_all_reg(I2C_ADDR_DISCHARGE);
			
				ina226_print_all_reg(I2C_ADDR_BATT_1);
		
				ina226_print_all_reg(I2C_ADDR_BATT_2);
			
				ina226_print_all_reg(I2C_ADDR_BATT_3);

				ina226_print_all_reg(I2C_ADDR_BATT_4);
			}
			
				
			cmd_update = FALSE;//命令解析完成后，清楚标志位，为下一次命令更新做准备
		}
		
	}
	ET0=1;
	uart_printf("Exit form hide box mode\n\r#");
}

