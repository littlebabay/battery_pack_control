#ifndef __HIDE_BOX_H
#define __HIDE_BOX_H
#include "STC/STC12C5A.h"
#include "../inc/main.h"
#include "../inc/uart.h"
#include "../inc/beep.h"
#include "../inc/relay.h"

extern unsigned char hide_box_enter; //1：进入hide_box模式，0：在正常模式运行
extern unsigned char cmd_update;//标志位： 1.接收到新命令 0.表示没有接收到新命令
extern void hide_box(void);//hide_box函数
extern unsigned char hide_box_compare_str(unsigned char *s1,unsigned char *s2);	//字符串对比函数

#endif