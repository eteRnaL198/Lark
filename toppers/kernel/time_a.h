#ifndef _TIME_A_H_
#define _TIME_A_H_

#include "sfrh8s2638.h"
#include "serial.h"

#define		tcnt0_addr		(*(volatile UINT16		*)0xFFFF16)
#define		TCNT0			tcnt0_addr

extern TickType timeA, timeB;

#endif