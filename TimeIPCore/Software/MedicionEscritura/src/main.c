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
#include "xutil.h"
#include "sys/intr.h"
#include "xtmrctr_l.h"

/* Declarations */
#define valor_maximo 10000

void* master_thread(void *);

/* Data */
int cuentas=0;

/* Functions */
int main()
{
    init_platform();
    xil_printf("MEDICION DE TIEMPO DE ESCRITURA\r\n");
    xil_printf("Valor Maximo = %d \r\n\n",valor_maximo);

    /* Initialize xilkernel */
    	xilkernel_init();

    /* Create the master thread */
    	xmk_add_static_thread(master_thread, 0);
    
    /* Start the kernel */
    	xilkernel_start();
    
    /* Never reached */
    	cleanup_platform();
    
    return 0;
}

/* The master thread */
void* master_thread(void *arg)
{
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

    	while(cuentas<valor_maximo)
    	{ 	cuentas=cuentas+1; }

    //Terminar cuenta de tiempo
       	valor_final_timer = XTmrCtr_GetTimerCounterReg(XPAR_AXI_TIMER_1_BASEADDR,0);
       	xil_printf("Valor final del timer: %d\r\n\n\n", valor_final_timer);

    return (void*)0;
}
