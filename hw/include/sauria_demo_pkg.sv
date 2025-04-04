/*
 * Copyright 2025 PoliTo
 * Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
 * SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
 *
 * Author: Tommaso Terzano <tommaso.terzano@polito.it> 
 *                         <tommaso.terzano@gmail.com>
 *  
 * Info: Package for the SAURIA demonstrator, contains functions and parameters for Cheshire integration
 */

package sauria_demo_pkg;

  `include "cheshire/typedef.svh"

  import cheshire_pkg::*;
  
  localparam byte_bt RegSauriaIdx  = 0;
  localparam doub_bt RegSauriaBase = 'h40000000;
  localparam doub_bt RegSauriaSize = 'h05000000;
  localparam doub_bt RegSauriaEnd  = RegSauriaBase + RegSauriaSize;

  localparam byte_bt MemSauriaIdx  = 0;
  localparam doub_bt MemSauriaBase = 'h45000000;
  localparam doub_bt MemSauriaSize = 'h05000000;
  localparam doub_bt MemSauriaEnd  = MemSauriaBase + MemSauriaSize;

  /* This function returns a Cheshire configuration. */
  function automatic cheshire_pkg::cheshire_cfg_t gen_cheshire_cfg();
    cheshire_pkg::cheshire_cfg_t ret = cheshire_pkg::DefaultCfg;
    
    /* These are needed otherwise cheshire won't communicate to external units */
    ret.AxiExtNumSlv = 1;
    ret.AxiExtNumRules = 1;
    ret.RegExtNumSlv = 1;
    ret.RegExtNumRules = 1;

    /* A memory map is also needed */
    ret.RegExtRegionIdx   [0] = RegSauriaIdx;
    ret.RegExtRegionStart [0] = RegSauriaBase;
    ret.RegExtRegionEnd   [0] = RegSauriaEnd;
    ret.AxiExtRegionIdx   [0] = MemSauriaIdx;
    ret.AxiExtRegionStart [0] = MemSauriaBase;
    ret.AxiExtRegionEnd   [0] = MemSauriaEnd;
    ret.NumExtInIntrs         = 1;

    return ret;
  endfunction
  
endpackage
