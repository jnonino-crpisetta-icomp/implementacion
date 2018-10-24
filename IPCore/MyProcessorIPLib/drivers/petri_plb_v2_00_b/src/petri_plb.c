/*****************************************************************************
* Filename:          D:\ProyectoIntegrador\trunk\Implementacion\IPCore\MyProcessorIPLib/drivers/petri_plb_v2_00_b/src/petri_plb.c
* Version:           2.00.b
* Description:       petri_plb Driver Source File
* Date:              Thu Sep 13 15:24:17 2012 (by Create and Import Peripheral Wizard)
*****************************************************************************/


/***************************** Include Files *******************************/

#include "petri_plb.h"

/************************** Function Definitions ***************************/

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
void PETRI_PLB_EnableInterrupt(void * baseaddr_p)
{
  Xuint32 baseaddr;
  baseaddr = (Xuint32) baseaddr_p;

  /*
   * Enable all interrupt source from user logic.
   */
  PETRI_PLB_mWriteReg(baseaddr, PETRI_PLB_INTR_IPIER_OFFSET, 0x00000001);

  /*
   * Enable all possible interrupt sources from device.
   */
  PETRI_PLB_mWriteReg(baseaddr, PETRI_PLB_INTR_DIER_OFFSET,
    INTR_TERR_MASK
    | INTR_DPTO_MASK
    | INTR_IPIR_MASK
    );

  /*
   * Set global interrupt enable.
   */
  PETRI_PLB_mWriteReg(baseaddr, PETRI_PLB_INTR_DGIER_OFFSET, INTR_GIE_MASK);
}

/**
 *
 * Example interrupt controller handler for PETRI_PLB device.
 * This is to show example of how to toggle write back ISR to clear interrupts.
 *
 * @param   baseaddr_p is the base address of the PETRI_PLB device.
 *
 * @return  None.
 *
 * @note    None.
 *
 */
void PETRI_PLB_Intr_DefaultHandler(void * baseaddr_p)
{
  Xuint32 baseaddr;
  Xuint32 IntrStatus;
Xuint32 IpStatus;
  baseaddr = (Xuint32) baseaddr_p;

  /*
   * Get status from Device Interrupt Status Register.
   */
  IntrStatus = PETRI_PLB_mReadReg(baseaddr, PETRI_PLB_INTR_DISR_OFFSET);

  xil_printf("Device Interrupt! DISR value : 0x%08x \n\r", IntrStatus);

  /*
   * Verify the source of the interrupt is the user logic and clear the interrupt
   * source by toggle write baca to the IP ISR register.
   */
  if ( (IntrStatus & INTR_IPIR_MASK) == INTR_IPIR_MASK )
  {
    xil_printf("User logic interrupt! \n\r");
    IpStatus = PETRI_PLB_mReadReg(baseaddr, PETRI_PLB_INTR_IPISR_OFFSET);
    PETRI_PLB_mWriteReg(baseaddr, PETRI_PLB_INTR_IPISR_OFFSET, IpStatus);
  }

}

