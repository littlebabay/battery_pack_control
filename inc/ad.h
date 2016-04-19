#ifndef __AD_H
#define __AD_H

#include "STC/stc12c5a.h"
#include "../inc/uart.h"
#include "stdio.h"

extern void ad_init(void);
extern unsigned char ad_start(void);

#endif