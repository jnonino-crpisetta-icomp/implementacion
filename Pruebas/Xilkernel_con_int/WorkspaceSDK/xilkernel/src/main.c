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
#include "xintc.h"
#include "xintc_l.h"
#include "xstatus.h"

/* Declarations */
#define DATA_SIZE   400
#define N_THREADS   4

void* master_thread(void *);
void* partial_sum_worker(void *);

/* Data */
int input_data[DATA_SIZE];
Xuint32 *cont_cero_ctrl =(Xuint32*)XPAR_CONTADOR_0_BASEADDR;
Xuint32 *cont_cero_limite =(Xuint32*)(XPAR_CONTADOR_0_BASEADDR+0x4);
Xuint32 *cont_cero_cant_int =(Xuint32*)(XPAR_CONTADOR_0_BASEADDR+0x8);

/* Functions */
void cont_cero_int_handler(void* baseaddr_p){
	int i;
	 xil_printf("Contador 0 Interrupt \r\n");
	 xil_printf("Contidad 0 Interrupciones %x\r\n",*cont_cero_cant_int);
	 *cont_cero_ctrl=0x80000000;
	 for(i=0;i<10000;i++){}
	 *cont_cero_ctrl=0xC0000000;
}

int main()
{
    int i;

    init_platform();
    *cont_cero_ctrl=0x00000000;//resetear
    *cont_cero_limite=0x01FFFFFF;
    xil_printf("contador 0 Limite %x \r\n",*cont_cero_limite);
    /* Assign random data to the input array */

    
 //   for (i = 0; i < DATA_SIZE; i++)
   //     input_data[i] = i + 1;

    /* Initialize xilkernel */
    xilkernel_init();

    xil_printf("Inicializar \r\n");

    XIntc_RegisterHandler(XPAR_INTC_SINGLE_BASEADDR,XPAR_MICROBLAZE_0_INTC_CONTADOR_0_INTERRUPT_INTR,(XInterruptHandler)cont_cero_int_handler,(void *)XPAR_INTC_SINGLE_BASEADDR);
    XIntc_MasterEnable(XPAR_MICROBLAZE_0_INTC_BASEADDR);
    XIntc_EnableIntr(XPAR_MICROBLAZE_0_INTC_BASEADDR, XPAR_CONTADOR_0_INTERRUPT_MASK);
    xil_printf("Fin avilitacion \r\n");

    *cont_cero_ctrl=0xC0000000;
    microblaze_enable_interrupts();

    /* Create the master thread */
 //   xmk_add_static_thread(master_thread, 0);
    
    /* Start the kernel */
    xilkernel_start();
    
    /* Never reached */
  //  cleanup_platform();
    
    return 0;
}

/* The master thread */
void* master_thread(void *arg)
{
    pthread_t worker[N_THREADS];
    pthread_attr_t attr;

#if SCHED_TYPE == SCHED_PRIO
    struct sched_param spar;
#endif

    int i, ret, *result;
    int args[N_THREADS];
    int final_result;

    xil_printf("----------------------------------------------------------------------------\r\n");
    xil_printf("Xilkernel POSIX Threads Demo\r\n");
    xil_printf("----------------------------------------------------------------------------\r\n");
    xil_printf("This Xilkernel based application provides a simple example of how to create\r\n"
               "multiple POSIX threads and synchronize with them when they are complete. This\r\n"
               "example creates an initial master thread. The master thread creates 4 worker\r\n"
               "threads that go off to compute the sum of subsets of a randomly created array\r\n"
               "and return the partial sum as the result. The master thread accumulates the\r\n"
               "partial sums and prints the result. This example can serve as your starting\r\n"
               "point for your end application thread structure.\r\n");
    xil_printf("----------------------------------------------------------------------------\r\n\r\n");

    xil_printf("Xilkernel Demo: Master Thread Starting.\r\n");

    pthread_attr_init (&attr);              
                                            
#if SCHED_TYPE == SCHED_PRIO
    spar.sched_priority = PRIO_HIGHEST;
    pthread_attr_setschedparam(&attr, &spar);
#endif

    /* This is how we can join with a thread and reclaim its return value */
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (i = 0; i < N_THREADS; i++) {
        args[i] = i;
        ret = pthread_create (&worker[i], &attr, (void*)partial_sum_worker, 
                              &args[i]);

        if (ret != 0) {
            xil_printf ("Xilkernel Demo: ERROR (%d) launching worker thread" \
                        "%d.\r\n", ret, i);  
            break;
        }
    }   

    if (ret) {
        xil_printf("Xilkernel Demo: Master Thread Terminating.\r\n");
        return (void*)-1;
    }

    final_result = 0;
    for (i = 0; i < N_THREADS; i++) {
        ret = pthread_join(worker[i], (void*)&result);
        final_result += (int)result;
        xil_printf("Xilkernel Demo: Collected result (%d) from worker: %d.\r\n", 
                   (int)result, i);
    }

    xil_printf("Xilkernel Demo: Result computed by worker threads = %d.\r\n", 
               final_result);

    xil_printf("Xilkernel Demo: Master Thread Completing.\r\n");
    return (void*)0;
}

/* The worker thread */
void* partial_sum_worker(void *arg)
{
    int i, psum;
    int my_id = *((int*)arg);
    int subarray_len = (DATA_SIZE / N_THREADS);
    int start = my_id * subarray_len;
    int end = start + subarray_len;

    psum = 0;
    for (i = start; i < end; i++) 
        psum += input_data[i];

    /* This is how return a value to the parent */
    pthread_exit((void*)psum);
    return NULL;
}
