
/*******************************************************************
*
* CAUTION: This file is automatically generated by libgen.
* Version: Xilinx EDK 14.3 EDK_P.40xd
* DO NOT EDIT.
*
* Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.

* 
* Description: XilKernel Configuration parameters
*
*******************************************************************/

#ifndef _OS_CONFIG_H
#define _OS_CONFIG_H


#define MB_XILKERNEL 

#define CONFIG_HARDWARE_EXCEPTIONS 

#define CONFIG_PTHREAD_SUPPORT true

#define MAX_PTHREADS 10

#define PTHREAD_STACK_SIZE 1000

#define CONFIG_TIMER_PIT true

#define SYSTMR_BASEADDR 0x41c20000

#define SYSTMR_INTERVAL 1000000

#define SYSTMR_CLK_FREQ 100000000

#define SYSTMR_CLK_FREQ_KHZ 100000

#define CONFIG_INTC true

#define SYSINTC_BASEADDR XPAR_MICROBLAZE_0_INTC_BASEADDR

#define SYSINTC_DEVICE_ID XPAR_MICROBLAZE_0_INTC_DEVICE_ID

#define SYSTMR_INTR_ID 3

#define CONFIG_SCHED true

#define SCHED_TYPE SCHED_RR

#define N_PRIO 32

#define CONFIG_RRSCHED true

#define MAX_READYQ 10

#endif
