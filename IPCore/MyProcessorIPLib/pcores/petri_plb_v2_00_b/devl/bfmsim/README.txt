------------------------------------------------------------------------------
--
-- BFM simulation Guide
--
------------------------------------------------------------------------------


Requirements
------------------------------------------------------------------------------
- ModelSim 6.6d or later 
- EDK BFM package installed
- ISE simulation libraries compiled (COMPXLIB)
- EDK simulation libraries compiled (COMPEDKLIB)


BFM Simulation Command Line Flow
------------------------------------------------------------------------------
1. Open any command/shell window, e.g. DOS, and go to this
   bfmsim directory.

2. Open the bfm_sim_cmd.make file, e.g. in DOS edit, to edit
   the following two stwitches if no (or incorrect) value is provided:

   ISELIB_OPT = -X <ISE simulation library path>
   EDKLIB_OPT = -E <EDK simulation library path>

   Save and close the make file, no other edits are required.

3. Type command 'make -f bfm_sim_cmd.make sim' (without the single quotes)
   to start BFM simulation.


BFM Simulation XPS Flow
------------------------------------------------------------------------------

1. Open this bfm_system.xmp project in XPS.

2. Click Project -> Project Options... to open up the Project Options
   dialog and specify the following options:

   - Device and Repository -
     * select the Architecture, Device Size, Package and Grade you desired
       in the Target Device group.
     * no other changes are necessary.

   - Hierarchy and Flow -
     * accept all defaults, no change.

   - HDL and Simulation -
     * select the simulator you desire in the Simulator Compile Script group.
     * specify EDK Library and Xilinx Library paths in the Simulation Libraries
       Path group if they are blank.
     * make sure VHDL is selected in the HDL group.
     * make sure Behavioral is selected in the Simulation Models group.

3. Click Simulation -> Generate Simulation HDL Files in XPS to generate the BFM   simulation platform. 

4. Click on Simulation -> Launch HDL Simulator to launch the simulator.


Documentation
------------------------------------------------------------------------------
Please refer to the following documents for details of BFM simulation in EDK:
- <EDK_Install>/third_party/doc/OpbToolKit.pdf
- <EDK_Install>/third_party/doc/PlbToolKit.pdf
- <EDK_Install>/doc/bfm_simulation.pdf
- <EDK_Install>/doc/ps_ug.pdf chapter 8 Simulation in EDK


