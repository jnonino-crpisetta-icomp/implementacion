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
#include "xgpio.h"

/* Declarations */
#define DATA_SIZE   400
#define N_THREADS   4
//-----------------------------------------------------
#define LED 0x01   /* Assumes bit 0 of GPIO is connected to an LED  */

/*
 * The following constant maps to the name of the hardware instances that
 * were created in the EDK XPS system.
 */
#define GPIO_EXAMPLE_DEVICE_ID  XPAR_LEDS_POSITIONS_DEVICE_ID

/*
 * The following constant is used to wait after an LED is turned on to make
 * sure that it is visible to the human eye.  This constant might need to be
 * tuned for faster or slower processor speeds.
 */
#define LED_DELAY     1000000

/*
 * The following constant is used to determine which channel of the GPIO is
 * used for the LED if there are 2 channels supported.
 */
#define LED_CHANNEL 1
u32 Data;
/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/

#ifdef PRE_2_00A_APPLICATION

/*
 * The following macros are provided to allow an application to compile that
 * uses an older version of the driver (pre 2.00a) which did not have a channel
 * parameter. Note that the channel parameter is fixed as channel 1.
 */
#define XGpio_SetDataDirection(InstancePtr, DirectionMask) \
        XGpio_SetDataDirection(InstancePtr, LED_CHANNEL, DirectionMask)

#define XGpio_DiscreteRead(InstancePtr) \
        XGpio_DiscreteRead(InstancePtr, LED_CHANNEL)

#define XGpio_DiscreteWrite(InstancePtr, Mask) \
        XGpio_DiscreteWrite(InstancePtr, LED_CHANNEL, Mask)

#define XGpio_DiscreteSet(InstancePtr, Mask) \
        XGpio_DiscreteSet(InstancePtr, LED_CHANNEL, Mask)

#endif

/************************** Function Prototypes ******************************/


/************************** Variable Definitions *****************************/

/*
 * The following are declared globally so they are zeroed and so they are
 * easily accessible from a debugger
 */

XGpio Gpio; /* The Instance of the GPIO Driver */

/*****************************************************************************/
/**
*
* The purpose of this function is to illustrate how to use the GPIO level 1
* driver to turn on and off an LED.
*
* @param	None
*
* @return	XST_FAILURE to indicate that the GPIO Intialisation had failed.
*
* @note		This function will not return if the test is running.
*
******************************************************************************/
//-----------------------------------------------------


void* master_thread(void *);
void* partial_sum_worker(void *);

/* Data */
int input_data[DATA_SIZE];


/* Functions */
int main()
{
    int i;

    init_platform();
    
    /* Assign random data to the input array */
    for (i = 0; i < DATA_SIZE; i++)
        input_data[i] = i + 1;

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
    pthread_t worker[N_THREADS];
    pthread_attr_t attr;

#if SCHED_TYPE == SCHED_PRIO
    struct sched_param spar;
#endif

    int i, ret, *result;
    int args[N_THREADS];
    int final_result;


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
        Data=i;
        ret = pthread_create (&worker[i], &attr, (void*)partial_sum_worker, 
                              &args[i]);

		XGpio_DiscreteWrite(&Gpio, LED_CHANNEL, Data);
		int Delay;
		for (Delay = 0; Delay < LED_DELAY; Delay++);

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
