/*
 * Copyright 2025 PoliTo
 * Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
 * SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
 *
 * Author: Tommaso Terzano <tommaso.terzano@polito.it> 
 *                         <tommaso.terzano@gmail.com>
 *  
 * Info: Test of the SAURIA-Cheshire demostrator.
 */

#include "regs/cheshire.h"
#include "dif/clint.h"
#include "dif/uart.h"
#include "params.h"
#include "util.h"
#include "sauria_regs.h"
#include "sauria_util.h"
#include <stdio.h>
#include <string.h>

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

/* Variables */
char ret_reg_hex_conv[13]; 
char ret_mem_hex_conv[13];
uint32_t ret_mem;
uint32_t ret_reg;

int main(void) {

    /* Set up the UART communication */
    uint32_t rtc_freq = *reg32(&__base_regs, CHESHIRE_RTC_FREQ_REG_OFFSET);
    uint64_t reset_freq = clint_get_core_freq(rtc_freq, 2500);
    uart_init(&__base_uart, reset_freq, __BOOT_BAUDRATE);

    /* Write a value into one of SAURIA's register */
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_REGS_IDX1_OFFSET) = 0x1 ;

    /* Write a value into SAURIA's RAM-A */
    *(volatile uint32_t *) (SAURIA_MEM_START_ADDRESS + SAURIA_SRAMA_OFFSET) = 0xDEADBEEF ;

    /* Read the value from the register and the memory */
    ret_reg = *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_REGS_IDX1_OFFSET);
    ret_mem = *(volatile uint32_t *) (SAURIA_MEM_START_ADDRESS + SAURIA_SRAMA_OFFSET);

    /* Convert the values to a hex-formatted string */
    uint32_to_hex_string(ret_reg, ret_reg_hex_conv);  // Convert integer to hex string
    uint32_to_hex_string(ret_mem, ret_mem_hex_conv);  // Convert integer to hex string

    /* Print the values */
    PRINTF(ret_mem_hex_conv);
    PRINTF(ret_reg_hex_conv);

    return 0;
}
