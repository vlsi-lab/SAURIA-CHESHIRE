/*
 * Copyright 2025 PoliTo
 * Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
 * SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
 *
 * Author: Tommaso Terzano <tommaso.terzano@polito.it> 
 *                         <tommaso.terzano@gmail.com>
 *  
 * Info: Single convolutional layer application for the SAURIA-Cheshire demonstrator.
 */

#include "regs/cheshire.h"
#include "dif/clint.h"
#include "dif/uart.h"
#include "dif/dma.h"
//#include "dif/dif_rv_plic.h"
#include "params.h"
#include "util.h"
#include <stdio.h>
#include <string.h>
#include "sauria_regs.h"
#include "sauria_io.h"
#include "sauria_util.h"
#include "sauria.h"
#include "sauria_approx_output_tensor_0_conv1.h"
#include "sauria_input_tensor_conv1.h"
#include "sauria_weight_tensor_conv1.h"

#define DEBUG

/* Macro for printf, enable it by defining DEBUG */
#ifdef DEBUG
  #define PRINTF(str) uart_write_str(&__base_uart, str, strlen(str)); \ 
                    uart_write_flush(&__base_uart);
#else
  #define PRINTF(...)
#endif

/* SAURIA base address define */
#define SAURIA_REG_START_ADDRESS 0x40000000
#define SAURIA_MEM_START_ADDRESS 0x45000000

/* Global IRQ enable address */
#define GLOBAL_IRQ_ENABLE_ADDRESS 0x00001808

/* External interrupt enable */
#define EXTERNAL_IRQ_ENABLE_ADDRESS 0x00000800

/* Variables */
char ret_reg_hex_conv[13]; 
char ret_mem_hex_conv[13];
uint32_t ret_mem;
uint32_t ret_reg;

int main(void) {
    /* Immediately return an error if DMA is not present */
    CHECK_ASSERT(-1, chs_hw_feature_present(CHESHIRE_HW_FEATURES_DMA_BIT));

    /* Set up the UART communication */
    uint32_t rtc_freq = *reg32(&__base_regs, CHESHIRE_RTC_FREQ_REG_OFFSET);
    uint64_t reset_freq = clint_get_core_freq(rtc_freq, 2500);
    uart_init(&__base_uart, reset_freq, __BOOT_BAUDRATE);

    /* Write SAURIA's IFMAP SRMA via the iDMA */
    int8_t *inputs_ptr = &input_tensor[0][0][0];
    sys_dma_memcpy((uintptr_t)(void *)(SAURIA_MEM_START_ADDRESS + SAURIA_SRAMA_OFFSET), (uintptr_t)(void *)inputs_ptr, sizeof(AB_c*A_h_padded*A_w_padded));

    ret_mem = *(volatile uint32_t *) (SAURIA_MEM_START_ADDRESS + SAURIA_SRAMA_OFFSET);

    /* Convert the value to a hex-formatted string */
    uint32_to_hex_string(ret_mem, ret_mem_hex_conv);  // Convert integer to hex string

    /* Print the value */
    PRINTF(ret_mem_hex_conv);
    
    return 0;
}
