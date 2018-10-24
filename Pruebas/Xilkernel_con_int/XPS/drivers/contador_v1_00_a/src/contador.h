/*****************************************************************************
* Filename:          D:\Xilkernel\XPS/drivers/contador_v1_00_a/src/contador.h
* Version:           1.00.a
* Description:       contador Driver Header File
* Date:              Tue Sep 18 19:33:08 2012 (by Create and Import Peripheral Wizard)
*****************************************************************************/

#ifndef CONTADOR_H
#define CONTADOR_H

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
 */
#define CONTADOR_USER_SLV_SPACE_OFFSET (0x00000000)
#define CONTADOR_SLV_REG0_OFFSET (CONTADOR_USER_SLV_SPACE_OFFSET + 0x00000000)
#define CONTADOR_SLV_REG1_OFFSET (CONTADOR_USER_SLV_SPACE_OFFSET + 0x00000004)
#define CONTADOR_SLV_REG2_OFFSET (CONTADOR_USER_SLV_SPACE_OFFSET + 0x00000008)

/**
 * Software Reset Space Register Offsets
 * -- RST : software reset register
 */
#define CONTADOR_SOFT_RST_SPACE_OFFSET (0x00000100)
#define CONTADOR_RST_REG_OFFSET (CONTADOR_SOFT_RST_SPACE_OFFSET + 0x00000000)

/**
 * Software Reset Masks
 * -- SOFT_RESET : software reset
 */
#define SOFT_RESET (0x0000000A)

/**************************** Type Definitions *****************************/


/***************** Macros (Inline Functions) Definitions *******************/

/**
 *
 * Write a value to a CONTADOR register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the CONTADOR device.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void CONTADOR_mWriteReg(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Data)
 *
 */
#define CONTADOR_mWriteReg(BaseAddress, RegOffset, Data) \
 	Xil_Out32((BaseAddress) + (RegOffset), (Xuint32)(Data))

/**
 *
 * Read a value from a CONTADOR register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the CONTADOR device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	Xuint32 CONTADOR_mReadReg(Xuint32 BaseAddress, unsigned RegOffset)
 *
 */
#define CONTADOR_mReadReg(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (RegOffset))


/**
 *
 * Write/Read 32 bit value to/from CONTADOR user logic slave registers.
 *
 * @param   BaseAddress is the base address of the CONTADOR device.
 * @param   RegOffset is the offset from the slave register to write to or read from.
 * @param   Value is the data written to the register.
 *
 * @return  Data is the data from the user logic slave register.
 *
 * @note
 * C-style signature:
 * 	void CONTADOR_mWriteSlaveRegn(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Value)
 * 	Xuint32 CONTADOR_mReadSlaveRegn(Xuint32 BaseAddress, unsigned RegOffset)
 *
 */
#define CONTADOR_mWriteSlaveReg0(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (CONTADOR_SLV_REG0_OFFSET) + (RegOffset), (Xuint32)(Value))
#define CONTADOR_mWriteSlaveReg1(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (CONTADOR_SLV_REG1_OFFSET) + (RegOffset), (Xuint32)(Value))
#define CONTADOR_mWriteSlaveReg2(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (CONTADOR_SLV_REG2_OFFSET) + (RegOffset), (Xuint32)(Value))

#define CONTADOR_mReadSlaveReg0(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (CONTADOR_SLV_REG0_OFFSET) + (RegOffset))
#define CONTADOR_mReadSlaveReg1(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (CONTADOR_SLV_REG1_OFFSET) + (RegOffset))
#define CONTADOR_mReadSlaveReg2(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (CONTADOR_SLV_REG2_OFFSET) + (RegOffset))

/**
 *
 * Reset CONTADOR via software.
 *
 * @param   BaseAddress is the base address of the CONTADOR device.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void CONTADOR_mReset(Xuint32 BaseAddress)
 *
 */
#define CONTADOR_mReset(BaseAddress) \
 	Xil_Out32((BaseAddress)+(CONTADOR_RST_REG_OFFSET), SOFT_RESET)

/************************** Function Prototypes ****************************/


/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the CONTADOR instance to be worked on.
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
XStatus CONTADOR_SelfTest(void * baseaddr_p);
/**
*  Defines the number of registers available for read and write*/
#define TEST_AXI_LITE_USER_NUM_REG 3


#endif /** CONTADOR_H */
