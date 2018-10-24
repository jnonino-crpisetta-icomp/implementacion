/*
 * Copyright (c) 2009 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/* Includes */
#include "xmk.h"
#include "os_config.h"
#include "sys/ksched.h"
#include "sys/init.h"
#include "config/config_param.h"
#include "stdio.h"
#include "xparameters.h"
#include "platform.h"
#include "platform_config.h"
#include <pthread.h>
#include <sys/types.h>
#include "semaphore.h"
#include "xtmrctr_l.h"
#include "xtmrctr.h"
#include "xutil.h"

#define cantidad_de_cambios 10000

#define numero_de_hilo_uno  1;
#define numero_de_hilo_dos  2;

/* Threads */
void* master_thread(void *);
void* hilo_escritor_1();
void* hilo_escritor_2();

pthread_t hilo_2;
pthread_t hilo_1;

unsigned long int valor_inicial_timer;
unsigned long int valor_final_timer;
int ControlStatus;

/* Timer */
XTmrCtr *timer;

/* Semaphores */

/* Functions */
int main()
{
    init_platform();
    
    xil_printf("INICIO MEDICION CAMBIO DE CONTEXTO\r\n");
    
    /* Initialize xilkernel */
    	xilkernel_init();

    	xmk_add_static_thread(master_thread, 0);

    /* Start the kernel */
       	xilkernel_start();

    /* Never reached */
        cleanup_platform();

    return 0;
}

void* master_thread(void *arg)
{
    pthread_attr_t attr;
    pthread_attr_init(&attr);

	int status;
	/* This is how we can join with a thread and reclaim its return value */
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	int *a;
	int *valor_final;

	//Lanzamiendo de los hilos escritores
		status = pthread_create(&hilo_1, &attr, (void*)hilo_escritor_1, NULL);
    	status = pthread_create(&hilo_2, &attr, (void*)hilo_escritor_2, NULL);

    	pthread_join(hilo_1, (void*)&a);
    	pthread_join(hilo_2, (void*)&valor_final);

       xil_printf("Valor final del timer: %d\r\n\n\n", valor_final);

    return (void*)0;
}


/* HILOS ESCRITORES */
void* hilo_escritor_1()
{
	int i;

    //Iniciar cuenta de tiempo
		XTmrCtr_SetControlStatusReg(XPAR_AXI_TIMER_1_BASEADDR,0,0x0);
		XTmrCtr_SetLoadReg(XPAR_AXI_TIMER_1_BASEADDR, 0, 0x00000000);
		XTmrCtr_LoadTimerCounterReg	(XPAR_AXI_TIMER_1_BASEADDR,0);
		ControlStatus = XTmrCtr_GetControlStatusReg(XPAR_AXI_TIMER_1_BASEADDR,0);
		XTmrCtr_SetControlStatusReg(XPAR_AXI_TIMER_1_BASEADDR, 0, ControlStatus & (~XTC_CSR_LOAD_MASK));
		valor_inicial_timer = XTmrCtr_GetTimerCounterReg(XPAR_AXI_TIMER_1_BASEADDR,0);
		xil_printf("Valor inicial del timer: %d\r\n\n", valor_inicial_timer);
		XTmrCtr_Enable(XPAR_AXI_TIMER_1_BASEADDR, 0);

		for(i=0;i<cantidad_de_cambios/2;i++)
		{	yield(); }


		pthread_exit((void*)NULL);
		return NULL;
}

void* hilo_escritor_2()
{
	int i;
	for(i=0;i<cantidad_de_cambios/2;i++)
	{	yield(); }

	//Terminar cuenta de tiempo
		valor_final_timer = XTmrCtr_GetTimerCounterReg(XPAR_AXI_TIMER_1_BASEADDR,0);

	pthread_exit((void*)valor_final_timer);
	return NULL;
}
