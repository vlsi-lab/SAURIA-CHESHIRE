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
 #include "params.h"
 #include "util.h"
 #include <stdio.h>
 #include <string.h>
 #include <math.h>
 #include <stdbool.h>
 #include "sauria_regs.h"
 #include "sauria_util.h"
 #include "sauria.h"
 #include "approx_output_tensor_0.h"
 #include "input_tensor.h"
 #include "weight_tensor.h"
 
 #define DEBUG
 
 /* Macro for printf, enable it by defining DEBUG */
 #ifdef DEBUG
   #define PRINTF(str) do { \
    volatile char *vstr = str; \
    uart_write_str(&__base_uart, vstr, strlen(vstr)); \
    uart_write_flush(&__base_uart); \
   } while (0)
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
 sauria_t sauria; 
 //int32_t psums[C_c][C_h][C_w] __attribute__ ((aligned (4))) = {0};

 /* Pseudo-DMA 1D trasfer function */
 int dma_run(void *dst_ptr, const void *src_ptr, uint32_t size_transfer_byte, uint32_t dst_inc) {
  if (!src_ptr || !dst_ptr || !size_transfer_byte) {
      return -1;
  }

  volatile uint8_t *src = (volatile uint8_t *)src_ptr;
  volatile uint8_t *dst = (volatile uint8_t *)dst_ptr;

  for (uint32_t i = 0; i < size_transfer_byte; i++) {
      dst[i*dst_inc] = src[i];
  }

  return 0;
}

uint16_t ceil_int(double num) {
  uint16_t result = (uint16_t)num; 
  if (num > (double)result) {
      result++;
  }
  return result;
}


 int main(void) {
    /* Immediately return an error if DMA is not present */
    CHECK_ASSERT(-1, chs_hw_feature_present(CHESHIRE_HW_FEATURES_DMA_BIT));

    /* Set up the UART communication */
    uint32_t rtc_freq = *reg32(&__base_regs, CHESHIRE_RTC_FREQ_REG_OFFSET);
    uint64_t reset_freq = clint_get_core_freq(rtc_freq, 2500);
    uart_init(&__base_uart, reset_freq, __BOOT_BAUDRATE);

    /* Write SAURIA's IFMAP SRMA via the iDMA */
    int8_t *inputs_ptr = &input_tensor[0][0][0];
    //sys_dma_memcpy((uintptr_t)(void *)(SAURIA_MEM_START_ADDRESS + SAURIA_SRAMA_OFFSET), (uintptr_t)(void *)inputs_ptr, sizeof(AB_c*A_h_padded*A_w_padded));
    
    uint32_to_hex_string(AB_c, ret_mem);  // Convert integer to hex string
    PRINTF(ret_mem);

    dma_run((void *)(SAURIA_MEM_START_ADDRESS + SAURIA_SRAMA_OFFSET), 
            (const void *)inputs_ptr, 
            AB_c * A_h_padded * A_w_padded,
            1);

    for (int i = 0; i < C_c; i++)
    {
      int8_t *weights_ptr = &weight_tensor[i][0][0][0];// + i*AB_c*B_h*B_w
      uint32_t *sramb_ptr = (uint32_t *)(SAURIA_MEM_START_ADDRESS + SAURIA_SRAMB_OFFSET+i);
      dma_run((const void *)sramb_ptr, 
              (const void *)weights_ptr, 
              (AB_c*B_h*B_w),
              C_c);
    }

    // ------------------------------------------------------------
    // CONFIGURATION REGISTERS' PARAMETERS
    // ------------------------------------------------------------

    //Control & Status

    bool start = false; //Starts a computation. Self-clearing

    bool done = false; //High when SAURIA finishes a computation. Can be toggled by writing a 1

    bool idle = false; //SAURIA is idle

    bool ready = false; //SAURIA is ready to start a new computation

    bool auto_restart = false; //Auto-restart (unsupported atm)

    bool mem_switch = false; //Forces the double-buffering system to swap. Self-clearing

    bool mem_keep_A = false; //Disables bouble-buffering on SRAMA, to keep the same data on all computations

    bool mem_keep_B = false; //Disables bouble-buffering on SRAMB, to keep the same data on all computations

    bool mem_keep_C = false; //Disables bouble-buffering on SRAMC, to keep the same data on all computations

    bool soft_rst = false; //Soft reset for all SAURIA FSMs

    bool global_ien = true; //Global interrupt enable

    bool done_ien = true; //Interrupt enable for SAURIA's done signal

    bool done_intr_status = false; //Interrupt status flag - Can be toggled by writing a 1

    //Main FSM

    uint16_t incntlim = (1*B_h*B_w*AB_c - 1); //Total number of MACs of the computation
    
    int X_used;
    if(C_c < X){
      X_used = C_c;
    }else if (C_c == X){
      X_used = X;
    }else{
      for(int x = X; x > 0; x--){
          if(C_c%x == 0){
              X_used = x;
              break;
          }
      }
    }
    uint16_t act_reps = (int)(ceil_int((double)C_c/(double)X_used)); //Number of ifmap tiling iterations

    int Y_used;
    if(C_w < Y){
      Y_used = C_w;
    }else if (C_w == Y){
      Y_used = Y;
    }else{
      for(int y = Y; y > 0; y--){
          if(C_w%y == 0){
              Y_used = y;
              break;
          }
      }
    }
    uint16_t wei_reps = (int)(ceil_int((double)C_w/(double)Y_used)*ceil_int((double)C_h/(double)1)); //Number of weight tiling iterations

    uint8_t neg_thres = 0; //Zero negligence threshold for the systolic array PEs

    uint16_t res_mask = (1 << 16) - 1; //Mask for the multiplier to select result precision
    //2^16 - 1 = 65535 - > 1111 1111 1111 1111
    
    uint8_t appr_mask = 255; //Mask for the multiplier to select result approximation

    bool sram_deepsleep = false;

    bool sram_powergate = false;

    //Ifmap Feeder

    //Effective kernel size (dilation)
    uint16_t B_w_eff = (1 + (B_w - 1)*d);
    uint16_t B_h_eff = (1 + (B_h - 1)*d);
    
    uint16_t xlim; //X counter limit
    //Aligned activations condition => Only when 1x1 convolution and no d or ss is applied
    if ((s == 1) && (d == 1) && (B_h == 1) && (B_w == 1) && ((AB_c % SRAMA_N) == 0) && ((Y_used % SRAMA_N) == 0)){
          xlim = Y_used;
    }else{
          xlim = ((1 + (Y_used - 1)*s) + B_w_eff + 1 - (B_w_eff % 2) + SRAMA_N);
    }

    uint16_t xstep = SRAMA_N; //X counter step

    uint16_t ylim = (A_w_padded*B_h_eff); //Y counter limit

    uint16_t ystep = (A_w_padded*d); //Y counter step

    uint16_t chlim = (A_w_padded*A_h_padded*AB_c); //Channel counter limit

    uint16_t chstep = (A_w_padded*A_h_padded); //Channel counter step

    uint16_t til_xlim = (int)((ceil_int((double)C_w/(double)Y_used))*Y_used*s); //Tiling X counter limit

    uint16_t til_xstep = (Y_used*s); //Tiling X counter step

    uint16_t til_ylim = (int)((ceil_int(C_h/1))*A_w_padded*1*s); //Tiling Y counter limit

    uint16_t til_ystep = (A_w_padded*1*s); //Tiling Y counter step

    //Dilation pattern generation
    uint64_t  Dil_pat = 0; //64-bit dilation pattern describing the horizontal shape of the convolution kernel
    for (int i = 0; i < DILP_W; i++) {
          if ((i % d == 0) && ((i / d) < B_w)) {
            Dil_pat |= (1ULL << (DILP_W - 1 - i));  // Set the corresponding bit to 1
          }
    }

    // Generate row mask and array
    uint8_t rows_active = 0; //Pattern of active rows (each bit represents one row out of 8)
    bool rows_active_arr[Y];
    memset(rows_active_arr, 0, sizeof(rows_active_arr)); // Initialize array to false (0)
    for (int j = 0; j < Y; j++) {
        if (j < Y_used) {
            rows_active |= (1 << (Y - 1 - j));  // Set the corresponding bit to 1
            rows_active_arr[j] = true;          // Set the array element to 1 (true)
        }
    }

    //Local woffs
    uint8_t lwoffs[Y]; //Local word offset for Rows [0:7]
    for (int i = 0; i < Y; i++) {
        lwoffs[i] = rows_active_arr[i] ? i * s : 0;
    }

    //Weight Feeder

    uint16_t wlim = (C_c*B_w*B_h*AB_c); //Weight counter limit

    uint16_t wstep = C_c; //Weight counter step

    //Aligned weights condition => feeder optimization   
    bool waligned = (((C_c % SRAMB_N) == 0) && (X_used == SRAMB_N)); //Aligned weights flag - Indicate the weights are perfectly aligned in SRAM memory reads

    uint16_t klim; //Out-Channel counter limit
    if (!waligned) {
      klim = (SRAMB_N+1);
    }else{
      klim = 1;
    }
    
    uint16_t kstep = SRAMB_N; //Out-Channel counter step

    uint16_t til_klim = C_c; //Tiling Out-Channel counter limit

    uint16_t til_kstep = X_used; //Tiling Out-Channel counter step

    // Generate column mask and array
    uint8_t cols_active = 0; //Pattern of active columns (each bit represents one column out of 8)
    bool cols_active_arr[X];
    memset(cols_active_arr, 0, sizeof(cols_active_arr)); // Initialize array to false (0)
    for (int i = 0; i < X; i++) {
        if (i < X_used) {
            cols_active |= (1 << (X - 1 - i));  // Set the corresponding bit to 1
            cols_active_arr[i] = true;          // Set the array element to 1 (true)
        }
    }

    //PS Manager

    //Internal tiles for SAURIA execution
    uint16_t X_tiles = (int)(ceil_int((double)C_w/(double)Y_used));
    uint16_t Y_tiles = C_h;
    uint16_t K_tiles = (C_c/X_used);
      
    //Number of context switches
    uint16_t ncontexts = (X_tiles*Y_tiles*K_tiles); //Number of computation contexts (total tiling iterations)

    uint16_t cxlim = (Y_used + SRAMC_N); //X counter limit for partial sums

    uint16_t cxstep = SRAMC_N; //X counter step for partial sums

    uint16_t cklim = (C_w*C_h*X_used); //Out-Channel counter limit for partial sums

    uint16_t ckstep = (C_w*C_h); //Out-Channel counter step for partial sums

    uint16_t til_cylim = (C_w*C_h); //Tiling Y counter limit for partial sums
    uint16_t til_cystep = Y_used; //Tiling Y counter step for partial sums

    uint16_t til_cklim = (C_w*C_h*C_c); //Tiling Out-Channel counter limit for partial sums

    uint16_t til_ckstep = (C_w*C_h*X_used); //Tiling Out-Channel counter step for partial sums

    uint8_t inactive_cols = (X-X_used); //Number of inactive columns

    bool preload_en = false; //Preload enable - Set to 1 to preload the MAC Accumulators with the initial data on the SRAM

    // ------------------------------------------------------------
    // WRITE CONFIGURATION REGISTERS
    // ------------------------------------------------------------

    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_REGS_IDX1_OFFSET) = 1;
    
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_REGS_IDX2_OFFSET) = 1;

    uint32_t reg = 0;
    reg = bitfield_field32_write(reg, SAURIA_CFG_CON_INCNTLIM_FIELD, incntlim);
    reg = bitfield_field32_write(reg, SAURIA_CFG_CON_ACT_REPS_FIELD, act_reps);
    reg = bitfield_field32_write(reg, SAURIA_CFG_CON_WEI_REPS_1_FIELD, wei_reps);
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_CON_IDX0_OFFSET) = reg;

    uint16_t wei_reps_shifted = wei_reps >> 1;
    reg = bitfield_field32_write(reg, SAURIA_CFG_CON_WEI_REPS_2_FIELD, wei_reps_shifted);
    reg = bitfield_field32_write(reg, SAURIA_CFG_CON_THRES_FIELD, neg_thres);
    reg = bitfield_field32_write(reg, SAURIA_CFG_CON_RES_MASK_FIELD, res_mask);
    reg = bitfield_field32_write(reg, SAURIA_CFG_CON_APPR_MASK_1_FIELD, appr_mask);
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_CON_IDX1_OFFSET) = reg;

    uint8_t appr_mask_shifted = appr_mask >> 4;
    reg = bitfield_field32_write(reg, SAURIA_CFG_CON_APPR_MASK_2_FIELD, appr_mask_shifted);
    reg = bitfield_bit32_write(reg, SAURIA_CFG_CON_SRAM_DEEPSLEEP_BIT, sram_deepsleep);
    reg = bitfield_bit32_write(reg, SAURIA_CFG_CON_SRAM_POWERGATE_BIT, sram_powergate);
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_CON_IDX2_OFFSET) = reg;

    reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_XLIM_FIELD, xlim);
    reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_XSTEP_FIELD, xstep);
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_ACT_IDX0_OFFSET) = reg;

    reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_YLIM_FIELD, ylim);
    reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_YSTEP_FIELD, ystep);
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_ACT_IDX1_OFFSET) = reg;

    reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_CHLIM_FIELD, chlim);
    reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_CHSTEP_FIELD, chstep);
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_ACT_IDX2_OFFSET) = reg;

    reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_TIL_XLIM_FIELD, til_xlim);
    reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_TIL_XSTEP_FIELD, til_xstep);
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_ACT_IDX3_OFFSET) = reg;

    reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_TIL_YLIM_FIELD, til_ylim);
    reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_TIL_YSTEP_FIELD, til_ystep);
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_ACT_IDX4_OFFSET) = reg;

    reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_DIL_PAT_BE_FIELD, Dil_pat);
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_ACT_IDX5_OFFSET) = reg;

    uint32_t dil_pat_shifted = Dil_pat >> 32;
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_ACT_IDX6_OFFSET) = dil_pat_shifted;

    reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_ROWS_ACTIVE_BE_FIELD, rows_active);
    reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_LOC_WOFFS0_FIELD, lwoffs[0]);
    reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_LOC_WOFFS1_FIELD, lwoffs[1]);
    reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_LOC_WOFFS2_FIELD, lwoffs[2]);
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_ACT_IDX7_OFFSET) = reg;

    reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_LOC_WOFFS3_FIELD, lwoffs[3]);
    reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_LOC_WOFFS4_FIELD, lwoffs[4]);
    reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_LOC_WOFFS5_FIELD, lwoffs[5]);
    reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_LOC_WOFFS6_FIELD, lwoffs[6]);
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_ACT_IDX8_OFFSET) = reg;

    reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_LOC_WOFFS7_FIELD, lwoffs[7]);
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_ACT_IDX9_OFFSET) = reg;
  
    reg = bitfield_field32_write(reg, SAURIA_CFG_WEI_WLIM_FIELD, wlim);
    reg = bitfield_field32_write(reg, SAURIA_CFG_WEI_WSTEP_FIELD, wstep);
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_WEI_IDX0_OFFSET) = reg;

    reg = bitfield_field32_write(reg, SAURIA_CFG_WEI_AUXLIM_FIELD, klim);
    reg = bitfield_field32_write(reg, SAURIA_CFG_WEI_AUXSTEP_FIELD, kstep);
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_WEI_IDX1_OFFSET) = reg;

    reg = bitfield_field32_write(reg, SAURIA_CFG_WEI_TIL_KLIM_FIELD, til_klim);
    reg = bitfield_field32_write(reg, SAURIA_CFG_WEI_TIL_KSTEP_FIELD, til_kstep);
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_WEI_IDX2_OFFSET) = reg;

    reg = bitfield_field32_write(reg, SAURIA_CFG_WEI_COLS_ACTIVE_BE_FIELD, cols_active);
    reg = bitfield_bit32_write(reg, SAURIA_CFG_WEI_WALIGNED_BIT, waligned);
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_WEI_IDX3_OFFSET) = reg;

    reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_NCONTEXTS_FIELD, ncontexts);
    reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_CXLIM_FIELD, cxlim);
    reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_CXSTEP_1_FIELD, cxstep);
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_OUT_IDX0_OFFSET) = reg;

    uint16_t cxstep_shifted = cxstep >> 2;
    reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_CXSTEP_2_FIELD, cxstep_shifted);
    reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_CKLIM_FIELD, cklim);
    reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_CKSTEP_1_FIELD, ckstep);
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_OUT_IDX1_OFFSET) = reg;

    uint16_t ckstep_shifted = ckstep >> 4;
    reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_CKSTEP_2_FIELD, ckstep_shifted);
    reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_TIL_CYLIM_FIELD, til_cylim);
    reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_TIL_CYSTEP_1_FIELD, til_cystep);
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_OUT_IDX2_OFFSET) = reg;

    uint16_t til_cystep_shifted = til_cystep >> 6;
    reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_TIL_CYSTEP_2_FIELD, til_cystep_shifted);
    reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_TIL_CKLIM_FIELD, til_cklim);
    reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_TIL_CKSTEP_1_FIELD, til_ckstep);
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_OUT_IDX3_OFFSET) = reg;
    
    uint8_t til_ckstep_shifted = til_ckstep >> 8;
    reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_TIL_CKSTEP_2_FIELD, til_ckstep_shifted);
    reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_INACTIVE_COLS_FIELD, inactive_cols);
    reg = bitfield_bit32_write(reg, SAURIA_CFG_OUT_PRELOAD_EN_BIT, preload_en);
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_OUT_IDX4_OFFSET) = reg;
    
    start = true;
    reg = bitfield_bit32_write(reg, SAURIA_CFG_REGS_IDX0_START_BIT, start);
    reg = bitfield_bit32_write(reg, SAURIA_CFG_REGS_IDX0_AUTO_RESTART_BIT, auto_restart);
    reg = bitfield_bit32_write(reg, SAURIA_CFG_REGS_IDX0_MEM_SWITCH_BIT, mem_switch);
    reg = bitfield_bit32_write(reg, SAURIA_CFG_REGS_IDX0_MEM_KEEP_A_BIT, mem_keep_A);
    reg = bitfield_bit32_write(reg, SAURIA_CFG_REGS_IDX0_MEM_KEEP_B_BIT, mem_keep_B);
    reg = bitfield_bit32_write(reg, SAURIA_CFG_REGS_IDX0_MEM_KEEP_C_BIT, mem_keep_C);
    reg = bitfield_bit32_write(reg, SAURIA_CFG_REGS_IDX0_SOFT_RST_BIT, soft_rst);
    *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_REGS_IDX0_OFFSET) = reg;
  
    ret_mem = *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_REGS_IDX0_DONE_BIT);
    uint32_to_hex_string(ret_mem, ret_mem_hex_conv);  // Convert integer to hex string

    /* Print the values */
    PRINTF(ret_mem_hex_conv);

    while(ret_mem & 0x2 != 1)
    {
      ret_mem = *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_CFG_REGS_IDX0_DONE_BIT);
      uint32_to_hex_string(ret_mem, ret_mem_hex_conv);  // Convert integer to hex string

      /* Print the values */
      PRINTF(ret_mem_hex_conv);
    }
    int psums_size = (C_c*C_h*C_w);

    
    // int32_t *psums_ptr = &psums[0][0][0];    
    // // Read the results
    // dma_run((const void *)psums_ptr, 
    //         (void *)(SAURIA_MEM_START_ADDRESS + SAURIA_SRAMC_OFFSET), 
    //         psums_size,
    // 1);

    // Check for errors
    int errors = 0;
    int errors_hex_conv = 0;
    int index = 0;
    for (int out_ch = 0; out_ch < C_c; out_ch++) {
      for (int psums_h = 0; psums_h < C_h; psums_h++) {
          for (int psums_w = 0; psums_w < C_w; psums_w++) {
            
              index = out_ch*C_h*C_w + psums_h*C_w + psums_w;
              ret_mem = *(volatile uint32_t *) (SAURIA_REG_START_ADDRESS + SAURIA_SRAMC_OFFSET + index);
      
              if(ret_mem != output_tensor[out_ch][psums_h][psums_w]) {
                errors++;
              }  
          }
      }
    }

    uint32_to_hex_string(errors, errors_hex_conv);  // Convert integer to hex string

    /* Print the values */
    PRINTF(errors_hex_conv);

    return 0;
 }
 