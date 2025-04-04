#ifndef _SAURIA_H_
#define _SAURIA_H_

#include <stdint.h>
#include <math.h>
#include "mmio.h"

#define SAURIA_INTR EXT_INTR_0

#define X 8                                                          //SYSTOLIC ARRAY COLUMNS
#define Y 8                                                          //SYSTOLIC ARRAY ROWS
//#define C_h 6                                         //PSUMS ROWS
//#define C_w 6                                         //PSUMS COLUMNS
#define A_h 32                                                        //IFMAPS ROWS
#define A_w 32                                                       //IFMAPS COLUMNS
#define AB_c 3                                                      //INPUT CHANNELS
#define B_h 3                                                        //WEIGHTS ROWS
#define B_w 3                                                        //WEIGHTS COLUMNS
#define s 1                                                          //STRIDE
#define d 1                                                          //DILATION
#define p 1                                                          //PADDING (Sauria doesn't manage padding, so this is managed by the application)
#define A_h_padded (A_h + 2*p)                                       //IFMAPS ROWS PADDED (if p = 0 -> A_h_padded = A_h)
#define A_w_padded (A_w + 2*p)                                       //IFMAPS COLUMNS PADDED (if p = 0 -> A_w_padded = A_w)
//#define A_h (1 + (C_h - 1)*s + 1 + (B_h - 1)*d - 1)   //IFMAPS ROWS
//#define A_w (1 + (C_w - 1)*s + 1 + (B_w - 1)*d - 1)   //IFMAPS COLUMNS
#define C_h 32                                                        //PSUMS ROWS ((int)(floor((A_h + 2*p - B_h - (B_h-1)*(d-1))/s) + 1))
#define C_w 32                                                        //PSUMS COLUMNS ((int)(floor((A_w + 2*p - B_w - (B_w-1)*(d-1))/s) + 1))
#define C_c 16                                                        //OUTPUT CHANNELS 
#define SRAMA_W 128                                                  //SRAM A DATA WIDTH
#define IA_W 8                                                       //IFAMPS DATA WIDTH
#define SRAMA_N (SRAMA_W / IA_W)                                     //SRAM A WORDS PER ROW
#define SRAMB_W 256                                                  //SRAM B DATA WIDTH
#define IB_W 8                                                       //WEIGHTS DATA WIDTH
#define SRAMB_N (SRAMB_W / IB_W)                                     //SRAM B WORDS PER ROW
#define SRAMC_W 128                                                  //SRAM C DATA WIDTH
#define OC_W 32                                                      //PSUMS DATA WIDTH
#define SRAMC_N (SRAMC_W/OC_W)                                     //SRAM C WORDS PER ROW
#define DILP_W 64                                                    //DILATION PARAMETER WIDTH

/*
  Aw = (1 + (Cw - 1)*s + 1 + (Bw - 1)*d - 1)
  Ah = (1 + (Ch - 1)*s + 1 + (Bh - 1)*d - 1)
  #define C_h ((A_h-B_h)/s+1)         //PSUMS ROWS
  #define C_w ((A_w-B_w)/s+1)         //PSUMS COLUMNS
  #define C_h (floor((A_h + 2*p - B_h - (B_h-1)*(d-1))/s) + 1)         //PSUMS ROWS  #include <math.h>
  #define C_w (floor((A_w + 2*p - B_w - (B_w-1)*(d-1))/s) + 1)         //PSUMS COLUMNS

*/

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Initialization parameters for SAURIA peripheral control registers..
 *
 */
typedef struct sauria {
  /**
   * The base address for the soc_ctrl hardware registers.
   */
  mmio_region_t base_addr;
} sauria_t;

// ---------------------------------------------------------------------------
// REGISTER REGION : Control & Status
// ---------------------------------------------------------------------------

/**
 * Write config register 0x0 and start a computation if start -> 1.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param start Starts a computation. Self-clearing.
 * @param auto_restart Auto-restart (unsupported atm).
 * @param mem_switch Forces the double-buffering system to swap. Self-clearing.
 * @param mem_keep_A Disables double-buffering on SRAMA, to keep the same data on all computations.
 * @param mem_keep_B Disables double-buffering on SRAMB, to keep the same data on all computations.
 * @param mem_keep_C Disables double-buffering on SRAMC, to keep the same data on all computations.
 * @param soft_rst Soft reset for all SAURIA FSMs.
 */
void sauria_start(const sauria_t *sauria, bool start, bool auto_restart, bool mem_switch, bool mem_keep_A, bool mem_keep_B, bool mem_keep_C, bool soft_rst);

/**
 * Read config register 0x0.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_read_reg0x0(const sauria_t *sauria);

/**
 * Read done bit from config register 0x0.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
bool sauria_done(const sauria_t *sauria);

/**
 * Read idle bit from config register 0x0.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
bool sauria_idle(const sauria_t *sauria);

/**
 * Read ready bit from config register 0x0.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
bool sauria_ready(const sauria_t *sauria);

/**
 * Write config register 0x4.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param global_ien Global interrupt enable
 */
void sauria_global_ien(const sauria_t *sauria, bool global_ien);

/**
 * Read config register 0x4 (global_ien bit).
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
bool sauria_read_global_ien(const sauria_t *sauria);

/**
 * Write config register 0x8.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param done_ien Done interrupt enable
 */
void sauria_done_ien(const sauria_t *sauria, bool done_ien);

/**
 * Read config register 0x8 (done_ien bit).
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
bool sauria_read_done_ien(const sauria_t *sauria);

/**
 * Write config register 0xC.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param done_intr_status Done interrupt status.
 */
void sauria_done_interrupt_status(const sauria_t *sauria, bool done_intr_status);

/**
 * Read Interrupt status flag from config register 0xC.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
bool sauria_read_done_interrupt_status(const sauria_t *sauria);

/**
 * Read status flags for the different FSMs (debugging) from config register 0x10.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_status_flags(const sauria_t *sauria);

/**
 * Read cycle counter (32-bit counter that reports the total cycles spent in the previous computation) from config register 0x14.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_cycle_counter(const sauria_t *sauria);

/**
 * Read stalls counter (32-bit counter that reports the number of stall cycles in the previous computation) from config register 0x18.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_stalls_counter(const sauria_t *sauria);

// ---------------------------------------------------------------------------
// REGISTER REGION : Main FSM
// ---------------------------------------------------------------------------

/**
 * Write config register 0x200.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param incntlim Total number of MACs of the computation
 * @param act_reps Number of ifmap tiling iterations
 * @param wei_reps Number of weight tiling iterations
 */
void sauria_reg0x200(const sauria_t *sauria, uint16_t incntlim, uint16_t act_reps, uint16_t wei_reps);

/**
 * Read config register 0x200.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_read_reg0x200(const sauria_t *sauria);

/**
 * Write config register 0x204.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param wei_reps Number of weight tiling iterations
 * @param neg_thres Zero negligence threshold for the systolic array PEs
 * @param res_mask Mask for the multiplier to select result precision
 * @param appr_mask Mask for the multiplier to select result approximation
 */
void sauria_reg0x204(const sauria_t *sauria, uint16_t wei_reps, uint8_t neg_thres, uint16_t res_mask, uint8_t appr_mask);

/**
 * Read config register 0x204.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_read_reg0x204(const sauria_t *sauria);

/**
 * Write config register 0x208.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param appr_mask Mask for the multiplier to select result approximation
 * @param sram_deepsleep
 * @param sram_powergate
 */
void sauria_reg0x208(const sauria_t *sauria, uint8_t appr_mask, bool sram_deepsleep, bool sram_powergate);

/**
 * Read config register 0x208.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_read_reg0x208(const sauria_t *sauria);

// ---------------------------------------------------------------------------
// REGISTER REGION : Ifmap Feeder
// ---------------------------------------------------------------------------

/**
 * Write config register 0x400.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param xlim X counter limit
 * @param xstep X counter step
 */
void sauria_reg0x400(const sauria_t *sauria, uint16_t xlim, uint16_t xstep);

/**
 * Read config register 0x400.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_read_reg0x400(const sauria_t *sauria);

/**
 * Write config register 0x404.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param ylim Y counter limit
 * @param ystep Y counter step
 */
void sauria_reg0x404(const sauria_t *sauria, uint16_t ylim, uint16_t ystep);

/**
 * Read config register 0x404.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_read_reg0x404(const sauria_t *sauria);

/**
 * Write config register 0x408.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param chlim Channel counter limit
 * @param chstep Channel counter step
 */
void sauria_reg0x408(const sauria_t *sauria, uint16_t chlim, uint16_t chstep);

/**
 * Read config register 0x408.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_read_reg0x408(const sauria_t *sauria);

/**
 * Write config register 0x40C.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param til_xlim Tiling X counter limit
 * @param til_xstep Tiling X counter step
 */
void sauria_reg0x40C(const sauria_t *sauria, uint16_t til_xlim, uint16_t til_xstep);

/**
 * Read config register 0x40C.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_read_reg0x40C(const sauria_t *sauria);

/**
 * Write config register 0x410.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param til_ylim Tiling Y counter limit
 * @param til_ystep Tiling Y counter step
 */
void sauria_reg0x410(const sauria_t *sauria, uint16_t til_ylim, uint16_t til_ystep);

/**
 * Read config register 0x410.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_read_reg0x410(const sauria_t *sauria);

/**
 * Write config register 0x414.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param dil_pat 64-bit dilation pattern describing the horizontal shape of the convolution kernel
 */
void sauria_reg0x414(const sauria_t *sauria, uint64_t dil_pat);

/**
 * Read config register 0x414.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_read_reg0x414(const sauria_t *sauria);

/**
 * Write config register 0x418.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param dil_pat 64-bit dilation pattern describing the horizontal shape of the convolution kernel
 */
void sauria_reg0x418(const sauria_t *sauria, uint64_t dil_pat);

/**
 * Read config register 0x418.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_read_reg0x418(const sauria_t *sauria);

/**
 * Write config register 0x41C.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param rows_active Pattern of active rows (each bit represents one row out of 8)
 * @param loc_woffs0 Local word offset for Row 0
 * @param loc_woffs1 Local word offset for Row 1
 * @param loc_woffs2 Local word offset for Row 2
 */
void sauria_reg0x41C(const sauria_t *sauria, uint8_t rows_active, uint8_t loc_woffs0, uint8_t loc_woffs1, uint8_t loc_woffs2);

/**
 * Read config register 0x41C.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_read_reg0x41C(const sauria_t *sauria);

/**
 * Write config register 0x420.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param loc_woffs3 Local word offset for Row 3
 * @param loc_woffs4 Local word offset for Row 4
 * @param loc_woffs5 Local word offset for Row 5
 * @param loc_woffs6 Local word offset for Row 6
 */
void sauria_reg0x420(const sauria_t *sauria, uint8_t loc_woffs3, uint8_t loc_woffs4, uint8_t loc_woffs5, uint8_t loc_woffs6);

/**
 * Read config register 0x420.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_read_reg0x420(const sauria_t *sauria);

/**
 * Write config register 0x424.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param loc_woffs7 Local word offset for Row 7
 */
void sauria_reg0x424(const sauria_t *sauria, uint8_t loc_woffs7);

/**
 * Read config register 0x424.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_read_reg0x424(const sauria_t *sauria);

// ---------------------------------------------------------------------------
// REGISTER REGION : Weight Feeder
// ---------------------------------------------------------------------------

/**
 * Write config register 0x600.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param wlim Weight counter limit
 * @param wstep Weight counter step
 */
void sauria_reg0x600(const sauria_t *sauria, uint16_t wlim, uint16_t wstep);

/**
 * Read config register 0x600.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_read_reg0x600(const sauria_t *sauria);

/**
 * Write config register 0x604.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param auxlim Out-Channel counter limit
 * @param auxstep Out-Channel counter step
 */
void sauria_reg0x604(const sauria_t *sauria, uint16_t auxlim, uint16_t auxstep);

/**
 * Read config register 0x604.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_read_reg0x604(const sauria_t *sauria);

/**
 * Write config register 0x608.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param til_klim Tiling Out-Channel counter limit
 * @param til_kstep Tiling Out-Channel counter step
 */
void sauria_reg0x608(const sauria_t *sauria, uint16_t til_klim, uint16_t til_kstep);

/**
 * Read config register 0x608.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_read_reg0x608(const sauria_t *sauria);

/**
 * Write config register 0x60C.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param cols_active Pattern of active columns (each bit represents one column out of 8)
 * @param waligned Aligned weights flag - Indicate the weights are perfectly aligned in SRAM memory reads
 */
void sauria_reg0x60C(const sauria_t *sauria, uint8_t cols_active, bool waligned);

/**
 * Read config register 0x60C.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_read_reg0x60C(const sauria_t *sauria);

// ---------------------------------------------------------------------------
// REGISTER REGION : PS Manager
// ---------------------------------------------------------------------------

/**
 * Write config register 0x800.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param ncontexts Number of computation contexts (total tiling iterations)
 * @param cxlim X counter limit for partial sums
 * @param cxstep X counter step for partial sums
 */
void sauria_reg0x800(const sauria_t *sauria, uint16_t ncontexts, uint16_t cxlim, uint16_t cxstep);

/**
 * Read config register 0x800.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_read_reg0x800(const sauria_t *sauria);

/**
 * Write config register 0x804.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param cxstep X counter step for partial sums
 * @param cklim Out-Channel counter limit for partial sums
 * @param ckstep Out-Channel counter step for partial sums
 */
void sauria_reg0x804(const sauria_t *sauria, uint16_t cxstep, uint16_t cklim, uint16_t ckstep);

/**
 * Read config register 0x804.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_read_reg0x804(const sauria_t *sauria);

/**
 * Write config register 0x808.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param ckstep Out-Channel counter step for partial sums
 * @param til_cylim Tiling Y counter limit for partial sums
 * @param til_cystep Tiling Y counter step for partial sums
 */
void sauria_reg0x808(const sauria_t *sauria, uint16_t ckstep, uint16_t til_cylim, uint16_t til_cystep);

/**
 * Read config register 0x808.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_read_reg0x808(const sauria_t *sauria);

/**
 * Write config register 0x80C.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param til_cystep Tiling Y counter step for partial sums
 * @param til_cklim Tiling Out-Channel counter limit for partial sums
 * @param til_ckstep Tiling Out-Channel counter step for partial sums
 */
void sauria_reg0x80C(const sauria_t *sauria, uint16_t til_cystep, uint16_t til_cklim, uint16_t til_ckstep);

/**
 * Read config register 0x80C.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_read_reg0x80C(const sauria_t *sauria);

/**
 * Write config register 0x810.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 * @param til_ckstep Tiling Out-Channel counter step for partial sums
 * @param inactive_cols Number of inactive columns
 * @param preload_en Preload enable - Set to 1 to preload the MAC Accumulators with the initial data on the SRAM
 */
void sauria_reg0x810(const sauria_t *sauria, uint16_t til_ckstep, uint8_t inactive_cols, bool preload_en);

/**
 * Read config register 0x810.
 * @param sauria Pointer to sauria_t represting the target SAURIA peripheral.
 */
uint32_t sauria_read_reg0x810(const sauria_t *sauria);

#ifdef __cplusplus
}
#endif

#endif // _SAURIA_H_