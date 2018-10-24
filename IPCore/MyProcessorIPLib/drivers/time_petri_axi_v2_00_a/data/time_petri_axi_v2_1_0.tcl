##############################################################################
## Filename:          D:\ProyectoIntegrador\trunk\Implementacion\IPCore\MyProcessorIPLib/drivers/time_petri_axi_v2_00_a/data/time_petri_axi_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Sat Oct 06 14:05:07 2012 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "time_petri_axi" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
