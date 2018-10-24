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
#include "sys/timer.h"
#include "config/config_param.h"
#include "stdio.h"
#include "xparameters.h"
#include "platform.h"
#include "platform_config.h"
#include <pthread.h>
#include <sys/types.h>
#include "xutil.h"
#include "xtmrctr_l.h"
#include "semaphore.h"
#include "sys/intr.h"
//#include "xtmrctr.h"



#define factor_frecuencia_segundos 75000000
#define hora_en_milisegundos 3600000
#define sleep_hora hora_en_milisegundos/factor_frecuencia_segundos


#define mesas 5
void* cortar();
void* lijar();
void* pintar();
void* secar();
void* armar();
void petri_intr_handler();
pthread_t hilo_cortador;
pthread_t hilo_lijador;
pthread_t hilo_pintor;
pthread_t hilo_secador;
pthread_t hilo_armador;
sem_t semaforos[5];
sem_t console_mutex;

//Funciones
void mostrar_marcado();

/* Data */
sem_t sem_acceso_materia_prima;
int cantidad_materia_prima = 5;
sem_t sem_acceso_cortadas;
int cantidad_patas_cortadas = 0;
int cantidad_tablas_cortadas = 0;
sem_t sem_acceso_lijadas;
int cantidad_patas_lijadas = 0;
int cantidad_tablas_lijadas = 0;
sem_t sem_acceso_pintadas;
int cantidad_patas_pintadas = 0;
int cantidad_tablas_pintadas = 0;
sem_t sem_acceso_secadas;
int cantidad_patas_secadas = 0;
int cantidad_tablas_secadas = 0;
sem_t sem_acceso_armadas;
int cantidad_mesas_armadas = 0;

/* Functions */
int main()
{
    init_platform();
    
    /* Initialize xilkernel */
    	xilkernel_init();
    
   	xil_printf("INICIO EJECUCION SEMAFOROS\r\n\n");
   	xil_printf("MESAS= %d\r\n\n",mesas);

   		int status;
	    status=0;
		status = status + sem_init(&sem_acceso_cortadas, 1, 1);
		status = status + sem_init(&sem_acceso_lijadas, 1, 1);
		status = status + sem_init(&sem_acceso_pintadas, 1, 1);
		status = status + sem_init(&sem_acceso_secadas, 1, 1);
		status = status + sem_init(&sem_acceso_armadas, 1, 1);
		status = status + sem_init(&console_mutex, 1, 1);
    	if(status == 0)
    	{	//print("\nSemaforos creado correctamente\r\n");

    	}
    	else
    	{
    		print("Error al crear el semaforo\r\n");
    		pthread_exit(NULL);
    	}

	//Espero
		int i;
		for (i=0 ; i<50000 ; i++) {}

    pthread_attr_t attr;

	#if SCHED_TYPE == SCHED_PRIO
    	struct sched_param spar;
	#endif

    pthread_attr_init (&attr);

    unsigned int valor_inicial_timer;
    int ControlStatus;
   	unsigned int valor_final_timer;

int a;
    //Iniciar cuenta de tiempo
		XTmrCtr_SetControlStatusReg(XPAR_AXI_TIMER_1_BASEADDR,0,0x0);
		XTmrCtr_SetLoadReg(XPAR_AXI_TIMER_1_BASEADDR, 0, 0x00000000);
		XTmrCtr_LoadTimerCounterReg	(XPAR_AXI_TIMER_1_BASEADDR,0);
		ControlStatus = XTmrCtr_GetControlStatusReg(XPAR_AXI_TIMER_1_BASEADDR,0);
		XTmrCtr_SetControlStatusReg(XPAR_AXI_TIMER_1_BASEADDR, 0, ControlStatus & (~XTC_CSR_LOAD_MASK));
		valor_inicial_timer = XTmrCtr_GetTimerCounterReg(XPAR_AXI_TIMER_1_BASEADDR,0);
		xil_printf("\r\n\nValor inicial del timer: %d\r\n\n", valor_inicial_timer);
		XTmrCtr_Enable(XPAR_AXI_TIMER_1_BASEADDR, 0);

    //Lanzamiendo de los hilos escritores
		status = pthread_create(&hilo_cortador, NULL, (void*)cortar, NULL);
		status = pthread_create(&hilo_lijador, NULL, (void*)lijar, NULL);
		status = pthread_create(&hilo_pintor, NULL, (void*)pintar, NULL);
		status = pthread_create(&hilo_secador, NULL, (void*)secar, NULL);
		status = pthread_create(&hilo_armador, NULL, (void*)armar, NULL);


		pthread_join(&hilo_armador, (void*)&a);

    //Terminar cuenta de tiempo
       	valor_final_timer = XTmrCtr_GetTimerCounterReg(XPAR_AXI_TIMER_1_BASEADDR,0);
       	xil_printf("Valor final del timer: %d\r\n", valor_final_timer);
       	xil_printf("Cantidad de mesas: %d\r\n\n\n", cantidad_mesas_armadas );
    	/* Start the kernel */
     	xilkernel_start();

    /* Never reached */
       	cleanup_platform();

    return 0;
}

/* HILOS */

void* cortar()
{

	while(1)
	{
		//Extraer materia prima
			if (cantidad_materia_prima > 0)
			{
				sem_wait(&sem_acceso_materia_prima);
				cantidad_materia_prima = cantidad_materia_prima - 1;
				sem_post(&sem_acceso_materia_prima);
			}
			else
			{	pthread_exit(NULL);}

		//Cortar

		//Poner elementos en materiales cortados
			while (cantidad_patas_cortadas > 4 && cantidad_tablas_cortadas > 1)
			{
				//Esperar para no superar la cota de plazas
			}
			sem_wait(&sem_acceso_cortadas);
			cantidad_patas_cortadas = cantidad_patas_cortadas + 4;
			cantidad_tablas_cortadas = cantidad_tablas_cortadas + 1;
			sem_post(&sem_acceso_cortadas);
/*
			i=i+1;
			sem_wait(&console_mutex);
			xil_printf("Mesa %d: CORTADA\r\n",i);
			sem_post(&console_mutex);
*/	}//Fin del while
	pthread_exit(NULL);
}

void* lijar()
{

	while(1)
	{
		//Extraer elementos cortados
			while (cantidad_patas_cortadas < 4 && cantidad_tablas_cortadas < 1)
			{
				//Espera hasta que haya elementos para lijar
			}
			sem_wait(&sem_acceso_cortadas);
			cantidad_patas_cortadas = cantidad_patas_cortadas - 4;
			cantidad_tablas_cortadas = cantidad_tablas_cortadas - 1;
			sem_post(&sem_acceso_cortadas);

		//Lijar

		//Poner elementos en materiales lijados
			while (cantidad_patas_lijadas != 0 && cantidad_tablas_lijadas != 0)
			{
				//Esperar para no superar la cota de plazas
			}
			sem_wait(&sem_acceso_lijadas);
			cantidad_patas_lijadas = cantidad_patas_lijadas + 4;
			cantidad_tablas_lijadas = cantidad_tablas_lijadas + 1;
			sem_post(&sem_acceso_lijadas);

/*			i=i+1;
			sem_wait(&console_mutex);
			xil_printf("Mesa %d: LIJADA\r\n",i);
			sem_post(&console_mutex);

			if (cantidad_mesas_armadas >= 5)
			{	break;	}
*/
	}//Fin del while
	pthread_exit(NULL);
}

void* pintar()
{

	while (1)
	{
		//Extraer elementos lijados
			while (cantidad_patas_lijadas < 4 && cantidad_tablas_cortadas < 1)
			{
				//Espera hasta que haya elementos para pintar
			}
			sem_wait(&sem_acceso_lijadas);
			cantidad_patas_lijadas = cantidad_patas_lijadas - 4;
			cantidad_tablas_lijadas = cantidad_tablas_lijadas - 1;
			sem_post(&sem_acceso_lijadas);

		//Pintar

		//Poner elementos en materiales pintados
			while (cantidad_patas_pintadas != 0 && cantidad_tablas_pintadas != 0)
			{
				//Esperar para no superar la cota de plazas
			}
			sem_wait(&sem_acceso_pintadas);
			cantidad_patas_pintadas = cantidad_patas_pintadas + 4;
			cantidad_tablas_pintadas = cantidad_tablas_pintadas + 1;
			sem_post(&sem_acceso_pintadas);

		//Escribir en consola
/*			i = i + 1;
			sem_wait(&console_mutex);
			xil_printf("Mesa %d: PINTADA\r\n",i);
			sem_post(&console_mutex);

			if (cantidad_mesas_armadas >= 5)
			{	break;	}
*/
	}//Fin del while
	pthread_exit(NULL);
}

void* secar()
{


	while(1)
	{
		//Extraer elementos secados
			while (cantidad_patas_pintadas < 4 && cantidad_tablas_pintadas < 1)
			{
				//Espera hasta que haya elementos para armar
			}
			sem_wait(&sem_acceso_pintadas);
			cantidad_patas_pintadas = cantidad_patas_pintadas - 4;
			cantidad_tablas_pintadas = cantidad_tablas_pintadas - 1;
			sem_post(&sem_acceso_pintadas);

		//Armar

		//Poner elementos en mesas armadas
			while (cantidad_patas_secadas > 4 && cantidad_tablas_secadas > 1)
			{
				//Esperar para no superar la cota de plazas
			}
			sem_wait(&sem_acceso_armadas);
			cantidad_patas_secadas = cantidad_patas_secadas + 4;
			cantidad_tablas_secadas = cantidad_tablas_secadas + 1;
			sem_post(&sem_acceso_secadas);

		//Escribir en la consola
/*			i=i+1;
			sem_wait(&console_mutex);
			xil_printf("Mesa %d: SECADA\r\n",i);
			sem_post(&console_mutex);

			if (cantidad_mesas_armadas >= 5)
			{	break;	}
*/
	}//Fin del while
	pthread_exit(NULL);
}

void* armar(){
	int disparo_t_cuatro= 0x00040000;
	int i=0;
	while(cantidad_mesas_armadas < 5)
	{
		//Extraer elementos secados
			while (cantidad_patas_secadas < 4 && cantidad_tablas_secadas < 1)
			{
				//Espera hasta que haya elementos para secar
			}
			sem_wait(&sem_acceso_secadas);
			cantidad_patas_secadas = cantidad_patas_secadas - 4;
			cantidad_tablas_secadas = cantidad_tablas_secadas - 1;
			sem_post(&sem_acceso_secadas);

		//Secar

		//Poner elementos en materiales secados
			if (cantidad_mesas_armadas < 5)
			{
				sem_wait(&sem_acceso_secadas);
				cantidad_mesas_armadas = cantidad_mesas_armadas + 1;
				sem_post(&sem_acceso_armadas);
			}

		//Imprimir en consola
			//i=i+1;
			/*			sem_wait(&console_mutex);
			xil_printf("Mesa %d: ARMADA\r\n",i);

			if (cantidad_mesas_armadas >= 5)
			{
				xil_printf("SE ARMARON %d MESAS\r\n\n",cantidad_mesas_armadas);
			}
			sem_post(&console_mutex);
*/
	}//Fin del while
	pthread_exit(NULL);
}
