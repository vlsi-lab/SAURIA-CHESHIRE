# Copyright 2025 PoliTo
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
# Author: Tommaso Terzano <tommaso.terzano@polito.it> 
#                         <tommaso.terzano@gmail.com>
 
# Info: Tcl script to start the simulation of the SAURIA demonstrator.

set TESTBENCH tb_sauria_demo_soc

set CHS_ROOT [exec bender path cheshire]

# Handle PROJECT variable
if {![info exists PROJECT]} {
     set PROJECT "helloworld"  ;# Default value if not set
 }

set BINARY "${CHS_ROOT}/sw/tests/${PROJECT}.spm.elf"

set BOOTMODE 0
set PRELMODE 1

# Set full path to c++ compiler.
if { ![info exists CXX_PATH] } {
    if { ![info exists CXX] } {
        if { ![info exists ::env(CXX)] } {
            set CXX "g++"
        } else {
            set CXX $::env(CXX)
        }
    }
    set CXX_PATH [exec which $CXX]
}

# Set voptargs only if not already set to make overridable.
# Default on fast simulation flags.
if {![info exists VOPTARGS]} {
    # TODO: what does this do?
    set VOPTARGS "-O1 +acc" 
}

set flags "-voptargs=-permissive -suppress 12110 -suppress 3009 -suppress 8386 -suppress 1323 -suppress 2912 -suppress 2732 -error 7 -cpppath ${CXX_PATH}"

set pargs ""
if {[info exists BOOTMODE]} { append pargs "+BOOTMODE=${BOOTMODE} " }
if {[info exists PRELMODE]} { append pargs "+PRELMODE=${PRELMODE} " }
if {[info exists BINARY]}   { append pargs "+BINARY=${BINARY} " }
if {[info exists IMAGE]}    { append pargs "+IMAGE=${IMAGE} " }

eval "vsim -c ${TESTBENCH} -t 1ps -vopt -voptargs=\"${VOPTARGS}\"" ${pargs} ${flags}

eval "add wave -position insertpoint  \
sim:/tb_sauria_demo_soc/fix/dut/sauria_cfg_port_slv/aw_addr \
sim:/tb_sauria_demo_soc/fix/dut/sauria_cfg_port_slv/aw_prot \
sim:/tb_sauria_demo_soc/fix/dut/sauria_cfg_port_slv/aw_valid \
sim:/tb_sauria_demo_soc/fix/dut/sauria_cfg_port_slv/aw_ready \
sim:/tb_sauria_demo_soc/fix/dut/sauria_cfg_port_slv/w_data \
sim:/tb_sauria_demo_soc/fix/dut/sauria_cfg_port_slv/w_strb \
sim:/tb_sauria_demo_soc/fix/dut/sauria_cfg_port_slv/w_valid \
sim:/tb_sauria_demo_soc/fix/dut/sauria_cfg_port_slv/w_ready \
sim:/tb_sauria_demo_soc/fix/dut/sauria_cfg_port_slv/b_resp \
sim:/tb_sauria_demo_soc/fix/dut/sauria_cfg_port_slv/b_valid \
sim:/tb_sauria_demo_soc/fix/dut/sauria_cfg_port_slv/b_ready \
sim:/tb_sauria_demo_soc/fix/dut/sauria_cfg_port_slv/ar_addr \
sim:/tb_sauria_demo_soc/fix/dut/sauria_cfg_port_slv/ar_prot \
sim:/tb_sauria_demo_soc/fix/dut/sauria_cfg_port_slv/ar_valid \
sim:/tb_sauria_demo_soc/fix/dut/sauria_cfg_port_slv/ar_ready \
sim:/tb_sauria_demo_soc/fix/dut/sauria_cfg_port_slv/r_data \
sim:/tb_sauria_demo_soc/fix/dut/sauria_cfg_port_slv/r_resp \
sim:/tb_sauria_demo_soc/fix/dut/sauria_cfg_port_slv/r_valid \
sim:/tb_sauria_demo_soc/fix/dut/sauria_cfg_port_slv/r_ready "

eval "add wave -position insertpoint  \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/aw_id \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/aw_addr \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/aw_len \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/aw_size \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/aw_burst \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/aw_lock \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/aw_cache \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/aw_prot \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/aw_qos \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/aw_region \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/aw_atop \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/aw_user \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/aw_valid \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/aw_ready \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/w_data \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/w_strb \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/w_last \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/w_user \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/w_valid \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/w_ready \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/b_id \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/b_resp \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/b_user \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/b_valid \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/b_ready \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/ar_id \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/ar_addr \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/ar_len \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/ar_size \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/ar_burst \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/ar_lock \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/ar_cache \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/ar_prot \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/ar_qos \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/ar_region \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/ar_user \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/ar_valid \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/ar_ready \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/r_id \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/r_data \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/r_resp \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/r_last \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/r_user \
sim:/tb_sauria_demo_soc/fix/dut/sauria_mem_port_slv/r_valid"

eval "run -all"

set StdArithNoWarnings 1
set NumericStdNoWarnings 1