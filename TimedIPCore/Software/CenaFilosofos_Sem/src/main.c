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
#include "xtmrctr_l.h"
#include "semaphore.h"

/* Declarations */
#define maximo_comidas_cada_filosofo 10

#define maximo_comidas_filosofo_uno maximo_comidas_cada_filosofo
#define maximo_comidas_filosofo_dos maximo_comidas_cada_filosofo
#define maximo_comidas_filosofo_tres maximo_comidas_cada_filosofo

#define una_hora 0.048 //Considerando un segundo como un pulso de clock a 75 MHz (el valor esta en milisegundos)

void* master_thread(void *);
void* filosofo_uno();
void* filosofo_dos();
void* filosofo_tres();

/* Data */
sem_t console_mutex;
int cantidad_comidas_filosofo_uno = 0;
int cantidad_comidas_filosofo_dos = 0;
int cantidad_comidas_filosofo_tres = 0;

sem_t sem_acceso_tenedor_uno_izq;
sem_t sem_acceso_tenedor_dos_izq;
sem_t sem_acceso_tenedor_tres_izq;

/* Functions */
int main()
{
    init_platform();
    
    xil_printf("INICIO DE EJECUCION SEMAFOROS - %d Comidas para cada filosofo", maximo_comidas_cada_filosofo);

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
	pthread_t hilo_filosofo_uno;
	pthread_t hilo_filosofo_dos;
	pthread_t hilo_filosofo_tres;
	pthread_attr_t attr;

    int status;
   	unsigned int valor_inicial_timer;
    int ControlStatus;
   	unsigned int valor_final_timer;

	#if SCHED_TYPE == SCHED_PRIO
    	struct sched_param spar;
	#endif

    pthread_attr_init (&attr);              
                                            
	#if SCHED_TYPE == SCHED_PRIO
    	spar.sched_priority = PRIO_HIGHEST;
    	pthread_attr_setschedparam(&attr, &spar);
	#endif

    /* This is how we can join with a thread and reclaim its return value */
    	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    	status=0;
    	status = status + sem_init(&sem_acceso_tenedor_uno_izq, 1, 1);
    	status = status + sem_init(&sem_acceso_tenedor_uno_izq, 1, 1);
    	status = status + sem_init(&sem_acceso_tenedor_uno_izq, 1, 1);
    	status = status + sem_init(&console_mutex, 1, 1);
    	if(status == 0)
    	{	print("\r\nSemaforos creado correctamente\r\n");	}
    	else
    	{
    		print("Error al crear el semaforo\r\n");
    		pthread_exit(NULL);
    	}

    int * comidas_uno;
    int * comidas_dos;
    int * comidas_tres;

    //Iniciar cuenta de tiempo
    	XTmrCtr_SetControlStatusReg(XPAR_AXI_TIMER_1_BASEADDR,0,0x0);
    	XTmrCtr_SetLoadReg(XPAR_AXI_TIMER_1_BASEADDR, 0, 0x00000000);
       	XTmrCtr_LoadTimerCounterReg	(XPAR_AXI_TIMER_1_BASEADDR,0);
       	ControlStatus = XTmrCtr_GetControlStatusReg(XPAR_AXI_TIMER_1_BASEADDR,0);
       	XTmrCtr_SetControlStatusReg(XPAR_AXI_TIMER_1_BASEADDR, 0, ControlStatus & (~XTC_CSR_LOAD_MASK));
       	valor_inicial_timer = XTmrCtr_GetTimerCounterReg(XPAR_AXI_TIMER_1_BASEADDR,0);
       	xil_printf("\r\n\nValor inicial del timer: %d\r\n\n", valor_inicial_timer);
       	XTmrCtr_Enable(XPAR_AXI_TIMER_1_BASEADDR, 0);

    status = pthread_create(&hilo_filosofo_uno, &attr, (void*)filosofo_uno, NULL);
//      	if (status != 0)	{  	xil_printf ("ERROR LANZANDO HILO FILOSOFO UNO");	}
    status = pthread_create(&hilo_filosofo_dos, &attr, (void*)filosofo_dos, NULL);
//       	if (status != 0)	{	xil_printf ("ERROR LANZANDO HILO FILOSOFO DOS");	}
    status = pthread_create(&hilo_filosofo_tres, &attr, (void*)filosofo_tres, NULL);
//       	if (status != 0)	{	xil_printf ("ERROR LANZANDO HILO FILOSOFO TRES");	}

	pthread_join(hilo_filosofo_uno,(void*)&comidas_uno);
	pthread_join(hilo_filosofo_dos,(void*)&comidas_dos);
	pthread_join(hilo_filosofo_tres,(void*)&comidas_tres);

    //Terminar cuenta de tiempo
       	valor_final_timer = XTmrCtr_GetTimerCounterReg(XPAR_AXI_TIMER_1_BASEADDR,0);
       	xil_printf("Valor final del timer: %d\r\n\n", valor_final_timer);

    return (void*)0;
}

void* filosofo_uno()
{
	int i=0;

	while(cantidad_comidas_filosofo_uno>maximo_comidas_filosofo_uno)
	{
		//Tomar el tenedor de su izquierda
			sem_wait(&sem_acceso_tenedor_uno_izq);
		//Tomar el tenedor de su derecha
			sem_wait(&sem_acceso_tenedor_tres_izq);

		//Comer
			sleep(una_hora);

		//Devolver el tenedor de su izquierda
			sem_post(&sem_acceso_tenedor_uno_izq);
		//Devolver el tenedor de su derecha
			sem_post(&sem_acceso_tenedor_tres_izq);

		i=i+1;
		sem_wait(&console_mutex);
			xil_printf("FILOSOFO 1: Comio %d veces\r\n",i);
		sem_post(&console_mutex);

	}//Fin del while
	pthread_exit((void*)i);
	return NULL;
}

void* filosofo_dos()
{
	int i=0;

	while(cantidad_comidas_filosofo_dos > maximo_comidas_filosofo_dos)
	{
		//Tomar el tenedor de su izquierda
			sem_wait(&sem_acceso_tenedor_dos_izq);
		//Tomar el tenedor de su derecha
			sem_wait(&sem_acceso_tenedor_uno_izq);

		//Comer
			sleep(una_hora);

		//Devolver el tenedor de su izquierda
			sem_post(&sem_acceso_tenedor_dos_izq);
		//Devolver el tenedor de su derecha
			sem_post(&sem_acceso_tenedor_uno_izq);

		i=i+1;
		sem_wait(&console_mutex);
			xil_printf("FILOSOFO 2: Comio %d veces\r\n",i);
		sem_post(&console_mutex);

	}//Fin del while
	pthread_exit((void*)i);
	return NULL;
}

void* filosofo_tres()
{
	int i=0;

	while(cantidad_comidas_filosofo_tres > maximo_comidas_filosofo_tres)
	{
		//Tomar el tenedor de su izquierda
			sem_wait(&sem_acceso_tenedor_tres_izq);
		//Tomar el tenedor de su derecha
			sem_wait(&sem_acceso_tenedor_dos_izq);

		//Comer
			sleep(una_hora);

		//Devolver el tenedor de su izquierda
			sem_post(&sem_acceso_tenedor_tres_izq);
		//Devolver el tenedor de su derecha
			sem_post(&sem_acceso_tenedor_dos_izq);

		i=i+1;
		sem_wait(&console_mutex);
			xil_printf("FILOSOFO 3: Comio %d veces\r\n",i);
		sem_post(&console_mutex);

	}//Fin del while
	pthread_exit((void*)i);
	return NULL;
}
