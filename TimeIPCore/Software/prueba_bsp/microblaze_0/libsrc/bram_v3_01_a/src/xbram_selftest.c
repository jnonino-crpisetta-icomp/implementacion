/******************************************************************************
*
* (c) Copyright 2011-2012 Xilinx, Inc. All rights reserved.
*
* This file contains confidential and proprietary information of Xilinx, Inc.
* and is protected under U.S. and international copyright and other
* intellectual property laws.
*
* DISCLAIMER
* This disclaimer is not a license and does not grant any rights to the
* materials distributed herewith. Except as otherwise provided in a valid
* license issued to you by Xilinx, and to the maximum extent permitted by
* applicable law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL
* FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS,
* IMPLIED, OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF
* MERCHANTABILITY, NON-INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE;
* and (2) Xilinx shall not be liable (whether in contract or tort, including
* negligence, or under any other theory of liability) for any loss or damage
* of any kind or nature related to, arising under or in connection with these
* materials, including for any direct, or any indirect, special, incidental,
* or consequential loss or damage (including loss of data, profits, goodwill,
* or any type of loss or damage suffered as a result of any action brought by
* a third party) even if such damage or loss was reasonably foreseeable or
* Xilinx had been advised of the possibility of the same.
*
* CRITICAL APPLICATIONS
* Xilinx products are not designed or intended to be fail-safe, or for use in
* any application requiring fail-safe performance, such as life-support or
* safety devices or systems, Class III medical devices, nuclear facilities,
* applications related to the deployment of airbags, or any other applications
* that could lead to death, personal injury, or severe property or
* environmental damage (individually and collectively, "Critical
* Applications"). Customer assumes the sole risk and liability of any use of
* Xilinx products in Critical Applications, subject only to applicable laws
* and regulations governing limitations on product liability.
*
* THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE
* AT ALL TIMES.
*
******************************************************************************/
/*****************************************************************************/
/**
* @file xbram_selftest.c
*
* The implementation of the XBram driver's self test function. This SelfTest
* is only applicable if ECC is enabled.
* If ECC is not enabled then this function will return XST_SUCCESS.
* See xbram.h for more information about the driver.
*
* @note
*
* None
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -----------------------------------------------
* 1.00a sa   24/11/10 First release
* 3.01a sa   01/13/12  Changed Selftest API from
*		       XBram_SelfTest(XBram *InstancePtr) to
*		       XBram_SelfTest(XBram *InstancePtr, u8 IntMask) and
*		       fixed a problem with interrupt generation for CR 639274
*		       Modified Selftest example to return XST_SUCCESS when
*		       ECC is not enabled and return XST_FAILURE when ECC is
*		       enabled and Control Base Address is zero (CR 636581)
*		       Modified Selftest to use correct CorrectableCounterBits
*		       for CR 635655
*		       Updated to check CorrectableFailingDataRegs in the case
*		       of LMB BRAM.
* </pre>
*****************************************************************************/

/***************************** Include Files ********************************/
#include "xbram.h"

/************************** Constant Definitions ****************************/
#define TOTAL_BITS	39

/**************************** Type Definitions ******************************/

/***************** Macros (Inline Functions) Definitions ********************/
#define RD(reg)		XBram_ReadReg(InstancePtr->Config.CtrlBaseAddress, \
					XBRAM_ ## reg)
#define WR(reg, data)	XBram_WriteReg(InstancePtr->Config.CtrlBaseAddress, \
						XBRAM_ ## reg, data)

#define CHECK(reg, data, result) if (result!=XST_SUCCESS || RD(reg)!=data) \
						result = XST_FAILURE;

/************************** Variable Definitions ****************************/
static u32 PrngResult;

/************************** Function Prototypes *****************************/
static inline u32 PrngData(u32 *PrngResult);

static inline u32 CalculateEcc(u32 Data);

static void InjectErrors(XBram * InstancePtr, u32 Addr,
			 int Index1, int Index2,
			 u32 *ActualData, u32 *ActualEcc);


/*****************************************************************************/
/**
* Generate a pseudo random number.
*
* @param	The PrngResult is the previous random number in the pseudo
*		random sequence, also knwon as the seed. It is modified to
*		the calculated pseudo random number by the function.
*
* @return 	The generated pseudo random number
*
* @note		None.
*
******************************************************************************/
static inline u32 PrngData(u32 *PrngResult)
{
	*PrngResult = *PrngResult * 0x77D15E25 + 0x3617C161;
	return *PrngResult;
}


/*****************************************************************************/
/**
* Calculate ECC from Data.
*
* @param	The Data Value
*
* @return 	The calculated ECC
*
* @note		None.
*
******************************************************************************/
static inline u32 CalculateEcc(u32 Data)
{
	unsigned char c[7], d[32];
	u32 Result = 0;
	int Index;

	for (Index = 0; Index < 32; Index++) {
		d[31 - Index] = Data & 1;
		Data = Data >> 1;
	}

	c[0] =  d[0]  ^ d[1]  ^ d[3]  ^ d[4]  ^ d[6]  ^ d[8]  ^ d[10] ^ d[11] ^
		d[13] ^ d[15] ^ d[17] ^ d[19] ^ d[21] ^ d[23] ^ d[25] ^ d[26] ^
		d[28] ^ d[30];

	c[1] =  d[0]  ^ d[2]  ^ d[3]  ^ d[5]  ^ d[6]  ^ d[9]  ^ d[10] ^ d[12] ^
		d[13] ^ d[16] ^ d[17] ^ d[20] ^ d[21] ^ d[24] ^ d[25] ^ d[27] ^
		d[28] ^ d[31];

	c[2] =  d[1]  ^ d[2]  ^ d[3]  ^ d[7]  ^ d[8]  ^ d[9]  ^ d[10] ^ d[14] ^
		d[15] ^ d[16] ^ d[17] ^ d[22] ^ d[23] ^ d[24] ^ d[25] ^ d[29] ^
		d[30] ^ d[31];

	c[3] =  d[4]  ^ d[5]  ^ d[6]  ^ d[7]  ^ d[8]  ^ d[9]  ^ d[10] ^ d[18] ^
		d[19] ^ d[20] ^ d[21] ^ d[22] ^ d[23] ^ d[24] ^ d[25];

	c[4] =  d[11] ^ d[12] ^ d[13] ^ d[14] ^ d[15] ^ d[16] ^ d[17] ^ d[18] ^
		d[19] ^ d[20] ^ d[21] ^ d[22] ^ d[23] ^ d[24] ^ d[25];

	c[5] = d[26] ^ d[27] ^ d[28] ^ d[29] ^ d[30] ^ d[31];

	c[6] =  d[0]  ^ d[1]  ^ d[2]  ^ d[3]  ^ d[4]  ^  d[5] ^  d[6] ^ d[7]  ^
		d[8]  ^ d[9]  ^ d[10] ^ d[11] ^ d[12] ^ d[13] ^ d[14] ^ d[15] ^
		d[16] ^ d[17] ^ d[18] ^ d[19] ^ d[20] ^ d[21] ^ d[22] ^ d[23] ^
		d[24] ^ d[25] ^ d[26] ^ d[27] ^ d[28] ^ d[29] ^ d[30] ^ d[31] ^
		c[5]  ^ c[4]  ^ c[3] ^  c[2]  ^ c[1]  ^ c[0];

	for (Index = 0; Index < 7; Index++) {
		Result = Result << 1;
		Result |= c[Index] & 1;
	}

	return Result;
}


/*****************************************************************************/
/**
* Inject errors using the hardware fault injection functionality, and write
* random data and read it back using the indicated location.
*
* @param	InstancePtr is a pointer to the XBram instance to
*		be worked on.
* @param	The Addr is the indicated memory location to use
* @param	The Index1 is the bit location of the first injected error
* @param	The Index2 is the bit location of the second injected error
* @param	The ActualData is filled in with expected data for checking
* @param	The ActualEcc is filled in with expected ECC for checking
*
* @return 	None
*
* @note		None.
*
******************************************************************************/
static void InjectErrors(XBram * InstancePtr, u32 Addr,
			 int Index1, int Index2,
			 u32 *ActualData, u32 *ActualEcc)
{
	u32 InjectedData = 0;
	u32 InjectedEcc = 0;
	u32 RandomData = PrngData(&PrngResult);

	if (Index1 < 32) {
		InjectedData = 1 << Index1;
	} else {
		InjectedEcc = 1 << (Index1 - 32);
	}

	if (Index2 < 32) {
		InjectedData |= (1 << Index2);
	} else {
		InjectedEcc |= 1 << (Index2 - 32);
	}

	WR(FI_D_0_OFFSET, InjectedData);
	WR(FI_ECC_0_OFFSET, InjectedEcc);

	XBram_Out32(Addr, RandomData);
	(void) XBram_In32(Addr);

	*ActualData = InjectedData ^ RandomData;
	*ActualEcc  = InjectedEcc ^ CalculateEcc(RandomData);
}


/*****************************************************************************/
/**
* Run a self-test on the driver/device. Unless fault injection is implemented
* in hardware, this function only does a minimal test in which available
* registers (if any) are written and read.
*
* With fault injection, all possible single-bit and double-bit errors are
* injected, and checked to the extent possible, given the implemented hardware.
*
* @param	InstancePtr is a pointer to the XBram instance.
* @param	IntMask is the interrupt mask to use. When testing
*		with interrupts, this should be set to allow interrupt
*		generation, otherwise it should be 0.
*
* @return
*		- XST_SUCCESS if fault injection/detection is working properly OR
*		  if ECC is Not Enabled in the HW.
*		- XST_FAILURE if the injected fault is not correctly detected or
*		  the Control Base Address is Zero when ECC is enabled.
*		.
*
*		If the BRAM device is not present in the
*		hardware a bus error could be generated. Other indicators of a
*		bus error, such as registers in bridges or buses, may be
*		necessary to determine if this function caused a bus error.
*
* @note		None.
*
******************************************************************************/
int XBram_SelfTest(XBram *InstancePtr, u8 IntMask)
{
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);



	if (InstancePtr->Config.EccPresent == 0) {
		return (XST_SUCCESS);
	}

	if (InstancePtr->Config.CtrlBaseAddress == 0) {
		return (XST_FAILURE);
	}

	/*
	 * Only 32-bit data width is supported as of yet. 64-bit and 128-bit
	 * widths will be supported in future.
	 */
	if (InstancePtr->Config.DataWidth != 32)
		return (XST_SUCCESS);

	/*
	 * Read from the implemented readable registers in the hardware device.
	 */
	if (InstancePtr->Config.CorrectableFailingRegisters) {
		(void) RD(CE_FFA_0_OFFSET);
	}
	if (InstancePtr->Config.CorrectableFailingDataRegs) {
		(void) RD(CE_FFD_0_OFFSET);
		(void) RD(CE_FFE_0_OFFSET);
	}
	if (InstancePtr->Config.UncorrectableFailingRegisters) {
		(void) RD(UE_FFA_0_OFFSET);
	}
	if (InstancePtr->Config.UncorrectableFailingDataRegs) {
		(void) RD(UE_FFD_0_OFFSET);
		(void) RD(UE_FFE_0_OFFSET);
	}

	/*
	 * Write and read the implemented read/write registers in the hardware
	 * device.
	 */
	if (InstancePtr->Config.EccStatusInterruptPresent) {
		WR(ECC_EN_IRQ_OFFSET, 0);
		if (RD(ECC_EN_IRQ_OFFSET) != 0) {
			return (XST_FAILURE);
		}
	}

	if (InstancePtr->Config.CorrectableCounterBits > 0) {
		u32 Value;

		/* Calculate counter max value */
		if (InstancePtr->Config.CorrectableCounterBits == 32) {
		 	Value = 0xFFFFFFFF;
		} else {
		 	Value = (1 <<
		 		InstancePtr->Config.CorrectableCounterBits) - 1;
		 }

		WR(CE_CNT_OFFSET, Value);
		if (RD(CE_CNT_OFFSET) != Value) {
			return (XST_FAILURE);
		}

		WR(CE_CNT_OFFSET, 0);
		if (RD(CE_CNT_OFFSET) != 0) {
			return (XST_FAILURE);
		}
	}

	/*
	 * If fault injection is implemented, inject all possible single-bit
	 * and double-bit errors, and check all observable effects.
	 */
	if (InstancePtr->Config.FaultInjectionPresent &&
	    InstancePtr->Config.WriteAccess != 0) {

		const u32 Addr[2] = {InstancePtr->Config.MemBaseAddress &
					0xfffffffc,
				     InstancePtr->Config.MemHighAddress &
					0xfffffffc};
		u32 SavedWords[2];
		u32 ActualData;
		u32 ActualEcc;
		u32 CounterValue = 0;
		u32 CounterMax;
		int WordIndex = 0;
		int Result = XST_SUCCESS;
		int Index1;
		int Index2;

		PrngResult = 42; /* Random seed */

		/* Save two words in BRAM used for test */
		SavedWords[0] = XBram_In32(Addr[0]);
		SavedWords[1] = XBram_In32(Addr[1]);

		/* Calculate counter max value */
		if (InstancePtr->Config.CorrectableCounterBits == 32) {
			CounterMax = 0xFFFFFFFF;
		} else {
			CounterMax =(1 <<
				InstancePtr->Config.CorrectableCounterBits) - 1;
		}

		/* Inject and check all single bit errors */
		for (Index1 = 0; Index1 < TOTAL_BITS; Index1++) {
			/* Save counter value */
			if (InstancePtr->Config.CorrectableCounterBits > 0) {
				CounterValue = RD(CE_CNT_OFFSET);
			}

			/* Inject single bit error */
			InjectErrors(InstancePtr, Addr[WordIndex], Index1,
					Index1, &ActualData, &ActualEcc);

			/* Check that CE is set */
			if (InstancePtr->Config.EccStatusInterruptPresent) {
				CHECK(ECC_STATUS_OFFSET,
					XBRAM_IR_CE_MASK, Result);
			}

			/* Check that address, data, ECC are correct */
			if (InstancePtr->Config.CorrectableFailingRegisters) {
				CHECK(CE_FFA_0_OFFSET, Addr[WordIndex], Result);
 			}
 			/* Checks are only for LMB BRAM */
 			if (InstancePtr->Config.CorrectableFailingDataRegs) {
  				CHECK(CE_FFD_0_OFFSET, ActualData, Result);
  				CHECK(CE_FFE_0_OFFSET, ActualEcc, Result);
  			}

			/* Check that counter has incremented */
			if (InstancePtr->Config.CorrectableCounterBits > 0 &&
				CounterValue < CounterMax) {
					CHECK(CE_CNT_OFFSET,
					CounterValue + 1, Result);
			}

			/* Restore correct data in the used word */
			XBram_Out32(Addr[WordIndex], SavedWords[WordIndex]);

			/* Allow interrupts to occur */
			/* Clear status register */
			if (InstancePtr->Config.EccStatusInterruptPresent) {
				WR(ECC_EN_IRQ_OFFSET, IntMask);
				WR(ECC_STATUS_OFFSET, XBRAM_IR_ALL_MASK);
				WR(ECC_EN_IRQ_OFFSET, 0);
			}

			/* Switch to the other word */
			WordIndex = WordIndex ^ 1;

			if (Result != XST_SUCCESS) break;

		}

		if (Result != XST_SUCCESS) {
			return XST_FAILURE;
		}

		for (Index1 = 0; Index1 < TOTAL_BITS; Index1++) {
			for (Index2 = 0; Index2 < TOTAL_BITS; Index2++) {
			    if (Index1 != Index2) {
				/* Inject double bit error */
				InjectErrors(InstancePtr,
					Addr[WordIndex],
						Index1, Index2,
						&ActualData,
						&ActualEcc);

				/* Check that UE is set */
				if (InstancePtr->Config.
				    EccStatusInterruptPresent) {
					CHECK(ECC_STATUS_OFFSET,
					XBRAM_IR_UE_MASK,
					Result);
				}

				/* Check that address, data, ECC are correct */
				if (InstancePtr->Config.
				    UncorrectableFailingRegisters) {
					CHECK(UE_FFA_0_OFFSET, Addr[WordIndex],
							Result);
					CHECK(UE_FFD_0_OFFSET,
						ActualData, Result);
					CHECK(UE_FFE_0_OFFSET, ActualEcc,
						Result);
					}

				/* Restore correct data in the used word */
				XBram_Out32(Addr[WordIndex],
						SavedWords[WordIndex]);

				/* Allow interrupts to occur */
				/* Clear status register */
				if (InstancePtr->Config.
				    EccStatusInterruptPresent) {
					WR(ECC_EN_IRQ_OFFSET, IntMask);
					WR(ECC_STATUS_OFFSET,
						XBRAM_IR_ALL_MASK);
					WR(ECC_EN_IRQ_OFFSET, 0);
				}

				/* Switch to the other word */
				WordIndex = WordIndex ^ 1;
			    }
				if (Result != XST_SUCCESS) break;
			}
			if (Result != XST_SUCCESS) break;
		}

		/* Check saturation of correctable error counter */
		if (InstancePtr->Config.CorrectableCounterBits > 0 &&
			Result == XST_SUCCESS) {

				WR(CE_CNT_OFFSET, CounterMax);

				InjectErrors(InstancePtr, Addr[WordIndex], 0, 0,
					&ActualData, &ActualEcc);

				CHECK(CE_CNT_OFFSET, CounterMax, Result);
		}

		/* Restore the two words used for test */
		XBram_Out32(Addr[0], SavedWords[0]);
		XBram_Out32(Addr[1], SavedWords[1]);

		/* Clear the Status Register. */
		if (InstancePtr->Config.EccStatusInterruptPresent) {
			WR(ECC_STATUS_OFFSET, XBRAM_IR_ALL_MASK);
		}

		/* Set Correctable Counter to zero */
		if (InstancePtr->Config.CorrectableCounterBits > 0) {
			WR(CE_CNT_OFFSET, 0);
		}

		return (Result);
	}

	return (XST_SUCCESS);
}

