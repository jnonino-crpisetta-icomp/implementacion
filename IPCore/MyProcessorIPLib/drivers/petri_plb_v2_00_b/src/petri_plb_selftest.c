/*****************************************************************************
* Filename:          D:\ProyectoIntegrador\trunk\Implementacion\IPCore\MyProcessorIPLib/drivers/petri_plb_v2_00_b/src/petri_plb_selftest.c
* Version:           2.00.b
* Description:       Contains a diagnostic self-test function for the petri_plb driver
* Date:              Thu Sep 13 15:24:17 2012 (by Create and Import Peripheral Wizard)
*****************************************************************************/


/***************************** Include Files *******************************/

#include "petri_plb.h"

/************************** Constant Definitions ***************************/


/************************** Variable Definitions ****************************/


/************************** Function Definitions ***************************/

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
XStatus PETRI_PLB_SelfTest(void * baseaddr_p)
{
  int     Index;
  Xuint32 baseaddr;
  Xuint8  Reg8Value;
  Xuint16 Reg16Value;
  Xuint32 Reg32Value;
  
  /*
   * Check and get the device address
   */
  /*
   * Base Address maybe 0. Up to developer to uncomment line below.
  XASSERT_NONVOID(baseaddr_p != XNULL);
   */
  baseaddr = (Xuint32) baseaddr_p;

  xil_printf("******************************\n\r");
  xil_printf("* User Peripheral Self Test\n\r");
  xil_printf("******************************\n\n\r");

  /*
   * Reset the device to get it back to the default state
   */
  xil_printf("Soft reset test...\n\r");
  PETRI_PLB_mReset(baseaddr);
  xil_printf("   - write 0x%08x to software reset register\n\r", SOFT_RESET);
  xil_printf("   - soft reset passed\n\n\r");

  /*
   * Write to user logic slave module register(s) and read back
   */
  xil_printf("User logic slave module test...\n\r");
  xil_printf("   - write 1 to slave register 0 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg0(baseaddr, 0, 1);
  Reg32Value = PETRI_PLB_mReadSlaveReg0(baseaddr, 0);
  xil_printf("   - read %d from register 0 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 1 )
  {
    xil_printf("   - slave register 0 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 2 to slave register 1 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg1(baseaddr, 0, 2);
  Reg32Value = PETRI_PLB_mReadSlaveReg1(baseaddr, 0);
  xil_printf("   - read %d from register 1 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 2 )
  {
    xil_printf("   - slave register 1 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 3 to slave register 2 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg2(baseaddr, 0, 3);
  Reg32Value = PETRI_PLB_mReadSlaveReg2(baseaddr, 0);
  xil_printf("   - read %d from register 2 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 3 )
  {
    xil_printf("   - slave register 2 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 4 to slave register 3 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg3(baseaddr, 0, 4);
  Reg32Value = PETRI_PLB_mReadSlaveReg3(baseaddr, 0);
  xil_printf("   - read %d from register 3 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 4 )
  {
    xil_printf("   - slave register 3 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 5 to slave register 4 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg4(baseaddr, 0, 5);
  Reg32Value = PETRI_PLB_mReadSlaveReg4(baseaddr, 0);
  xil_printf("   - read %d from register 4 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 5 )
  {
    xil_printf("   - slave register 4 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 6 to slave register 5 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg5(baseaddr, 0, 6);
  Reg32Value = PETRI_PLB_mReadSlaveReg5(baseaddr, 0);
  xil_printf("   - read %d from register 5 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 6 )
  {
    xil_printf("   - slave register 5 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 7 to slave register 6 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg6(baseaddr, 0, 7);
  Reg32Value = PETRI_PLB_mReadSlaveReg6(baseaddr, 0);
  xil_printf("   - read %d from register 6 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 7 )
  {
    xil_printf("   - slave register 6 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 8 to slave register 7 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg7(baseaddr, 0, 8);
  Reg32Value = PETRI_PLB_mReadSlaveReg7(baseaddr, 0);
  xil_printf("   - read %d from register 7 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 8 )
  {
    xil_printf("   - slave register 7 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 9 to slave register 8 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg8(baseaddr, 0, 9);
  Reg32Value = PETRI_PLB_mReadSlaveReg8(baseaddr, 0);
  xil_printf("   - read %d from register 8 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 9 )
  {
    xil_printf("   - slave register 8 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 10 to slave register 9 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg9(baseaddr, 0, 10);
  Reg32Value = PETRI_PLB_mReadSlaveReg9(baseaddr, 0);
  xil_printf("   - read %d from register 9 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 10 )
  {
    xil_printf("   - slave register 9 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 11 to slave register 10 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg10(baseaddr, 0, 11);
  Reg32Value = PETRI_PLB_mReadSlaveReg10(baseaddr, 0);
  xil_printf("   - read %d from register 10 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 11 )
  {
    xil_printf("   - slave register 10 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 12 to slave register 11 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg11(baseaddr, 0, 12);
  Reg32Value = PETRI_PLB_mReadSlaveReg11(baseaddr, 0);
  xil_printf("   - read %d from register 11 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 12 )
  {
    xil_printf("   - slave register 11 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 13 to slave register 12 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg12(baseaddr, 0, 13);
  Reg32Value = PETRI_PLB_mReadSlaveReg12(baseaddr, 0);
  xil_printf("   - read %d from register 12 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 13 )
  {
    xil_printf("   - slave register 12 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 14 to slave register 13 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg13(baseaddr, 0, 14);
  Reg32Value = PETRI_PLB_mReadSlaveReg13(baseaddr, 0);
  xil_printf("   - read %d from register 13 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 14 )
  {
    xil_printf("   - slave register 13 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 15 to slave register 14 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg14(baseaddr, 0, 15);
  Reg32Value = PETRI_PLB_mReadSlaveReg14(baseaddr, 0);
  xil_printf("   - read %d from register 14 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 15 )
  {
    xil_printf("   - slave register 14 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 16 to slave register 15 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg15(baseaddr, 0, 16);
  Reg32Value = PETRI_PLB_mReadSlaveReg15(baseaddr, 0);
  xil_printf("   - read %d from register 15 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 16 )
  {
    xil_printf("   - slave register 15 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 17 to slave register 16 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg16(baseaddr, 0, 17);
  Reg32Value = PETRI_PLB_mReadSlaveReg16(baseaddr, 0);
  xil_printf("   - read %d from register 16 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 17 )
  {
    xil_printf("   - slave register 16 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 18 to slave register 17 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg17(baseaddr, 0, 18);
  Reg32Value = PETRI_PLB_mReadSlaveReg17(baseaddr, 0);
  xil_printf("   - read %d from register 17 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 18 )
  {
    xil_printf("   - slave register 17 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 19 to slave register 18 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg18(baseaddr, 0, 19);
  Reg32Value = PETRI_PLB_mReadSlaveReg18(baseaddr, 0);
  xil_printf("   - read %d from register 18 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 19 )
  {
    xil_printf("   - slave register 18 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 20 to slave register 19 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg19(baseaddr, 0, 20);
  Reg32Value = PETRI_PLB_mReadSlaveReg19(baseaddr, 0);
  xil_printf("   - read %d from register 19 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 20 )
  {
    xil_printf("   - slave register 19 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 21 to slave register 20 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg20(baseaddr, 0, 21);
  Reg32Value = PETRI_PLB_mReadSlaveReg20(baseaddr, 0);
  xil_printf("   - read %d from register 20 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 21 )
  {
    xil_printf("   - slave register 20 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 22 to slave register 21 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg21(baseaddr, 0, 22);
  Reg32Value = PETRI_PLB_mReadSlaveReg21(baseaddr, 0);
  xil_printf("   - read %d from register 21 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 22 )
  {
    xil_printf("   - slave register 21 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 23 to slave register 22 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg22(baseaddr, 0, 23);
  Reg32Value = PETRI_PLB_mReadSlaveReg22(baseaddr, 0);
  xil_printf("   - read %d from register 22 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 23 )
  {
    xil_printf("   - slave register 22 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 24 to slave register 23 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg23(baseaddr, 0, 24);
  Reg32Value = PETRI_PLB_mReadSlaveReg23(baseaddr, 0);
  xil_printf("   - read %d from register 23 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 24 )
  {
    xil_printf("   - slave register 23 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 25 to slave register 24 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg24(baseaddr, 0, 25);
  Reg32Value = PETRI_PLB_mReadSlaveReg24(baseaddr, 0);
  xil_printf("   - read %d from register 24 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 25 )
  {
    xil_printf("   - slave register 24 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 26 to slave register 25 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg25(baseaddr, 0, 26);
  Reg32Value = PETRI_PLB_mReadSlaveReg25(baseaddr, 0);
  xil_printf("   - read %d from register 25 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 26 )
  {
    xil_printf("   - slave register 25 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 27 to slave register 26 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg26(baseaddr, 0, 27);
  Reg32Value = PETRI_PLB_mReadSlaveReg26(baseaddr, 0);
  xil_printf("   - read %d from register 26 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 27 )
  {
    xil_printf("   - slave register 26 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 28 to slave register 27 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg27(baseaddr, 0, 28);
  Reg32Value = PETRI_PLB_mReadSlaveReg27(baseaddr, 0);
  xil_printf("   - read %d from register 27 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 28 )
  {
    xil_printf("   - slave register 27 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 29 to slave register 28 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg28(baseaddr, 0, 29);
  Reg32Value = PETRI_PLB_mReadSlaveReg28(baseaddr, 0);
  xil_printf("   - read %d from register 28 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 29 )
  {
    xil_printf("   - slave register 28 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 30 to slave register 29 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg29(baseaddr, 0, 30);
  Reg32Value = PETRI_PLB_mReadSlaveReg29(baseaddr, 0);
  xil_printf("   - read %d from register 29 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 30 )
  {
    xil_printf("   - slave register 29 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 31 to slave register 30 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg30(baseaddr, 0, 31);
  Reg32Value = PETRI_PLB_mReadSlaveReg30(baseaddr, 0);
  xil_printf("   - read %d from register 30 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 31 )
  {
    xil_printf("   - slave register 30 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 32 to slave register 31 word 0\n\r");
  PETRI_PLB_mWriteSlaveReg31(baseaddr, 0, 32);
  Reg32Value = PETRI_PLB_mReadSlaveReg31(baseaddr, 0);
  xil_printf("   - read %d from register 31 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 32 )
  {
    xil_printf("   - slave register 31 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - slave register write/read passed\n\n\r");

  /*
   * Enable all possible interrupts and clear interrupt status register(s)
   */
  xil_printf("Interrupt controller test...\n\r");
  Reg32Value = PETRI_PLB_mReadReg(baseaddr, PETRI_PLB_INTR_IPISR_OFFSET);
  xil_printf("   - IP (user logic) interrupt status : 0x%08x\n\r", Reg32Value);
  xil_printf("   - clear IP (user logic) interrupt status register\n\r");
  PETRI_PLB_mWriteReg(baseaddr, PETRI_PLB_INTR_IPISR_OFFSET, Reg32Value);
  Reg32Value = PETRI_PLB_mReadReg(baseaddr, PETRI_PLB_INTR_DISR_OFFSET);
  xil_printf("   - Device (peripheral) interrupt status : 0x%08x\n\r", Reg32Value);
  xil_printf("   - clear Device (peripheral) interrupt status register\n\r");
  PETRI_PLB_mWriteReg(baseaddr, PETRI_PLB_INTR_DISR_OFFSET, Reg32Value);
  xil_printf("   - enable all possible interrupt(s)\n\r");
  PETRI_PLB_EnableInterrupt(baseaddr_p);
  xil_printf("   - write/read interrupt register passed\n\n\r");

  return XST_SUCCESS;
}
