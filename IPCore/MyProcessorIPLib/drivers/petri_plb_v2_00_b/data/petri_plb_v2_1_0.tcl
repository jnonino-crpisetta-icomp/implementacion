##############################################################################
## Filename:          D:\ProyectoIntegrador\trunk\Implementacion\IPCore\MyProcessorIPLib/drivers/petri_plb_v2_00_b/data/petri_plb_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Thu Sep 13 15:24:17 2012 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "petri_plb" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
