onerror {resume}


divider add {BFM System Level Ports}
wave add -radix bin /bfm_system/sys_clk
wave add -radix bin /bfm_system/sys_reset

divider add {PLBv46 Bus Master Signals}
wave add -radix bin /bfm_system/plb_bus_M_request
wave add -radix bin /bfm_system/plb_bus_M_priority
wave add -radix bin /bfm_system/plb_bus_M_busLock
wave add -radix bin /bfm_system/plb_bus_M_RNW
wave add -radix hex /bfm_system/plb_bus_M_BE
wave add -radix bin /bfm_system/plb_bus_M_MSize
wave add -radix bin /bfm_system/plb_bus_M_size
wave add -radix bin /bfm_system/plb_bus_M_type
wave add -radix bin /bfm_system/plb_bus_M_TAttribute
wave add -radix bin /bfm_system/plb_bus_M_lockErr
wave add -radix bin /bfm_system/plb_bus_M_abort
wave add -radix hex /bfm_system/plb_bus_M_UABus
wave add -radix hex /bfm_system/plb_bus_M_ABus
wave add -radix hex /bfm_system/plb_bus_M_wrDBus
wave add -radix bin /bfm_system/plb_bus_M_wrBurst
wave add -radix bin /bfm_system/plb_bus_M_rdBurst
wave add -radix bin /bfm_system/plb_bus_PLB_MAddrAck
wave add -radix bin /bfm_system/plb_bus_PLB_MSSize
wave add -radix bin /bfm_system/plb_bus_PLB_MRearbitrate
wave add -radix bin /bfm_system/plb_bus_PLB_MTimeout
wave add -radix bin /bfm_system/plb_bus_PLB_MBusy
wave add -radix bin /bfm_system/plb_bus_PLB_MRdErr
wave add -radix bin /bfm_system/plb_bus_PLB_MWrErr
wave add -radix bin /bfm_system/plb_bus_PLB_MIRQ
wave add -radix hex /bfm_system/plb_bus_PLB_MRdDBus
wave add -radix hex /bfm_system/plb_bus_PLB_MRdWdAddr
wave add -radix bin /bfm_system/plb_bus_PLB_MRdDAck
wave add -radix bin /bfm_system/plb_bus_PLB_MRdBTerm
wave add -radix bin /bfm_system/plb_bus_PLB_MWrDAck
wave add -radix bin /bfm_system/plb_bus_PLB_MWrBTerm

divider add {PLBv46 Bus Slave Signals}
wave add -radix hex /bfm_system/plb_bus_PLB_ABus
wave add -radix hex /bfm_system/plb_bus_PLB_UABus
wave add -radix bin /bfm_system/plb_bus_PLB_PAValid
wave add -radix bin /bfm_system/plb_bus_PLB_SAValid
wave add -radix bin /bfm_system/plb_bus_PLB_rdPrim
wave add -radix bin /bfm_system/plb_bus_PLB_wrPrim
wave add -radix bin /bfm_system/plb_bus_PLB_masterID
wave add -radix bin /bfm_system/plb_bus_PLB_abort
wave add -radix bin /bfm_system/plb_bus_PLB_busLock
wave add -radix bin /bfm_system/plb_bus_PLB_RNW
wave add -radix hex /bfm_system/plb_bus_PLB_BE
wave add -radix bin /bfm_system/plb_bus_PLB_MSize
wave add -radix bin /bfm_system/plb_bus_PLB_size
wave add -radix bin /bfm_system/plb_bus_PLB_type
wave add -radix bin /bfm_system/plb_bus_PLB_lockErr
wave add -radix hex /bfm_system/plb_bus_PLB_wrDBus
wave add -radix bin /bfm_system/plb_bus_PLB_wrBurst
wave add -radix bin /bfm_system/plb_bus_PLB_rdBurst
wave add -radix bin /bfm_system/plb_bus_PLB_wrPendReq
wave add -radix bin /bfm_system/plb_bus_PLB_rdPendReq
wave add -radix bin /bfm_system/plb_bus_PLB_wrPendPri
wave add -radix bin /bfm_system/plb_bus_PLB_rdPendPri
wave add -radix bin /bfm_system/plb_bus_PLB_reqPri
wave add -radix bin /bfm_system/plb_bus_PLB_TAttribute
wave add -radix bin /bfm_system/plb_bus_Sl_addrAck
wave add -radix bin /bfm_system/plb_bus_Sl_SSize
wave add -radix bin /bfm_system/plb_bus_Sl_wait
wave add -radix bin /bfm_system/plb_bus_Sl_rearbitrate
wave add -radix bin /bfm_system/plb_bus_Sl_wrDAck
wave add -radix bin /bfm_system/plb_bus_Sl_wrComp
wave add -radix bin /bfm_system/plb_bus_Sl_wrBTerm
wave add -radix hex /bfm_system/plb_bus_Sl_rdDBus
wave add -radix hex /bfm_system/plb_bus_Sl_rdWdAddr
wave add -radix bin /bfm_system/plb_bus_Sl_rdDAck
wave add -radix bin /bfm_system/plb_bus_Sl_rdComp
wave add -radix bin /bfm_system/plb_bus_Sl_rdBTerm
wave add -radix bin /bfm_system/plb_bus_Sl_MBusy
wave add -radix bin /bfm_system/plb_bus_Sl_MWrErr
wave add -radix bin /bfm_system/plb_bus_Sl_MRdErr
wave add -radix bin /bfm_system/plb_bus_Sl_MIRQ

divider add {BFM Synch Bus Signals}
wave add -radix hex /bfm_system/synch_bus/synch_bus/FROM_SYNCH_OUT
wave add -radix hex /bfm_system/synch_bus/synch_bus/TO_SYNCH_IN

divider add {petri_plb Peripheral Interface Signals}
wave add -radix bin /bfm_system/my_core/my_core/uut/SPLB_Clk
wave add -radix bin /bfm_system/my_core/my_core/uut/SPLB_Rst
wave add -radix hex /bfm_system/my_core/my_core/uut/PLB_ABus
wave add -radix hex /bfm_system/my_core/my_core/uut/PLB_UABus
wave add -radix bin /bfm_system/my_core/my_core/uut/PLB_PAValid
wave add -radix bin /bfm_system/my_core/my_core/uut/PLB_SAValid
wave add -radix bin /bfm_system/my_core/my_core/uut/PLB_rdPrim
wave add -radix bin /bfm_system/my_core/my_core/uut/PLB_wrPrim
wave add -radix bin /bfm_system/my_core/my_core/uut/PLB_masterID
wave add -radix bin /bfm_system/my_core/my_core/uut/PLB_abort
wave add -radix bin /bfm_system/my_core/my_core/uut/PLB_busLock
wave add -radix bin /bfm_system/my_core/my_core/uut/PLB_RNW
wave add -radix hex /bfm_system/my_core/my_core/uut/PLB_BE
wave add -radix bin /bfm_system/my_core/my_core/uut/PLB_MSize
wave add -radix bin /bfm_system/my_core/my_core/uut/PLB_size
wave add -radix bin /bfm_system/my_core/my_core/uut/PLB_type
wave add -radix bin /bfm_system/my_core/my_core/uut/PLB_lockErr
wave add -radix hex /bfm_system/my_core/my_core/uut/PLB_wrDBus
wave add -radix bin /bfm_system/my_core/my_core/uut/PLB_wrBurst
wave add -radix bin /bfm_system/my_core/my_core/uut/PLB_rdBurst
wave add -radix bin /bfm_system/my_core/my_core/uut/PLB_wrPendReq
wave add -radix bin /bfm_system/my_core/my_core/uut/PLB_rdPendReq
wave add -radix bin /bfm_system/my_core/my_core/uut/PLB_wrPendPri
wave add -radix bin /bfm_system/my_core/my_core/uut/PLB_rdPendPri
wave add -radix bin /bfm_system/my_core/my_core/uut/PLB_reqPri
wave add -radix bin /bfm_system/my_core/my_core/uut/PLB_TAttribute
wave add -radix bin /bfm_system/my_core/my_core/uut/Sl_addrAck
wave add -radix bin /bfm_system/my_core/my_core/uut/Sl_SSize
wave add -radix bin /bfm_system/my_core/my_core/uut/Sl_wait
wave add -radix bin /bfm_system/my_core/my_core/uut/Sl_rearbitrate
wave add -radix bin /bfm_system/my_core/my_core/uut/Sl_wrDAck
wave add -radix bin /bfm_system/my_core/my_core/uut/Sl_wrComp
wave add -radix bin /bfm_system/my_core/my_core/uut/Sl_wrBTerm
wave add -radix hex /bfm_system/my_core/my_core/uut/Sl_rdDBus
wave add -radix hex /bfm_system/my_core/my_core/uut/Sl_rdWdAddr
wave add -radix bin /bfm_system/my_core/my_core/uut/Sl_rdDAck
wave add -radix bin /bfm_system/my_core/my_core/uut/Sl_rdComp
wave add -radix bin /bfm_system/my_core/my_core/uut/Sl_rdBTerm
wave add -radix bin /bfm_system/my_core/my_core/uut/Sl_MBusy
wave add -radix bin /bfm_system/my_core/my_core/uut/Sl_MWrErr
wave add -radix bin /bfm_system/my_core/my_core/uut/Sl_MRdErr
wave add -radix bin /bfm_system/my_core/my_core/uut/Sl_MIRQ
wave add -radix bin /bfm_system/my_core/my_core/uut/IP2INTC_Irpt

divider add {Peripheral Internal Signals}
wave add -radix bin /bfm_system/my_core/my_core/uut/ipif_Bus2IP_Clk
wave add -radix bin /bfm_system/my_core/my_core/uut/ipif_Bus2IP_Reset
wave add -radix hex /bfm_system/my_core/my_core/uut/ipif_IP2Bus_Data
wave add -radix bin /bfm_system/my_core/my_core/uut/ipif_IP2Bus_WrAck
wave add -radix bin /bfm_system/my_core/my_core/uut/ipif_IP2Bus_RdAck
wave add -radix bin /bfm_system/my_core/my_core/uut/ipif_IP2Bus_Error
wave add -radix hex /bfm_system/my_core/my_core/uut/ipif_Bus2IP_Addr
wave add -radix hex /bfm_system/my_core/my_core/uut/ipif_Bus2IP_Data
wave add -radix bin /bfm_system/my_core/my_core/uut/ipif_Bus2IP_RNW
wave add -radix hex /bfm_system/my_core/my_core/uut/ipif_Bus2IP_BE
wave add -radix bin /bfm_system/my_core/my_core/uut/ipif_Bus2IP_CS
wave add -radix bin /bfm_system/my_core/my_core/uut/ipif_Bus2IP_RdCE
wave add -radix bin /bfm_system/my_core/my_core/uut/ipif_Bus2IP_WrCE
wave add -radix bin /bfm_system/my_core/my_core/uut/rst_Bus2IP_Reset
wave add -radix bin /bfm_system/my_core/my_core/uut/rst_IP2Bus_WrAck
wave add -radix bin /bfm_system/my_core/my_core/uut/rst_IP2Bus_Error
wave add -radix bin /bfm_system/my_core/my_core/uut/intr_IPIF_Reg_Interrupts
wave add -radix bin /bfm_system/my_core/my_core/uut/intr_IPIF_Lvl_Interrupts
wave add -radix hex /bfm_system/my_core/my_core/uut/intr_IP2Bus_Data
wave add -radix bin /bfm_system/my_core/my_core/uut/intr_IP2Bus_WrAck
wave add -radix bin /bfm_system/my_core/my_core/uut/intr_IP2Bus_RdAck
wave add -radix bin /bfm_system/my_core/my_core/uut/intr_IP2Bus_Error
wave add -radix bin /bfm_system/my_core/my_core/uut/user_Bus2IP_RdCE
wave add -radix bin /bfm_system/my_core/my_core/uut/user_Bus2IP_WrCE
wave add -radix hex /bfm_system/my_core/my_core/uut/user_IP2Bus_Data
wave add -radix bin /bfm_system/my_core/my_core/uut/user_IP2Bus_RdAck
wave add -radix bin /bfm_system/my_core/my_core/uut/user_IP2Bus_WrAck
wave add -radix bin /bfm_system/my_core/my_core/uut/user_IP2Bus_Error
wave add -radix bin /bfm_system/my_core/my_core/uut/user_IP2Bus_IntrEvent

divider add {User Logic Interface Signals}
wave add -radix bin /bfm_system/my_core/my_core/uut/user_logic_i/Bus2IP_Clk
wave add -radix bin /bfm_system/my_core/my_core/uut/user_logic_i/Bus2IP_Reset
wave add -radix hex /bfm_system/my_core/my_core/uut/user_logic_i/Bus2IP_Data
wave add -radix hex /bfm_system/my_core/my_core/uut/user_logic_i/Bus2IP_BE
wave add -radix bin /bfm_system/my_core/my_core/uut/user_logic_i/Bus2IP_RdCE
wave add -radix bin /bfm_system/my_core/my_core/uut/user_logic_i/Bus2IP_WrCE
wave add -radix hex /bfm_system/my_core/my_core/uut/user_logic_i/IP2Bus_Data
wave add -radix bin /bfm_system/my_core/my_core/uut/user_logic_i/IP2Bus_RdAck
wave add -radix bin /bfm_system/my_core/my_core/uut/user_logic_i/IP2Bus_WrAck
wave add -radix bin /bfm_system/my_core/my_core/uut/user_logic_i/IP2Bus_Error
wave add -radix bin /bfm_system/my_core/my_core/uut/user_logic_i/IP2Bus_IntrEvent

divider add {User Logic Internal Slave Space Signals}

divider add {User Logic Internal Interrupt Signals}

