//----------------------------------------------------------------------------
// user_logic.vhd - module
//----------------------------------------------------------------------------
//
// ***************************************************************************
// ** Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.            **
// **                                                                       **
// ** Xilinx, Inc.                                                          **
// ** XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"         **
// ** AS A COURTESY TO YOU, SOLELY FOR USE IN DEVELOPING PROGRAMS AND       **
// ** SOLUTIONS FOR XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE,        **
// ** OR INFORMATION AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE,        **
// ** APPLICATION OR STANDARD, XILINX IS MAKING NO REPRESENTATION           **
// ** THAT THIS IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,     **
// ** AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE      **
// ** FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY              **
// ** WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE               **
// ** IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR        **
// ** REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF       **
// ** INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS       **
// ** FOR A PARTICULAR PURPOSE.                                             **
// **                                                                       **
// ***************************************************************************
//
//----------------------------------------------------------------------------
// Filename:          user_logic.vhd
// Version:           2.00.b
// Description:       User logic module.
// Date:              Thu Sep 13 15:24:04 2012 (by Create and Import Peripheral Wizard)
// Verilog Standard:  Verilog-2001
//----------------------------------------------------------------------------
// Naming Conventions:
//   active low signals:                    "*_n"
//   clock signals:                         "clk", "clk_div#", "clk_#x"
//   reset signals:                         "rst", "rst_n"
//   generics:                              "C_*"
//   user defined types:                    "*_TYPE"
//   state machine next state:              "*_ns"
//   state machine current state:           "*_cs"
//   combinatorial signals:                 "*_com"
//   pipelined or register delay signals:   "*_d#"
//   counter signals:                       "*cnt*"
//   clock enable signals:                  "*_ce"
//   internal version of output port:       "*_i"
//   device pins:                           "*_pin"
//   ports:                                 "- Names begin with Uppercase"
//   processes:                             "*_PROCESS"
//   component instantiations:              "<ENTITY_>I_<#|FUNC>"
//----------------------------------------------------------------------------

module user_logic
(
  // -- ADD USER PORTS BELOW THIS LINE ---------------
  // --USER ports added here 
  // -- ADD USER PORTS ABOVE THIS LINE ---------------

  // -- DO NOT EDIT BELOW THIS LINE ------------------
  // -- Bus protocol ports, do not add to or delete 
  Bus2IP_Clk,                     // Bus to IP clock
  Bus2IP_Reset,                   // Bus to IP reset
  Bus2IP_Data,                    // Bus to IP data bus
  Bus2IP_BE,                      // Bus to IP byte enables
  Bus2IP_RdCE,                    // Bus to IP read chip enable
  Bus2IP_WrCE,                    // Bus to IP write chip enable
  IP2Bus_Data,                    // IP to Bus data bus
  IP2Bus_RdAck,                   // IP to Bus read transfer acknowledgement
  IP2Bus_WrAck,                   // IP to Bus write transfer acknowledgement
  IP2Bus_Error,                   // IP to Bus error response
  IP2Bus_IntrEvent                // IP to Bus interrupt event
  // -- DO NOT EDIT ABOVE THIS LINE ------------------
); // user_logic

// -- ADD USER PARAMETERS BELOW THIS LINE ------------
// --USER parameters added here 
	parameter cant_plazas								= 32;	//Cantidad de plazas de la red de Petri modelada
	parameter cant_transiciones						= 32;	//Cantidad de transiciones de la red de Petri modelada
	parameter tamano_de_elementos						= 8; 	//Tamano de los elementos de los arreglos, medido en bits
	parameter tamano_cola								= 5;	//Tamano de contador del contador para entrada de disparos	//Tamano de contador del contador para entrada de disparos
	parameter tamano_vector_incremento_de_tiempo	= 3;	// Cantidad de bits para expresar el numero de unidades en las que se incrementea cada transicion
// -- ADD USER PARAMETERS ABOVE THIS LINE ------------

// -- DO NOT EDIT BELOW THIS LINE --------------------
// -- Bus protocol parameters, do not add to or delete
parameter C_SLV_DWIDTH                   = 32;
parameter C_NUM_REG                      = 32;
parameter C_NUM_INTR                     = 1;
// -- DO NOT EDIT ABOVE THIS LINE --------------------

// -- ADD USER PORTS BELOW THIS LINE -----------------
// --USER ports added here 
// -- ADD USER PORTS ABOVE THIS LINE -----------------

// -- DO NOT EDIT BELOW THIS LINE --------------------
// -- Bus protocol ports, do not add to or delete
input                                     Bus2IP_Clk;
input                                     Bus2IP_Reset;
input      [0 : C_SLV_DWIDTH-1]           Bus2IP_Data;
input      [0 : C_SLV_DWIDTH/8-1]         Bus2IP_BE;
input      [0 : C_NUM_REG-1]              Bus2IP_RdCE;
input      [0 : C_NUM_REG-1]              Bus2IP_WrCE;
output     [0 : C_SLV_DWIDTH-1]           IP2Bus_Data;
output                                    IP2Bus_RdAck;
output                                    IP2Bus_WrAck;
output                                    IP2Bus_Error;
output     [0 : C_NUM_INTR-1]             IP2Bus_IntrEvent;
// -- DO NOT EDIT ABOVE THIS LINE --------------------

//----------------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------------

  // --USER nets declarations added here, as needed for user logic

  // Nets for user logic slave model s/w accessible register example
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg0/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg1/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg2/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg3/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg4/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg5/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg6/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg7/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg8/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg9/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg10/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg11/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg12/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg13/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg14/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg15/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg16/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg17/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg18/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg19/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg20/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg21/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg22/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg23/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg24/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg25/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg26/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg27/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg28/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg29/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg30/* synthesis syn_keep = 1 */;
//  reg        [0 : C_SLV_DWIDTH-1]           slv_reg31/* synthesis syn_keep = 1 */;
  wire       [0 : 31]                       slv_reg_write_sel;
  wire       [0 : 31]                       slv_reg_read_sel;
  reg        [0 : C_SLV_DWIDTH-1]           slv_ip2bus_data/* synthesis syn_keep = 1 */;
  wire                                      slv_read_ack;
  wire                                      slv_write_ack;
  integer                                   byte_index, bit_index;

  // --USER logic implementation added here

  // ------------------------------------------------------
  // Example code to read/write user logic slave model s/w accessible registers
  // 
  // Note:
  // The example code presented here is to show you one way of reading/writing
  // software accessible registers implemented in the user logic slave model.
  // Each bit of the Bus2IP_WrCE/Bus2IP_RdCE signals is configured to correspond
  // to one software accessible register by the top level template. For example,
  // if you have four 32 bit software accessible registers in the user logic,
  // you are basically operating on the following memory mapped registers:
  // 
  //    Bus2IP_WrCE/Bus2IP_RdCE   Memory Mapped Register
  //                     "1000"   C_BASEADDR + 0x0
  //                     "0100"   C_BASEADDR + 0x4
  //                     "0010"   C_BASEADDR + 0x8
  //                     "0001"   C_BASEADDR + 0xC
  // 
  // ------------------------------------------------------

  assign
    slv_reg_write_sel = Bus2IP_WrCE[0:31],
    slv_reg_read_sel  = Bus2IP_RdCE[0:31],
//    slv_write_ack     = Bus2IP_WrCE[0] || Bus2IP_WrCE[1] || Bus2IP_WrCE[2] || Bus2IP_WrCE[3] || Bus2IP_WrCE[4] || Bus2IP_WrCE[5] || Bus2IP_WrCE[6] || Bus2IP_WrCE[7] || Bus2IP_WrCE[8] || Bus2IP_WrCE[9] || Bus2IP_WrCE[10] || Bus2IP_WrCE[11] || Bus2IP_WrCE[12] || Bus2IP_WrCE[13] || Bus2IP_WrCE[14] || Bus2IP_WrCE[15] || Bus2IP_WrCE[16] || Bus2IP_WrCE[17] || Bus2IP_WrCE[18] || Bus2IP_WrCE[19] || Bus2IP_WrCE[20] || Bus2IP_WrCE[21] || Bus2IP_WrCE[22] || Bus2IP_WrCE[23] || Bus2IP_WrCE[24] || Bus2IP_WrCE[25] || Bus2IP_WrCE[26] || Bus2IP_WrCE[27] || Bus2IP_WrCE[28] || Bus2IP_WrCE[29] || Bus2IP_WrCE[30] || Bus2IP_WrCE[31],
    slv_read_ack      = Bus2IP_RdCE[0] || Bus2IP_RdCE[1] || Bus2IP_RdCE[2] || Bus2IP_RdCE[3] || Bus2IP_RdCE[4] || Bus2IP_RdCE[5] || Bus2IP_RdCE[6] || Bus2IP_RdCE[7] || Bus2IP_RdCE[8] || Bus2IP_RdCE[9] || Bus2IP_RdCE[10] || Bus2IP_RdCE[11] || Bus2IP_RdCE[12] || Bus2IP_RdCE[13] || Bus2IP_RdCE[14] || Bus2IP_RdCE[15] || Bus2IP_RdCE[16] || Bus2IP_RdCE[17] || Bus2IP_RdCE[18] || Bus2IP_RdCE[19] || Bus2IP_RdCE[20] || Bus2IP_RdCE[21] || Bus2IP_RdCE[22] || Bus2IP_RdCE[23] || Bus2IP_RdCE[24] || Bus2IP_RdCE[25] || Bus2IP_RdCE[26] || Bus2IP_RdCE[27] || Bus2IP_RdCE[28] || Bus2IP_RdCE[29] || Bus2IP_RdCE[30] || Bus2IP_RdCE[31];

  // implement slave model register read mux
  always @( slv_reg_read_sel )// or slv_reg0 or slv_reg1 or slv_reg2 or slv_reg3 or slv_reg4 or slv_reg5 or slv_reg6 or slv_reg7 or slv_reg8 or slv_reg9 or slv_reg10 or slv_reg11 or slv_reg12 or slv_reg13 or slv_reg14 or slv_reg15 or slv_reg16 or slv_reg17 or slv_reg18 or slv_reg19 or slv_reg20 or slv_reg21 or slv_reg22 or slv_reg23 or slv_reg24 or slv_reg25 or slv_reg26 or slv_reg27 or slv_reg28 or slv_reg29 or slv_reg30 or slv_reg31 )
    begin 

      case ( slv_reg_read_sel )
        //Se usan para escribir datos, por eso aca no se leen
				//32'b10000000000000000000000000000000 : slv_ip2bus_data <= slv_reg0;//00
				//32'b01000000000000000000000000000000 : slv_ip2bus_data <= slv_reg1;//04
				//32'b00100000000000000000000000000000 : slv_ip2bus_data <= slv_reg2;//08
				//32'b00010000000000000000000000000000 : slv_ip2bus_data <= slv_reg3;//0C
				//32'b00001000000000000000000000000000 : slv_ip2bus_data <= slv_reg4;//10
				//32'b00000100000000000000000000000000 : slv_ip2bus_data <= slv_reg5;//14
				//32'b00000010000000000000000000000000 : slv_ip2bus_data <= slv_reg6;//18
				//32'b00000001000000000000000000000000 : slv_ip2bus_data <= slv_reg7;//1C
				//32'b00000000100000000000000000000000 : slv_ip2bus_data <= slv_reg8;//20
				//32'b00000000010000000000000000000000 : slv_ip2bus_data <= slv_reg9;//24
				//32'b00000000001000000000000000000000 : slv_ip2bus_data <= slv_reg10;//28
        //Usadas para leer
				32'b00000000000100000000000000000000 : slv_ip2bus_data <= disparos_en_espera;		//2C slv_reg11;
				32'b00000000000010000000000000000000 : slv_ip2bus_data <= disparos_posibles;		//30 slv_reg12;
				32'b00000000000001000000000000000000 : slv_ip2bus_data <= disparos_ya_ejecutados;//34 slv_reg13;
				//32'b00000000000000100000000000000000 : slv_ip2bus_data <= slv_reg14;//38
				//32'b00000000000000010000000000000000 : slv_ip2bus_data <= slv_reg15;//3C
				//32'b00000000000000001000000000000000 : slv_ip2bus_data <= slv_reg16;//40
				//32'b00000000000000000100000000000000 : slv_ip2bus_data <= slv_reg17;//44
				//32'b00000000000000000010000000000000 : slv_ip2bus_data <= slv_reg18;//48
				//32'b00000000000000000001000000000000 : slv_ip2bus_data <= slv_reg19;//4C
				//32'b00000000000000000000100000000000 : slv_ip2bus_data <= slv_reg20;//50
				//32'b00000000000000000000010000000000 : slv_ip2bus_data <= slv_reg21;//54
				//32'b00000000000000000000001000000000 : slv_ip2bus_data <= slv_reg22;//58
				//32'b00000000000000000000000100000000 : slv_ip2bus_data <= slv_reg23;//5C
				//32'b00000000000000000000000010000000 : slv_ip2bus_data <= slv_reg24;//60
				//32'b00000000000000000000000001000000 : slv_ip2bus_data <= slv_reg25;//64
				//32'b00000000000000000000000000100000 : slv_ip2bus_data <= slv_reg26;//68
				//32'b00000000000000000000000000010000 : slv_ip2bus_data <= slv_reg27;//6C
				//32'b00000000000000000000000000001000 : slv_ip2bus_data <= slv_reg28;//70
				//32'b00000000000000000000000000000100 : slv_ip2bus_data <= slv_reg29;//74
				//32'b00000000000000000000000000000010 : slv_ip2bus_data <= slv_reg30;//78
				//32'b00000000000000000000000000000001 : slv_ip2bus_data <= slv_reg31;//7C
        default : slv_ip2bus_data <= 0;
      endcase

    end // SLAVE_REG_READ_PROC

  // ------------------------------------------------------------
  // Example code to drive IP to Bus signals
  // ------------------------------------------------------------

  assign IP2Bus_Data    = slv_ip2bus_data;
  assign IP2Bus_WrAck   = slv_write_ack;
  assign IP2Bus_RdAck   = slv_read_ack;
  assign IP2Bus_Error   = 0;

//***********************PROCESADOR DE PETRI**************************************
  
	// Datos
		//Marcado
			reg [tamano_de_elementos-1:0] marcado [cant_plazas-1:0]/* synthesis syn_keep = 1 */;
			reg [tamano_de_elementos-1:0] marcado_inicial [cant_plazas-1:0]/* synthesis syn_keep = 1 */;
		//Matriz de incidencia
			reg signed [tamano_de_elementos-1:0] matriz_incidencia [cant_plazas-1:0] [cant_transiciones-1:0]/* synthesis syn_keep = 1 */;	
		//Arcos inhibidores
			reg matriz_inhibicion [cant_plazas-1:0] [cant_transiciones-1:0]/* synthesis syn_keep = 1 */;
		//Plazas acotadas
			reg [tamano_de_elementos-1:0] cotas_plazas [cant_plazas-1:0]/* synthesis syn_keep = 1 */;
		//Transiciones automaticas
			reg [cant_transiciones-1:0] transiciones_automaticas/* synthesis syn_keep = 1 */;
		//Redes de Petri con Tiempo
			reg [tamano_de_elementos_tiempo-1:0] vector_EFT [cant_transiciones-1:0]/* synthesis syn_keep = 1 */;
			reg [tamano_de_elementos_tiempo-1:0] vector_LFT [cant_transiciones-1:0]/* synthesis syn_keep = 1 */;
			reg [tamano_vector_incremento_de_tiempo-1:0] vector_incremento_de_tiempo [cant_transiciones-1:0]/* synthesis syn_keep = 1 */;
			reg [tamano_de_elementos_tiempo-1:0] vector_tiempo_sensibilizacion [cant_transiciones-1:0]/* synthesis syn_keep = 1 */;	
		//Determinacion de disparos posibles
			reg [cant_transiciones-1:0] t_sensibilizadas/* synthesis syn_keep = 1 */;
			reg [cant_transiciones-1:0] disparos_posibles/* synthesis syn_keep = 1 */;
		//Ingreso de nuevos disparos
			reg [cant_transiciones-1:0]new_disp/* synthesis syn_keep = 1 */; //registro nuevo disparo
		
	//Señal de carga de datos
		reg carga/* synthesis syn_keep = 1 */;

/**************************EJECUCION DE LA RED PARA DETERMINAR ESTADOS**************************/

	//Resultado ecuacion: marcado+matriz_i
		reg signed [tamano_de_elementos-1:0] resultado[cant_plazas-1:0][cant_transiciones-1:0]/* synthesis syn_keep = 1 */;
		//Registros Verificacion SIGNO
			reg [cant_plazas-1:0] sign_matrix [cant_transiciones-1:0] /* synthesis syn_keep = 1 */;
			reg [cant_transiciones-1:0] t_enable_sign/* synthesis syn_keep = 1 */;
		//Registros Verificacion INHIBICIÓN
			reg [cant_plazas-1:0] inhibe_matrix [cant_transiciones-1:0] /* synthesis syn_keep = 1 */;
			reg [cant_transiciones-1:0] t_enable_inhibicion/* synthesis syn_keep = 1 */;	
		//Registros Verificacion COTAS
			reg [cant_plazas-1:0] limit_matrix [cant_transiciones-1:0]/* synthesis syn_keep = 1 */;
			reg [cant_transiciones-1:0] t_enable_limit/* synthesis syn_keep = 1 */;
		//Registros Verificacion TIEMPO
			reg [cant_transiciones-1:0] t_enable_time/* synthesis syn_keep = 1 */;

	/*RESULTADO*/
		//Determinacion de la matriz "resultado".	
		integer columnas;
		integer filas;
		always @(posedge Bus2IP_Clk)
			begin
				for (columnas=0 ; columnas<cant_transiciones ; columnas=columnas+1) //Recorro columnas
					begin
						for (filas=0 ; filas<cant_plazas ; filas=filas+1) // Recorro filas
							begin
								resultado[filas][columnas] = marcado[filas] + matriz_incidencia[filas][columnas]; //Ecuacion
								// Verificacion habilitacion por signo - Creacion de matriz
									sign_matrix [columnas][filas] = resultado[filas][columnas][tamano_de_elementos-1];
								//Verificacion habilitacion por inhibicion - Creacion de matriz
									inhibe_matrix [columnas][filas] = (|marcado[filas]) & matriz_inhibicion[filas][columnas];
								// Verificacion de habilitacion por cotas - Creacion de matriz
									if (resultado[filas][columnas][tamano_de_elementos-1]==1'b0 && resultado[filas][columnas] > cotas_plazas[filas]) // Verifico si supero la cota
										begin
											limit_matrix [columnas][filas] = 1'b0; // Cota SI superada
										end
									else  limit_matrix [columnas][filas] = 1'b1; // Cota NO superada 
							end //Fin for recorre filas
					end //Fin for recorre columnas
			end
	
	/*DETERMINACION DE HABILITACIONES*/
		integer columnas_habilitaciones;
		integer k;
		//always @(posedge Bus2IP_Clk)
		always @(*)	
			begin
				for (columnas_habilitaciones=0 ; columnas_habilitaciones<cant_transiciones ; columnas_habilitaciones=columnas_habilitaciones+1) //Recorro columnas
					begin
						/*SIGNO*/
						//Determinacion del vector de habilitacion de transiciones segun el "signo"
							t_enable_sign [columnas_habilitaciones] = ~(|(sign_matrix[columnas_habilitaciones][cant_plazas-1:0]));
						
						/*ARCOS INHIBIDORES*/
						//Determinacion del vector de habilitacion de transicones segun los "arcos inhibidores"
							t_enable_inhibicion [columnas_habilitaciones] = ~(|(inhibe_matrix[columnas_habilitaciones][cant_plazas-1:0]));
						
						/*COTAS*/
						//Determinacion del vector de habilitacion de transicones segun las "cotas de plazas"
							t_enable_limit [columnas_habilitaciones] = &(limit_matrix[columnas_habilitaciones][cant_plazas-1:0]);
					
					end
						
				/*REDES TEMPORALES*/		
				//Determinacion del vector de habilitacion de transiciones segun las "marcas temporales"
					for (k=0 ; k<cant_transiciones ; k=k+1) //Recorro transiciones
						begin
							if (vector_tiempo_sensibilizacion[k]>=vector_EFT[k] & vector_tiempo_sensibilizacion[k]<=vector_LFT[k]) t_enable_time[k] = 1'b1;
							else t_enable_time[k] = 1'b0;
						end
				
				//Determinacion de las transciones habilitadas, es decir, disparos posibles
					t_sensibilizadas = t_enable_sign & t_enable_inhibicion & t_enable_limit;
					//disparos_posibles = t_sensibilizadas;								
					disparos_posibles = t_enable_sign & t_enable_inhibicion & t_enable_limit & t_enable_time;
							
			end //FIN de always @(posedge Bus2IP_Clk) /*DETERMINACION DE HABILITACIONES*/

	//Determinacion si la red sigue activa o si se trabo
		wire red_activa;
		assign red_activa = |disparos_posibles; //Si no hay ningun disparo posible, va a tirar un cero, eso implica que la red se trabo.;
		
	//Colas de disparos
		//Actualizacion del vector de salida de cada cola segun los valores del contador de cada cola
			reg [cant_transiciones-1:0] disparos_en_espera;
			reg [cant_transiciones-1:0] colas_entrada_llenas;
			reg [cant_transiciones-1:0] colas_entrada_vacias;
			reg [cant_transiciones-1:0] disparos_ya_ejecutados;	
			reg [cant_transiciones-1:0] colas_salida_llenas;
			reg [cant_transiciones-1:0] colas_salida_vacias;
			integer indice;
			always@(*)
				begin
					for(indice=0 ; indice<cant_transiciones ; indice=indice+1)
						begin
							disparos_en_espera[indice] 		= |counter_cola_disparos_entrada[indice];
							colas_entrada_llenas[indice] 		= &counter_cola_disparos_entrada[indice];
							colas_entrada_vacias[indice] 		= ~|counter_cola_disparos_entrada[indice];
							disparos_ya_ejecutados[indice] 	= |counter_cola_disparos_salida[indice];
							colas_salida_llenas[indice] 		= &counter_cola_disparos_salida[indice];
							colas_salida_vacias[indice] 		= ~|counter_cola_disparos_salida[indice];
						end
				end
		
		//Entrada y Salida de disparos en las colas
			reg [cant_transiciones-1:0] disparo_entrada_incrementa;
			reg [cant_transiciones-1:0] disparo_entrada_decrementa;
			//Contadores
			reg [tamano_cola-1:0] counter_cola_disparos_entrada [cant_transiciones-1:0]/* synthesis syn_keep = 1 */;
			integer index_entrada;
			always @(posedge Bus2IP_Clk)
				begin
					if(Bus2IP_Reset==1'b1)
						begin
							for (index_entrada=0 ; index_entrada<cant_transiciones ; index_entrada=index_entrada+1)
								begin
									counter_cola_disparos_entrada[index_entrada]<={tamano_cola{1'b0}};
								end
						end
				else	
					for (index_entrada=0 ; index_entrada<cant_transiciones ; index_entrada=index_entrada+1)
						begin
							//Incremento cola entrada
								if ({disparo_entrada_incrementa[index_entrada] , disparo_entrada_decrementa[index_entrada]} == 2'b10) //Debe incrementar 
									begin
										counter_cola_disparos_entrada[index_entrada] <= counter_cola_disparos_entrada[index_entrada] + 1'b1;
									end //FIN if(disparo_entrante[index_entrada] == 1'b1)
							//Decremento cola entrada	
								else if ({disparo_entrada_incrementa[index_entrada] , disparo_entrada_decrementa[index_entrada]} == 2'b01) //Debe decrementar  
									begin
										counter_cola_disparos_entrada[index_entrada] <= counter_cola_disparos_entrada[index_entrada] - 1'b1;// {tamano_cola{1'b1}};
									end //FIN if(disparo_dec_entrante[index_entrada] == 1'b1)
							//Otras opciones
								else
									begin
										counter_cola_disparos_entrada[index_entrada] <= counter_cola_disparos_entrada[index_entrada];
									end
						end //FIN for (index_entrada=0 ; index_entrada<cant_transiciones ; index_entrada=index_entrada+1)
				end //FIN always
			
			reg [tamano_cola-1:0] counter_cola_disparos_salida [cant_transiciones-1:0]/* synthesis syn_keep = 1 */;
			reg [cant_transiciones-1:0] disparo_salida_incrementa;
			reg [cant_transiciones-1:0] disparo_salida_decrementa;
			integer index_salida;
			always @(posedge Bus2IP_Clk)
				begin
					if(Bus2IP_Reset==1'b1)
						begin
							for (index_salida=0 ; index_salida<cant_transiciones ; index_salida=index_salida+1)
								begin
									counter_cola_disparos_salida[index_salida]<={tamano_cola{1'b0}};
								end
						end
				else	
					for (index_salida=0 ; index_salida<cant_transiciones ; index_salida=index_salida+1)
						begin
							//Incremento cola salida
								if ({disparo_salida_incrementa[index_salida] , disparo_salida_decrementa[index_salida]} == 2'b10) //Debe incrementar 
									begin
										counter_cola_disparos_salida[index_salida] <= counter_cola_disparos_salida[index_salida] + 1'b1;
									end //FIN if(disparo_salida_decrementa[index_salida] == 1'b1)
							//Decremento cola salida	
								else if ({disparo_salida_incrementa[index_salida] , disparo_salida_decrementa[index_salida]} == 2'b01) //Debe decrementar 
									begin
										counter_cola_disparos_salida[index_salida] <= counter_cola_disparos_salida[index_salida] - 1'b1;//{tamano_cola{1'b1}};
									end //FIN if(disparo_salida_decrementa[index_salida] == 1'b1)
							//Otras opciones
								else 
									begin
										counter_cola_disparos_salida[index_salida] <= counter_cola_disparos_salida[index_salida];
									end
							end //FIN for (index_salida=0 ; index_salida<cant_transiciones ; index_salida=index_salida+1)
				end //FIN always
	
	//Actualizacion del marcado
		integer index2;
		integer index3;
		integer index4;
		integer index5;
		always @(negedge Bus2IP_Clk)
			begin
				if(carga==1'b1)	//Proceso de carga
					begin
						for (index4=0 ; index4<cant_plazas ; index4=index4+1)
							begin
								marcado[index4] <= marcado_inicial[index4];
							end
						for (index5=0 ; index5<cant_transiciones ; index5=index5+1)
							begin
								vector_tiempo_sensibilizacion[index5] <= {tamano_de_elementos_tiempo{1'b0}};
							end
					end	//Fin if(carga==1'b1)
				else //Ejecucion de la red
					begin
						for(index2=0 ; index2<cant_transiciones ; index2=index2+1)
							begin
								if ( colas_salida_llenas[index2]==1'b0 & ((transiciones_automaticas[index2]|disparos_en_espera[index2]) & disparos_posibles[index2] == 1'b1)) // Veo si el disparo en espera esta en los disparos posibles
									begin
										//Actualizo el marcado con el valor de la matriz resultado
											for (index3=0 ; index3<cant_plazas ; index3=index3+1)
												begin					
													marcado[index3] <= resultado[index3][index2];
												end
										
										//Incremento el contador de la cola de disparos de salida correspondiete
											disparo_salida_incrementa <= {cant_transiciones{1'b0}};
											disparo_salida_incrementa[index2] <= 1'b1;
										
										//Decremento el contador de la cola de disparos en espera correspondiente
											disparo_entrada_decrementa <= {cant_transiciones{1'b0}};
											disparo_entrada_decrementa[index2] <= 1'b1;
																					
										//Reseteo la marca de tiempo de la transicion que se disparo
											vector_tiempo_sensibilizacion[index2] <= {tamano_de_elementos_tiempo{1'b0}};
									
									end //Fin if ( disparos_en_espera[index2] & disparos_posibles[index2] == 1'b1)
								else //NO hay disparo en espera para esa transicion o el disparo aun no es posible
									begin
										disparo_entrada_decrementa[index2] 	<= 1'b0;
										disparo_salida_incrementa[index2] 	<= 1'b0;
										
										//Actualizo marcas temporales
											if (t_sensibilizadas[index2] == 1'b0) vector_tiempo_sensibilizacion[index2] <= {tamano_de_elementos_tiempo{1'b0}};
											if (t_sensibilizadas[index2] == 1'b1) //Transicion sensibilizada
												begin
													if (vector_tiempo_sensibilizacion[index2]+vector_incremento_de_tiempo[index2] >= {tamano_de_elementos_tiempo{1'b1}} )
														begin
															vector_tiempo_sensibilizacion[index2] <= {tamano_de_elementos_tiempo{1'b1}};
														end
													else
														begin
															vector_tiempo_sensibilizacion[index2] <= vector_tiempo_sensibilizacion[index2]+vector_incremento_de_tiempo[index2];
														end
												end
									end //FIN else no hay disparo en espera para esa transicion o el disparo aun no es posible
							end //Fin for
					end //Fin else
			end //Fin always

/****************************CARGA DE DATOS**********************/

	wire ack_escritura;
	assign slv_write_ack = ack_escritura_reg;
	
	//BUS (se debe cumplir: tamano_bus=bits_bus_plazas+bits_bus_transiciones+bits_bus_elemento)
		localparam tamano_bus				= C_SLV_DWIDTH;//Tamano del Bus de datos
		localparam tamano_bus_address		= C_NUM_REG;	//Tamano del Bus de direcciones
		localparam bits_bus_plazas			= 8;				//Cantidad de bits del dato del bus dedicado a indicar la fila de la matriz
		localparam bits_bus_transiciones	= 8;				//Cantidad de bits del dato del bus dedicado a indicar la columna de la matriz
		localparam bits_bus_elementos		= 16;				//Cantidad de bits del dato del bus dedicado a indicar el elemento
 
	//Definicion de los posibles address para escritura
		localparam m_marcado    						= 32'b10000000000000000000000000000000;//00
		localparam m_incidencia 						= 32'b01000000000000000000000000000000;//04
		localparam m_inhibicion 						= 32'b00100000000000000000000000000000;//08
		localparam p_cotas								= 32'b00010000000000000000000000000000;//0C
		localparam t_automatica 						= 32'b00001000000000000000000000000000;//10
		localparam load_vector_EFT						= 32'b00000100000000000000000000000000;//14
		localparam load_vector_incrementos_tiempo = 32'b00000010000000000000000000000000;//18		
		localparam load_vector_LFT						= 32'b00000001000000000000000000000000;//1C
		localparam new_disparo  						= 32'b00000000100000000000000000000000;//20
		localparam sacar_disparo						= 32'b00000000010000000000000000000000;//24
		localparam error									= 32'b00000000001000000000000000000000;//28
			
	localparam tamano_de_elementos_tiempo = 64;	//Tamano de los elementos de los arreglos de cuenta de tiempo, medido en bits
	
	reg ack_escritura_reg;
	
	integer filas_reset;
	integer columnas_reset;
	always@(negedge Bus2IP_Clk, negedge Bus2IP_Reset)
		begin
			if (Bus2IP_Reset==1'b1)
				begin//Reseteo de variables
					disparo_entrada_incrementa <={cant_transiciones{1'b0}};
					for (filas_reset=0 ; filas_reset<cant_plazas ; filas_reset=filas_reset+1)
						begin
						marcado_inicial[filas_reset] 							<= {tamano_de_elementos{1'b0}};
						cotas_plazas [filas_reset] 							<= {tamano_de_elementos{1'b0}};
							for (columnas_reset=0 ; columnas_reset<cant_transiciones ; columnas_reset=columnas_reset+1)
								begin
									matriz_incidencia[filas_reset][columnas_reset] 	<= {tamano_de_elementos{1'b0}};
									matriz_inhibicion [filas_reset][columnas_reset] <= 1'b0;
									
								end //FIN for (filas_reset=0 ; filas_reset<cant_plazas ; filas_reset=filas_reset+1)
						end //FIN for (columnas_reset=0 ; columnas_reset<cant_transiciones ; columnas_reset=columnas_reset+1)
				end //Fin if(Bus2IP_Reset==1'b1)
			else //No es Bus2IP_Reset
				begin
					case (slv_reg_write_sel)
						m_marcado: //Carga del marcado inicial
							begin
								carga<=1'b1;
								marcado_inicial [Bus2IP_Data[tamano_bus-1:tamano_bus-bits_bus_plazas]]<=Bus2IP_Data[tamano_de_elementos-1:0];
								disparo_entrada_incrementa <= {cant_transiciones{1'b0}};
								disparo_salida_decrementa <= {cant_transiciones{1'b0}};								
								ack_escritura_reg = 1'b1;
							end //FIN del caso m_marcado
						m_incidencia: //Carga de la matriz de incidencia
							begin
								carga<=1'b1;
								matriz_incidencia [Bus2IP_Data[tamano_bus-1:tamano_bus-bits_bus_plazas]] [Bus2IP_Data[tamano_bus-bits_bus_plazas-1:tamano_bus-bits_bus_plazas-bits_bus_transiciones]] <= Bus2IP_Data[tamano_de_elementos-1:0];
								disparo_entrada_incrementa <= {cant_transiciones{1'b0}};
								disparo_salida_decrementa <= {cant_transiciones{1'b0}};
								ack_escritura_reg = 1'b1;	
							end //FIN del caso m_incidencia
						m_inhibicion: //Carga de la matriz de inhibicion
							begin
								carga<=1'b1;
								matriz_inhibicion [Bus2IP_Data[tamano_bus-1:tamano_bus-bits_bus_plazas]] [Bus2IP_Data[tamano_bus-bits_bus_plazas-1:tamano_bus-bits_bus_plazas-bits_bus_transiciones]] <= Bus2IP_Data[0];
								disparo_entrada_incrementa <= {cant_transiciones{1'b0}};
								disparo_salida_decrementa <= {cant_transiciones{1'b0}};
								ack_escritura_reg = 1'b1;							
							end	//FIN del caso m_inhibicion	
						p_cotas: //Carga del vector de cotas
							begin
								carga<=1'b1;
								cotas_plazas [Bus2IP_Data[tamano_bus-1:tamano_bus-bits_bus_plazas]] <=Bus2IP_Data[tamano_de_elementos-1:0];
								disparo_entrada_incrementa <={cant_transiciones{1'b0}};
								disparo_salida_decrementa <= {cant_transiciones{1'b0}};
								ack_escritura_reg = 1'b1;
							end //FIN del caso p_cotas
						t_automatica:
							begin
								carga<=1'b1;
								transiciones_automaticas [Bus2IP_Data[tamano_bus-bits_bus_plazas-1:tamano_bus-bits_bus_plazas-bits_bus_transiciones]]<=Bus2IP_Data[0];//generar vector sacar de aca
								disparo_entrada_incrementa <={cant_transiciones{1'b0}};
								disparo_salida_decrementa <= {cant_transiciones{1'b0}};
								ack_escritura_reg = 1'b1;
							end //FIN del caso t_automatica
						load_vector_EFT:
							begin
								carga<=1'b1;
								if (Bus2IP_Data[tamano_bus-1:tamano_bus-bits_bus_plazas]==8'b00000000) //Parte menos significativa de LFT
									begin
										vector_EFT [Bus2IP_Data[tamano_bus-bits_bus_plazas-1:tamano_bus-bits_bus_plazas-bits_bus_transiciones]][(tamano_de_elementos_tiempo/4)-1:0]<=Bus2IP_Data[(tamano_de_elementos_tiempo/4)-1:0];
									end
								else if (Bus2IP_Data[tamano_bus-1:tamano_bus-bits_bus_plazas]==8'b00000001)
									begin
										vector_EFT [Bus2IP_Data[tamano_bus-bits_bus_plazas-1:tamano_bus-bits_bus_plazas-bits_bus_transiciones]][((tamano_de_elementos_tiempo/4)*2)-1:(tamano_de_elementos_tiempo/4)*1]<=Bus2IP_Data[(tamano_de_elementos_tiempo/4)-1:0];
									end
								else if (Bus2IP_Data[tamano_bus-1:tamano_bus-bits_bus_plazas]==8'b00000010)
									begin
										vector_EFT [Bus2IP_Data[tamano_bus-bits_bus_plazas-1:tamano_bus-bits_bus_plazas-bits_bus_transiciones]][((tamano_de_elementos_tiempo/4)*3)-1:(tamano_de_elementos_tiempo/4)*2]<=Bus2IP_Data[(tamano_de_elementos_tiempo/4)-1:0];
									end
								else if (Bus2IP_Data[tamano_bus-1:tamano_bus-bits_bus_plazas]==8'b00000011) //Parte mas significativa de LFT
									begin
										vector_EFT [Bus2IP_Data[tamano_bus-bits_bus_plazas-1:tamano_bus-bits_bus_plazas-bits_bus_transiciones]][tamano_de_elementos_tiempo-1:(tamano_de_elementos_tiempo/4)*3]<=Bus2IP_Data[(tamano_de_elementos_tiempo/4)-1:0];
									end
								disparo_entrada_incrementa <= {cant_transiciones{1'b0}};
								disparo_salida_decrementa <= {cant_transiciones{1'b0}};
								ack_escritura_reg = 1'b1;
							end
						load_vector_incrementos_tiempo:
							begin
								carga<=1'b1;
								vector_incremento_de_tiempo [Bus2IP_Data[tamano_bus-bits_bus_plazas-1:tamano_bus-bits_bus_plazas-bits_bus_transiciones]]<=Bus2IP_Data[tamano_de_elementos-1:0];//generar vector sacar de aca
								disparo_entrada_incrementa <= {cant_transiciones{1'b0}};
								disparo_salida_decrementa <= {cant_transiciones{1'b0}};
								ack_escritura_reg = 1'b1;
							end
						load_vector_LFT:
							begin
								carga<=1'b1;
								if (Bus2IP_Data[tamano_bus-1:tamano_bus-bits_bus_plazas]==8'b00000000) //Parte menos significativa de LFT
									begin
										vector_LFT [Bus2IP_Data[tamano_bus-bits_bus_plazas-1:tamano_bus-bits_bus_plazas-bits_bus_transiciones]][(tamano_de_elementos_tiempo/4)-1:0]<=Bus2IP_Data[(tamano_de_elementos_tiempo/4)-1:0];
									end
								else if (Bus2IP_Data[tamano_bus-1:tamano_bus-bits_bus_plazas]==8'b00000001)
									begin
										vector_LFT [Bus2IP_Data[tamano_bus-bits_bus_plazas-1:tamano_bus-bits_bus_plazas-bits_bus_transiciones]][((tamano_de_elementos_tiempo/4)*2)-1:(tamano_de_elementos_tiempo/4)*1]<=Bus2IP_Data[(tamano_de_elementos_tiempo/4)-1:0];
									end
								else if (Bus2IP_Data[tamano_bus-1:tamano_bus-bits_bus_plazas]==8'b00000010)
									begin
										vector_LFT [Bus2IP_Data[tamano_bus-bits_bus_plazas-1:tamano_bus-bits_bus_plazas-bits_bus_transiciones]][((tamano_de_elementos_tiempo/4)*3)-1:(tamano_de_elementos_tiempo/4)*2]<=Bus2IP_Data[(tamano_de_elementos_tiempo/4)-1:0];
									end
								else if (Bus2IP_Data[tamano_bus-1:tamano_bus-bits_bus_plazas]==8'b00000011) //Parte mas significativa de LFT
									begin
										vector_LFT [Bus2IP_Data[tamano_bus-bits_bus_plazas-1:tamano_bus-bits_bus_plazas-bits_bus_transiciones]][tamano_de_elementos_tiempo-1:(tamano_de_elementos_tiempo/4)*3]<=Bus2IP_Data[(tamano_de_elementos_tiempo/4)-1:0];
									end
								disparo_entrada_incrementa <= {cant_transiciones{1'b0}};
								disparo_salida_decrementa <= {cant_transiciones{1'b0}};
								ack_escritura_reg = 1'b1;
							end
						new_disparo://prepara el vector de nuevo disparo y sube el flag de incremento
							begin
								carga<=1'b0;
								//Verificar si la cola esta llena o no
									if(colas_entrada_llenas[Bus2IP_Data[tamano_bus-bits_bus_plazas-1:tamano_bus-bits_bus_plazas-bits_bus_transiciones]]==1'b0) //Cola NO llena
										begin
											disparo_entrada_incrementa <= {cant_transiciones{1'b0}};
											disparo_entrada_incrementa [Bus2IP_Data[tamano_bus-bits_bus_plazas-1:tamano_bus-bits_bus_plazas-bits_bus_transiciones]] <= 1'b1;//generar vector sacar de aca
											disparo_salida_decrementa <= {cant_transiciones{1'b0}};
											ack_escritura_reg = 1'b1;
										end
									else //Cola LLENA
										begin
											disparo_entrada_incrementa <={cant_transiciones{1'b0}};
											disparo_salida_decrementa <= {cant_transiciones{1'b0}};
											ack_escritura_reg = 1'b0;
										end
							end //FIN del caso new_disparo
						sacar_disparo:
							begin
								carga<=1'b0;
								//Verificar si el disparo se encuentra en la cola de salida
									if (colas_salida_vacias[Bus2IP_Data[tamano_bus-bits_bus_plazas-1:tamano_bus-bits_bus_plazas-bits_bus_transiciones]]==1'b0 ) // La cola del disparo que se quiere sacar no esta vacia
										begin
											disparo_salida_decrementa <= {cant_transiciones{1'b0}};
											disparo_salida_decrementa [Bus2IP_Data[tamano_bus-bits_bus_plazas-1:tamano_bus-bits_bus_plazas-bits_bus_transiciones]] <= 1'b1;
											disparo_entrada_incrementa <={cant_transiciones{1'b0}};
											ack_escritura_reg = 1'b1;
										end
									else //Cola vacia - El disparo que se quiere sacar NO fue ejecutado aun
										begin
											disparo_salida_decrementa <= {cant_transiciones{1'b0}};
											disparo_entrada_incrementa <={cant_transiciones{1'b0}};
											ack_escritura_reg = 1'b0;
										end
							end //FIN del caso sacar_disparo
						default:
							begin
								carga<=1'b0;
								disparo_entrada_incrementa <={cant_transiciones{1'b0}};
								disparo_salida_decrementa <= {cant_transiciones{1'b0}};
								ack_escritura_reg = 1'b0;							
							end //FIN del caso default
				endcase	//FIN	del case	
			end //FIN del else	
		end	//FIN always@(negedge Bus2IP_Clk, posedge Bus2IP_Reset) 
  

endmodule
