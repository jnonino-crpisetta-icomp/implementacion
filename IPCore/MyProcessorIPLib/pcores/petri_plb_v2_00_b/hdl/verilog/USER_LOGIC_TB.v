`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   17:24:11 09/07/2012
// Design Name:   user_logic
// Module Name:   D:/ProyectoIntegrador/trunk/Implementacion/IPCore/MyProcessorIPLib/pcores/petri_axi_v2_00_a/devl/projnav/USER_LOGIC_TB.v
// Project Name:  petri_axi
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
	wire [31:0] IP2Bus_Data;
	wire IP2Bus_RdAck;
	wire IP2Bus_WrAck;
	wire IP2Bus_Error;

	// Instantiate the Unit Under Test (UUT)
	user_logic uut 
	(	.Bus2IP_Clk(Bus2IP_Clk), 
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
	localparam leer_en_espera						= 32'b00000000000100000000000000000000;//2C
	localparam leer_posibles						= 32'b00000000000010000000000000000000;//2C
	localparam leer_ejecutados						= 32'b00000000000001000000000000000000;//34
		
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
				Bus2IP_Resetn=1'b0;
				#100
				Bus2IP_Resetn=1'b1;
				#100
				
				//Carga de datos
					//Marcado inicial
						//Marcado inicial [0]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_marcado;
							//Plazas: 00000000=00H - Transiciones: 00000000=00H - Elemento: 0000000000000001=0001H
							Bus2IP_Data 	= 32'h00000001;	
							#1000;
						//Marcado inicial [1]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_marcado;
							//Plazas: 00000001=01H - Transiciones: 00000000=00H - Elemento: 0000000000000000=0000H
							Bus2IP_Data 	= 32'h01000000;	
							#1000;
						//Marcado inicial [2]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_marcado;
							//Plazas: 00000010=02H - Transiciones: 00000000=00H - Elemento: 0000000000000000=0000H
							Bus2IP_Data 	= 32'h02000000;	
							#1000;
					
					//Matriz de incidencia
						//Matriz de incidencia [0][0]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_incidencia;
							//Plazas: 00000000=00H - Transiciones: 00000000=00H - Elemento: 1111111111111111
							Bus2IP_Data 	= 32'h0000FFFF;	
							#1000
						//Matriz de incidencia [0][1]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_incidencia;
							//Plazas: 00000000=00H - Transiciones: 00000001=01H - Elemento: 0000000000000001
							Bus2IP_Data 	= 32'h00010001;	
							#1000;
						//Matriz de incidencia [0][2]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_incidencia;
							//Plazas: 00000000=00H - Transiciones: 00000010=02H - Elemento: 1111111111111111
							Bus2IP_Data 	= 32'h0002FFFF;
							#1000;	
						//Matriz de incidencia [0][3]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_incidencia;
							//Plazas: 00000000=00H - Transiciones: 00000011=03H - Elemento: 0000000000000001
							Bus2IP_Data 	= 32'h00030001;
							#1000;	
						//Matriz de incidencia [1][0]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_incidencia;
							//Plazas: 00000001=01H - Transiciones: 00000000=00H - Elemento: 0000000000000001
							Bus2IP_Data 	= 32'h01000001;	
							#1000;
						//Matriz de incidencia [1][1]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_incidencia;
							//Plazas: 00000001=01H - Transiciones: 00000001=01H - Elemento: 1111111111111111
							Bus2IP_Data 	= 32'h0101FFFF;	
							#1000;
						//Matriz de incidencia [1][2]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_incidencia;
							//Plazas: 00000001=01H - Transiciones: 00000010=02H - Elemento: 0000000000000000
							Bus2IP_Data 	= 32'h01020000;	
							#1000;
						//Matriz de incidencia [1][3]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_incidencia;
							//Plazas: 00000001=01H - Transiciones: 00000011=03H - Elemento: 0000000000000000
							Bus2IP_Data 	= 32'h01030000;	
							#1000;
						//Matriz de incidencia [2][0]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_incidencia;
							//Plazas: 00000010=02H - Transiciones: 00000000=00H - Elemento: 0000000000000000
							Bus2IP_Data 	= 32'h02000000;	
							#1000;
						//Matriz de incidencia [2][1]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_incidencia;
							//Plazas: 00000010=02H - Transiciones: 00000001=01H - Elemento: 0000000000000000
							Bus2IP_Data 	= 32'h02010000;	
							#1000;
						//Matriz de incidencia [2][2]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_incidencia;
							//Plazas: 00000010=02H - Transiciones: 00000010=02H - Elemento: 0000000000000001
							Bus2IP_Data 	= 32'h02020001;	
							#1000;
						//Matriz de incidencia [2][3]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_incidencia;
							//Plazas: 00000010=02H - Transiciones: 00000011=03H - Elemento: 1111111111111111
							Bus2IP_Data 	= 32'h0203FFFF;	
							#1000;							
				
					//Matriz de inhibicion
						//Matriz de inhibicion [0][0]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_inhibicion;
							//Plazas: 00000000=00H - Transiciones: 00000000=00H - Elemento: 0000000000000000
							Bus2IP_Data 	= 32'h00000000;	
							#1000;
						//Matriz de inhibicion [0][1]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_inhibicion;
							//Plazas: 00000000=00H - Transiciones: 00000001=01H - Elemento: 0000000000000000
							Bus2IP_Data 	= 32'h00010000;	
							#1000;
						//Matriz de inhibicion [0][2]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_inhibicion;
							//Plazas: 00000000=00H - Transiciones: 00000010=02H - Elemento: 0000000000000000
							Bus2IP_Data 	= 32'h00020000;	
							#1000;	
						//Matriz de inhibicion [0][3]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_inhibicion;
							//Plazas: 00000000=00H - Transiciones: 00000011=03H - Elemento: 0000000000000000
							Bus2IP_Data 	= 32'h00030000;	
							#1000;
						//Matriz de inhibicion [1][0]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_inhibicion;
							//Plazas: 00000001=01H - Transiciones: 00000000=00H - Elemento: 0000000000000000
							Bus2IP_Data 	= 32'h01000000;	
							#1000;
						//Matriz de inhibicion [1][1]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_inhibicion;
							//Plazas: 00000001=01H - Transiciones: 00000001=01H - Elemento: 0000000000000000
							Bus2IP_Data 	= 32'h01010000;	
							#1000;
						//Matriz de inhibicion [1][2]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_inhibicion;
							//Plazas: 00000001=01H - Transiciones: 00000010=02H - Elemento: 0000000000000000
							Bus2IP_Data 	= 32'h01020000;	
							#1000;	
						//Matriz de inhibicion [1][3]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_inhibicion;
							//Plazas: 00000001=01H - Transiciones: 00000011=03H - Elemento: 0000000000000000
							Bus2IP_Data 	= 32'h01030000;	
							#1000;	
						//Matriz de inhibicion [2][0]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_inhibicion;
							//Plazas: 00000010=02H - Transiciones: 00000000=00H - Elemento: 0000000000000000
							Bus2IP_Data 	= 32'h02000000;	
							#1000;
						//Matriz de inhibicion [2][1]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_inhibicion;
							//Plazas: 00000010=02H - Transiciones: 00000001=01H - Elemento: 0000000000000000
							Bus2IP_Data 	= 32'h02010000;	
							#1000;
						//Matriz de inhibicion [2][2]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_inhibicion;
							//Plazas: 00000010=02H - Transiciones: 00000010=02H - Elemento: 0000000000000000
							Bus2IP_Data 	= 32'h02020000;	
							#1000;
						//Matriz de inhibicion [2][3]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= m_inhibicion;
							//Plazas: 00000010=02H - Transiciones: 00000011=03H - Elemento: 0000000000000000
							Bus2IP_Data 	= 32'h02030000;	
							#1000;							

					//Vector de cotas	
						//Vector de cotas [0]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= p_cotas;
							//Plazas: 00000000=00H - Transiciones: 00000000=00H - Elemento: 0000000000000001
							Bus2IP_Data	= 32'h00000001;	
							#1000;
						//Vector de cotas [1]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= p_cotas;
							//Plazas: 00000001=01H - Transiciones: 00000000=00H - Elemento: 0000000000000001
							Bus2IP_Data	= 32'h01000001;	
							#1000;
						//Vector de cotas [2]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= p_cotas;
							//Plazas: 00000010=02H - Transiciones: 00000000=00H - Elemento: 0000000000000001
							Bus2IP_Data	= 32'h02000001;	
							#1000;
						
					//Vector de Transiciones Automaticas
						//Transicion Automatica [0]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= t_automatica;
							//Plazas: 00000000=00H - Transiciones: 00000000=00H - Elemento: 0000000000000000
							Bus2IP_Data	= 32'h00000000;	
							#1000;
						//Transicion Automatica[1]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= t_automatica;
							//Plazas: 00000000=00H - Transiciones: 00000001=01H - Elemento: 0000000000000000
							Bus2IP_Data	= 32'h00010000;	
							#1000;
						//Transicion Automatica[2]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= t_automatica;
							//Plazas: 00000000=00H - Transiciones: 00000010=02H - Elemento: 0000000000000000
							Bus2IP_Data	= 32'h00020000;	
							#1000;
						//Transicion Automatica[3]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= t_automatica;
							//Plazas: 00000000=00H - Transiciones: 00000011=03H - Elemento: 0000000000000000
							Bus2IP_Data	= 32'h00030000;	
							#1000;

					//Vector de tiempo EFT
						//Vector EFT[0]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_EFT;
							//Plazas: 00000000=00H - Transiciones: 00000000=00H - Elemento: 0000000000000000
							Bus2IP_Data	= 32'h00000000;	
							#1000;
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_EFT;
							//Plazas: 00000001=01H - Transiciones: 00000000=00H - Elemento: 0000000000000000
							Bus2IP_Data	= 32'h01000000;	
							#1000;
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_EFT;
							//Plazas: 00000010=02H - Transiciones: 00000000=00H - Elemento: 0000000000000000
							Bus2IP_Data	= 32'h02000000;	
							#1000;
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_EFT;
							//Plazas: 00000011=03H - Transiciones: 00000000=00H - Elemento: 0000000000000000
							Bus2IP_Data	= 32'h03000000;	
							#1000;							
							
						//Vector EFT[1]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_EFT;
							//Palabra: 00000000=00H - Transiciones: 00000001=01H - Elemento: 0000000000000000
							Bus2IP_Data	= 32'h00010000;	
							#1000;
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_EFT;
							//Palabra: 00000001=01H - Transiciones: 00000001=01H - Elemento: 0000000000000000
							Bus2IP_Data	= 32'h01010000;	
							#1000;
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_EFT;
							//Palabra: 00000010=02H - Transiciones: 00000001=01H - Elemento: 0000000000000000
							Bus2IP_Data	= 32'h02010000;	
							#1000;
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_EFT;
							//Palabra: 00000011=03H - Transiciones: 00000001=01H - Elemento: 0000000000000000
							Bus2IP_Data	= 32'h03010000;	
							#1000;
						//Vector EFT[2]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_EFT;
							//Palabra: 00000000=00H - Transiciones: 00000010=02H - Elemento: 0000000000000000
							Bus2IP_Data	= 32'h00020000;	
							#1000;
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_EFT;
							//Palabra: 00000001=01H - Transiciones: 00000010=02H - Elemento: 0000000000000000
							Bus2IP_Data	= 32'h01020000;	
							#1000;
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_EFT;
							//Palabra: 00000010=02H - Transiciones: 00000010=02H - Elemento: 0000000000000000
							Bus2IP_Data	= 32'h02020000;	
							#1000;
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_EFT;
							//Palabra: 00000011=03H - Transiciones: 00000010=02H - Elemento: 0000000000000000
							Bus2IP_Data	= 32'h03020000;	
							#1000;
						//Vector EFT[3]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_EFT;
							//Palabra: 00000000=00H - Transiciones: 00000011=03H - Elemento: 0000000000000000
							Bus2IP_Data	= 32'h00030000;	
							#1000;
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_EFT;
							//Palabra: 00000001=01H - Transiciones: 00000011=03H - Elemento: 0000000000000000
							Bus2IP_Data	= 32'h01030000;	
							#1000;
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_EFT;
							//Palabra: 00000010=02H - Transiciones: 00000011=03H - Elemento: 0000000000000000
							Bus2IP_Data	= 32'h02030000;	
							#1000;
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_EFT;
							//Palabra: 00000011=03H - Transiciones: 00000011=03H - Elemento: 0000000000000000
							Bus2IP_Data	= 32'h03030000;	
							#1000;
						
					//Vector de tiempo LFT
						//Vector LFT[0]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_LFT;
							//Palabra: 00000000=00H - Transiciones: 00000000=00H - Elemento: 1111111111111111
							Bus2IP_Data	= 32'h0000FFFF;	
							#1000;
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_LFT;
							//Palabra: 00000001=01H - Transiciones: 00000000=00H - Elemento: 1111111111111111
							Bus2IP_Data	= 32'h0100FFFF;	
							#1000;	
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_LFT;
							//Palabra: 00000010=02H - Transiciones: 00000000=00H - Elemento: 1111111111111111
							Bus2IP_Data	= 32'h0200FFFF;	
							#1000;	
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_LFT;
							//Palabra: 00000011=03H - Transiciones: 00000000=00H - Elemento: 1111111111111111
							Bus2IP_Data	= 32'h0300FFFF;	
							#1000;								
						//Vector LFT[1]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_LFT;
							//Palabra: 00000000=00H - Transiciones: 00000001=01H - Elemento: 1111111111111111
							Bus2IP_Data	= 32'h0001FFFF;	
							#1000;
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_LFT;
							//Palabra: 00000001=00H - Transiciones: 00000001=01H - Elemento: 1111111111111111
							Bus2IP_Data	= 32'h0101FFFF;	
							#1000;
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_LFT;
							//Palabra: 00000010=02H - Transiciones: 00000001=01H - Elemento: 1111111111111111
							Bus2IP_Data	= 32'h0201FFFF;	
							#1000;
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_LFT;
							//Palabra: 00000011=03H - Transiciones: 00000001=01H - Elemento: 1111111111111111
							Bus2IP_Data	= 32'h0301FFFF;	
							#1000;
						//Vector LFT[2]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_LFT;
							//Palabra: 00000000=00H - Transiciones: 00000010=02H - Elemento: 1111111111111111
							Bus2IP_Data	= 32'h0002FFFF;	
							#1000;
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_LFT;
							//Palabra: 00000001=00H - Transiciones: 00000010=02H - Elemento: 1111111111111111
							Bus2IP_Data	= 32'h0102FFFF;	
							#1000;
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_LFT;
							//Palabra: 00000010=02H - Transiciones: 00000010=02H - Elemento: 1111111111111111
							Bus2IP_Data	= 32'h0202FFFF;	
							#1000;
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_LFT;
							//Palabra: 00000011=03H - Transiciones: 00000010=02H - Elemento: 1111111111111111
							Bus2IP_Data	= 32'h0302FFFF;	
							#1000;
						//Vector LFT[3]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_LFT;
							//Palabra: 00000000=00H - Transiciones: 00000011=03H - Elemento: 1111111111111111
							Bus2IP_Data	= 32'h0003FFFF;	
							#1000;
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_LFT;
							//Palabra: 00000001=01H - Transiciones: 00000011=03H - Elemento: 1111111111111111
							Bus2IP_Data	= 32'h0103FFFF;	
							#1000;
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_LFT;
							//Palabra: 00000010=02H - Transiciones: 00000011=03H - Elemento: 1111111111111111
							Bus2IP_Data	= 32'h0203FFFF;	
							#1000;
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_LFT;
							//Palabra: 00000011=03H - Transiciones: 00000011=03H - Elemento: 1111111111111111
							Bus2IP_Data	= 32'h0303FFFF;	
							#1000;
				
					//Factor de escala para incrementar las marcas de tiempo	
						//Vector de incrementos de tiempo[0]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_incrementos_tiempo;
							//Plazas: 00000000=00H - Transiciones: 00000000=00H - Elemento: 0000000000000001
							Bus2IP_Data	= 32'h00000001;	
							#1000;	
						//Vector de incrementos de tiempo[1]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_incrementos_tiempo;
							//Plazas: 00000000=00H - Transiciones: 00000001=01H - Elemento: 0000000000000001
							Bus2IP_Data	= 32'h00010001;	
							#1000;	
						//Vector de incrementos de tiempo[2]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_incrementos_tiempo;
							//Plazas: 00000000=00H - Transiciones: 00000010=02H - Elemento: 0000000000000001
							Bus2IP_Data	= 32'h00020001;	
							#1000;
						//Vector de incrementos de tiempo[3]
							@(negedge Bus2IP_Clk)
							Bus2IP_WrCE 	= load_vector_incrementos_tiempo;
							//Plazas: 00000000=00H - Transiciones: 00000011=03H - Elemento: 0000000000000001
							Bus2IP_Data	= 32'h00030001;	
							#1000;	
													
						
				//Dejar de cargar
					#1000;
				
				//Secuencia de disparos
					@(posedge Bus2IP_Clk)
					Bus2IP_WrCE 	= new_disparo;
					//Plazas: 00000000=00H - Transiciones: 00000000=00H - Elemento: 0000000000000000=0000H
					Bus2IP_Data	= 32'h00000000;	
					@(posedge Bus2IP_Clk)
					Bus2IP_WrCE 	= error;
					
					#50;
					
					@(posedge Bus2IP_Clk)
					Bus2IP_WrCE 	= new_disparo;
					//Plazas: 00000000=00H - Transiciones: 00000001=01H - Elemento: 0000000000000000=0000H
					Bus2IP_Data	= 32'h00010000;	
					@(posedge Bus2IP_Clk)
					Bus2IP_WrCE 	= error;
					
					#50;
					
					@(posedge Bus2IP_Clk)
					Bus2IP_WrCE 	= new_disparo;
					//Plazas: 00000000=00H - Transiciones: 00000000=00H - Elemento: 0000000000000000=0000H
					Bus2IP_Data	= 32'h00000000;	
					@(posedge Bus2IP_Clk)
					Bus2IP_WrCE 	= error;
					
					#50;
					
					@(posedge Bus2IP_Clk)
					Bus2IP_WrCE 	= new_disparo;
					//Plazas: 00000000=00H - Transiciones: 00000001=01H - Elemento: 0000000000000000=0000H
					Bus2IP_Data	= 32'h00010000;	
					@(posedge Bus2IP_Clk)
					Bus2IP_WrCE 	= error;
			
					#1000;
					$stop;
			
	end
      
endmodule

