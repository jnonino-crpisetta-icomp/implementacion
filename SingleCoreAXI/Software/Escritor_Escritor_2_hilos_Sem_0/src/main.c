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

/* Threads */
void* hilo_escritor_1();
void* hilo_escritor_2();
pthread_t hilo_2;
pthread_t hilo_1;

/* Data */
static int variable_compartida;
int valor_maximo = 10000;

/* Timer */
XTmrCtr *timer;

/* Semaphores */
sem_t * mutex;

/* Functions */
int main()
{
    init_platform();
    
    /* Initialize xilkernel */
    	xilkernel_init();

    pthread_attr_t attr;

    #if SCHED_TYPE == SCHED_PRIO
       	struct sched_param spar;
    #endif

    pthread_attr_init (&attr);

    xil_printf("INICIO EJECUCION CON SEMAFOROS\r\n\n");

    //Crear semaforos
    int status;
    status = sem_init(&mutex, NULL, 1);
    	if(status == 0)
    	{	print("Semaforo creado correctamente\r\n\n");	}
    	else
    	{
    		print("Error al crear el semaforo\r\n\n");
    		pthread_exit(NULL);
    	}

    unsigned long int valor_inicial_timer;
    unsigned long int valor_final_timer;
    int ControlStatus;
    int opciones;
    //Iniciar cuenta de tiempo
    	XTmrCtr_SetControlStatusReg(XPAR_AXI_TIMER_1_BASEADDR,0,0x0);
    	XTmrCtr_SetLoadReg(XPAR_AXI_TIMER_1_BASEADDR, 0, 0x00000000);
    	XTmrCtr_LoadTimerCounterReg	(XPAR_AXI_TIMER_1_BASEADDR,0);
    	ControlStatus = XTmrCtr_GetControlStatusReg(XPAR_AXI_TIMER_1_BASEADDR,0);
    	XTmrCtr_SetControlStatusReg(XPAR_AXI_TIMER_1_BASEADDR, 0, ControlStatus & (~XTC_CSR_LOAD_MASK));
    	valor_inicial_timer = XTmrCtr_GetTimerCounterReg(XPAR_AXI_TIMER_1_BASEADDR,0);
    	xil_printf("Valor inicial del timer: %d\r\n\n", valor_inicial_timer);
    	XTmrCtr_Enable(XPAR_AXI_TIMER_1_BASEADDR, 0);



    //Se pide el semaforo para evitar que los hilos comiencen
       	sem_wait(&mutex);

    //Lanzamiendo de los hilos escritores
      	status = pthread_create(&hilo_1, NULL, (void*)hilo_escritor_1, NULL);
     	status = pthread_create(&hilo_2, NULL, (void*)hilo_escritor_2, NULL);

    //Libero el semaforo asi los hilos pueden empezar
    	sem_post(&mutex);

    //Espero que todos los hilos finalicen
    	pthread_join(hilo_1, NULL);
    	pthread_join(hilo_2, NULL);
    	xil_printf("TODOS LOS HILOS TERMINARON\r\n");

    //Terminar cuenta de tiempo
        valor_final_timer = XTmrCtr_GetTimerCounterReg(XPAR_AXI_TIMER_1_BASEADDR,0);
    	xil_printf("Valor final del timer: %d\r\n\n\n", valor_final_timer);

    /* Start the kernel */
       	xilkernel_start();

    /* Never reached */
        cleanup_platform();

    return 0;
}

/* HILOS ESCRITORES */
void* hilo_escritor_1()
{
	int numero_de_hilo = 1;
	int i;

	for(i=0;i<valor_maximo;i++)
	{
		//Pedir Semaforo
			sem_wait(&mutex);
		//Devolver semaforo
			sem_post(&mutex);
	}
	pthread_exit(NULL);
}

void* hilo_escritor_2()
{
	int numero_de_hilo = 2;
	int i;

	for(i=0;i<valor_maximo;i++)
	{
		//Pedir Semaforo
			sem_wait(&mutex);

		//Devolver semaforo
			sem_post(&mutex);
	}

	pthread_exit(NULL);
}
