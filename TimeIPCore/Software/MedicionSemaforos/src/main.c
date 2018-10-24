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

#define valor_maximo 10000

/* Threads */
void* master_thread(void *);

/* Timer */
XTmrCtr *timer;

/* Semaphores */
sem_t  semaforo;

/* Functions */
int main()
{
    init_platform();
    xil_printf("INICIO EJECUCION CON SEMAFOROS\r\n");
    xil_printf("Valor Maximo = %d \r\n\n",valor_maximo);

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


	status = sem_init(&semaforo, 1, 1);
   	if(status == 0)
  	{//	print("Semaforo creado correctamente\r\n\n");

  	}
    else
  	{
   		print("Error al crear el semaforo\r\n\n");
  		pthread_exit(NULL);
   	}

    int i;
 	unsigned int valor_inicial_timer;
    int ControlStatus;
  	unsigned int valor_final_timer;

    //Iniciar cuenta de tiempo
      	XTmrCtr_SetControlStatusReg(XPAR_AXI_TIMER_1_BASEADDR,0,0x0);
      	XTmrCtr_SetLoadReg(XPAR_AXI_TIMER_1_BASEADDR, 0, 0x00000000);
       	XTmrCtr_LoadTimerCounterReg	(XPAR_AXI_TIMER_1_BASEADDR,0);
       	ControlStatus = XTmrCtr_GetControlStatusReg(XPAR_AXI_TIMER_1_BASEADDR,0);
       	XTmrCtr_SetControlStatusReg(XPAR_AXI_TIMER_1_BASEADDR, 0, ControlStatus & (~XTC_CSR_LOAD_MASK));
       	valor_inicial_timer = XTmrCtr_GetTimerCounterReg(XPAR_AXI_TIMER_1_BASEADDR,0);
       	xil_printf("Valor inicial del timer: %d\r\n\n", valor_inicial_timer);
       	XTmrCtr_Enable(XPAR_AXI_TIMER_1_BASEADDR, 0);

       	for(i=0;i<valor_maximo;i++)
       	{
       		sem_wait(&semaforo);

       		sem_post(&semaforo);
       	}

    //Terminar cuenta de tiempo
       	valor_final_timer = XTmrCtr_GetTimerCounterReg(XPAR_AXI_TIMER_1_BASEADDR,0);
       	xil_printf("Valor final del timer: %d\r\n\n\n", valor_final_timer);

    return (void*)0;
}
