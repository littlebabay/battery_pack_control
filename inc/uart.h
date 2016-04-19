#ifndef __UART_H
#define __UART_H
#include "STC/STC12C5A.h"
#include "../inc/main.h"
#include "../inc/hide_box.h"

typedef unsigned char BYTE;
typedef unsigned int WORD;

extern unsigned char receive_buf[];

void serial_init(void);
void send_byte(unsigned  char byte);
void uart_printf(unsigned char *s);

#endif