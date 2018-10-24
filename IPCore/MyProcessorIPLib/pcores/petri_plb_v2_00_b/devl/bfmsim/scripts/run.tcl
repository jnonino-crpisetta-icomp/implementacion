##############################################################################
## Filename:          D:\ProyectoIntegrador\trunk\Implementacion\IPCore\MyProcessorIPLib/pcores/petri_plb_v2_00_b/devl/bfmsim/scripts/run.tcl
## Description:       ISim Run Script - modify with your discretion
## Date:              Thu Sep 13 15:24:17 2012 (by Create and Import Peripheral Wizard)
##############################################################################


# Load Wave window
source ../../scripts/wave.tcl

# Load BFL
source ../../scripts/sample.tcl

# Start system clock and reset system
isim force add /bfm_system/sys_clk 1 -time 0 ns, -value 0 -time 10 ns -repeat 20 ns
isim force add /bfm_system/sys_reset 1 -time 0 ns -value 0 -time 200 ns

# Run test time
run 100 us

