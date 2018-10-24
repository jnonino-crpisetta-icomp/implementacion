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
#include "xutil.h"
#include "xtmrctr_l.h"
#include "semaphore.h"
#include "sys/intr.h"
//#include "xtmrctr.h"

/* Declarations */
#define N_THREADS   4
#define tiempo_espera_entre_cargas	5000
#define mesas 5



#define disparo_t_cero 	  0x00000000
#define disparo_t_uno 	  0x00010000
#define disparo_t_dos 	  0x00020000
#define disparo_t_tres 	  0x00030000
#define disparo_t_cuatro  0x00040000
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
int disparos[10];
//Funciones 
void mostrar_marcado();

/* Data */
int cantidad_plazas = 10;
int cantidad_transiciones = 10;
int cantidad_palabras_vector_tiempo = 3;
static int cantidad_de_mesas = 0;

//Direcciones para escribir en Petri
	Xuint32 *m_marcado_addr    						= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR);
	Xuint32 *m_incidencia_addr 						= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x4);
	Xuint32 *m_inhibicion_addr 						= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x8);
	Xuint32 *p_cotas_addr							= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0xC);
	Xuint32 *t_automatica_addr 						= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x10);
	Xuint32 *load_vector_EFT_addr					= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x14);
	Xuint32 *load_vector_incrementos_tiempo_addr 	= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x18);
	Xuint32 *load_vector_LFT_addr					= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x1C);
	Xuint32 *new_disparo_addr  						= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x20);
	Xuint32 *sacar_disparo_addr						= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x24);
	Xuint32 *t_intr_addr							= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x28);
	Xuint32 *prioridades							= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x2C);
	Xuint32 *error_addr								= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x30);

//Direcciones para leer en Petri
	Xuint32 *leer_disparos_en_espera				= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x34);
	Xuint32 *leer_disparos_posibles					= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x38);
	Xuint32 *leer_disparos_ejecutados				= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x3C);
	Xuint32 *leer_t_num								= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x40);
	Xuint32 *red_activa								= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x44);
	Xuint32 *leer_marcado_p_cero					= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x48);
	Xuint32 *leer_marcado_p_uno						= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x4C);
	Xuint32 *leer_marcado_p_dos						= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x50);
	Xuint32 *leer_marcado_p_tres					= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x54);
	Xuint32 *leer_marcado_p_cuatro					= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x58);
	Xuint32 *leer_marcado_p_cinco					= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x5C);
	Xuint32 *leer_marcado_p_seis					= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x60);
	Xuint32 *leer_marcado_p_siete					= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x64);
	Xuint32 *leer_marcado_p_ocho					= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x68);
	Xuint32 *leer_marcado_p_nueve					= (Xuint32 *)(XPAR_PETRI_AXI_INT_0_BASEADDR + 0x6C);
                                                                                                    
/* Functions */
int main()
{
    init_platform();
    
    /* Initialize xilkernel */
    	xilkernel_init();
    
   	xil_printf("INICIO EJECUCION PETRI\r\n");
   	xil_printf("MESAS= %d\r\n\n",mesas);
    //Carga de datos
		int matriz_incidencia [cantidad_plazas][cantidad_transiciones];
			matriz_incidencia[0][0] = 0x0000FFFF;
		   	matriz_incidencia[0][1] = 0x00010000;
		   	matriz_incidencia[0][2] = 0x00020000;
		   	matriz_incidencia[0][3] = 0x00030000;
		   	matriz_incidencia[0][4] = 0x00040000;
		   	matriz_incidencia[0][5] = 0x00050000;
		   	matriz_incidencia[0][6] = 0x00060000;
		   	matriz_incidencia[0][7] = 0x00070000;
		   	matriz_incidencia[0][8] = 0x00080000;
		   	matriz_incidencia[0][9] = 0x00090000;

		   	matriz_incidencia[1][0] = 0x01000004;
		   	matriz_incidencia[1][1] = 0x0101FFFC;
		   	matriz_incidencia[1][2] = 0x01020000;
		   	matriz_incidencia[1][3] = 0x01030000;
	    	matriz_incidencia[1][4] = 0x01040000;
	    	matriz_incidencia[1][5] = 0x01050000;
	    	matriz_incidencia[1][6] = 0x01060000;
	    	matriz_incidencia[1][7] = 0x01070000;
	    	matriz_incidencia[1][8] = 0x01080000;
	    	matriz_incidencia[1][9] = 0x01090000;

		   	matriz_incidencia[2][0] = 0x02000001;
		   	matriz_incidencia[2][1] = 0x0201FFFF;
		   	matriz_incidencia[2][2] = 0x02020000;
		   	matriz_incidencia[2][3] = 0x02030000;
	    	matriz_incidencia[2][4] = 0x02040000;
	    	matriz_incidencia[2][5] = 0x02050000;
	    	matriz_incidencia[2][6] = 0x02060000;
	    	matriz_incidencia[2][7] = 0x02070000;
	    	matriz_incidencia[2][8] = 0x02080000;
	    	matriz_incidencia[2][9] = 0x02090000;

	    	matriz_incidencia[3][0] = 0x03000000;
	    	matriz_incidencia[3][1] = 0x03010004;
	    	matriz_incidencia[3][2] = 0x0302FFFC;
	    	matriz_incidencia[3][3] = 0x03030000;
	    	matriz_incidencia[3][4] = 0x03040000;
	    	matriz_incidencia[3][5] = 0x03050000;
	    	matriz_incidencia[3][6] = 0x03060000;
	    	matriz_incidencia[3][7] = 0x03070000;
	    	matriz_incidencia[3][8] = 0x03080000;
	    	matriz_incidencia[3][9] = 0x03090000;

	    	matriz_incidencia[4][0] = 0x04000000;
	    	matriz_incidencia[4][1] = 0x04010001;
	    	matriz_incidencia[4][2] = 0x0402FFFF;
	    	matriz_incidencia[4][3] = 0x04030000;
	    	matriz_incidencia[4][4] = 0x04040000;
	    	matriz_incidencia[4][5] = 0x04050000;
	    	matriz_incidencia[4][6] = 0x04060000;
	    	matriz_incidencia[4][7] = 0x04070000;
	    	matriz_incidencia[4][8] = 0x04080000;
	    	matriz_incidencia[4][9] = 0x04090000;

	    	matriz_incidencia[5][0] = 0x05000000;
	    	matriz_incidencia[5][1] = 0x05010000;
	    	matriz_incidencia[5][2] = 0x05020004;
	    	matriz_incidencia[5][3] = 0x0503FFFC;
	    	matriz_incidencia[5][4] = 0x05040000;
	    	matriz_incidencia[5][5] = 0x05050000;
	    	matriz_incidencia[5][6] = 0x05060000;
	    	matriz_incidencia[5][7] = 0x05070000;
	    	matriz_incidencia[5][8] = 0x05080000;
	    	matriz_incidencia[5][9] = 0x05090000;

	    	matriz_incidencia[6][0] = 0x06000000;
	    	matriz_incidencia[6][1] = 0x06010000;
	    	matriz_incidencia[6][2] = 0x06020001;
	    	matriz_incidencia[6][3] = 0x0603FFFF;
	    	matriz_incidencia[6][4] = 0x06040000;
	    	matriz_incidencia[6][5] = 0x06050000;
	    	matriz_incidencia[6][6] = 0x06060000;
	    	matriz_incidencia[6][7] = 0x06070000;
	    	matriz_incidencia[6][8] = 0x06080000;
	    	matriz_incidencia[6][9] = 0x06090000;

	    	matriz_incidencia[7][0] = 0x07000000;
	    	matriz_incidencia[7][1] = 0x07010000;
	    	matriz_incidencia[7][2] = 0x07020000;
	    	matriz_incidencia[7][3] = 0x07030004;
	    	matriz_incidencia[7][4] = 0x0704FFFC;
	    	matriz_incidencia[7][5] = 0x07050000;
	    	matriz_incidencia[7][6] = 0x07060000;
	    	matriz_incidencia[7][7] = 0x07070000;
	    	matriz_incidencia[7][8] = 0x07080000;
	    	matriz_incidencia[7][9] = 0x07090000;

	    	matriz_incidencia[8][0] = 0x08000000;
	    	matriz_incidencia[8][1] = 0x08010000;
	    	matriz_incidencia[8][2] = 0x08020000;
	    	matriz_incidencia[8][3] = 0x08030001;
	    	matriz_incidencia[8][4] = 0x0804FFFF;
	    	matriz_incidencia[8][5] = 0x08050000;
	    	matriz_incidencia[8][6] = 0x08060000;
	    	matriz_incidencia[8][7] = 0x08070000;
	    	matriz_incidencia[8][8] = 0x08080000;
	    	matriz_incidencia[8][9] = 0x08090000;

	    	matriz_incidencia[9][0] = 0x09000000;
	    	matriz_incidencia[9][1] = 0x09010000;
	    	matriz_incidencia[9][2] = 0x09020000;
	    	matriz_incidencia[9][3] = 0x09030000;
	    	matriz_incidencia[9][4] = 0x09040001;
	    	matriz_incidencia[9][5] = 0x09050000;
	    	matriz_incidencia[9][6] = 0x09060000;
	    	matriz_incidencia[9][7] = 0x09070000;
	    	matriz_incidencia[9][8] = 0x09080000;
	    	matriz_incidencia[9][9] = 0x09090000;

		int matriz_inhibicion [cantidad_plazas][cantidad_transiciones];
	    	matriz_inhibicion[0][0] = 0x00000000;
	    	matriz_inhibicion[0][1] = 0x00010000;
	    	matriz_inhibicion[0][2] = 0x00020000;
	    	matriz_inhibicion[0][3] = 0x00030000;
	    	matriz_inhibicion[0][4] = 0x00040000;
	    	matriz_inhibicion[0][5] = 0x00050000;
	    	matriz_inhibicion[0][6] = 0x00060000;
	    	matriz_inhibicion[0][7] = 0x00070000;
	    	matriz_inhibicion[0][8] = 0x00080000;
	    	matriz_inhibicion[0][9] = 0x00090000;

	    	matriz_inhibicion[1][0] = 0x01000000;
	    	matriz_inhibicion[1][1] = 0x01010000;
	    	matriz_inhibicion[1][2] = 0x01020000;
	    	matriz_inhibicion[1][3] = 0x01030000;
	    	matriz_inhibicion[1][4] = 0x01040000;
	    	matriz_inhibicion[1][5] = 0x01050000;
	    	matriz_inhibicion[1][6] = 0x01060000;
	    	matriz_inhibicion[1][7] = 0x01070000;
	    	matriz_inhibicion[1][8] = 0x01080000;
	    	matriz_inhibicion[1][9] = 0x01090000;

	    	matriz_inhibicion[2][0] = 0x02000000;
	    	matriz_inhibicion[2][1] = 0x02010000;
	    	matriz_inhibicion[2][2] = 0x02020000;
	    	matriz_inhibicion[2][3] = 0x02030000;
	    	matriz_inhibicion[2][4] = 0x02040000;
	    	matriz_inhibicion[2][5] = 0x02050000;
	    	matriz_inhibicion[2][6] = 0x02060000;
	    	matriz_inhibicion[2][7] = 0x02070000;
	    	matriz_inhibicion[2][8] = 0x02080000;
	    	matriz_inhibicion[2][9] = 0x02090000;

	    	matriz_inhibicion[3][0] = 0x03000000;
	    	matriz_inhibicion[3][1] = 0x03010000;
	    	matriz_inhibicion[3][2] = 0x03020000;
	    	matriz_inhibicion[3][3] = 0x03030000;
	    	matriz_inhibicion[3][4] = 0x03040000;
	    	matriz_inhibicion[3][5] = 0x03050000;
	    	matriz_inhibicion[3][6] = 0x03060000;
	    	matriz_inhibicion[3][7] = 0x03070000;
	    	matriz_inhibicion[3][8] = 0x03080000;
	    	matriz_inhibicion[3][9] = 0x03090000;

	    	matriz_inhibicion[4][0] = 0x04000000;
	    	matriz_inhibicion[4][1] = 0x04010000;
	    	matriz_inhibicion[4][2] = 0x04020000;
	    	matriz_inhibicion[4][3] = 0x04030000;
	    	matriz_inhibicion[4][4] = 0x04040000;
	    	matriz_inhibicion[4][5] = 0x04050000;
	    	matriz_inhibicion[4][6] = 0x04060000;
	    	matriz_inhibicion[4][7] = 0x04070000;
	    	matriz_inhibicion[4][8] = 0x04080000;
	    	matriz_inhibicion[4][9] = 0x04090000;

	    	matriz_inhibicion[5][0] = 0x05000000;
	    	matriz_inhibicion[5][1] = 0x05010000;
	    	matriz_inhibicion[5][2] = 0x05020000;
	    	matriz_inhibicion[5][3] = 0x05030000;
	    	matriz_inhibicion[5][4] = 0x05040000;
	    	matriz_inhibicion[5][5] = 0x05050000;
	    	matriz_inhibicion[5][6] = 0x05060000;
	    	matriz_inhibicion[5][7] = 0x05070000;
	    	matriz_inhibicion[5][8] = 0x05080000;
	    	matriz_inhibicion[5][9] = 0x05090000;

	    	matriz_inhibicion[6][0] = 0x06000000;
	    	matriz_inhibicion[6][1] = 0x06010000;
	    	matriz_inhibicion[6][2] = 0x06020000;
	    	matriz_inhibicion[6][3] = 0x06030000;
	    	matriz_inhibicion[6][4] = 0x06040000;
	    	matriz_inhibicion[6][5] = 0x06050000;
	    	matriz_inhibicion[6][6] = 0x06060000;
	    	matriz_inhibicion[6][7] = 0x06070000;
	    	matriz_inhibicion[6][8] = 0x06080000;
	    	matriz_inhibicion[6][9] = 0x06090000;

	    	matriz_inhibicion[7][0] = 0x07000000;
	    	matriz_inhibicion[7][1] = 0x07010000;
	    	matriz_inhibicion[7][2] = 0x07020000;
	    	matriz_inhibicion[7][3] = 0x07030000;
	    	matriz_inhibicion[7][4] = 0x07040000;
	    	matriz_inhibicion[7][5] = 0x07050000;
	    	matriz_inhibicion[7][6] = 0x07060000;
	    	matriz_inhibicion[7][7] = 0x07070000;
	    	matriz_inhibicion[7][8] = 0x07080000;
	    	matriz_inhibicion[7][9] = 0x07090000;

	    	matriz_inhibicion[8][0] = 0x08000000;
	    	matriz_inhibicion[8][1] = 0x08010000;
	    	matriz_inhibicion[8][2] = 0x08020000;
	    	matriz_inhibicion[8][3] = 0x08030000;
	    	matriz_inhibicion[8][4] = 0x08040000;
	    	matriz_inhibicion[8][5] = 0x08050000;
	    	matriz_inhibicion[8][6] = 0x08060000;
	    	matriz_inhibicion[8][7] = 0x08070000;
	    	matriz_inhibicion[8][8] = 0x08080000;
	    	matriz_inhibicion[8][9] = 0x08090000;

	    	matriz_inhibicion[9][0] = 0x09000000;
	    	matriz_inhibicion[9][1] = 0x09010000;
	    	matriz_inhibicion[9][2] = 0x09020000;
	    	matriz_inhibicion[9][3] = 0x09030000;
	    	matriz_inhibicion[9][4] = 0x09040000;
	    	matriz_inhibicion[9][5] = 0x09050000;
	    	matriz_inhibicion[9][6] = 0x09060000;
	    	matriz_inhibicion[9][7] = 0x09070000;
	    	matriz_inhibicion[9][8] = 0x09080000;
	    	matriz_inhibicion[9][9] = 0x09090000;

		int marcado_inicial [cantidad_plazas];
		   	marcado_inicial[0] = 0x0000003F;
		   	marcado_inicial[1] = 0x01000000;
		   	marcado_inicial[2] = 0x02000000;
		   	marcado_inicial[3] = 0x03000000;
		   	marcado_inicial[4] = 0x04000000;
		   	marcado_inicial[5] = 0x05000000;
		   	marcado_inicial[6] = 0x06000000;
		   	marcado_inicial[7] = 0x07000000;
		   	marcado_inicial[8] = 0x08000000;
		   	marcado_inicial[9] = 0x09000000;

		int cotas_plazas [cantidad_plazas];
	    	cotas_plazas[0] = 0x0000003F;
	    	cotas_plazas[1] = 0x01000009;
	    	cotas_plazas[2] = 0x02000003;
	    	cotas_plazas[3] = 0x03000005;
	    	cotas_plazas[4] = 0x04000002;
	    	cotas_plazas[5] = 0x05000005;
	    	cotas_plazas[6] = 0x06000002;
	    	cotas_plazas[7] = 0x07000009;
	    	cotas_plazas[8] = 0x08000003;
	    	cotas_plazas[9] = 0x09000006;

	    int transiciones_automaticas [cantidad_transiciones];
	    	transiciones_automaticas[0] = 0x00000000;
	    	transiciones_automaticas[1] = 0x00010000;
	    	transiciones_automaticas[2] = 0x00020000;
	    	transiciones_automaticas[3] = 0x00030000;
	    	transiciones_automaticas[4] = 0x00040000;
	    	transiciones_automaticas[5] = 0x00050000;
	    	transiciones_automaticas[6] = 0x00060000;
	    	transiciones_automaticas[7] = 0x00070000;
	    	transiciones_automaticas[8] = 0x00080000;
	    	transiciones_automaticas[9] = 0x00090000;

		int vector_EFT [cantidad_transiciones][cantidad_palabras_vector_tiempo];
	    	vector_EFT[0][0] = 0x00001C20;//7200
	    	vector_EFT[0][1] = 0x01000000;
	    	vector_EFT[0][2] = 0x02000000;

	    	vector_EFT[1][0] = 0x00012A30;//10800
	    	vector_EFT[1][1] = 0x01010000;
	    	vector_EFT[1][2] = 0x02010000;

	    	vector_EFT[2][0] = 0x00020708;//1800
	    	vector_EFT[2][1] = 0x01020000;
	    	vector_EFT[2][2] = 0x02020000;

	    	vector_EFT[3][0] = 0x00031518;//5400
	    	vector_EFT[3][1] = 0x01030000;
	    	vector_EFT[3][2] = 0x02030000;

	    	vector_EFT[4][0] = 0x00040E10;//3600
	    	vector_EFT[4][1] = 0x01040000;
	    	vector_EFT[4][2] = 0x02040000;

	    	vector_EFT[5][0] = 0x00050000;
	    	vector_EFT[5][1] = 0x01050000;
	    	vector_EFT[5][2] = 0x02050000;

	    	vector_EFT[6][0] = 0x00060000;
	    	vector_EFT[6][1] = 0x01060000;
	    	vector_EFT[6][2] = 0x02060000;

	    	vector_EFT[7][0] = 0x00070000;
	    	vector_EFT[7][1] = 0x01070000;
	    	vector_EFT[7][2] = 0x02070000;

	    	vector_EFT[8][0] = 0x00080000;
	    	vector_EFT[8][1] = 0x01080000;
	    	vector_EFT[8][2] = 0x02080000;

	    	vector_EFT[9][0] = 0x00090000;
	    	vector_EFT[9][1] = 0x01090000;
	    	vector_EFT[9][2] = 0x02090000;

	    int vector_incrementos [cantidad_transiciones];
		   	vector_incrementos[0] = 0x00000001;
		   	vector_incrementos[1] = 0x00010001;
		   	vector_incrementos[2] = 0x00020001;
		   	vector_incrementos[3] = 0x00030001;
		   	vector_incrementos[4] = 0x00040001;
		   	vector_incrementos[5] = 0x00050001;
		   	vector_incrementos[6] = 0x00060001;
		   	vector_incrementos[7] = 0x00070001;
		   	vector_incrementos[8] = 0x00080001;
		   	vector_incrementos[9] = 0x00090001;

		int vector_LFT [cantidad_transiciones][cantidad_palabras_vector_tiempo];
	    	vector_LFT[0][0] = 0x0000FFFF;
	    	vector_LFT[0][1] = 0x0100FFFF;
	    	vector_LFT[0][2] = 0x0200FFFF;

	    	vector_LFT[1][0] = 0x0001FFFF;
	    	vector_LFT[1][1] = 0x0101FFFF;
	    	vector_LFT[1][2] = 0x0201FFFF;

	    	vector_LFT[2][0] = 0x0002FFFF;
	    	vector_LFT[2][1] = 0x0102FFFF;
	    	vector_LFT[2][2] = 0x0202FFFF;

	    	vector_LFT[3][0] = 0x0003FFFF;
	    	vector_LFT[3][1] = 0x0103FFFF;
	    	vector_LFT[3][2] = 0x0203FFFF;

	    	vector_LFT[4][0] = 0x0004FFFF;
	    	vector_LFT[4][1] = 0x0104FFFF;
	    	vector_LFT[4][2] = 0x0204FFFF;

	    	vector_LFT[5][0] = 0x0005FFFF;
	    	vector_LFT[5][1] = 0x0105FFFF;
	    	vector_LFT[5][2] = 0x0205FFFF;

	    	vector_LFT[6][0] = 0x0006FFFF;
	    	vector_LFT[6][1] = 0x0106FFFF;
	    	vector_LFT[6][2] = 0x0206FFFF;

	    	vector_LFT[7][0] = 0x0007FFFF;
	    	vector_LFT[7][1] = 0x0107FFFF;
	    	vector_LFT[7][2] = 0x0207FFFF;

	    	vector_LFT[8][0] = 0x0008FFFF;
	    	vector_LFT[8][1] = 0x0108FFFF;
	    	vector_LFT[8][2] = 0x0208FFFF;

	    	vector_LFT[9][0] = 0x0009FFFF;
	    	vector_LFT[9][1] = 0x0109FFFF;
	    	vector_LFT[9][2] = 0x0209FFFF;
	
	int transiciones_intr [cantidad_transiciones];		
	    	transiciones_intr[0] = 0x00000001;
	    	transiciones_intr[1] = 0x00010001;
	    	transiciones_intr[2] = 0x00020001;
	    	transiciones_intr[3] = 0x00030001;
	    	transiciones_intr[4] = 0x00040001;
	    	transiciones_intr[5] = 0x00050000;
	    	transiciones_intr[6] = 0x00060000;
	    	transiciones_intr[7] = 0x00070000;
	    	transiciones_intr[8] = 0x00080000;
	    	transiciones_intr[9] = 0x00090000;
			
			
		   	*(m_incidencia_addr) = matriz_incidencia[0][0];
		   	*(m_incidencia_addr) = matriz_incidencia[0][1];
		   	*(m_incidencia_addr) = matriz_incidencia[0][2];
		   	*(m_incidencia_addr) = matriz_incidencia[0][3];
		   	*(m_incidencia_addr) = matriz_incidencia[0][4];
		   	*(m_incidencia_addr) = matriz_incidencia[0][5];
		   	*(m_incidencia_addr) = matriz_incidencia[0][6];
		   	*(m_incidencia_addr) = matriz_incidencia[0][7];
		   	*(m_incidencia_addr) = matriz_incidencia[0][8];
		   	*(m_incidencia_addr) = matriz_incidencia[0][9];

		   	*(m_incidencia_addr) = matriz_incidencia[1][0];
		   	*(m_incidencia_addr) = matriz_incidencia[1][1];
		   	*(m_incidencia_addr) = matriz_incidencia[1][2];
		   	*(m_incidencia_addr) = matriz_incidencia[1][3];
		   	*(m_incidencia_addr) = matriz_incidencia[1][4];
		   	*(m_incidencia_addr) = matriz_incidencia[1][5];
		   	*(m_incidencia_addr) = matriz_incidencia[1][6];
		   	*(m_incidencia_addr) = matriz_incidencia[1][7];
		   	*(m_incidencia_addr) = matriz_incidencia[1][8];
		   	*(m_incidencia_addr) = matriz_incidencia[1][9];

		   	*(m_incidencia_addr) = matriz_incidencia[2][0];
		   	*(m_incidencia_addr) = matriz_incidencia[2][1];
		   	*(m_incidencia_addr) = matriz_incidencia[2][2];
		   	*(m_incidencia_addr) = matriz_incidencia[2][3];
		   	*(m_incidencia_addr) = matriz_incidencia[2][4];
		   	*(m_incidencia_addr) = matriz_incidencia[2][5];
		   	*(m_incidencia_addr) = matriz_incidencia[2][6];
		   	*(m_incidencia_addr) = matriz_incidencia[2][7];
		   	*(m_incidencia_addr) = matriz_incidencia[2][8];
		   	*(m_incidencia_addr) = matriz_incidencia[2][9];

		   	*(m_incidencia_addr) = matriz_incidencia[3][0];
		   	*(m_incidencia_addr) = matriz_incidencia[3][1];
		   	*(m_incidencia_addr) = matriz_incidencia[3][2];
		   	*(m_incidencia_addr) = matriz_incidencia[3][3];
		   	*(m_incidencia_addr) = matriz_incidencia[3][4];
		   	*(m_incidencia_addr) = matriz_incidencia[3][5];
		   	*(m_incidencia_addr) = matriz_incidencia[3][6];
		   	*(m_incidencia_addr) = matriz_incidencia[3][7];
		   	*(m_incidencia_addr) = matriz_incidencia[3][8];
		   	*(m_incidencia_addr) = matriz_incidencia[3][9];

		   	*(m_incidencia_addr) = matriz_incidencia[4][0];
		   	*(m_incidencia_addr) = matriz_incidencia[4][1];
		   	*(m_incidencia_addr) = matriz_incidencia[4][2];
		   	*(m_incidencia_addr) = matriz_incidencia[4][3];
		   	*(m_incidencia_addr) = matriz_incidencia[4][4];
		   	*(m_incidencia_addr) = matriz_incidencia[4][5];
		   	*(m_incidencia_addr) = matriz_incidencia[4][6];
		   	*(m_incidencia_addr) = matriz_incidencia[4][7];
		   	*(m_incidencia_addr) = matriz_incidencia[4][8];
		   	*(m_incidencia_addr) = matriz_incidencia[4][9];

		   	*(m_incidencia_addr) = matriz_incidencia[5][0];
		   	*(m_incidencia_addr) = matriz_incidencia[5][1];
		   	*(m_incidencia_addr) = matriz_incidencia[5][2];
		   	*(m_incidencia_addr) = matriz_incidencia[5][3];
		   	*(m_incidencia_addr) = matriz_incidencia[5][4];
		   	*(m_incidencia_addr) = matriz_incidencia[5][5];
		   	*(m_incidencia_addr) = matriz_incidencia[5][6];
		   	*(m_incidencia_addr) = matriz_incidencia[5][7];
		   	*(m_incidencia_addr) = matriz_incidencia[5][8];
		   	*(m_incidencia_addr) = matriz_incidencia[5][9];

		   	*(m_incidencia_addr) = matriz_incidencia[6][0];
		   	*(m_incidencia_addr) = matriz_incidencia[6][1];
		   	*(m_incidencia_addr) = matriz_incidencia[6][2];
		   	*(m_incidencia_addr) = matriz_incidencia[6][3];
		   	*(m_incidencia_addr) = matriz_incidencia[6][4];
		   	*(m_incidencia_addr) = matriz_incidencia[6][5];
		   	*(m_incidencia_addr) = matriz_incidencia[6][6];
		   	*(m_incidencia_addr) = matriz_incidencia[6][7];
		   	*(m_incidencia_addr) = matriz_incidencia[6][8];
		   	*(m_incidencia_addr) = matriz_incidencia[6][9];

		   	*(m_incidencia_addr) = matriz_incidencia[7][0];
		   	*(m_incidencia_addr) = matriz_incidencia[7][1];
		   	*(m_incidencia_addr) = matriz_incidencia[7][2];
		   	*(m_incidencia_addr) = matriz_incidencia[7][3];
		   	*(m_incidencia_addr) = matriz_incidencia[7][4];
		   	*(m_incidencia_addr) = matriz_incidencia[7][5];
		   	*(m_incidencia_addr) = matriz_incidencia[7][6];
		   	*(m_incidencia_addr) = matriz_incidencia[7][7];
		   	*(m_incidencia_addr) = matriz_incidencia[7][8];
		   	*(m_incidencia_addr) = matriz_incidencia[7][9];

		   	*(m_incidencia_addr) = matriz_incidencia[8][0];
		   	*(m_incidencia_addr) = matriz_incidencia[8][1];
		   	*(m_incidencia_addr) = matriz_incidencia[8][2];
		   	*(m_incidencia_addr) = matriz_incidencia[8][3];
		   	*(m_incidencia_addr) = matriz_incidencia[8][4];
		   	*(m_incidencia_addr) = matriz_incidencia[8][5];
		   	*(m_incidencia_addr) = matriz_incidencia[8][6];
		   	*(m_incidencia_addr) = matriz_incidencia[8][7];
		   	*(m_incidencia_addr) = matriz_incidencia[8][8];
		   	*(m_incidencia_addr) = matriz_incidencia[8][9];

		   	*(m_incidencia_addr) = matriz_incidencia[9][0];
		   	*(m_incidencia_addr) = matriz_incidencia[9][1];
		   	*(m_incidencia_addr) = matriz_incidencia[9][2];
		   	*(m_incidencia_addr) = matriz_incidencia[9][3];
		   	*(m_incidencia_addr) = matriz_incidencia[9][4];
		   	*(m_incidencia_addr) = matriz_incidencia[9][5];
		   	*(m_incidencia_addr) = matriz_incidencia[9][6];
		   	*(m_incidencia_addr) = matriz_incidencia[9][7];
		   	*(m_incidencia_addr) = matriz_incidencia[9][8];
		   	*(m_incidencia_addr) = matriz_incidencia[9][9];

		   	*(m_inhibicion_addr) = matriz_inhibicion[0][0];
		   	*(m_inhibicion_addr) = matriz_inhibicion[0][1];
		   	*(m_inhibicion_addr) = matriz_inhibicion[0][2];
		   	*(m_inhibicion_addr) = matriz_inhibicion[0][3];
		   	*(m_inhibicion_addr) = matriz_inhibicion[0][4];
		   	*(m_inhibicion_addr) = matriz_inhibicion[0][5];
		   	*(m_inhibicion_addr) = matriz_inhibicion[0][6];
		   	*(m_inhibicion_addr) = matriz_inhibicion[0][7];
		   	*(m_inhibicion_addr) = matriz_inhibicion[0][8];
		   	*(m_inhibicion_addr) = matriz_inhibicion[0][9];

		   	*(m_inhibicion_addr) = matriz_inhibicion[1][0];
		   	*(m_inhibicion_addr) = matriz_inhibicion[1][1];
		   	*(m_inhibicion_addr) = matriz_inhibicion[1][2];
		   	*(m_inhibicion_addr) = matriz_inhibicion[1][3];
		   	*(m_inhibicion_addr) = matriz_inhibicion[1][4];
		   	*(m_inhibicion_addr) = matriz_inhibicion[1][5];
		   	*(m_inhibicion_addr) = matriz_inhibicion[1][6];
		   	*(m_inhibicion_addr) = matriz_inhibicion[1][7];
		   	*(m_inhibicion_addr) = matriz_inhibicion[1][8];
		   	*(m_inhibicion_addr) = matriz_inhibicion[1][9];

		   	*(m_inhibicion_addr) = matriz_inhibicion[2][0];
		   	*(m_inhibicion_addr) = matriz_inhibicion[2][1];
		   	*(m_inhibicion_addr) = matriz_inhibicion[2][2];
		   	*(m_inhibicion_addr) = matriz_inhibicion[2][3];
		   	*(m_inhibicion_addr) = matriz_inhibicion[2][4];
		   	*(m_inhibicion_addr) = matriz_inhibicion[2][5];
		   	*(m_inhibicion_addr) = matriz_inhibicion[2][6];
		   	*(m_inhibicion_addr) = matriz_inhibicion[2][7];
		   	*(m_inhibicion_addr) = matriz_inhibicion[2][8];
		   	*(m_inhibicion_addr) = matriz_inhibicion[2][9];

		   	*(m_inhibicion_addr) = matriz_inhibicion[3][0];
		   	*(m_inhibicion_addr) = matriz_inhibicion[3][1];
		   	*(m_inhibicion_addr) = matriz_inhibicion[3][2];
		   	*(m_inhibicion_addr) = matriz_inhibicion[3][3];
		   	*(m_inhibicion_addr) = matriz_inhibicion[3][4];
		   	*(m_inhibicion_addr) = matriz_inhibicion[3][5];
		   	*(m_inhibicion_addr) = matriz_inhibicion[3][6];
		   	*(m_inhibicion_addr) = matriz_inhibicion[3][7];
		   	*(m_inhibicion_addr) = matriz_inhibicion[3][8];
		   	*(m_inhibicion_addr) = matriz_inhibicion[3][9];

		   	*(m_inhibicion_addr) = matriz_inhibicion[4][0];
		   	*(m_inhibicion_addr) = matriz_inhibicion[4][1];
		   	*(m_inhibicion_addr) = matriz_inhibicion[4][2];
		   	*(m_inhibicion_addr) = matriz_inhibicion[4][3];
		   	*(m_inhibicion_addr) = matriz_inhibicion[4][4];
		   	*(m_inhibicion_addr) = matriz_inhibicion[4][5];
		   	*(m_inhibicion_addr) = matriz_inhibicion[4][6];
		   	*(m_inhibicion_addr) = matriz_inhibicion[4][7];
		   	*(m_inhibicion_addr) = matriz_inhibicion[4][8];
		   	*(m_inhibicion_addr) = matriz_inhibicion[4][9];

		   	*(m_inhibicion_addr) = matriz_inhibicion[5][0];
		   	*(m_inhibicion_addr) = matriz_inhibicion[5][1];
		   	*(m_inhibicion_addr) = matriz_inhibicion[5][2];
		   	*(m_inhibicion_addr) = matriz_inhibicion[5][3];
		   	*(m_inhibicion_addr) = matriz_inhibicion[5][4];
		   	*(m_inhibicion_addr) = matriz_inhibicion[5][5];
		   	*(m_inhibicion_addr) = matriz_inhibicion[5][6];
		   	*(m_inhibicion_addr) = matriz_inhibicion[5][7];
		   	*(m_inhibicion_addr) = matriz_inhibicion[5][8];
		   	*(m_inhibicion_addr) = matriz_inhibicion[5][9];

		   	*(m_inhibicion_addr) = matriz_inhibicion[6][0];
		   	*(m_inhibicion_addr) = matriz_inhibicion[6][1];
		   	*(m_inhibicion_addr) = matriz_inhibicion[6][2];
		   	*(m_inhibicion_addr) = matriz_inhibicion[6][3];
		   	*(m_inhibicion_addr) = matriz_inhibicion[6][4];
		   	*(m_inhibicion_addr) = matriz_inhibicion[6][5];
		   	*(m_inhibicion_addr) = matriz_inhibicion[6][6];
		   	*(m_inhibicion_addr) = matriz_inhibicion[6][7];
		   	*(m_inhibicion_addr) = matriz_inhibicion[6][8];
		   	*(m_inhibicion_addr) = matriz_inhibicion[6][9];

		   	*(m_inhibicion_addr) = matriz_inhibicion[7][0];
		   	*(m_inhibicion_addr) = matriz_inhibicion[7][1];
		   	*(m_inhibicion_addr) = matriz_inhibicion[7][2];
		   	*(m_inhibicion_addr) = matriz_inhibicion[7][3];
		   	*(m_inhibicion_addr) = matriz_inhibicion[7][4];
		   	*(m_inhibicion_addr) = matriz_inhibicion[7][5];
		   	*(m_inhibicion_addr) = matriz_inhibicion[7][6];
		   	*(m_inhibicion_addr) = matriz_inhibicion[7][7];
		   	*(m_inhibicion_addr) = matriz_inhibicion[7][8];
		   	*(m_inhibicion_addr) = matriz_inhibicion[7][9];

		   	*(m_inhibicion_addr) = matriz_inhibicion[8][0];
		   	*(m_inhibicion_addr) = matriz_inhibicion[8][1];
		   	*(m_inhibicion_addr) = matriz_inhibicion[8][2];
		   	*(m_inhibicion_addr) = matriz_inhibicion[8][3];
		   	*(m_inhibicion_addr) = matriz_inhibicion[8][4];
		   	*(m_inhibicion_addr) = matriz_inhibicion[8][5];
		   	*(m_inhibicion_addr) = matriz_inhibicion[8][6];
		   	*(m_inhibicion_addr) = matriz_inhibicion[8][7];
		   	*(m_inhibicion_addr) = matriz_inhibicion[8][8];
		   	*(m_inhibicion_addr) = matriz_inhibicion[8][9];

		   	*(m_inhibicion_addr) = matriz_inhibicion[9][0];
		   	*(m_inhibicion_addr) = matriz_inhibicion[9][1];
		   	*(m_inhibicion_addr) = matriz_inhibicion[9][2];
		   	*(m_inhibicion_addr) = matriz_inhibicion[9][3];
		   	*(m_inhibicion_addr) = matriz_inhibicion[9][4];
		   	*(m_inhibicion_addr) = matriz_inhibicion[9][5];
		   	*(m_inhibicion_addr) = matriz_inhibicion[9][6];
		   	*(m_inhibicion_addr) = matriz_inhibicion[9][7];
		   	*(m_inhibicion_addr) = matriz_inhibicion[9][8];
		   	*(m_inhibicion_addr) = matriz_inhibicion[9][9];

		   	*(p_cotas_addr) = cotas_plazas[0];
		   	*(p_cotas_addr) = cotas_plazas[1];
		   	*(p_cotas_addr) = cotas_plazas[2];
		   	*(p_cotas_addr) = cotas_plazas[3];
		   	*(p_cotas_addr) = cotas_plazas[4];
		   	*(p_cotas_addr) = cotas_plazas[5];
		   	*(p_cotas_addr) = cotas_plazas[6];
		   	*(p_cotas_addr) = cotas_plazas[7];
		   	*(p_cotas_addr) = cotas_plazas[8];
		   	*(p_cotas_addr) = cotas_plazas[9];

		   	*(t_automatica_addr) = transiciones_automaticas[0];
		   	*(t_automatica_addr) = transiciones_automaticas[1];
		   	*(t_automatica_addr) = transiciones_automaticas[2];
		   	*(t_automatica_addr) = transiciones_automaticas[3];
		   	*(t_automatica_addr) = transiciones_automaticas[4];
		   	*(t_automatica_addr) = transiciones_automaticas[5];
		   	*(t_automatica_addr) = transiciones_automaticas[6];
		   	*(t_automatica_addr) = transiciones_automaticas[7];
		   	*(t_automatica_addr) = transiciones_automaticas[8];
		   	*(t_automatica_addr) = transiciones_automaticas[9];

		   	*(load_vector_EFT_addr) = vector_EFT[0][0];
		   	*(load_vector_EFT_addr) = vector_EFT[0][1];
		   	*(load_vector_EFT_addr) = vector_EFT[0][2];

		   	*(load_vector_EFT_addr) = vector_EFT[1][0];
		   	*(load_vector_EFT_addr) = vector_EFT[1][1];
		   	*(load_vector_EFT_addr) = vector_EFT[1][2];

		   	*(load_vector_EFT_addr) = vector_EFT[2][0];
		   	*(load_vector_EFT_addr) = vector_EFT[2][1];
		   	*(load_vector_EFT_addr) = vector_EFT[2][2];

		   	*(load_vector_EFT_addr) = vector_EFT[3][0];
		   	*(load_vector_EFT_addr) = vector_EFT[3][1];
		   	*(load_vector_EFT_addr) = vector_EFT[3][2];

		   	*(load_vector_EFT_addr) = vector_EFT[4][0];
		   	*(load_vector_EFT_addr) = vector_EFT[4][1];
		   	*(load_vector_EFT_addr) = vector_EFT[4][2];

		   	*(load_vector_EFT_addr) = vector_EFT[5][0];
		   	*(load_vector_EFT_addr) = vector_EFT[5][1];
		   	*(load_vector_EFT_addr) = vector_EFT[5][2];

		   	*(load_vector_EFT_addr) = vector_EFT[6][0];
		   	*(load_vector_EFT_addr) = vector_EFT[6][1];
		   	*(load_vector_EFT_addr) = vector_EFT[6][2];

		   	*(load_vector_EFT_addr) = vector_EFT[7][0];
		   	*(load_vector_EFT_addr) = vector_EFT[7][1];
		   	*(load_vector_EFT_addr) = vector_EFT[7][2];

		   	*(load_vector_EFT_addr) = vector_EFT[8][0];
		   	*(load_vector_EFT_addr) = vector_EFT[8][1];
		   	*(load_vector_EFT_addr) = vector_EFT[8][2];

		   	*(load_vector_EFT_addr) = vector_EFT[9][0];
		   	*(load_vector_EFT_addr) = vector_EFT[9][1];
		   	*(load_vector_EFT_addr) = vector_EFT[9][2];

		   	*(load_vector_incrementos_tiempo_addr) = vector_incrementos[0];
		   	*(load_vector_incrementos_tiempo_addr) = vector_incrementos[1];
		   	*(load_vector_incrementos_tiempo_addr) = vector_incrementos[2];
		   	*(load_vector_incrementos_tiempo_addr) = vector_incrementos[3];
		   	*(load_vector_incrementos_tiempo_addr) = vector_incrementos[4];
		   	*(load_vector_incrementos_tiempo_addr) = vector_incrementos[5];
		   	*(load_vector_incrementos_tiempo_addr) = vector_incrementos[6];
		   	*(load_vector_incrementos_tiempo_addr) = vector_incrementos[7];
		   	*(load_vector_incrementos_tiempo_addr) = vector_incrementos[8];
		   	*(load_vector_incrementos_tiempo_addr) = vector_incrementos[9];

		   	*(load_vector_LFT_addr) = vector_LFT[0][0];
		   	*(load_vector_LFT_addr) = vector_LFT[0][1];
		   	*(load_vector_LFT_addr) = vector_LFT[0][2];

		   	*(load_vector_LFT_addr) = vector_LFT[1][0];
		   	*(load_vector_LFT_addr) = vector_LFT[1][1];
		   	*(load_vector_LFT_addr) = vector_LFT[1][2];

		   	*(load_vector_LFT_addr) = vector_LFT[2][0];
		   	*(load_vector_LFT_addr) = vector_LFT[2][1];
		   	*(load_vector_LFT_addr) = vector_LFT[2][2];

		   	*(load_vector_LFT_addr) = vector_LFT[3][0];
		   	*(load_vector_LFT_addr) = vector_LFT[3][1];
		   	*(load_vector_LFT_addr) = vector_LFT[3][2];

		   	*(load_vector_LFT_addr) = vector_LFT[4][0];
		   	*(load_vector_LFT_addr) = vector_LFT[4][1];
		   	*(load_vector_LFT_addr) = vector_LFT[4][2];

		   	*(load_vector_LFT_addr) = vector_LFT[5][0];
		   	*(load_vector_LFT_addr) = vector_LFT[5][1];
		   	*(load_vector_LFT_addr) = vector_LFT[5][2];

		   	*(load_vector_LFT_addr) = vector_LFT[6][0];
		   	*(load_vector_LFT_addr) = vector_LFT[6][1];
		   	*(load_vector_LFT_addr) = vector_LFT[6][2];

		   	*(load_vector_LFT_addr) = vector_LFT[7][0];
		   	*(load_vector_LFT_addr) = vector_LFT[7][1];
		   	*(load_vector_LFT_addr) = vector_LFT[7][2];

		   	*(load_vector_LFT_addr) = vector_LFT[8][0];
		   	*(load_vector_LFT_addr) = vector_LFT[8][1];
		   	*(load_vector_LFT_addr) = vector_LFT[8][2];

		   	*(load_vector_LFT_addr) = vector_LFT[9][0];
		   	*(load_vector_LFT_addr) = vector_LFT[9][1];
		   	*(load_vector_LFT_addr) = vector_LFT[9][2];

			*(m_marcado_addr) = marcado_inicial[0];
			*(m_marcado_addr) = marcado_inicial[1];
			*(m_marcado_addr) = marcado_inicial[2];
			*(m_marcado_addr) = marcado_inicial[3];
			*(m_marcado_addr) = marcado_inicial[4];
			*(m_marcado_addr) = marcado_inicial[5];
			*(m_marcado_addr) = marcado_inicial[6];
			*(m_marcado_addr) = marcado_inicial[7];
			*(m_marcado_addr) = marcado_inicial[8];
			*(m_marcado_addr) = marcado_inicial[9];

		   	*(t_intr_addr) = transiciones_intr[0];
		   	*(t_intr_addr) = transiciones_intr[1];
		   	*(t_intr_addr) = transiciones_intr[2];
		   	*(t_intr_addr) = transiciones_intr[3];
		   	*(t_intr_addr) = transiciones_intr[4];
		   	*(t_intr_addr) = transiciones_intr[5];
		   	*(t_intr_addr) = transiciones_intr[6];
		   	*(t_intr_addr) = transiciones_intr[7];
		   	*(t_intr_addr) = transiciones_intr[8];
		   	*(t_intr_addr) = transiciones_intr[9];		

		

	    int status;
	    status=0;
		status = status + sem_init(&semaforos[0], 1, 0);
		status = status + sem_init(&semaforos[1], 1, 0);
		status = status + sem_init(&semaforos[2], 1, 0);
		status = status + sem_init(&semaforos[3], 1, 0);
		status = status + sem_init(&semaforos[4], 1, 0);
		status = status + sem_init(&console_mutex, 1, 1);
    	if(status == 0)
    	{	//print("\nSemaforos creado correctamente\r\n");

    	}
    	else
    	{
    		print("Error al crear el semaforo\r\n");
    		pthread_exit(NULL);
    	}

		disparos[0]=0x00000001;
		disparos[1]=0x00000002;
		disparos[2]=0x00000004;
		disparos[3]=0x00000008;
		disparos[4]=0x00000010;
		disparos[5]=0x00000020;
		disparos[6]=0x00000040;
		disparos[7]=0x00000080;
		disparos[8]=0x00000100;
		disparos[9]=0x00000200;
	//Espero
		int i;
		for (i=0 ; i<50000 ; i++) {}

    pthread_attr_t attr;

	#if SCHED_TYPE == SCHED_PRIO
    	struct sched_param spar;
	#endif

    pthread_attr_init (&attr);

    //Iniciar Interrupcion.
    register_int_handler(XPAR_MICROBLAZE_0_INTC_PETRI_AXI_INT_0_INTERRUPT_INTR,petri_intr_handler,(void*)XPAR_INTC_SINGLE_BASEADDR);
    enable_interrupt(XPAR_MICROBLAZE_0_INTC_PETRI_AXI_INT_0_INTERRUPT_INTR);



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


     	//while(cantidad_de_mesas<5){yield();}

     	pthread_join(&hilo_armador, (void*)&a);


    //Terminar cuenta de tiempo
       	valor_final_timer = XTmrCtr_GetTimerCounterReg(XPAR_AXI_TIMER_1_BASEADDR,0);
       	xil_printf("Valor final del timer: %d\r\n\n\n", valor_final_timer);
       	xil_printf("Cantidad de mesas: %d\r\n\n\n", cantidad_de_mesas);
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
		//Pedir T0
			*(new_disparo_addr) = disparo_t_cero;

		//Ver si T0 se ejecuto
			sem_wait(&semaforos[0]);

		//Sacar T0 de los disparos ejecutados
			*(sacar_disparo_addr) = disparo_t_cero;
//			i=i+1;
//			sem_wait(&console_mutex);
//			xil_printf("Mesa %d: CORTADA\r\n",i);
//			sem_post(&console_mutex);
//		if (cantidad_de_mesas == 5) break;
	}//Fin del while
	pthread_exit(NULL);
}

void* lijar()
{


	while(1)
	{
		//Solicitar el disparo de T1
			*(new_disparo_addr) = disparo_t_uno;


		//Ver si T1 se ejecuto
			sem_wait(&semaforos[1]);

		//Sacar T1 de los disparos ejecutados
			*(sacar_disparo_addr) = disparo_t_uno;

//			i=i+1;
//			sem_wait(&console_mutex);
//			xil_printf("Mesa %d: LIJADA\r\n",i);
//			sem_post(&console_mutex);
	//	if (cantidad_de_mesas == 5) break;
	}//Fin del while
	pthread_exit(NULL);
}

void* pintar()
{

		while (1)
	{
		//Pedir T2
			*(new_disparo_addr) = disparo_t_dos;


		//Ver si T2 se ejecuto
			sem_wait(&semaforos[2]);

		//Sacar T2 de los disparos ejecutados
			*(sacar_disparo_addr) = disparo_t_dos;
//			i=i+1;
//			sem_wait(&console_mutex);
//			xil_printf("Mesa %d: PINTADA\r\n",i);
//			sem_post(&console_mutex);
		//if (cantidad_de_mesas == 5) break;
	}//Fin del while
	pthread_exit(NULL);
}

void* secar()
{

	while(1)
	{
		//Solicitar el disparo de T3
			*(new_disparo_addr) = disparo_t_tres;

		//Ver si T3 se ejecuto
			sem_wait(&semaforos[3]);

		//Sacar T3 de los disparos ejecutados
			*(sacar_disparo_addr) = disparo_t_tres;
//			i=i+1;
//			sem_wait(&console_mutex);
//			xil_printf("Mesa %d: SECADA\r\n",i);
//			sem_post(&console_mutex);
//		if (cantidad_de_mesas == 5) break;
	}//Fin del while
	pthread_exit(NULL);
}

void* armar(){

	while(cantidad_de_mesas < mesas)
	{
		//Pedir T4
			*(new_disparo_addr) = disparo_t_cuatro;

		//Ver si T4 se ejecuto
		//while(1){}
			sem_wait(&semaforos[4]);

		//Sacar T4 de los disparos ejecutados
			*(sacar_disparo_addr) = disparo_t_cuatro;

		//ARMAR UNA MESA
			cantidad_de_mesas = cantidad_de_mesas + 1;
//			i=i+1;
//			sem_wait(&console_mutex);
//			xil_printf("Mesa %d: ARMADA\r\n",i);

	/*	if (cantidad_de_mesas >= 5)
		{
			xil_printf("SE ARMARON %d MESAS\r\n\n",cantidad_de_mesas);
		}
		sem_post(&console_mutex);
*/
	}//Fin del while
	pthread_exit(cantidad_de_mesas);
}

void petri_intr_handler(){

	sem_post(&semaforos[*(leer_t_num)]);


	}

void mostrar_marcado()
{
	int marcado_cero;
	int marcado_uno;
	int marcado_dos;
	int marcado_tres;
	int marcado_cuatro;
	int marcado_cinco;
	int marcado_seis;
	int marcado_siete;
	int marcado_ocho;
	int marcado_nueve;

	marcado_cero = *(leer_marcado_p_cero);
	xil_printf ("Marcado de P0 = %08xH\r\n",marcado_cero);
	marcado_uno = *(leer_marcado_p_uno);
	xil_printf ("Marcado de P1 = %08xH\r\n", marcado_uno);
	marcado_dos = *(leer_marcado_p_dos);
	xil_printf ("Marcado de P2 = %08xH\r\n", marcado_dos);
	marcado_tres = *(leer_marcado_p_tres);
	xil_printf ("Marcado de P3 = %08xH\r\n", marcado_tres);
	marcado_cuatro = *(leer_marcado_p_cuatro);
	xil_printf ("Marcado de P4 = %08xH\r\n", marcado_cuatro);
	marcado_cinco = *(leer_marcado_p_cinco);
	xil_printf ("Marcado de P5 = %08xH\r\n", marcado_cinco);
	marcado_seis = *(leer_marcado_p_seis);
	xil_printf ("Marcado de P6 = %08xH\r\n", marcado_seis);
	marcado_siete = *(leer_marcado_p_siete);
	xil_printf ("Marcado de P7 = %08xH\r\n", marcado_siete);
	marcado_ocho = *(leer_marcado_p_ocho);
	xil_printf ("Marcado de P8 = %08xH\r\n", marcado_ocho);
	marcado_nueve = *(leer_marcado_p_nueve);
	xil_printf ("Marcado de P9 = %08xH\r\n", marcado_nueve);
}

