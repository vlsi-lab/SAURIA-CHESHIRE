# Copyright 2025 PoliTo
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
#
# Author: Tommaso Terzano <tommaso.terzano@polito.it> 
#                         <tommaso.terzano@gmail.com>
#
# Info: Makefile of the SAURIA-Cheshire-demo project

SCD_ROOT := $(shell realpath .)
BENDER	 ?= bender -d $(SCD_ROOT)

# Build the hw
all:

include sauria_demo.mk
