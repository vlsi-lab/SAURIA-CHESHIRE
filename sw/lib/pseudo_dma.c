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

#include <pseudo_dma.h>

/* Pseudo-DMA 1D trasfer function */
int dma_run(uint32_t src_ptr, uint32_t dst_ptr, uint32_t size_transfer_byte){
  /* Check if the pointers are valid and the size is non-zero */
  if (!src_ptr || !dst_ptr || !size_transfer_byte) {
    return -1;
  }

  volatile uint32_t *src = (volatile uint32_t *)src_ptr;
  volatile uint32_t *dst = (volatile uint32_t *)dst_ptr;

  for (uint32_t i = 0; i < size_transfer_byte; i++) {
    dst[i] = src[i];
  }

  return 0;
}
