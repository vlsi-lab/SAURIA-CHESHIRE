/*
 * Copyright 2025 PoliTo
 * Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
 * SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
 *
 * Author: Tommaso Terzano <tommaso.terzano@polito.it> 
 *                         <tommaso.terzano@gmail.com>
 *  
 * Info: Pseudo-DMA transfer functions.
 */

#include <stdio.h>
#include <stdint.h>

int dma_run(uint32_t src_ptr, uint32_t dst_ptr, uint32_t size_transfer_byte);
