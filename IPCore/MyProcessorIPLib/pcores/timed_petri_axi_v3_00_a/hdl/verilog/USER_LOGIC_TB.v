`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   15:32:37 10/08/2012
// Design Name:   user_logic
// Module Name:   D:/ProyectoIntegrador/trunk/Implementacion/IPCore/MyProcessorIPLib/pcores/timed_petri_axi_v3_00_a/hdl/verilog/USER_LOGIC_TB.v
// Project Name:  timed_petri_axi
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: user_logic
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module USER_LOGIC_TB;

	// Inputs
	reg Bus2IP_Clk;
	reg Bus2IP_Resetn;
	reg [31:0] Bus2IP_Data;
	reg [3:0] Bus2IP_BE;
	reg [31:0] Bus2IP_RdCE;
	reg [31:0] Bus2IP_WrCE;

	// Outputs
	wire Interrupt;
	wire [31:0] IP2Bus_Data;
	wire IP2Bus_RdAck;
	wire IP2Bus_WrAck;
	wire IP2Bus_Error;

	// Instantiate the Unit Under Test (UUT)
	user_logic 
	#(	.cant_plazas(2),
		.cant_transiciones(1),
		.bits_cant_transiciones(),
		.tamano_de_elementos(5),
		.tamano_cola(5),
		.tamano_vector_incremento_de_tiempo(5),
		.tamano_de_elementos_tiempo(48)
	)
	uut 
	(
		.Interrupt(Interrupt), 
		.Bus2IP_Clk(Bus2IP_Clk), 
		.Bus2IP_Resetn(Bus2IP_Resetn), 
		.Bus2IP_Data(Bus2IP_Data), 
		.Bus2IP_BE(Bus2IP_BE), 
		.Bus2IP_RdCE(Bus2IP_RdCE), 
		.Bus2IP_WrCE(Bus2IP_WrCE), 
		.IP2Bus_Data(IP2Bus_Data), 
		.IP2Bus_RdAck(IP2Bus_RdAck), 
		.IP2Bus_WrAck(IP2Bus_WrAck), 
		.IP2Bus_Error(IP2Bus_Error)
	);
	
	//Clock
		always #10 Bus2IP_Clk = ~Bus2IP_Clk;

	//Definicion de los posibles address para escritura
		localparam m_marcado    						= 32'b10000000000000000000000000000000;//00
		localparam m_incidencia_positiva				= 32'b01000000000000000000000000000000;//04
		localparam m_incidencia_negativa				= 32'b00100000000000000000000000000000;//08
		localparam m_inhibicion 						= 32'b00010000000000000000000000000000;//0C
		localparam p_cotas								= 32'b00001000000000000000000000000000;//10
		localparam t_automatica 						= 32'b00000100000000000000000000000000;//14
		localparam load_vector_duracion				= 32'b00000010000000000000000000000000;//18
		localparam load_vector_incrementos_tiempo = 32'b00000001000000000000000000000000;//1C		
		localparam t_intr									= 32'b00000000100000000000000000000000;//20
		localparam v_prioridades						= 32'b00000000010000000000000000000000;//24
		localparam new_disparo  						= 32'b00000000001000000000000000000000;//28
		localparam sacar_disparo						= 32'b00000000000100000000000000000000;//2C
		localparam error									= 32'b00000000000010000000000000000000;//30

	initial 
		begin
			// Initialize Inputs
				Bus2IP_Clk = 0;
				Bus2IP_Resetn = 0;
				Bus2IP_Data = 0;
				Bus2IP_BE = 0;
				Bus2IP_RdCE = 0;
				Bus2IP_WrCE = 0;

			// Wait 100 ns for global reset to finish
				#100;
        
			// Add stimulus here
				
				Bus2IP_Resetn = 1;
				
				//Matriz de incidencia Positiva
					//Matriz de incidencia Positiva [0][0]
						@(negedge Bus2IP_Clk)
						Bus2IP_WrCE 	= m_incidencia_positiva;
						//Plazas: 00000000=00H - Transiciones: 00000000=00H - Elemento: 0000000000000000
						Bus2IP_Data 	= 32'h00000000;	
					//Matriz de incidencia Positiva [1][0]
						@(negedge Bus2IP_Clk)
						Bus2IP_WrCE 	= m_incidencia_positiva;
						//Plazas: 00000001=01H - Transiciones: 00000000=00H - Elemento: 0000000000000001
						Bus2IP_Data 	= 32'h01000001;	
						
				//Matriz de incidencia Negativa
					//Matriz de incidencia Negativa [0][0]
						@(negedge Bus2IP_Clk)
						Bus2IP_WrCE 	= m_incidencia_negativa;
						//Plazas: 00000000=00H - Transiciones: 00000000=00H - Elemento: 0000000000000001
						Bus2IP_Data 	= 32'h00000001;	
					//Matriz de incidencia Negativa [1][0]
						@(negedge Bus2IP_Clk)
						Bus2IP_WrCE 	= m_incidencia_negativa;
						//Plazas: 00000001=01H - Transiciones: 00000000=00H - Elemento: 0000000000000000
						Bus2IP_Data 	= 32'h01000000;

				//Matriz de inhibicion
					//Matriz de inhibicion [0][0]
						@(negedge Bus2IP_Clk)
						Bus2IP_WrCE 	= m_inhibicion;
						//Plazas: 00000000=00H - Transiciones: 00000000=00H - Elemento: 0000000000000000
						Bus2IP_Data 	= 32'h00000000;	
					//Matriz de inhibicion [1][0]
						@(negedge Bus2IP_Clk)
						Bus2IP_WrCE 	= m_inhibicion;
						//Plazas: 00000001=01H - Transiciones: 00000000=00H - Elemento: 0000000000000000
						Bus2IP_Data 	= 32'h01000000;	

				//Vector de cotas	
					//Vector de cotas [0]
						@(negedge Bus2IP_Clk)
						Bus2IP_WrCE 	= p_cotas;
						//Plazas: 00000000=00H - Transiciones: 00000000=00H - Elemento: 1111111111111111
						Bus2IP_Data	= 32'h0000FFFF;	
					//Vector de cotas [1]
						@(negedge Bus2IP_Clk)
						Bus2IP_WrCE 	= p_cotas;
						//Plazas: 00000001=01H - Transiciones: 00000000=00H - Elemento: 1111111111111111
						Bus2IP_Data	= 32'h0100FFFF;	

					//Vector de Transiciones Automaticas
						//Transicion Automatica [0]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= t_automatica;
							//Plazas: 00000000=00H - Transiciones: 00000000=00H - Elemento: 0000000000000000
							Bus2IP_Data	= 32'h00000000;	
							
					//Vector de tiempo Duracion
						//Vector Duracion[0]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_duracion;
							//Plazas: 00000000=00H - Transiciones: 00000000=00H - Elemento: 0000000000001010
							Bus2IP_Data	= 32'h0000000A;								

					//Factor de escala para incrementar las marcas de tiempo	
						//Vector de incrementos de tiempo[0]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_incrementos_tiempo;
							//Plazas: 00000000=00H - Transiciones: 00000000=00H - Elemento: 0000000000000010
							Bus2IP_Data	= 32'h00000002;

					//Vector de Transiciones que Interrumpen
						//Transicion que Interrumpen [0]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= t_intr;
							//Plazas: 00000000=00H - Transiciones: 00000000=00H - Elemento: 0000000000000001
							Bus2IP_Data	= 32'h00000001;	
							
					//Marcado inicial
						//Marcado inicial [0]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_marcado;
							//Plazas: 00000000=00H - Transiciones: 00000000=00H - Elemento: 0000000000000001=0001H
							Bus2IP_Data 	= 32'h00000001;	
						//Marcado inicial [1]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_marcado;
							//Plazas: 00000001=01H - Transiciones: 00000000=00H - Elemento: 0000000000000000=0000H
							Bus2IP_Data 	= 32'h01000000;	

				//Dejar de cargar
					#1000;
				
				//Secuencia de disparos
					@(posedge Bus2IP_Clk)
					Bus2IP_WrCE 	= new_disparo;
					//Plazas: 00000000=00H - Transiciones: 00000000=00H - Elemento: 0000000000000000=0000H
					Bus2IP_Data	= 32'h00000000;	
					@(posedge Bus2IP_Clk)
					Bus2IP_WrCE 	= error;

				//Detener la simulacion
					#1000;
					$stop;					
						
		end
      
endmodule

