##############################################################################
## Filename:          D:\ProyectoIntegrador\trunk\Implementacion\IPCore\MyProcessorIPLib/drivers/petri_axi_v2_01_b/data/petri_axi_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Wed Sep 12 20:32:10 2012 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "petri_axi" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
