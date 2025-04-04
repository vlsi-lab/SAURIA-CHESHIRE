# Copyright 2025 PoliTo
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
# Author: Tommaso Terzano <tommaso.terzano@polito.it> 
#                         <tommaso.terzano@gmail.com>
 
# Info: Tcl script to start the simulation of the SAURIA demonstrator.

set TESTBENCH tb_sauria_demo_soc

set CHS_ROOT [exec bender path cheshire]

# Handle BIN_SEL variable
if {![info exists BIN_SEL]} {
     set BIN_SEL 0  ;# Default value if not set
 }

switch $BIN_SEL {
    0 {
        set BINARY "${CHS_ROOT}/sw/tests/helloworld.spm.elf"
    }
    1 {
        set BINARY "${CHS_ROOT}/sw/tests/sauria_test.spm.elf"
    }
    2 {
        set BINARY "${CHS_ROOT}/sw/tests/sauria_conv_single_layer.spm.elf"
    }
    default {
        puts "Error: Invalid BIN_SEL value: $BIN_SEL"
        exit 1
    }
}

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

set StdArithNoWarnings 1
set NumericStdNoWarnings 1