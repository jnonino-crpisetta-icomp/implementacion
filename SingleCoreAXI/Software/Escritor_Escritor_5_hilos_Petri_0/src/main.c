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
//#include "xtmrctr.h"

/* Declarations */
#define N_THREADS   5
#define tiempo_espera_entre_cargas	5000

void* hilo_escritor_1();
void* hilo_escritor_2();
void* hilo_escritor_3();
void* hilo_escritor_4();
void* hilo_escritor_5();
pthread_t hilo_1;
pthread_t hilo_2;
pthread_t hilo_3;
pthread_t hilo_4;
pthread_t hilo_5;

//Funciones
void mostrar_marcado();

/* Data */
int cantidad_plazas = 11;
int cantidad_transiciones = 10;
int cantidad_palabras_vector_tiempo = 3;
static int variable_compartida;
int valor_maximo = 10000;

//Direcciones para escribir en Petri
	Xuint32 *m_marcado_addr    						= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR);
	Xuint32 *m_incidencia_addr 						= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR + 0x4);
	Xuint32 *m_inhibicion_addr 						= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR + 0x8);
	Xuint32 *p_cotas_addr							= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR + 0xC);
	Xuint32 *t_automatica_addr 						= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR + 0x10);
	Xuint32 *load_vector_EFT_addr					= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR + 0x14);
	Xuint32 *load_vector_incrementos_tiempo_addr 	= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR + 0x18);
	Xuint32 *load_vector_LFT_addr					= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR + 0x1C);
	Xuint32 *new_disparo_addr  						= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR + 0x20);
	Xuint32 *sacar_disparo_addr						= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR + 0x24);
	Xuint32 *error_addr								= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR + 0x28);

	//Direcciones para leer en Petri
	Xuint32 *leer_disparos_en_espera				= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR + 0x2C);
	Xuint32 *leer_disparos_posibles					= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR + 0x30);
	Xuint32 *leer_disparos_ejecutados				= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR + 0x34);
	Xuint32 *leer_marcado_p_cero					= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR + 0x38);
	Xuint32 *leer_marcado_p_uno						= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR + 0x3C);
	Xuint32 *leer_marcado_p_dos						= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR + 0x40);
	Xuint32 *leer_marcado_p_tres					= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR + 0x44);
	Xuint32 *leer_marcado_p_cuatro					= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR + 0x48);
	Xuint32 *leer_marcado_p_cinco					= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR + 0x4C);
	Xuint32 *leer_marcado_p_seis					= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR + 0x50);
	Xuint32 *leer_marcado_p_siete					= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR + 0x54);
	Xuint32 *leer_marcado_p_ocho					= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR + 0x58);
	Xuint32 *leer_marcado_p_nueve					= (Xuint32 *)(XPAR_PETRI_AXI_0_BASEADDR + 0x5C);

/* Functions */
int main()
{
    init_platform();
    
    /* Initialize xilkernel */
    	xilkernel_init();
    
   	xil_printf("INICIO EJECUCION PETRI\r\n\n");

    //Carga de datos
		int matriz_incidencia [cantidad_plazas][cantidad_transiciones];
			matriz_incidencia[0][0] = 0x0000FFFF;
		   	matriz_incidencia[0][1] = 0x00010001;
		   	matriz_incidencia[0][2] = 0x0002FFFF;
		   	matriz_incidencia[0][3] = 0x00030001;
		   	matriz_incidencia[0][4] = 0x0004FFFF;
		   	matriz_incidencia[0][5] = 0x00050001;
		   	matriz_incidencia[0][6] = 0x0006FFFF;
		   	matriz_incidencia[0][7] = 0x00070001;
		   	matriz_incidencia[0][8] = 0x00080000;
		   	matriz_incidencia[0][9] = 0x00090000;

		   	matriz_incidencia[1][0] = 0x0100FFFF;
		   	matriz_incidencia[1][1] = 0x01010001;
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
	    	matriz_incidencia[3][1] = 0x03010000;
	    	matriz_incidencia[3][2] = 0x0302FFFF;
	    	matriz_incidencia[3][3] = 0x03030001;
	    	matriz_incidencia[3][4] = 0x03040000;
	    	matriz_incidencia[3][5] = 0x03050000;
	    	matriz_incidencia[3][6] = 0x03060000;
	    	matriz_incidencia[3][7] = 0x03070000;
	    	matriz_incidencia[3][8] = 0x03080000;
	    	matriz_incidencia[3][9] = 0x03090000;

	    	matriz_incidencia[4][0] = 0x04000000;
	    	matriz_incidencia[4][1] = 0x04010000;
	    	matriz_incidencia[4][2] = 0x04020001;
	    	matriz_incidencia[4][3] = 0x0403FFFF;
	    	matriz_incidencia[4][4] = 0x04040000;
	    	matriz_incidencia[4][5] = 0x04050000;
	    	matriz_incidencia[4][6] = 0x04060000;
	    	matriz_incidencia[4][7] = 0x04070000;
	    	matriz_incidencia[4][8] = 0x04080000;
	    	matriz_incidencia[4][9] = 0x04090000;

	    	matriz_incidencia[5][0] = 0x05000000;
	    	matriz_incidencia[5][1] = 0x05010000;
	    	matriz_incidencia[5][2] = 0x05020000;
	    	matriz_incidencia[5][3] = 0x05030000;
	    	matriz_incidencia[5][4] = 0x0504FFFF;
	    	matriz_incidencia[5][5] = 0x05050001;
	    	matriz_incidencia[5][6] = 0x05060000;
	    	matriz_incidencia[5][7] = 0x05070000;
	    	matriz_incidencia[5][8] = 0x05080000;
	    	matriz_incidencia[5][9] = 0x05090000;

	    	matriz_incidencia[6][0] = 0x06000000;
	    	matriz_incidencia[6][1] = 0x06010000;
	    	matriz_incidencia[6][2] = 0x06020000;
	    	matriz_incidencia[6][3] = 0x06030000;
	    	matriz_incidencia[6][4] = 0x06040001;
	    	matriz_incidencia[6][5] = 0x0605FFFF;
	    	matriz_incidencia[6][6] = 0x06060000;
	    	matriz_incidencia[6][7] = 0x06070000;
	    	matriz_incidencia[6][8] = 0x06080000;
	    	matriz_incidencia[6][9] = 0x06090000;

	    	matriz_incidencia[7][0] = 0x07000000;
	    	matriz_incidencia[7][1] = 0x07010000;
	    	matriz_incidencia[7][2] = 0x07020000;
	    	matriz_incidencia[7][3] = 0x07030000;
	    	matriz_incidencia[7][4] = 0x07040000;
	    	matriz_incidencia[7][5] = 0x07050000;
	    	matriz_incidencia[7][6] = 0x0706FFFF;
	    	matriz_incidencia[7][7] = 0x07070001;
	    	matriz_incidencia[7][8] = 0x07080000;
	    	matriz_incidencia[7][9] = 0x07090000;

	    	matriz_incidencia[8][0] = 0x08000000;
	    	matriz_incidencia[8][1] = 0x08010000;
	    	matriz_incidencia[8][2] = 0x08020000;
	    	matriz_incidencia[8][3] = 0x08030000;
	    	matriz_incidencia[8][4] = 0x08040000;
	    	matriz_incidencia[8][5] = 0x08050000;
	    	matriz_incidencia[8][6] = 0x08060001;
	    	matriz_incidencia[8][7] = 0x0807FFFF;
	    	matriz_incidencia[8][8] = 0x08080000;
	    	matriz_incidencia[8][9] = 0x08090000;

	    	matriz_incidencia[9][0] = 0x09000000;
	    	matriz_incidencia[9][1] = 0x09010000;
	    	matriz_incidencia[9][2] = 0x09020000;
	    	matriz_incidencia[9][3] = 0x09030000;
	    	matriz_incidencia[9][4] = 0x09040000;
	    	matriz_incidencia[9][5] = 0x09050000;
	    	matriz_incidencia[9][6] = 0x09060000;
	    	matriz_incidencia[9][7] = 0x09070000;
	    	matriz_incidencia[9][8] = 0x09080000;
	    	matriz_incidencia[9][9] = 0x09090000;

	    	matriz_incidencia[10][0] = 0x0A000000;
	    	matriz_incidencia[10][1] = 0x0A010000;
	    	matriz_incidencia[10][2] = 0x0A020000;
	    	matriz_incidencia[10][3] = 0x0A030000;
	    	matriz_incidencia[10][4] = 0x0A040000;
	    	matriz_incidencia[10][5] = 0x0A050000;
	    	matriz_incidencia[10][6] = 0x0A060000;
	    	matriz_incidencia[10][7] = 0x0A070000;
	    	matriz_incidencia[10][8] = 0x0A080000;
	    	matriz_incidencia[10][9] = 0x0A090000;

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

	    	matriz_inhibicion[10][0] = 0x0A000000;
	    	matriz_inhibicion[10][1] = 0x0A010000;
	    	matriz_inhibicion[10][2] = 0x0A020000;
	    	matriz_inhibicion[10][3] = 0x0A030000;
	    	matriz_inhibicion[10][4] = 0x0A040000;
	    	matriz_inhibicion[10][5] = 0x0A050000;
	    	matriz_inhibicion[10][6] = 0x0A060000;
	    	matriz_inhibicion[10][7] = 0x0A070000;
	    	matriz_inhibicion[10][8] = 0x0A080000;
	    	matriz_inhibicion[10][9] = 0x0A090000;

		int marcado_inicial [cantidad_plazas];
		   	marcado_inicial[0] = 0x00000001;
		   	marcado_inicial[1] = 0x01000001;
		   	marcado_inicial[2] = 0x02000000;
		   	marcado_inicial[3] = 0x03000001;
		   	marcado_inicial[4] = 0x04000000;
		   	marcado_inicial[5] = 0x05000001;
		   	marcado_inicial[6] = 0x06000000;
		   	marcado_inicial[7] = 0x07000001;
		   	marcado_inicial[8] = 0x08000000;
		   	marcado_inicial[9] = 0x09000001;
		   	marcado_inicial[10] = 0x0A000000;

		int cotas_plazas [cantidad_plazas];
	    	cotas_plazas[0] = 0x00000001;
	    	cotas_plazas[1] = 0x01000001;
	    	cotas_plazas[2] = 0x02000001;
	    	cotas_plazas[3] = 0x03000001;
	    	cotas_plazas[4] = 0x04000001;
	    	cotas_plazas[5] = 0x05000001;
	    	cotas_plazas[6] = 0x06000001;
	    	cotas_plazas[7] = 0x07000001;
	    	cotas_plazas[8] = 0x08000001;
	    	cotas_plazas[9] = 0x09000001;
	    	cotas_plazas[10] = 0x0A000001;

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
	    	vector_EFT[0][0] = 0x00000000;
	    	vector_EFT[0][1] = 0x01000000;
	    	vector_EFT[0][2] = 0x02000000;

	    	vector_EFT[1][0] = 0x00010000;
	    	vector_EFT[1][1] = 0x01010000;
	    	vector_EFT[1][2] = 0x02010000;

	    	vector_EFT[2][0] = 0x00020000;
	    	vector_EFT[2][1] = 0x01020000;
	    	vector_EFT[2][2] = 0x02020000;

	    	vector_EFT[3][0] = 0x00030000;
	    	vector_EFT[3][1] = 0x01030000;
	    	vector_EFT[3][2] = 0x02030000;

	    	vector_EFT[4][0] = 0x00040000;
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

	    print("Comienza la Carga de la Matriz de Incidencia\r\n");
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

		   	*(m_incidencia_addr) = matriz_incidencia[10][0];
		   	*(m_incidencia_addr) = matriz_incidencia[10][1];
		   	*(m_incidencia_addr) = matriz_incidencia[10][2];
		   	*(m_incidencia_addr) = matriz_incidencia[10][3];
		   	*(m_incidencia_addr) = matriz_incidencia[10][4];
		   	*(m_incidencia_addr) = matriz_incidencia[10][5];
		   	*(m_incidencia_addr) = matriz_incidencia[10][6];
		   	*(m_incidencia_addr) = matriz_incidencia[10][7];
		   	*(m_incidencia_addr) = matriz_incidencia[10][8];
		    *(m_incidencia_addr) = matriz_incidencia[10][9];
		print("Termino Carga de la Matriz de Incidencia \r\n\n");

		print("Comienza la Carga de la Matriz de Inhibicion\r\n");
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

		   	*(m_inhibicion_addr) = matriz_inhibicion[10][0];
		   	*(m_inhibicion_addr) = matriz_inhibicion[10][1];
		   	*(m_inhibicion_addr) = matriz_inhibicion[10][2];
		   	*(m_inhibicion_addr) = matriz_inhibicion[10][3];
		   	*(m_inhibicion_addr) = matriz_inhibicion[10][4];
		   	*(m_inhibicion_addr) = matriz_inhibicion[10][5];
		   	*(m_inhibicion_addr) = matriz_inhibicion[10][6];
		   	*(m_inhibicion_addr) = matriz_inhibicion[10][7];
		   	*(m_inhibicion_addr) = matriz_inhibicion[10][8];
		   	*(m_inhibicion_addr) = matriz_inhibicion[10][9];
		print("Termino Carga de la Matriz de Inhibicion\r\n\n");

		print("Comienza la Carga del vector de Cotas de Plazas \r\n");
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
		   	*(p_cotas_addr) = cotas_plazas[10];
		print("Termino Carga del vector de Cotas de Plazas\r\n\n");

		print("Comienza la Carga del vector de Transiciones Automaticas\r\n");
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
		print("Termino Carga del vector de Transiciones Automaticas\r\n\n");

		print("Comienza la Carga del vector EFT\r\n");
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
		print("Termino Carga del vector de EFT\r\n\n");

		print("Comienza la Carga del vector de incrementos\r\n");
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
		print("Termino Carga del vector de de incrementos\r\n\n");

		print("Comienza la Carga del vector LFT\r\n");
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
		print("Termino Carga del vector de LFT\r\n\n");

		print("Comienza la Carga del vector de Marcado Inicial\r\n");
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
			*(m_marcado_addr) = marcado_inicial[10];
		print("Termino Carga del vector de Marcado Inicial\r\n\n");

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
   	int status;

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
		status = pthread_create(&hilo_1, NULL, (void*)hilo_escritor_1, NULL);
		status = pthread_create(&hilo_2, NULL, (void*)hilo_escritor_2, NULL);
		status = pthread_create(&hilo_3, NULL, (void*)hilo_escritor_3, NULL);
		status = pthread_create(&hilo_4, NULL, (void*)hilo_escritor_4, NULL);
		status = pthread_create(&hilo_5, NULL, (void*)hilo_escritor_5, NULL);

    	pthread_join(hilo_1, NULL);
    	pthread_join(hilo_2, NULL);
    	pthread_join(hilo_3, NULL);
     	pthread_join(hilo_4, NULL);
     	pthread_join(hilo_5, NULL);

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

/* HILOS SUMADORES */
void* hilo_escritor_1()
{
	int numero_de_hilo = 1;
	int disparo_t_cero 	= 0x00000000;
	int disparo_t_uno 	= 0x00010000;
	int disparos_ya_ejecutados;
	int i;

	for(i=0;i<valor_maximo;i++)
	{
		//Pedir T0
			*(new_disparo_addr) = disparo_t_cero;
			*(error_addr) = 0xFFFFFFFF;

		//Ver si T0 se ejecuto
			disparos_ya_ejecutados = *(leer_disparos_ejecutados);
			while ( (disparos_ya_ejecutados & 0x00000001) != 0x00000001)
			{	disparos_ya_ejecutados = *(leer_disparos_ejecutados);	}

		//Sacar T0 de los disparos ejecutados
			*(sacar_disparo_addr) = disparo_t_cero;
			*(error_addr) = 0x00000000;

		//Solicitar el disparo de T1
			*(new_disparo_addr) = disparo_t_uno;
			*(error_addr) = 0xFFFFFFFF;

		//Ver si T1 se ejecuto
			disparos_ya_ejecutados = *(leer_disparos_ejecutados);
			while ( (disparos_ya_ejecutados & 0x00000002) != 0x00000002)
			{	disparos_ya_ejecutados = *(leer_disparos_ejecutados);	}

		//Sacar T1 de los disparos ejecutados
			*(sacar_disparo_addr) = disparo_t_uno;
			*(error_addr) = 0x00000000;

	}//Fin del while de variable compartida

	pthread_exit(NULL);
}

void* hilo_escritor_2()
{
	int numero_de_hilo = 2;
	int disparo_t_dos 	= 0x00020000;
	int disparo_t_tres 	= 0x00030000;
	int disparos_ya_ejecutados;
	int i;

	for(i=0;i<valor_maximo;i++)
	{
		//Pedir T2
			*(new_disparo_addr) = disparo_t_dos;
			*(error_addr) = 0xFFFFFFFF;

		//Ver si T2 se ejecuto
			disparos_ya_ejecutados = *(leer_disparos_ejecutados);
			while ( (disparos_ya_ejecutados & 0x00000004) != 0x00000004)
			{	disparos_ya_ejecutados = *(leer_disparos_ejecutados);	}

		//Sacar T2 de los disparos ejecutados
			*(sacar_disparo_addr) = disparo_t_dos;
			*(error_addr) = 0x00000000;

		//Solicitar el disparo de T3
			*(new_disparo_addr) = disparo_t_tres;
			*(error_addr) = 0xFFFFFFFF;

			disparos_ya_ejecutados = *(leer_disparos_ejecutados);
			while ( (disparos_ya_ejecutados & 0x00000008) != 0x00000008)
			{	disparos_ya_ejecutados = *(leer_disparos_ejecutados);	}

		//Sacar T3 de los disparos ejecutados
			*(sacar_disparo_addr) = disparo_t_tres;
			*(error_addr) = 0x00000000;

	}//Fin del while de variable compartida

	pthread_exit(NULL);
}

void* hilo_escritor_3()
{
	int numero_de_hilo = 3;
	int disparo_t_cuatro= 0x00040000;
	int disparo_t_cinco = 0x00050000;
	int disparos_ya_ejecutados;
	int i;

	for(i=0;i<valor_maximo;i++)
	{
		//Pedir T4
			*(new_disparo_addr) = disparo_t_cuatro;
			*(error_addr) = 0xFFFFFFFF;

		//Ver si T4 se ejecuto
			disparos_ya_ejecutados = *(leer_disparos_ejecutados);
			while ( (disparos_ya_ejecutados & 0x00000010) != 0x00000010)
			{	disparos_ya_ejecutados = *(leer_disparos_ejecutados);	}

		//Sacar T4 de los disparos ejecutados
			*(sacar_disparo_addr) = disparo_t_cuatro;
			*(error_addr) = 0x00000000;

		//Solicitar el disparo de T5
			*(new_disparo_addr) = disparo_t_cinco;
			*(error_addr) = 0xFFFFFFFF;

			disparos_ya_ejecutados = *(leer_disparos_ejecutados);
			while ( (disparos_ya_ejecutados & 0x00000020) != 0x00000020)
			{	disparos_ya_ejecutados = *(leer_disparos_ejecutados);	}

		//Sacar T3 de los disparos ejecutados
			*(sacar_disparo_addr) = disparo_t_cinco;
			*(error_addr) = 0x00000000;

	}//Fin del while de variable compartida

	pthread_exit(NULL);
}

void* hilo_escritor_4()
{
	int numero_de_hilo = 4;
	int disparo_t_seis 	= 0x00060000;
	int disparo_t_siete = 0x00070000;
	int disparos_ya_ejecutados;
	int i;

	for(i=0;i<valor_maximo;i++)
	{
		//Pedir T6
			*(new_disparo_addr) = disparo_t_seis;
			*(error_addr) = 0xFFFFFFFF;

		//Ver si T6 se ejecuto
			disparos_ya_ejecutados = *(leer_disparos_ejecutados);
			while ( (disparos_ya_ejecutados & 0x000000040) != 0x000000040)
			{	disparos_ya_ejecutados = *(leer_disparos_ejecutados);	}

		//Sacar T6 de los disparos ejecutados
			*(sacar_disparo_addr) = disparo_t_seis;
			*(error_addr) = 0x00000000;

		//Solicitar el disparo de T7
			*(new_disparo_addr) = disparo_t_siete;
			*(error_addr) = 0xFFFFFFFF;

			disparos_ya_ejecutados = *(leer_disparos_ejecutados);
			while ( (disparos_ya_ejecutados & 0x00000080) != 0x00000080)
			{	disparos_ya_ejecutados = *(leer_disparos_ejecutados);	}

		//Sacar T3 de los disparos ejecutados
			*(sacar_disparo_addr) = disparo_t_siete;
			*(error_addr) = 0x00000000;

	}//Fin del while de variable compartida

	pthread_exit(NULL);
}

void* hilo_escritor_5()
{	xil_printf("HOLA");
	int numero_de_hilo = 5;
	int disparo_t_ocho 	= 0x00080000;
	int disparo_t_nueve = 0x00090000;
	int disparos_ya_ejecutados;
	int k;

	for(k=0;k<valor_maximo;k++)
	{
		//Pedir T8
			*(new_disparo_addr) = disparo_t_ocho;
			*(error_addr) = 0xFFFFFFFF;

		//Ver si T8 se ejecuto
			disparos_ya_ejecutados = *(leer_disparos_ejecutados);
			while ( (disparos_ya_ejecutados & 0x000000100) != 0x000000100)
			{	disparos_ya_ejecutados = *(leer_disparos_ejecutados);	}

		//Sacar T8 de los disparos ejecutados
			*(sacar_disparo_addr) = disparo_t_ocho;
			*(error_addr) = 0x00000000;

		//Solicitar el disparo de T9
			*(new_disparo_addr) = disparo_t_nueve;
			*(error_addr) = 0xFFFFFFFF;

			disparos_ya_ejecutados = *(leer_disparos_ejecutados);
			while ( (disparos_ya_ejecutados & 0x00000200) != 0x00000200)
			{	disparos_ya_ejecutados = *(leer_disparos_ejecutados);	}

		//Sacar T3 de los disparos ejecutados
			*(sacar_disparo_addr) = disparo_t_nueve;
			*(error_addr) = 0x00000000;

	}//Fin del while de variable compartida

	pthread_exit(NULL);
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
