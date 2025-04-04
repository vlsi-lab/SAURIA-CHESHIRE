# Copyright 2025 PoliTo
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Tommaso Terzano <tommaso.terzano@polito.it> 
#                         <tommaso.terzano@gmail.com>
#
# Info: Makefile library of the SAURIA-Cheshire-demo project

# Sauria demo project defines
SAURIA_DEMO_ROOT    ?= $(shell realpath .)
SAURIA_DEMO_HW_DIR  := $(SAURIA_DEMO_ROOT)/hw
SAURIA_DEMO_SW_DIR  := $(SAURIA_DEMO_ROOT)/sw
SAURIA_DEMO_TGT_DIR := $(SAURIA_DEMO_ROOT)/target
SAURIA_DEMO_XIL_DIR := $(SAURIA_DEMO_TGT_DIR)/fpga
SAURIA_DEMO_SIM_DIR := $(SAURIA_DEMO_TGT_DIR)/sim
SAURIA_DEMO_VSIM_DIR := $(SAURIA_DEMO_TGT_DIR)/sim/vsim

# Cheshire defines
CHS_ROOT  := $(shell bender path cheshire)

# Regint defines
REGINTFC_ROOT  := $(shell bender path register_interface)

# SAURIA defines
SAURIA_ROOT := $(SAURIA_DEMO_ROOT)/vendor/sauria
SAURIA_PULP_ROOT := $(SAURIA_ROOT)/pulp_platform
SAURIA_RTL_ROOT := $(SAURIA_ROOT)/RTL
SAURIA_INCLUDE_DIRS := +incdir+$(SAURIA_PULP_ROOT)/common_cells/include +incdir+$(SAURIA_PULP_ROOT)/axi/include

# Sauria demo include directories
SAURIA_DEMO_INCLUDE_DIR := +incdir+$(SAURIA_DEMO_ROOT)/hw/include \
													 +incdir+$(SAURIA_PULP_ROOT)/axi/include \
													 +incdir+$(SAURIA_PULP_ROOT)/common_cells/include \
													 +incdir+$(CHS_ROOT)/hw/include \
													 +incdir+$(REGINTFC_ROOT)/include
	
# Tools defines
BENDER_ROOT ?= $(SAURIA_DEMO_ROOT)/.bender

# Correct GCC directory
CHS_SW_GCC_BINROOT = /software/riscv/riscv64-multilib-newlib/bin

# Include the Cheshire Makefile
include $(shell bender path cheshire)/cheshire.mk

set-up:
	bender update

update-sauria:
	# Removing pre-existing Sauria folder in vendor
	rm -rf $(SAURIA_ROOT)
	cd $(SAURIA_DEMO_ROOT)/vendor && git clone https://github.com/sromeo98/sauria.git
	cd $(SAURIA_ROOT) && git submodule update --init --recursive

.PHONY: hw-chs
hw-chs:
	# Compiling Cheshire
	$(MAKE) -B chs-hw-all
	$(MAKE) -B chs-sim-all
	cd $(SAURIA_DEMO_VSIM_DIR) && vsim -c -do "set BINARY ../../../sw/tests/helloworld.spm.elf; set BOOTMODE 0; set PRELMODE 1; source $(CHS_ROOT)/target/sim/vsim/compile.cheshire_soc.tcl; quit" > chs_compile_log.txt

.PHONY: hw-sauria
hw-sauria:
	# Compiling SAURIA core
	cd $(SAURIA_DEMO_VSIM_DIR) && vlog $(SAURIA_PULP_ROOT)/axi/src/axi_pkg.sv
	cd $(SAURIA_DEMO_VSIM_DIR) && vlog $(SAURIA_RTL_ROOT)/src/sauria_pkg.sv
	
	# Preprocess the file list
	cd $(SAURIA_DEMO_VSIM_DIR) && sed "s|\$${PULP_DIR}|$(SAURIA_PULP_ROOT)|g" $(SAURIA_RTL_ROOT)/filelist.f > prepreprocessed_filelist.f
	cd $(SAURIA_DEMO_VSIM_DIR) && sed "s|\$${RTL_DIR}|$(SAURIA_RTL_ROOT)|g" prepreprocessed_filelist.f > preprocessed_filelist.f
	
	# Compile the file list
	cd $(SAURIA_DEMO_VSIM_DIR) && vlog -f preprocessed_filelist.f $(SAURIA_INCLUDE_DIRS)

.PHONY: hw-demo
hw-demo:
	
	# Compiling the SAURIA demo project
	cd $(SAURIA_DEMO_VSIM_DIR) && vlog $(CHS_ROOT)/hw/cheshire_pkg.sv
	cd $(SAURIA_DEMO_VSIM_DIR) && vlog $(CHS_ROOT)/target/sim/src/tb_cheshire_pkg.sv
	cd $(SAURIA_DEMO_VSIM_DIR) && vlog $(SAURIA_DEMO_ROOT)/hw/include/sauria_demo_pkg.sv $(SAURIA_DEMO_INCLUDE_DIR)
	cd $(SAURIA_DEMO_VSIM_DIR) && vlog $(SAURIA_DEMO_ROOT)/hw/axi_intfc_bridge.sv $(SAURIA_DEMO_INCLUDE_DIR)
	cd $(SAURIA_DEMO_VSIM_DIR) && vlog $(SAURIA_DEMO_ROOT)/hw/axi_lite_intfc_bridge.sv $(SAURIA_DEMO_INCLUDE_DIR)
	cd $(SAURIA_DEMO_VSIM_DIR) && vlog $(SAURIA_DEMO_ROOT)/hw/sauria_demo_soc.sv $(SAURIA_DEMO_INCLUDE_DIR)
	cd $(SAURIA_DEMO_VSIM_DIR) && vlog $(SAURIA_DEMO_ROOT)/target/sim/src/fixture_sauria_demo_soc.sv $(SAURIA_DEMO_INCLUDE_DIR)
	cd $(SAURIA_DEMO_VSIM_DIR) && vlog $(SAURIA_DEMO_ROOT)/target/sim/src/tb_sauria_demo_soc.sv $(SAURIA_DEMO_INCLUDE_DIR)

.PHONY: sw
sw:
	@if ls $(CHS_ROOT)/sw/lib/sauria 1> /dev/null 2>&1; then \
		rm $(CHS_ROOT)/sw/lib/sauria_*; \
	fi

	@if ls $(CHS_ROOT)/sw/tests/sauria_* 1> /dev/null 2>&1; then \
		rm $(CHS_ROOT)/sw/tests/sauria_*; \
	fi

	find $(SAURIA_DEMO_SW_DIR)/lib/ -type f -exec cp {} $(CHS_ROOT)/sw/include \;

	cp $(SAURIA_DEMO_SW_DIR)/data/* $(CHS_ROOT)/sw/include
	cp $(SAURIA_DEMO_SW_DIR)/src/* $(CHS_ROOT)/sw/tests

	$(MAKE) -B chs-sw-all

BIN_SEL ?= 0

.PHONY: sim-gui
sim-gui:
	@cd $(SAURIA_DEMO_VSIM_DIR) && vsim -gui -do "set BIN_SEL $(BIN_SEL); source start.sauria_demo.tcl; run -all" &

.PHONY: hw-all
hw-all: hw-chs hw-sauria hw-demo