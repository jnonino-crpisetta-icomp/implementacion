/*****************************************************************************
* Filename:          D:\ProyectoIntegrador\trunk\Implementacion\IPCore\MyProcessorIPLib/drivers/petri_plb_v2_00_b/src/petri_plb.h
* Version:           2.00.b
* Description:       petri_plb Driver Header File
* Date:              Thu Sep 13 15:24:17 2012 (by Create and Import Peripheral Wizard)
*****************************************************************************/

#ifndef PETRI_PLB_H
#define PETRI_PLB_H

/***************************** Include Files *******************************/

#include "xbasic_types.h"
#include "xstatus.h"
#include "xil_io.h"

/************************** Constant Definitions ***************************/


/**
 * User Logic Slave Space Offsets
 * -- SLV_REG0 : user logic slave module register 0
 * -- SLV_REG1 : user logic slave module register 1
 * -- SLV_REG2 : user logic slave module register 2
 * -- SLV_REG3 : user logic slave module register 3
 * -- SLV_REG4 : user logic slave module register 4
 * -- SLV_REG5 : user logic slave module register 5
 * -- SLV_REG6 : user logic slave module register 6
 * -- SLV_REG7 : user logic slave module register 7
 * -- SLV_REG8 : user logic slave module register 8
 * -- SLV_REG9 : user logic slave module register 9
 * -- SLV_REG10 : user logic slave module register 10
 * -- SLV_REG11 : user logic slave module register 11
 * -- SLV_REG12 : user logic slave module register 12
 * -- SLV_REG13 : user logic slave module register 13
 * -- SLV_REG14 : user logic slave module register 14
 * -- SLV_REG15 : user logic slave module register 15
 * -- SLV_REG16 : user logic slave module register 16
 * -- SLV_REG17 : user logic slave module register 17
 * -- SLV_REG18 : user logic slave module register 18
 * -- SLV_REG19 : user logic slave module register 19
 * -- SLV_REG20 : user logic slave module register 20
 * -- SLV_REG21 : user logic slave module register 21
 * -- SLV_REG22 : user logic slave module register 22
 * -- SLV_REG23 : user logic slave module register 23
 * -- SLV_REG24 : user logic slave module register 24
 * -- SLV_REG25 : user logic slave module register 25
 * -- SLV_REG26 : user logic slave module register 26
 * -- SLV_REG27 : user logic slave module register 27
 * -- SLV_REG28 : user logic slave module register 28
 * -- SLV_REG29 : user logic slave module register 29
 * -- SLV_REG30 : user logic slave module register 30
 * -- SLV_REG31 : user logic slave module register 31
 */
#define PETRI_PLB_USER_SLV_SPACE_OFFSET (0x00000000)
#define PETRI_PLB_SLV_REG0_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000000)
#define PETRI_PLB_SLV_REG1_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000004)
#define PETRI_PLB_SLV_REG2_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000008)
#define PETRI_PLB_SLV_REG3_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x0000000C)
#define PETRI_PLB_SLV_REG4_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000010)
#define PETRI_PLB_SLV_REG5_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000014)
#define PETRI_PLB_SLV_REG6_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000018)
#define PETRI_PLB_SLV_REG7_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x0000001C)
#define PETRI_PLB_SLV_REG8_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000020)
#define PETRI_PLB_SLV_REG9_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000024)
#define PETRI_PLB_SLV_REG10_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000028)
#define PETRI_PLB_SLV_REG11_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x0000002C)
#define PETRI_PLB_SLV_REG12_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000030)
#define PETRI_PLB_SLV_REG13_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000034)
#define PETRI_PLB_SLV_REG14_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000038)
#define PETRI_PLB_SLV_REG15_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x0000003C)
#define PETRI_PLB_SLV_REG16_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000040)
#define PETRI_PLB_SLV_REG17_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000044)
#define PETRI_PLB_SLV_REG18_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000048)
#define PETRI_PLB_SLV_REG19_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x0000004C)
#define PETRI_PLB_SLV_REG20_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000050)
#define PETRI_PLB_SLV_REG21_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000054)
#define PETRI_PLB_SLV_REG22_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000058)
#define PETRI_PLB_SLV_REG23_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x0000005C)
#define PETRI_PLB_SLV_REG24_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000060)
#define PETRI_PLB_SLV_REG25_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000064)
#define PETRI_PLB_SLV_REG26_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000068)
#define PETRI_PLB_SLV_REG27_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x0000006C)
#define PETRI_PLB_SLV_REG28_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000070)
#define PETRI_PLB_SLV_REG29_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000074)
#define PETRI_PLB_SLV_REG30_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x00000078)
#define PETRI_PLB_SLV_REG31_OFFSET (PETRI_PLB_USER_SLV_SPACE_OFFSET + 0x0000007C)

/**
 * Software Reset Space Register Offsets
 * -- RST : software reset register
 */
#define PETRI_PLB_SOFT_RST_SPACE_OFFSET (0x00000100)
#define PETRI_PLB_RST_REG_OFFSET (PETRI_PLB_SOFT_RST_SPACE_OFFSET + 0x00000000)

/**
 * Software Reset Masks
 * -- SOFT_RESET : software reset
 */
#define SOFT_RESET (0x0000000A)

/**
 * Interrupt Controller Space Offsets
 * -- INTR_DISR  : device (peripheral) interrupt status register
 * -- INTR_DIPR  : device (peripheral) interrupt pending register
 * -- INTR_DIER  : device (peripheral) interrupt enable register
 * -- INTR_DIIR  : device (peripheral) interrupt id (priority encoder) register
 * -- INTR_DGIER : device (peripheral) global interrupt enable register
 * -- INTR_ISR   : ip (user logic) interrupt status register
 * -- INTR_IER   : ip (user logic) interrupt enable register
 */
#define PETRI_PLB_INTR_CNTRL_SPACE_OFFSET (0x00000200)
#define PETRI_PLB_INTR_DISR_OFFSET (PETRI_PLB_INTR_CNTRL_SPACE_OFFSET + 0x00000000)
#define PETRI_PLB_INTR_DIPR_OFFSET (PETRI_PLB_INTR_CNTRL_SPACE_OFFSET + 0x00000004)
#define PETRI_PLB_INTR_DIER_OFFSET (PETRI_PLB_INTR_CNTRL_SPACE_OFFSET + 0x00000008)
#define PETRI_PLB_INTR_DIIR_OFFSET (PETRI_PLB_INTR_CNTRL_SPACE_OFFSET + 0x00000018)
#define PETRI_PLB_INTR_DGIER_OFFSET (PETRI_PLB_INTR_CNTRL_SPACE_OFFSET + 0x0000001C)
#define PETRI_PLB_INTR_IPISR_OFFSET (PETRI_PLB_INTR_CNTRL_SPACE_OFFSET + 0x00000020)
#define PETRI_PLB_INTR_IPIER_OFFSET (PETRI_PLB_INTR_CNTRL_SPACE_OFFSET + 0x00000028)

/**
 * Interrupt Controller Masks
 * -- INTR_TERR_MASK : transaction error
 * -- INTR_DPTO_MASK : data phase time-out
 * -- INTR_IPIR_MASK : ip interrupt requeset
 * -- INTR_RFDL_MASK : read packet fifo deadlock interrupt request
 * -- INTR_WFDL_MASK : write packet fifo deadlock interrupt request
 * -- INTR_IID_MASK  : interrupt id
 * -- INTR_GIE_MASK  : global interrupt enable
 * -- INTR_NOPEND    : the DIPR has no pending interrupts
 */
#define INTR_TERR_MASK (0x00000001UL)
#define INTR_DPTO_MASK (0x00000002UL)
#define INTR_IPIR_MASK (0x00000004UL)
#define INTR_RFDL_MASK (0x00000020UL)
#define INTR_WFDL_MASK (0x00000040UL)
#define INTR_IID_MASK (0x000000FFUL)
#define INTR_GIE_MASK (0x80000000UL)
#define INTR_NOPEND (0x80)

/**************************** Type Definitions *****************************/


/***************** Macros (Inline Functions) Definitions *******************/

/**
 *
 * Write a value to a PETRI_PLB register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the PETRI_PLB device.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void PETRI_PLB_mWriteReg(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Data)
 *
 */
#define PETRI_PLB_mWriteReg(BaseAddress, RegOffset, Data) \
 	Xil_Out32((BaseAddress) + (RegOffset), (Xuint32)(Data))

/**
 *
 * Read a value from a PETRI_PLB register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the PETRI_PLB device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	Xuint32 PETRI_PLB_mReadReg(Xuint32 BaseAddress, unsigned RegOffset)
 *
 */
#define PETRI_PLB_mReadReg(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (RegOffset))


/**
 *
 * Write/Read 32 bit value to/from PETRI_PLB user logic slave registers.
 *
 * @param   BaseAddress is the base address of the PETRI_PLB device.
 * @param   RegOffset is the offset from the slave register to write to or read from.
 * @param   Value is the data written to the register.
 *
 * @return  Data is the data from the user logic slave register.
 *
 * @note
 * C-style signature:
 * 	void PETRI_PLB_mWriteSlaveRegn(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Value)
 * 	Xuint32 PETRI_PLB_mReadSlaveRegn(Xuint32 BaseAddress, unsigned RegOffset)
 *
 */
#define PETRI_PLB_mWriteSlaveReg0(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG0_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg1(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG1_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg2(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG2_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg3(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG3_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg4(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG4_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg5(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG5_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg6(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG6_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg7(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG7_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg8(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG8_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg9(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG9_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg10(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG10_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg11(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG11_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg12(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG12_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg13(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG13_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg14(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG14_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg15(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG15_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg16(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG16_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg17(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG17_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg18(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG18_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg19(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG19_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg20(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG20_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg21(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG21_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg22(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG22_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg23(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG23_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg24(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG24_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg25(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG25_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg26(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG26_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg27(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG27_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg28(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG28_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg29(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG29_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg30(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG30_OFFSET) + (RegOffset), (Xuint32)(Value))
#define PETRI_PLB_mWriteSlaveReg31(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (PETRI_PLB_SLV_REG31_OFFSET) + (RegOffset), (Xuint32)(Value))

#define PETRI_PLB_mReadSlaveReg0(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG0_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg1(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG1_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg2(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG2_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg3(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG3_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg4(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG4_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg5(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG5_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg6(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG6_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg7(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG7_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg8(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG8_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg9(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG9_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg10(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG10_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg11(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG11_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg12(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG12_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg13(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG13_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg14(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG14_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg15(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG15_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg16(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG16_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg17(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG17_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg18(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG18_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg19(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG19_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg20(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG20_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg21(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG21_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg22(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG22_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg23(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG23_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg24(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG24_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg25(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG25_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg26(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG26_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg27(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG27_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg28(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG28_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg29(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG29_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg30(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG30_OFFSET) + (RegOffset))
#define PETRI_PLB_mReadSlaveReg31(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (PETRI_PLB_SLV_REG31_OFFSET) + (RegOffset))

/**
 *
 * Reset PETRI_PLB via software.
 *
 * @param   BaseAddress is the base address of the PETRI_PLB device.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void PETRI_PLB_mReset(Xuint32 BaseAddress)
 *
 */
#define PETRI_PLB_mReset(BaseAddress) \
 	Xil_Out32((BaseAddress)+(PETRI_PLB_RST_REG_OFFSET), SOFT_RESET)

/************************** Function Prototypes ****************************/


/**
 *
 * Enable all possible interrupts from PETRI_PLB device.
 *
 * @param   baseaddr_p is the base address of the PETRI_PLB device.
 *
 * @return  None.
 *
 * @note    None.
 *
 */
void PETRI_PLB_EnableInterrupt(void * baseaddr_p);

/**
 *
 * Example interrupt controller handler.
 *
 * @param   baseaddr_p is the base address of the PETRI_PLB device.
 *
 * @return  None.
 *
 * @note    None.
 *
 */
void PETRI_PLB_Intr_DefaultHandler(void * baseaddr_p);

/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the PETRI_PLB instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */
XStatus PETRI_PLB_SelfTest(void * baseaddr_p);

#endif /** PETRI_PLB_H */
