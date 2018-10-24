
/*******************************************************************
*
* CAUTION: This file is automatically generated by libgen.
* Version: Xilinx EDK 14.2 EDK_P.28xd
* DO NOT EDIT.
*
* Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.

* 
* Description: Driver parameters
*
*******************************************************************/

#define STDIN_BASEADDRESS 0x40600000
#define STDOUT_BASEADDRESS 0x40600000
/* Definitions for driver TMRCTR */
#define XPAR_XTMRCTR_NUM_INSTANCES 2

/* Definitions for peripheral AXI_TIMER_0 */
#define XPAR_AXI_TIMER_0_DEVICE_ID 0
#define XPAR_AXI_TIMER_0_BASEADDR 0x41C00000
#define XPAR_AXI_TIMER_0_HIGHADDR 0x41C0FFFF
#define XPAR_AXI_TIMER_0_CLOCK_FREQ_HZ 75000000


/* Definitions for peripheral AXI_TIMER_1 */
#define XPAR_AXI_TIMER_1_DEVICE_ID 1
#define XPAR_AXI_TIMER_1_BASEADDR 0x41C40000
#define XPAR_AXI_TIMER_1_HIGHADDR 0x41C4FFFF
#define XPAR_AXI_TIMER_1_CLOCK_FREQ_HZ 75000000


/******************************************************************/

/* Canonical definitions for peripheral AXI_TIMER_0 */
#define XPAR_TMRCTR_0_DEVICE_ID XPAR_AXI_TIMER_0_DEVICE_ID
#define XPAR_TMRCTR_0_BASEADDR 0x41C00000
#define XPAR_TMRCTR_0_HIGHADDR 0x41C0FFFF
#define XPAR_TMRCTR_0_CLOCK_FREQ_HZ XPAR_AXI_TIMER_0_CLOCK_FREQ_HZ
/* Canonical definitions for peripheral AXI_TIMER_1 */
#define XPAR_TMRCTR_1_DEVICE_ID XPAR_AXI_TIMER_1_DEVICE_ID
#define XPAR_TMRCTR_1_BASEADDR 0x41C40000
#define XPAR_TMRCTR_1_HIGHADDR 0x41C4FFFF
#define XPAR_TMRCTR_1_CLOCK_FREQ_HZ XPAR_AXI_TIMER_1_CLOCK_FREQ_HZ

/******************************************************************/

/* Definitions for driver UARTLITE */
#define XPAR_XUARTLITE_NUM_INSTANCES 2

/* Definitions for peripheral DEBUG_MODULE */
#define XPAR_DEBUG_MODULE_BASEADDR 0x41400000
#define XPAR_DEBUG_MODULE_HIGHADDR 0x4140FFFF
#define XPAR_DEBUG_MODULE_DEVICE_ID 0
#define XPAR_DEBUG_MODULE_BAUDRATE 0
#define XPAR_DEBUG_MODULE_USE_PARITY 0
#define XPAR_DEBUG_MODULE_ODD_PARITY 0
#define XPAR_DEBUG_MODULE_DATA_BITS 0


/* Definitions for peripheral RS232_UART_1 */
#define XPAR_RS232_UART_1_BASEADDR 0x40600000
#define XPAR_RS232_UART_1_HIGHADDR 0x4060FFFF
#define XPAR_RS232_UART_1_DEVICE_ID 1
#define XPAR_RS232_UART_1_BAUDRATE 9600
#define XPAR_RS232_UART_1_USE_PARITY 0
#define XPAR_RS232_UART_1_ODD_PARITY 1
#define XPAR_RS232_UART_1_DATA_BITS 8


/******************************************************************/

/* Canonical definitions for peripheral DEBUG_MODULE */
#define XPAR_UARTLITE_0_DEVICE_ID XPAR_DEBUG_MODULE_DEVICE_ID
#define XPAR_UARTLITE_0_BASEADDR 0x41400000
#define XPAR_UARTLITE_0_HIGHADDR 0x4140FFFF
#define XPAR_UARTLITE_0_BAUDRATE 0
#define XPAR_UARTLITE_0_USE_PARITY 0
#define XPAR_UARTLITE_0_ODD_PARITY 0
#define XPAR_UARTLITE_0_DATA_BITS 0
#define XPAR_UARTLITE_0_SIO_CHAN -1

/* Canonical definitions for peripheral RS232_UART_1 */
#define XPAR_UARTLITE_1_DEVICE_ID XPAR_RS232_UART_1_DEVICE_ID
#define XPAR_UARTLITE_1_BASEADDR 0x40600000
#define XPAR_UARTLITE_1_HIGHADDR 0x4060FFFF
#define XPAR_UARTLITE_1_BAUDRATE 9600
#define XPAR_UARTLITE_1_USE_PARITY 0
#define XPAR_UARTLITE_1_ODD_PARITY 1
#define XPAR_UARTLITE_1_DATA_BITS 8
#define XPAR_UARTLITE_1_SIO_CHAN 0


/******************************************************************/

/* Definitions for driver GPIO */
#define XPAR_XGPIO_NUM_INSTANCES 3

/* Definitions for peripheral DIP_SWITCHES_8BITS */
#define XPAR_DIP_SWITCHES_8BITS_BASEADDR 0x40040000
#define XPAR_DIP_SWITCHES_8BITS_HIGHADDR 0x4004FFFF
#define XPAR_DIP_SWITCHES_8BITS_DEVICE_ID 0
#define XPAR_DIP_SWITCHES_8BITS_INTERRUPT_PRESENT 0
#define XPAR_DIP_SWITCHES_8BITS_IS_DUAL 0


/* Definitions for peripheral LEDS_8BITS */
#define XPAR_LEDS_8BITS_BASEADDR 0x40020000
#define XPAR_LEDS_8BITS_HIGHADDR 0x4002FFFF
#define XPAR_LEDS_8BITS_DEVICE_ID 1
#define XPAR_LEDS_8BITS_INTERRUPT_PRESENT 0
#define XPAR_LEDS_8BITS_IS_DUAL 0


/* Definitions for peripheral PUSH_BUTTONS_5BITS */
#define XPAR_PUSH_BUTTONS_5BITS_BASEADDR 0x40000000
#define XPAR_PUSH_BUTTONS_5BITS_HIGHADDR 0x4000FFFF
#define XPAR_PUSH_BUTTONS_5BITS_DEVICE_ID 2
#define XPAR_PUSH_BUTTONS_5BITS_INTERRUPT_PRESENT 0
#define XPAR_PUSH_BUTTONS_5BITS_IS_DUAL 0


/******************************************************************/

/* Definitions for driver S6_DDRX */
#define XPAR_XS6DDR_NUM_INSTANCES 1

/* Definitions for peripheral MCB_DDR2 */
#define XPAR_MCB_DDR2_DEVICE_ID 0
#define XPAR_MCB_DDR2_S0_AXI_ENABLE 1
#define XPAR_MCB_DDR2_S1_AXI_ENABLE 0
#define XPAR_MCB_DDR2_S2_AXI_ENABLE 0
#define XPAR_MCB_DDR2_S3_AXI_ENABLE 0
#define XPAR_MCB_DDR2_S4_AXI_ENABLE 0
#define XPAR_MCB_DDR2_S5_AXI_ENABLE 0
#define XPAR_MCB_DDR2_MEM_BANKADDR_WIDTH 3
#define XPAR_MCB_DDR2_MEM_ADDR_WIDTH 13
#define XPAR_MCB_DDR2_MEM_NUM_COL_BITS 10
#define XPAR_MCB_DDR2_NUM_DQ_PINS 16


/******************************************************************/


/* Definitions for peripheral MCB_DDR2 */
#define XPAR_MCB_DDR2_S0_AXI_BASEADDR 0xA8000000
#define XPAR_MCB_DDR2_S0_AXI_HIGHADDR 0xAFFFFFFF


/******************************************************************/

/* Canonical definitions for peripheral MCB_DDR2 */
#define XPAR_S6DDR_0_DEVICE_ID XPAR_MCB_DDR2_DEVICE_ID
#define XPAR_S6DDR_0_S0_AXI_ENABLE 1
#define XPAR_S6DDR_0_S1_AXI_ENABLE 0
#define XPAR_S6DDR_0_S2_AXI_ENABLE 0
#define XPAR_S6DDR_0_S3_AXI_ENABLE 0
#define XPAR_S6DDR_0_S4_AXI_ENABLE 0
#define XPAR_S6DDR_0_S5_AXI_ENABLE 0
#define XPAR_S6DDR_0_MEM_BANKADDR_WIDTH 3
#define XPAR_S6DDR_0_MEM_ADDR_WIDTH 13
#define XPAR_S6DDR_0_MEM_NUM_COL_BITS 10
#define XPAR_S6DDR_0_NUM_DQ_PINS 16
#define XPAR_S6DDR_0_S0_AXI_BASEADDR 0xA8000000
#define XPAR_S6DDR_0_S0_AXI_HIGHADDR 0xAFFFFFFF


/******************************************************************/

/* Definitions for driver BRAM */
#define XPAR_XBRAM_NUM_INSTANCES 2

/* Definitions for peripheral MICROBLAZE_0_D_BRAM_CTRL */
#define XPAR_MICROBLAZE_0_D_BRAM_CTRL_DEVICE_ID 0
#define XPAR_MICROBLAZE_0_D_BRAM_CTRL_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_D_BRAM_CTRL_ECC 0
#define XPAR_MICROBLAZE_0_D_BRAM_CTRL_FAULT_INJECT 0
#define XPAR_MICROBLAZE_0_D_BRAM_CTRL_CE_FAILING_REGISTERS 0
#define XPAR_MICROBLAZE_0_D_BRAM_CTRL_UE_FAILING_REGISTERS 0
#define XPAR_MICROBLAZE_0_D_BRAM_CTRL_ECC_STATUS_REGISTERS 0
#define XPAR_MICROBLAZE_0_D_BRAM_CTRL_CE_COUNTER_WIDTH 0
#define XPAR_MICROBLAZE_0_D_BRAM_CTRL_ECC_ONOFF_REGISTER 0
#define XPAR_MICROBLAZE_0_D_BRAM_CTRL_ECC_ONOFF_RESET_VALUE 1
#define XPAR_MICROBLAZE_0_D_BRAM_CTRL_WRITE_ACCESS 2
#define XPAR_MICROBLAZE_0_D_BRAM_CTRL_BASEADDR 0x00000000
#define XPAR_MICROBLAZE_0_D_BRAM_CTRL_HIGHADDR 0x00001FFF


/* Definitions for peripheral MICROBLAZE_0_I_BRAM_CTRL */
#define XPAR_MICROBLAZE_0_I_BRAM_CTRL_DEVICE_ID 1
#define XPAR_MICROBLAZE_0_I_BRAM_CTRL_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_I_BRAM_CTRL_ECC 0
#define XPAR_MICROBLAZE_0_I_BRAM_CTRL_FAULT_INJECT 0
#define XPAR_MICROBLAZE_0_I_BRAM_CTRL_CE_FAILING_REGISTERS 0
#define XPAR_MICROBLAZE_0_I_BRAM_CTRL_UE_FAILING_REGISTERS 0
#define XPAR_MICROBLAZE_0_I_BRAM_CTRL_ECC_STATUS_REGISTERS 0
#define XPAR_MICROBLAZE_0_I_BRAM_CTRL_CE_COUNTER_WIDTH 0
#define XPAR_MICROBLAZE_0_I_BRAM_CTRL_ECC_ONOFF_REGISTER 0
#define XPAR_MICROBLAZE_0_I_BRAM_CTRL_ECC_ONOFF_RESET_VALUE 1
#define XPAR_MICROBLAZE_0_I_BRAM_CTRL_WRITE_ACCESS 2
#define XPAR_MICROBLAZE_0_I_BRAM_CTRL_BASEADDR 0x00000000
#define XPAR_MICROBLAZE_0_I_BRAM_CTRL_HIGHADDR 0x00001FFF


/******************************************************************/

/* Canonical definitions for peripheral MICROBLAZE_0_D_BRAM_CTRL */
#define XPAR_BRAM_0_DEVICE_ID XPAR_MICROBLAZE_0_D_BRAM_CTRL_DEVICE_ID
#define XPAR_BRAM_0_DATA_WIDTH 32
#define XPAR_BRAM_0_ECC 0
#define XPAR_BRAM_0_FAULT_INJECT 0
#define XPAR_BRAM_0_CE_FAILING_REGISTERS 0
#define XPAR_BRAM_0_UE_FAILING_REGISTERS 0
#define XPAR_BRAM_0_ECC_STATUS_REGISTERS 0
#define XPAR_BRAM_0_CE_COUNTER_WIDTH 0
#define XPAR_BRAM_0_ECC_ONOFF_REGISTER 0
#define XPAR_BRAM_0_ECC_ONOFF_RESET_VALUE 1
#define XPAR_BRAM_0_WRITE_ACCESS 2
#define XPAR_BRAM_0_BASEADDR 0x00000000
#define XPAR_BRAM_0_HIGHADDR 0x00001FFF

/* Canonical definitions for peripheral MICROBLAZE_0_I_BRAM_CTRL */
#define XPAR_BRAM_1_DEVICE_ID XPAR_MICROBLAZE_0_I_BRAM_CTRL_DEVICE_ID
#define XPAR_BRAM_1_DATA_WIDTH 32
#define XPAR_BRAM_1_ECC 0
#define XPAR_BRAM_1_FAULT_INJECT 0
#define XPAR_BRAM_1_CE_FAILING_REGISTERS 0
#define XPAR_BRAM_1_UE_FAILING_REGISTERS 0
#define XPAR_BRAM_1_ECC_STATUS_REGISTERS 0
#define XPAR_BRAM_1_CE_COUNTER_WIDTH 0
#define XPAR_BRAM_1_ECC_ONOFF_REGISTER 0
#define XPAR_BRAM_1_ECC_ONOFF_RESET_VALUE 1
#define XPAR_BRAM_1_WRITE_ACCESS 2
#define XPAR_BRAM_1_BASEADDR 0x00000000
#define XPAR_BRAM_1_HIGHADDR 0x00001FFF


/******************************************************************/

#define XPAR_INTC_MAX_NUM_INTR_INPUTS 3
#define XPAR_XINTC_HAS_IPR 1
#define XPAR_XINTC_HAS_SIE 1
#define XPAR_XINTC_HAS_CIE 1
#define XPAR_XINTC_HAS_IVR 1
#define XPAR_XINTC_USE_DCR 0
/* Definitions for driver INTC */
#define XPAR_XINTC_NUM_INSTANCES 1

/* Definitions for peripheral MICROBLAZE_0_INTC */
#define XPAR_MICROBLAZE_0_INTC_DEVICE_ID 0
#define XPAR_MICROBLAZE_0_INTC_BASEADDR 0x41200000
#define XPAR_MICROBLAZE_0_INTC_HIGHADDR 0x4120FFFF
#define XPAR_MICROBLAZE_0_INTC_KIND_OF_INTR 0xFFFFFFF9
#define XPAR_MICROBLAZE_0_INTC_HAS_FAST 0


/******************************************************************/

#define XPAR_INTC_SINGLE_BASEADDR 0x41200000
#define XPAR_INTC_SINGLE_HIGHADDR 0x4120FFFF
#define XPAR_INTC_SINGLE_DEVICE_ID XPAR_MICROBLAZE_0_INTC_DEVICE_ID
#define XPAR_PETRI_AXI_INT_0_INTERRUPT_MASK 0X000001
#define XPAR_MICROBLAZE_0_INTC_PETRI_AXI_INT_0_INTERRUPT_INTR 0
#define XPAR_AXI_TIMER_1_INTERRUPT_MASK 0X000002
#define XPAR_MICROBLAZE_0_INTC_AXI_TIMER_1_INTERRUPT_INTR 1
#define XPAR_AXI_TIMER_0_INTERRUPT_MASK 0X000004
#define XPAR_MICROBLAZE_0_INTC_AXI_TIMER_0_INTERRUPT_INTR 2

/******************************************************************/

/* Canonical definitions for peripheral MICROBLAZE_0_INTC */
#define XPAR_INTC_0_DEVICE_ID XPAR_MICROBLAZE_0_INTC_DEVICE_ID
#define XPAR_INTC_0_BASEADDR 0x41200000
#define XPAR_INTC_0_HIGHADDR 0x4120FFFF
#define XPAR_INTC_0_KIND_OF_INTR 0xFFFFFFF9
#define XPAR_INTC_0_HAS_FAST 0

#define XPAR_INTC_0_TMRCTR_1_VEC_ID XPAR_MICROBLAZE_0_INTC_AXI_TIMER_1_INTERRUPT_INTR
#define XPAR_INTC_0_TMRCTR_0_VEC_ID XPAR_MICROBLAZE_0_INTC_AXI_TIMER_0_INTERRUPT_INTR

/******************************************************************/


/* Definitions for peripheral PETRI_AXI_INT_0 */
#define XPAR_PETRI_AXI_INT_0_BASEADDR 0x7EE00000
#define XPAR_PETRI_AXI_INT_0_HIGHADDR 0x7EE0FFFF


/******************************************************************/

/* Definitions for bus frequencies */
#define XPAR_CPU_M_AXI_DP_FREQ_HZ 75000000
/******************************************************************/

/* Canonical definitions for bus frequencies */
#define XPAR_PROC_BUS_0_FREQ_HZ 75000000
/******************************************************************/

#define XPAR_CPU_CORE_CLOCK_FREQ_HZ 75000000
#define XPAR_MICROBLAZE_CORE_CLOCK_FREQ_HZ 75000000

/******************************************************************/


/* Definitions for peripheral MICROBLAZE_0 */
#define XPAR_MICROBLAZE_0_SCO 0
#define XPAR_MICROBLAZE_0_FREQ 75000000
#define XPAR_MICROBLAZE_0_DATA_SIZE 32
#define XPAR_MICROBLAZE_0_DYNAMIC_BUS_SIZING 1
#define XPAR_MICROBLAZE_0_AVOID_PRIMITIVES 0
#define XPAR_MICROBLAZE_0_FAULT_TOLERANT 0
#define XPAR_MICROBLAZE_0_ECC_USE_CE_EXCEPTION 0
#define XPAR_MICROBLAZE_0_LOCKSTEP_SLAVE 0
#define XPAR_MICROBLAZE_0_ENDIANNESS 1
#define XPAR_MICROBLAZE_0_AREA_OPTIMIZED 0
#define XPAR_MICROBLAZE_0_OPTIMIZATION 0
#define XPAR_MICROBLAZE_0_INTERCONNECT 2
#define XPAR_MICROBLAZE_0_STREAM_INTERCONNECT 0
#define XPAR_MICROBLAZE_0_DPLB_DWIDTH 32
#define XPAR_MICROBLAZE_0_DPLB_NATIVE_DWIDTH 32
#define XPAR_MICROBLAZE_0_DPLB_BURST_EN 0
#define XPAR_MICROBLAZE_0_DPLB_P2P 0
#define XPAR_MICROBLAZE_0_IPLB_DWIDTH 32
#define XPAR_MICROBLAZE_0_IPLB_NATIVE_DWIDTH 32
#define XPAR_MICROBLAZE_0_IPLB_BURST_EN 0
#define XPAR_MICROBLAZE_0_IPLB_P2P 0
#define XPAR_MICROBLAZE_0_M_AXI_DP_SUPPORTS_THREADS 0
#define XPAR_MICROBLAZE_0_M_AXI_DP_THREAD_ID_WIDTH 1
#define XPAR_MICROBLAZE_0_M_AXI_DP_SUPPORTS_READ 1
#define XPAR_MICROBLAZE_0_M_AXI_DP_SUPPORTS_WRITE 1
#define XPAR_MICROBLAZE_0_M_AXI_DP_SUPPORTS_NARROW_BURST 0
#define XPAR_MICROBLAZE_0_M_AXI_DP_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M_AXI_DP_ADDR_WIDTH 32
#define XPAR_MICROBLAZE_0_M_AXI_DP_PROTOCOL AXI4LITE
#define XPAR_MICROBLAZE_0_M_AXI_DP_EXCLUSIVE_ACCESS 0
#define XPAR_MICROBLAZE_0_INTERCONNECT_M_AXI_DP_READ_ISSUING 1
#define XPAR_MICROBLAZE_0_INTERCONNECT_M_AXI_DP_WRITE_ISSUING 1
#define XPAR_MICROBLAZE_0_M_AXI_IP_SUPPORTS_THREADS 0
#define XPAR_MICROBLAZE_0_M_AXI_IP_THREAD_ID_WIDTH 1
#define XPAR_MICROBLAZE_0_M_AXI_IP_SUPPORTS_READ 1
#define XPAR_MICROBLAZE_0_M_AXI_IP_SUPPORTS_WRITE 0
#define XPAR_MICROBLAZE_0_M_AXI_IP_SUPPORTS_NARROW_BURST 0
#define XPAR_MICROBLAZE_0_M_AXI_IP_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M_AXI_IP_ADDR_WIDTH 32
#define XPAR_MICROBLAZE_0_M_AXI_IP_PROTOCOL AXI4LITE
#define XPAR_MICROBLAZE_0_INTERCONNECT_M_AXI_IP_READ_ISSUING 1
#define XPAR_MICROBLAZE_0_D_AXI 1
#define XPAR_MICROBLAZE_0_D_PLB 0
#define XPAR_MICROBLAZE_0_D_LMB 1
#define XPAR_MICROBLAZE_0_I_AXI 0
#define XPAR_MICROBLAZE_0_I_PLB 0
#define XPAR_MICROBLAZE_0_I_LMB 1
#define XPAR_MICROBLAZE_0_USE_MSR_INSTR 1
#define XPAR_MICROBLAZE_0_USE_PCMP_INSTR 1
#define XPAR_MICROBLAZE_0_USE_BARREL 1
#define XPAR_MICROBLAZE_0_USE_DIV 0
#define XPAR_MICROBLAZE_0_USE_HW_MUL 1
#define XPAR_MICROBLAZE_0_USE_FPU 0
#define XPAR_MICROBLAZE_0_USE_REORDER_INSTR 1
#define XPAR_MICROBLAZE_0_UNALIGNED_EXCEPTIONS 0
#define XPAR_MICROBLAZE_0_ILL_OPCODE_EXCEPTION 0
#define XPAR_MICROBLAZE_0_M_AXI_I_BUS_EXCEPTION 0
#define XPAR_MICROBLAZE_0_M_AXI_D_BUS_EXCEPTION 0
#define XPAR_MICROBLAZE_0_IPLB_BUS_EXCEPTION 0
#define XPAR_MICROBLAZE_0_DPLB_BUS_EXCEPTION 0
#define XPAR_MICROBLAZE_0_DIV_ZERO_EXCEPTION 0
#define XPAR_MICROBLAZE_0_FPU_EXCEPTION 0
#define XPAR_MICROBLAZE_0_FSL_EXCEPTION 0
#define XPAR_MICROBLAZE_0_USE_STACK_PROTECTION 0
#define XPAR_MICROBLAZE_0_PVR 0
#define XPAR_MICROBLAZE_0_PVR_USER1 0x00
#define XPAR_MICROBLAZE_0_PVR_USER2 0x00000000
#define XPAR_MICROBLAZE_0_DEBUG_ENABLED 1
#define XPAR_MICROBLAZE_0_NUMBER_OF_PC_BRK 1
#define XPAR_MICROBLAZE_0_NUMBER_OF_RD_ADDR_BRK 0
#define XPAR_MICROBLAZE_0_NUMBER_OF_WR_ADDR_BRK 0
#define XPAR_MICROBLAZE_0_INTERRUPT_IS_EDGE 1
#define XPAR_MICROBLAZE_0_EDGE_IS_POSITIVE 1
#define XPAR_MICROBLAZE_0_RESET_MSR 0x00000000
#define XPAR_MICROBLAZE_0_OPCODE_0X0_ILLEGAL 0
#define XPAR_MICROBLAZE_0_FSL_LINKS 0
#define XPAR_MICROBLAZE_0_FSL_DATA_SIZE 32
#define XPAR_MICROBLAZE_0_USE_EXTENDED_FSL_INSTR 0
#define XPAR_MICROBLAZE_0_M0_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S0_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M1_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S1_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M2_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S2_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M3_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S3_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M4_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S4_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M5_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S5_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M6_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S6_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M7_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S7_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M8_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S8_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M9_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S9_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M10_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S10_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M11_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S11_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M12_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S12_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M13_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S13_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M14_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S14_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M15_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_S15_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_0_M0_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S0_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M1_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S1_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M2_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S2_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M3_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S3_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M4_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S4_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M5_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S5_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M6_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S6_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M7_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S7_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M8_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S8_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M9_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S9_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M10_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S10_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M11_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S11_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M12_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S12_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M13_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S13_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M14_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S14_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M15_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_S15_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_ICACHE_BASEADDR 0xA8000000
#define XPAR_MICROBLAZE_0_ICACHE_HIGHADDR 0xAFFFFFFF
#define XPAR_MICROBLAZE_0_USE_ICACHE 1
#define XPAR_MICROBLAZE_0_ALLOW_ICACHE_WR 1
#define XPAR_MICROBLAZE_0_ADDR_TAG_BITS 14
#define XPAR_MICROBLAZE_0_CACHE_BYTE_SIZE 8192
#define XPAR_MICROBLAZE_0_ICACHE_USE_FSL 0
#define XPAR_MICROBLAZE_0_ICACHE_LINE_LEN 4
#define XPAR_MICROBLAZE_0_ICACHE_ALWAYS_USED 1
#define XPAR_MICROBLAZE_0_ICACHE_INTERFACE 0
#define XPAR_MICROBLAZE_0_ICACHE_VICTIMS 0
#define XPAR_MICROBLAZE_0_ICACHE_STREAMS 0
#define XPAR_MICROBLAZE_0_ICACHE_FORCE_TAG_LUTRAM 0
#define XPAR_MICROBLAZE_0_ICACHE_DATA_WIDTH 0
#define XPAR_MICROBLAZE_0_M_AXI_IC_SUPPORTS_THREADS 0
#define XPAR_MICROBLAZE_0_M_AXI_IC_THREAD_ID_WIDTH 1
#define XPAR_MICROBLAZE_0_M_AXI_IC_SUPPORTS_READ 1
#define XPAR_MICROBLAZE_0_M_AXI_IC_SUPPORTS_WRITE 0
#define XPAR_MICROBLAZE_0_M_AXI_IC_SUPPORTS_NARROW_BURST 0
#define XPAR_MICROBLAZE_0_M_AXI_IC_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M_AXI_IC_ADDR_WIDTH 32
#define XPAR_MICROBLAZE_0_M_AXI_IC_PROTOCOL AXI4
#define XPAR_MICROBLAZE_0_M_AXI_IC_USER_VALUE 0b11111
#define XPAR_MICROBLAZE_0_M_AXI_IC_SUPPORTS_USER_SIGNALS 1
#define XPAR_MICROBLAZE_0_M_AXI_IC_AWUSER_WIDTH 5
#define XPAR_MICROBLAZE_0_M_AXI_IC_ARUSER_WIDTH 5
#define XPAR_MICROBLAZE_0_M_AXI_IC_WUSER_WIDTH 1
#define XPAR_MICROBLAZE_0_M_AXI_IC_RUSER_WIDTH 1
#define XPAR_MICROBLAZE_0_M_AXI_IC_BUSER_WIDTH 1
#define XPAR_MICROBLAZE_0_INTERCONNECT_M_AXI_IC_READ_ISSUING 2
#define XPAR_MICROBLAZE_0_DCACHE_BASEADDR 0xA8000000
#define XPAR_MICROBLAZE_0_DCACHE_HIGHADDR 0xAFFFFFFF
#define XPAR_MICROBLAZE_0_USE_DCACHE 1
#define XPAR_MICROBLAZE_0_ALLOW_DCACHE_WR 1
#define XPAR_MICROBLAZE_0_DCACHE_ADDR_TAG 14
#define XPAR_MICROBLAZE_0_DCACHE_BYTE_SIZE 8192
#define XPAR_MICROBLAZE_0_DCACHE_USE_FSL 0
#define XPAR_MICROBLAZE_0_DCACHE_LINE_LEN 4
#define XPAR_MICROBLAZE_0_DCACHE_ALWAYS_USED 1
#define XPAR_MICROBLAZE_0_DCACHE_INTERFACE 0
#define XPAR_MICROBLAZE_0_DCACHE_USE_WRITEBACK 0
#define XPAR_MICROBLAZE_0_DCACHE_VICTIMS 0
#define XPAR_MICROBLAZE_0_DCACHE_FORCE_TAG_LUTRAM 0
#define XPAR_MICROBLAZE_0_DCACHE_DATA_WIDTH 0
#define XPAR_MICROBLAZE_0_M_AXI_DC_SUPPORTS_THREADS 0
#define XPAR_MICROBLAZE_0_M_AXI_DC_THREAD_ID_WIDTH 1
#define XPAR_MICROBLAZE_0_M_AXI_DC_SUPPORTS_READ 1
#define XPAR_MICROBLAZE_0_M_AXI_DC_SUPPORTS_WRITE 1
#define XPAR_MICROBLAZE_0_M_AXI_DC_SUPPORTS_NARROW_BURST 0
#define XPAR_MICROBLAZE_0_M_AXI_DC_DATA_WIDTH 32
#define XPAR_MICROBLAZE_0_M_AXI_DC_ADDR_WIDTH 32
#define XPAR_MICROBLAZE_0_M_AXI_DC_PROTOCOL AXI4
#define XPAR_MICROBLAZE_0_M_AXI_DC_EXCLUSIVE_ACCESS 0
#define XPAR_MICROBLAZE_0_M_AXI_DC_USER_VALUE 0b11111
#define XPAR_MICROBLAZE_0_M_AXI_DC_SUPPORTS_USER_SIGNALS 1
#define XPAR_MICROBLAZE_0_M_AXI_DC_AWUSER_WIDTH 5
#define XPAR_MICROBLAZE_0_M_AXI_DC_ARUSER_WIDTH 5
#define XPAR_MICROBLAZE_0_M_AXI_DC_WUSER_WIDTH 1
#define XPAR_MICROBLAZE_0_M_AXI_DC_RUSER_WIDTH 1
#define XPAR_MICROBLAZE_0_M_AXI_DC_BUSER_WIDTH 1
#define XPAR_MICROBLAZE_0_INTERCONNECT_M_AXI_DC_READ_ISSUING 2
#define XPAR_MICROBLAZE_0_INTERCONNECT_M_AXI_DC_WRITE_ISSUING 32
#define XPAR_MICROBLAZE_0_USE_MMU 0
#define XPAR_MICROBLAZE_0_MMU_DTLB_SIZE 4
#define XPAR_MICROBLAZE_0_MMU_ITLB_SIZE 2
#define XPAR_MICROBLAZE_0_MMU_TLB_ACCESS 3
#define XPAR_MICROBLAZE_0_MMU_ZONES 16
#define XPAR_MICROBLAZE_0_MMU_PRIVILEGED_INSTR 0
#define XPAR_MICROBLAZE_0_USE_INTERRUPT 1
#define XPAR_MICROBLAZE_0_USE_EXT_BRK 1
#define XPAR_MICROBLAZE_0_USE_EXT_NM_BRK 1
#define XPAR_MICROBLAZE_0_USE_BRANCH_TARGET_CACHE 0
#define XPAR_MICROBLAZE_0_BRANCH_TARGET_CACHE_SIZE 0
#define XPAR_MICROBLAZE_0_PC_WIDTH 32

/******************************************************************/

#define XPAR_CPU_ID 0
#define XPAR_MICROBLAZE_ID 0
#define XPAR_MICROBLAZE_SCO 0
#define XPAR_MICROBLAZE_FREQ 75000000
#define XPAR_MICROBLAZE_DATA_SIZE 32
#define XPAR_MICROBLAZE_DYNAMIC_BUS_SIZING 1
#define XPAR_MICROBLAZE_AVOID_PRIMITIVES 0
#define XPAR_MICROBLAZE_FAULT_TOLERANT 0
#define XPAR_MICROBLAZE_ECC_USE_CE_EXCEPTION 0
#define XPAR_MICROBLAZE_LOCKSTEP_SLAVE 0
#define XPAR_MICROBLAZE_ENDIANNESS 1
#define XPAR_MICROBLAZE_AREA_OPTIMIZED 0
#define XPAR_MICROBLAZE_OPTIMIZATION 0
#define XPAR_MICROBLAZE_INTERCONNECT 2
#define XPAR_MICROBLAZE_STREAM_INTERCONNECT 0
#define XPAR_MICROBLAZE_DPLB_DWIDTH 32
#define XPAR_MICROBLAZE_DPLB_NATIVE_DWIDTH 32
#define XPAR_MICROBLAZE_DPLB_BURST_EN 0
#define XPAR_MICROBLAZE_DPLB_P2P 0
#define XPAR_MICROBLAZE_IPLB_DWIDTH 32
#define XPAR_MICROBLAZE_IPLB_NATIVE_DWIDTH 32
#define XPAR_MICROBLAZE_IPLB_BURST_EN 0
#define XPAR_MICROBLAZE_IPLB_P2P 0
#define XPAR_MICROBLAZE_M_AXI_DP_SUPPORTS_THREADS 0
#define XPAR_MICROBLAZE_M_AXI_DP_THREAD_ID_WIDTH 1
#define XPAR_MICROBLAZE_M_AXI_DP_SUPPORTS_READ 1
#define XPAR_MICROBLAZE_M_AXI_DP_SUPPORTS_WRITE 1
#define XPAR_MICROBLAZE_M_AXI_DP_SUPPORTS_NARROW_BURST 0
#define XPAR_MICROBLAZE_M_AXI_DP_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M_AXI_DP_ADDR_WIDTH 32
#define XPAR_MICROBLAZE_M_AXI_DP_PROTOCOL AXI4LITE
#define XPAR_MICROBLAZE_M_AXI_DP_EXCLUSIVE_ACCESS 0
#define XPAR_MICROBLAZE_INTERCONNECT_M_AXI_DP_READ_ISSUING 1
#define XPAR_MICROBLAZE_INTERCONNECT_M_AXI_DP_WRITE_ISSUING 1
#define XPAR_MICROBLAZE_M_AXI_IP_SUPPORTS_THREADS 0
#define XPAR_MICROBLAZE_M_AXI_IP_THREAD_ID_WIDTH 1
#define XPAR_MICROBLAZE_M_AXI_IP_SUPPORTS_READ 1
#define XPAR_MICROBLAZE_M_AXI_IP_SUPPORTS_WRITE 0
#define XPAR_MICROBLAZE_M_AXI_IP_SUPPORTS_NARROW_BURST 0
#define XPAR_MICROBLAZE_M_AXI_IP_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M_AXI_IP_ADDR_WIDTH 32
#define XPAR_MICROBLAZE_M_AXI_IP_PROTOCOL AXI4LITE
#define XPAR_MICROBLAZE_INTERCONNECT_M_AXI_IP_READ_ISSUING 1
#define XPAR_MICROBLAZE_D_AXI 1
#define XPAR_MICROBLAZE_D_PLB 0
#define XPAR_MICROBLAZE_D_LMB 1
#define XPAR_MICROBLAZE_I_AXI 0
#define XPAR_MICROBLAZE_I_PLB 0
#define XPAR_MICROBLAZE_I_LMB 1
#define XPAR_MICROBLAZE_USE_MSR_INSTR 1
#define XPAR_MICROBLAZE_USE_PCMP_INSTR 1
#define XPAR_MICROBLAZE_USE_BARREL 1
#define XPAR_MICROBLAZE_USE_DIV 0
#define XPAR_MICROBLAZE_USE_HW_MUL 1
#define XPAR_MICROBLAZE_USE_FPU 0
#define XPAR_MICROBLAZE_USE_REORDER_INSTR 1
#define XPAR_MICROBLAZE_UNALIGNED_EXCEPTIONS 0
#define XPAR_MICROBLAZE_ILL_OPCODE_EXCEPTION 0
#define XPAR_MICROBLAZE_M_AXI_I_BUS_EXCEPTION 0
#define XPAR_MICROBLAZE_M_AXI_D_BUS_EXCEPTION 0
#define XPAR_MICROBLAZE_IPLB_BUS_EXCEPTION 0
#define XPAR_MICROBLAZE_DPLB_BUS_EXCEPTION 0
#define XPAR_MICROBLAZE_DIV_ZERO_EXCEPTION 0
#define XPAR_MICROBLAZE_FPU_EXCEPTION 0
#define XPAR_MICROBLAZE_FSL_EXCEPTION 0
#define XPAR_MICROBLAZE_USE_STACK_PROTECTION 0
#define XPAR_MICROBLAZE_PVR 0
#define XPAR_MICROBLAZE_PVR_USER1 0x00
#define XPAR_MICROBLAZE_PVR_USER2 0x00000000
#define XPAR_MICROBLAZE_DEBUG_ENABLED 1
#define XPAR_MICROBLAZE_NUMBER_OF_PC_BRK 1
#define XPAR_MICROBLAZE_NUMBER_OF_RD_ADDR_BRK 0
#define XPAR_MICROBLAZE_NUMBER_OF_WR_ADDR_BRK 0
#define XPAR_MICROBLAZE_INTERRUPT_IS_EDGE 1
#define XPAR_MICROBLAZE_EDGE_IS_POSITIVE 1
#define XPAR_MICROBLAZE_RESET_MSR 0x00000000
#define XPAR_MICROBLAZE_OPCODE_0X0_ILLEGAL 0
#define XPAR_MICROBLAZE_FSL_LINKS 0
#define XPAR_MICROBLAZE_FSL_DATA_SIZE 32
#define XPAR_MICROBLAZE_USE_EXTENDED_FSL_INSTR 0
#define XPAR_MICROBLAZE_M0_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S0_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M1_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S1_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M2_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S2_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M3_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S3_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M4_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S4_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M5_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S5_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M6_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S6_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M7_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S7_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M8_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S8_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M9_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S9_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M10_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S10_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M11_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S11_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M12_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S12_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M13_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S13_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M14_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S14_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M15_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_S15_AXIS_PROTOCOL GENERIC
#define XPAR_MICROBLAZE_M0_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S0_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M1_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S1_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M2_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S2_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M3_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S3_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M4_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S4_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M5_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S5_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M6_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S6_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M7_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S7_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M8_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S8_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M9_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S9_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M10_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S10_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M11_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S11_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M12_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S12_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M13_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S13_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M14_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S14_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M15_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_S15_AXIS_DATA_WIDTH 32
#define XPAR_MICROBLAZE_ICACHE_BASEADDR 0xA8000000
#define XPAR_MICROBLAZE_ICACHE_HIGHADDR 0xAFFFFFFF
#define XPAR_MICROBLAZE_USE_ICACHE 1
#define XPAR_MICROBLAZE_ALLOW_ICACHE_WR 1
#define XPAR_MICROBLAZE_ADDR_TAG_BITS 14
#define XPAR_MICROBLAZE_CACHE_BYTE_SIZE 8192
#define XPAR_MICROBLAZE_ICACHE_USE_FSL 0
#define XPAR_MICROBLAZE_ICACHE_LINE_LEN 4
#define XPAR_MICROBLAZE_ICACHE_ALWAYS_USED 1
#define XPAR_MICROBLAZE_ICACHE_INTERFACE 0
#define XPAR_MICROBLAZE_ICACHE_VICTIMS 0
#define XPAR_MICROBLAZE_ICACHE_STREAMS 0
#define XPAR_MICROBLAZE_ICACHE_FORCE_TAG_LUTRAM 0
#define XPAR_MICROBLAZE_ICACHE_DATA_WIDTH 0
#define XPAR_MICROBLAZE_M_AXI_IC_SUPPORTS_THREADS 0
#define XPAR_MICROBLAZE_M_AXI_IC_THREAD_ID_WIDTH 1
#define XPAR_MICROBLAZE_M_AXI_IC_SUPPORTS_READ 1
#define XPAR_MICROBLAZE_M_AXI_IC_SUPPORTS_WRITE 0
#define XPAR_MICROBLAZE_M_AXI_IC_SUPPORTS_NARROW_BURST 0
#define XPAR_MICROBLAZE_M_AXI_IC_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M_AXI_IC_ADDR_WIDTH 32
#define XPAR_MICROBLAZE_M_AXI_IC_PROTOCOL AXI4
#define XPAR_MICROBLAZE_M_AXI_IC_USER_VALUE 0b11111
#define XPAR_MICROBLAZE_M_AXI_IC_SUPPORTS_USER_SIGNALS 1
#define XPAR_MICROBLAZE_M_AXI_IC_AWUSER_WIDTH 5
#define XPAR_MICROBLAZE_M_AXI_IC_ARUSER_WIDTH 5
#define XPAR_MICROBLAZE_M_AXI_IC_WUSER_WIDTH 1
#define XPAR_MICROBLAZE_M_AXI_IC_RUSER_WIDTH 1
#define XPAR_MICROBLAZE_M_AXI_IC_BUSER_WIDTH 1
#define XPAR_MICROBLAZE_INTERCONNECT_M_AXI_IC_READ_ISSUING 2
#define XPAR_MICROBLAZE_DCACHE_BASEADDR 0xA8000000
#define XPAR_MICROBLAZE_DCACHE_HIGHADDR 0xAFFFFFFF
#define XPAR_MICROBLAZE_USE_DCACHE 1
#define XPAR_MICROBLAZE_ALLOW_DCACHE_WR 1
#define XPAR_MICROBLAZE_DCACHE_ADDR_TAG 14
#define XPAR_MICROBLAZE_DCACHE_BYTE_SIZE 8192
#define XPAR_MICROBLAZE_DCACHE_USE_FSL 0
#define XPAR_MICROBLAZE_DCACHE_LINE_LEN 4
#define XPAR_MICROBLAZE_DCACHE_ALWAYS_USED 1
#define XPAR_MICROBLAZE_DCACHE_INTERFACE 0
#define XPAR_MICROBLAZE_DCACHE_USE_WRITEBACK 0
#define XPAR_MICROBLAZE_DCACHE_VICTIMS 0
#define XPAR_MICROBLAZE_DCACHE_FORCE_TAG_LUTRAM 0
#define XPAR_MICROBLAZE_DCACHE_DATA_WIDTH 0
#define XPAR_MICROBLAZE_M_AXI_DC_SUPPORTS_THREADS 0
#define XPAR_MICROBLAZE_M_AXI_DC_THREAD_ID_WIDTH 1
#define XPAR_MICROBLAZE_M_AXI_DC_SUPPORTS_READ 1
#define XPAR_MICROBLAZE_M_AXI_DC_SUPPORTS_WRITE 1
#define XPAR_MICROBLAZE_M_AXI_DC_SUPPORTS_NARROW_BURST 0
#define XPAR_MICROBLAZE_M_AXI_DC_DATA_WIDTH 32
#define XPAR_MICROBLAZE_M_AXI_DC_ADDR_WIDTH 32
#define XPAR_MICROBLAZE_M_AXI_DC_PROTOCOL AXI4
#define XPAR_MICROBLAZE_M_AXI_DC_EXCLUSIVE_ACCESS 0
#define XPAR_MICROBLAZE_M_AXI_DC_USER_VALUE 0b11111
#define XPAR_MICROBLAZE_M_AXI_DC_SUPPORTS_USER_SIGNALS 1
#define XPAR_MICROBLAZE_M_AXI_DC_AWUSER_WIDTH 5
#define XPAR_MICROBLAZE_M_AXI_DC_ARUSER_WIDTH 5
#define XPAR_MICROBLAZE_M_AXI_DC_WUSER_WIDTH 1
#define XPAR_MICROBLAZE_M_AXI_DC_RUSER_WIDTH 1
#define XPAR_MICROBLAZE_M_AXI_DC_BUSER_WIDTH 1
#define XPAR_MICROBLAZE_INTERCONNECT_M_AXI_DC_READ_ISSUING 2
#define XPAR_MICROBLAZE_INTERCONNECT_M_AXI_DC_WRITE_ISSUING 32
#define XPAR_MICROBLAZE_USE_MMU 0
#define XPAR_MICROBLAZE_MMU_DTLB_SIZE 4
#define XPAR_MICROBLAZE_MMU_ITLB_SIZE 2
#define XPAR_MICROBLAZE_MMU_TLB_ACCESS 3
#define XPAR_MICROBLAZE_MMU_ZONES 16
#define XPAR_MICROBLAZE_MMU_PRIVILEGED_INSTR 0
#define XPAR_MICROBLAZE_USE_INTERRUPT 1
#define XPAR_MICROBLAZE_USE_EXT_BRK 1
#define XPAR_MICROBLAZE_USE_EXT_NM_BRK 1
#define XPAR_MICROBLAZE_USE_BRANCH_TARGET_CACHE 0
#define XPAR_MICROBLAZE_BRANCH_TARGET_CACHE_SIZE 0
#define XPAR_MICROBLAZE_PC_WIDTH 32
#define XPAR_MICROBLAZE_HW_VER "8.40.a"

/******************************************************************/

