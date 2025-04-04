#ifndef _SAURIA_REG_DEFS_
#define _SAURIA_REG_DEFS_

#ifdef __cplusplus
extern "C" {
#endif
// Register width
#define SAURIA_PARAM_REG_WIDTH 32

// ------------------------------------------------------------
//SAURIA Control & Status registers
// ------------------------------------------------------------

//SAURIA Control signals
#define SAURIA_CFG_REGS_IDX0_OFFSET 0x0
#define SAURIA_CFG_REGS_IDX0_START_BIT 0
#define SAURIA_CFG_REGS_IDX0_DONE_BIT 1
#define SAURIA_CFG_REGS_IDX0_IDLE_BIT 2
#define SAURIA_CFG_REGS_IDX0_READY_BIT 3
#define SAURIA_CFG_REGS_IDX0_AUTO_RESTART_BIT 7
#define SAURIA_CFG_REGS_IDX0_MEM_SWITCH_BIT 16
#define SAURIA_CFG_REGS_IDX0_MEM_KEEP_A_BIT 17
#define SAURIA_CFG_REGS_IDX0_MEM_KEEP_B_BIT 18
#define SAURIA_CFG_REGS_IDX0_MEM_KEEP_C_BIT 19
#define SAURIA_CFG_REGS_IDX0_SOFT_RST_BIT 23

//SAURIA Global Interrupt Enable
#define SAURIA_CFG_REGS_IDX1_OFFSET 0x4
#define SAURIA_CFG_REGS_GLOBAL_IEN_BIT 0

//SAURIA IP Interrupt Enable
#define SAURIA_CFG_REGS_IDX2_OFFSET 0x8
#define SAURIA_CFG_REGS_DONE_IEN_BIT 0

//SAURIA IP Interrupt Status
#define SAURIA_CFG_REGS_IDX3_OFFSET 0xC
#define SAURIA_CFG_REGS_DONE_INTR_BIT 0

//SAURIA Status flags
#define SAURIA_CFG_REGS_IDX4_OFFSET 0x10

//SAURIA Cycle Counter
#define SAURIA_CFG_REGS_IDX5_OFFSET 0x14

//SAURIA Stalls Counter
#define SAURIA_CFG_REGS_IDX6_OFFSET 0x18


// ------------------------------------------------------------
//SAURIA Control Config region (Main FSM) registers
// ------------------------------------------------------------

//SAURIA Control signals
#define SAURIA_CFG_CON_IDX0_OFFSET 0x200
#define SAURIA_CFG_CON_INCNTLIM_MASK 0xffff
#define SAURIA_CFG_CON_INCNTLIM_OFFSET 0
#define SAURIA_CFG_CON_INCNTLIM_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_CON_INCNTLIM_MASK, .index = SAURIA_CFG_CON_INCNTLIM_OFFSET })
#define SAURIA_CFG_CON_ACT_REPS_MASK 0x7fff
#define SAURIA_CFG_CON_ACT_REPS_OFFSET 16
#define SAURIA_CFG_CON_ACT_REPS_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_CON_ACT_REPS_MASK, .index = SAURIA_CFG_CON_ACT_REPS_OFFSET })
#define SAURIA_CFG_CON_WEI_REPS_1_MASK 0x1   //WEI_REPS is splitted between 2 registers
#define SAURIA_CFG_CON_WEI_REPS_1_OFFSET 31
#define SAURIA_CFG_CON_WEI_REPS_1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_CON_WEI_REPS_1_MASK, .index = SAURIA_CFG_CON_WEI_REPS_1_OFFSET })
//--------------------------------------------------------

#define SAURIA_CFG_CON_IDX1_OFFSET 0x204
#define SAURIA_CFG_CON_WEI_REPS_2_MASK 0x2fff
#define SAURIA_CFG_CON_WEI_REPS_2_OFFSET 0
#define SAURIA_CFG_CON_WEI_REPS_2_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_CON_WEI_REPS_2_MASK, .index = SAURIA_CFG_CON_WEI_REPS_2_OFFSET })    
#define SAURIA_CFG_CON_THRES_MASK 0x3
#define SAURIA_CFG_CON_THRES_OFFSET 14
#define SAURIA_CFG_CON_THRES_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_CON_THRES_MASK, .index = SAURIA_CFG_CON_THRES_OFFSET })
#define SAURIA_CFG_CON_RES_MASK_MASK 0xfff
#define SAURIA_CFG_CON_RES_MASK_OFFSET 16
#define SAURIA_CFG_CON_RES_MASK_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_CON_RES_MASK_MASK, .index = SAURIA_CFG_CON_RES_MASK_OFFSET })
#define SAURIA_CFG_CON_APPR_MASK_1_MASK 0xf  //APPR_MASK is splitted between 2 registers
#define SAURIA_CFG_CON_APPR_MASK_1_OFFSET 28
#define SAURIA_CFG_CON_APPR_MASK_1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_CON_APPR_MASK_1_MASK, .index = SAURIA_CFG_CON_APPR_MASK_1_OFFSET })  
//--------------------------------------------------------

#define SAURIA_CFG_CON_IDX2_OFFSET 0x208
#define SAURIA_CFG_CON_APPR_MASK_2_MASK 0xf  
#define SAURIA_CFG_CON_APPR_MASK_2_OFFSET 0
#define SAURIA_CFG_CON_APPR_MASK_2_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_CON_APPR_MASK_2_MASK, .index = SAURIA_CFG_CON_APPR_MASK_2_OFFSET })
//--------------------------------------------------------
#define SAURIA_CFG_CON_SRAM_DEEPSLEEP_BIT 4
#define SAURIA_CFG_CON_SRAM_POWERGATE_BIT 5


// ------------------------------------------------------------
//SAURIA Activation config region registers
// ------------------------------------------------------------

#define SAURIA_CFG_ACT_IDX0_OFFSET 0x400
#define SAURIA_CFG_ACT_XLIM_MASK 0xffff
#define SAURIA_CFG_ACT_XLIM_OFFSET 0
#define SAURIA_CFG_ACT_XLIM_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_XLIM_MASK, .index = SAURIA_CFG_ACT_XLIM_OFFSET })
#define SAURIA_CFG_ACT_XSTEP_MASK 0xffff
#define SAURIA_CFG_ACT_XSTEP_OFFSET 16
#define SAURIA_CFG_ACT_XSTEP_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_XSTEP_MASK, .index = SAURIA_CFG_ACT_XSTEP_OFFSET })
//--------------------------------------------------------

#define SAURIA_CFG_ACT_IDX1_OFFSET 0x404
#define SAURIA_CFG_ACT_YLIM_MASK 0xffff
#define SAURIA_CFG_ACT_YLIM_OFFSET 0
#define SAURIA_CFG_ACT_YLIM_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_YLIM_MASK, .index = SAURIA_CFG_ACT_YLIM_OFFSET })    
#define SAURIA_CFG_ACT_YSTEP_MASK 0xffff
#define SAURIA_CFG_ACT_YSTEP_OFFSET 16
#define SAURIA_CFG_ACT_YSTEP_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_YSTEP_MASK, .index = SAURIA_CFG_ACT_YSTEP_OFFSET })  
//--------------------------------------------------------

#define SAURIA_CFG_ACT_IDX2_OFFSET 0x408
#define SAURIA_CFG_ACT_CHLIM_MASK 0xffff
#define SAURIA_CFG_ACT_CHLIM_OFFSET 0
#define SAURIA_CFG_ACT_CHLIM_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_CHLIM_MASK, .index = SAURIA_CFG_ACT_CHLIM_OFFSET })    
#define SAURIA_CFG_ACT_CHSTEP_MASK 0xffff
#define SAURIA_CFG_ACT_CHSTEP_OFFSET 16
#define SAURIA_CFG_ACT_CHSTEP_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_CHSTEP_MASK, .index = SAURIA_CFG_ACT_CHSTEP_OFFSET })
//--------------------------------------------------------   

#define SAURIA_CFG_ACT_IDX3_OFFSET 0x40C
#define SAURIA_CFG_ACT_TIL_XLIM_MASK 0xffff
#define SAURIA_CFG_ACT_TIL_XLIM_OFFSET 0
#define SAURIA_CFG_ACT_TIL_XLIM_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_TIL_XLIM_MASK, .index = SAURIA_CFG_ACT_TIL_XLIM_OFFSET })    
#define SAURIA_CFG_ACT_TIL_XSTEP_MASK 0xffff
#define SAURIA_CFG_ACT_TIL_XSTEP_OFFSET 16
#define SAURIA_CFG_ACT_TIL_XSTEP_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_TIL_XSTEP_MASK, .index = SAURIA_CFG_ACT_TIL_XSTEP_OFFSET })
//--------------------------------------------------------  

#define SAURIA_CFG_ACT_IDX4_OFFSET 0x410
#define SAURIA_CFG_ACT_TIL_YLIM_MASK 0xffff
#define SAURIA_CFG_ACT_TIL_YLIM_OFFSET 0
#define SAURIA_CFG_ACT_TIL_YLIM_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_TIL_YLIM_MASK, .index = SAURIA_CFG_ACT_TIL_YLIM_OFFSET })    
#define SAURIA_CFG_ACT_TIL_YSTEP_MASK 0xffff
#define SAURIA_CFG_ACT_TIL_YSTEP_OFFSET 16
#define SAURIA_CFG_ACT_TIL_YSTEP_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_TIL_YSTEP_MASK, .index = SAURIA_CFG_ACT_TIL_YSTEP_OFFSET })
//--------------------------------------------------------  

//SAURIA_CFG_ACT_DIL_PAT_BE_1
#define SAURIA_CFG_ACT_IDX5_OFFSET 0x414
#define SAURIA_CFG_ACT_DIL_PAT_BE_MASK 0xffffffff
#define SAURIA_CFG_ACT_DIL_PAT_BE_OFFSET 0
#define SAURIA_CFG_ACT_DIL_PAT_BE_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_DIL_PAT_BE_MASK, .index = SAURIA_CFG_ACT_DIL_PAT_BE_OFFSET })  
//-------------------------------------------------------- //DIL_PAT_BE is splitted between 2 registers

//SAURIA_CFG_ACT_DIL_PAT_BE_2
#define SAURIA_CFG_ACT_IDX6_OFFSET 0x418
//--------------------------------------------------------  

#define SAURIA_CFG_ACT_IDX7_OFFSET 0x41C   
#define SAURIA_CFG_ACT_ROWS_ACTIVE_BE_MASK 0xff
#define SAURIA_CFG_ACT_ROWS_ACTIVE_BE_OFFSET 0
#define SAURIA_CFG_ACT_ROWS_ACTIVE_BE_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_ROWS_ACTIVE_BE_MASK, .index = SAURIA_CFG_ACT_ROWS_ACTIVE_BE_OFFSET })
#define SAURIA_CFG_ACT_LOC_WOFFS0_MASK 0xff
#define SAURIA_CFG_ACT_LOC_WOFFS0_OFFSET 8
#define SAURIA_CFG_ACT_LOC_WOFFS0_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_LOC_WOFFS0_MASK, .index = SAURIA_CFG_ACT_LOC_WOFFS0_OFFSET })
#define SAURIA_CFG_ACT_LOC_WOFFS1_MASK 0xff
#define SAURIA_CFG_ACT_LOC_WOFFS1_OFFSET 16
#define SAURIA_CFG_ACT_LOC_WOFFS1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_LOC_WOFFS1_MASK, .index = SAURIA_CFG_ACT_LOC_WOFFS1_OFFSET })
#define SAURIA_CFG_ACT_LOC_WOFFS2_MASK 0xff
#define SAURIA_CFG_ACT_LOC_WOFFS2_OFFSET 24
#define SAURIA_CFG_ACT_LOC_WOFFS2_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_LOC_WOFFS2_MASK, .index = SAURIA_CFG_ACT_LOC_WOFFS2_OFFSET })
//--------------------------------------------------------  

#define SAURIA_CFG_ACT_IDX8_OFFSET 0x420
#define SAURIA_CFG_ACT_LOC_WOFFS3_MASK 0xff
#define SAURIA_CFG_ACT_LOC_WOFFS3_OFFSET 0
#define SAURIA_CFG_ACT_LOC_WOFFS3_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_LOC_WOFFS3_MASK, .index = SAURIA_CFG_ACT_LOC_WOFFS3_OFFSET })  
#define SAURIA_CFG_ACT_LOC_WOFFS4_MASK 0xff
#define SAURIA_CFG_ACT_LOC_WOFFS4_OFFSET 8
#define SAURIA_CFG_ACT_LOC_WOFFS4_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_LOC_WOFFS4_MASK, .index = SAURIA_CFG_ACT_LOC_WOFFS4_OFFSET })
#define SAURIA_CFG_ACT_LOC_WOFFS5_MASK 0xff
#define SAURIA_CFG_ACT_LOC_WOFFS5_OFFSET 16
#define SAURIA_CFG_ACT_LOC_WOFFS5_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_LOC_WOFFS5_MASK, .index = SAURIA_CFG_ACT_LOC_WOFFS5_OFFSET })  
#define SAURIA_CFG_ACT_LOC_WOFFS6_MASK 0xff
#define SAURIA_CFG_ACT_LOC_WOFFS6_OFFSET 24
#define SAURIA_CFG_ACT_LOC_WOFFS6_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_LOC_WOFFS6_MASK, .index = SAURIA_CFG_ACT_LOC_WOFFS6_OFFSET })
//-------------------------------------------------------- 

#define SAURIA_CFG_ACT_IDX9_OFFSET 0x424
#define SAURIA_CFG_ACT_LOC_WOFFS7_MASK 0xff
#define SAURIA_CFG_ACT_LOC_WOFFS7_OFFSET 0
#define SAURIA_CFG_ACT_LOC_WOFFS7_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_LOC_WOFFS7_MASK, .index = SAURIA_CFG_ACT_LOC_WOFFS7_OFFSET })   
//-------------------------------------------------------- 


// ------------------------------------------------------------
//SAURIA Weight config region registers
// ------------------------------------------------------------

#define SAURIA_CFG_WEI_IDX0_OFFSET 0x600
#define SAURIA_CFG_WEI_WLIM_MASK 0xffff
#define SAURIA_CFG_WEI_WLIM_OFFSET 0
#define SAURIA_CFG_WEI_WLIM_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_WEI_WLIM_MASK, .index = SAURIA_CFG_WEI_WLIM_OFFSET })
#define SAURIA_CFG_WEI_WSTEP_MASK 0xffff
#define SAURIA_CFG_WEI_WSTEP_OFFSET 16
#define SAURIA_CFG_WEI_WSTEP_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_WEI_WSTEP_MASK, .index = SAURIA_CFG_WEI_WSTEP_OFFSET })
//--------------------------------------------------------

#define SAURIA_CFG_WEI_IDX1_OFFSET 0x604
#define SAURIA_CFG_WEI_AUXLIM_MASK 0xffff
#define SAURIA_CFG_WEI_AUXLIM_OFFSET 0
#define SAURIA_CFG_WEI_AUXLIM_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_WEI_AUXLIM_MASK, .index = SAURIA_CFG_WEI_AUXLIM_OFFSET })    
#define SAURIA_CFG_WEI_AUXSTEP_MASK 0xffff
#define SAURIA_CFG_WEI_AUXSTEP_OFFSET 16
#define SAURIA_CFG_WEI_AUXSTEP_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_WEI_AUXSTEP_MASK, .index = SAURIA_CFG_WEI_AUXSTEP_OFFSET })  
//--------------------------------------------------------

#define SAURIA_CFG_WEI_IDX2_OFFSET 0x608
#define SAURIA_CFG_WEI_TIL_KLIM_MASK 0xffff
#define SAURIA_CFG_WEI_TIL_KLIM_OFFSET 0
#define SAURIA_CFG_WEI_TIL_KLIM_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_WEI_TIL_KLIM_MASK, .index = SAURIA_CFG_WEI_TIL_KLIM_OFFSET })    
#define SAURIA_CFG_WEI_TIL_KSTEP_MASK 0xffff
#define SAURIA_CFG_WEI_TIL_KSTEP_OFFSET 16
#define SAURIA_CFG_WEI_TIL_KSTEP_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_WEI_TIL_KSTEP_MASK, .index = SAURIA_CFG_WEI_TIL_KSTEP_OFFSET })
//--------------------------------------------------------   

#define SAURIA_CFG_WEI_IDX3_OFFSET 0x60C
#define SAURIA_CFG_WEI_COLS_ACTIVE_BE_MASK 0xff
#define SAURIA_CFG_WEI_COLS_ACTIVE_BE_OFFSET 0
#define SAURIA_CFG_WEI_COLS_ACTIVE_BE_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_WEI_COLS_ACTIVE_BE_MASK, .index = SAURIA_CFG_WEI_COLS_ACTIVE_BE_OFFSET })    
#define SAURIA_CFG_WEI_WALIGNED_BIT 8
//--------------------------------------------------------  


// ------------------------------------------------------------
//SAURIA Output config region registers  (PS Manager)
// ------------------------------------------------------------

#define SAURIA_CFG_OUT_IDX0_OFFSET 0x800
#define SAURIA_CFG_OUT_NCONTEXTS_MASK 0x7fff
#define SAURIA_CFG_OUT_NCONTEXTS_OFFSET 0
#define SAURIA_CFG_OUT_NCONTEXTS_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_NCONTEXTS_MASK, .index = SAURIA_CFG_OUT_NCONTEXTS_OFFSET })
#define SAURIA_CFG_OUT_CXLIM_MASK 0x7fff
#define SAURIA_CFG_OUT_CXLIM_OFFSET 15
#define SAURIA_CFG_OUT_CXLIM_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_CXLIM_MASK, .index = SAURIA_CFG_OUT_CXLIM_OFFSET })
#define SAURIA_CFG_OUT_CXSTEP_1_MASK 0x3   //CXSTEP is splitted between 2 registers
#define SAURIA_CFG_OUT_CXSTEP_1_OFFSET 30
#define SAURIA_CFG_OUT_CXSTEP_1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_CXSTEP_1_MASK, .index = SAURIA_CFG_OUT_CXSTEP_1_OFFSET })
//--------------------------------------------------------

#define SAURIA_CFG_OUT_IDX1_OFFSET 0x804
#define SAURIA_CFG_OUT_CXSTEP_2_MASK 0x1fff
#define SAURIA_CFG_OUT_CXSTEP_2_OFFSET 0
#define SAURIA_CFG_OUT_CXSTEP_2_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_CXSTEP_2_MASK, .index = SAURIA_CFG_OUT_CXSTEP_2_OFFSET })    
#define SAURIA_CFG_OUT_CKLIM_MASK 0x7fff
#define SAURIA_CFG_OUT_CKLIM_OFFSET 13
#define SAURIA_CFG_OUT_CKLIM_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_CKLIM_MASK, .index = SAURIA_CFG_OUT_CKLIM_OFFSET })
#define SAURIA_CFG_OUT_CKSTEP_1_MASK 0xf   //OUT_CKSTEP is splitted between 2 registers
#define SAURIA_CFG_OUT_CKSTEP_1_OFFSET 28
#define SAURIA_CFG_OUT_CKSTEP_1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_CKSTEP_1_MASK, .index = SAURIA_CFG_OUT_CKSTEP_1_OFFSET })  
//--------------------------------------------------------

#define SAURIA_CFG_OUT_IDX2_OFFSET 0x808
#define SAURIA_CFG_OUT_CKSTEP_2_MASK 0x7ff
#define SAURIA_CFG_OUT_CKSTEP_2_OFFSET 0
#define SAURIA_CFG_OUT_CKSTEP_2_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_CKSTEP_2_MASK, .index = SAURIA_CFG_OUT_CKSTEP_2_OFFSET })    
#define SAURIA_CFG_OUT_TIL_CYLIM_MASK 0x7fff
#define SAURIA_CFG_OUT_TIL_CYLIM_OFFSET 11
#define SAURIA_CFG_OUT_TIL_CYLIM_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_TIL_CYLIM_MASK, .index = SAURIA_CFG_OUT_TIL_CYLIM_OFFSET })
#define SAURIA_CFG_OUT_TIL_CYSTEP_1_MASK 0x3f   //TIL_CYSTEP is splitted between 2 registers
#define SAURIA_CFG_OUT_TIL_CYSTEP_1_OFFSET 26
#define SAURIA_CFG_OUT_TIL_CYSTEP_1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_TIL_CYSTEP_1_MASK, .index = SAURIA_CFG_OUT_TIL_CYSTEP_1_OFFSET })
//--------------------------------------------------------   

#define SAURIA_CFG_OUT_IDX3_OFFSET 0x80C
#define SAURIA_CFG_OUT_TIL_CYSTEP_2_MASK 0x1ff
#define SAURIA_CFG_OUT_TIL_CYSTEP_2_OFFSET 0
#define SAURIA_CFG_OUT_TIL_CYSTEP_2_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_TIL_CYSTEP_2_MASK, .index = SAURIA_CFG_OUT_TIL_CYSTEP_2_OFFSET })
#define SAURIA_CFG_OUT_TIL_CKLIM_MASK 0x7fff
#define SAURIA_CFG_OUT_TIL_CKLIM_OFFSET 9
#define SAURIA_CFG_OUT_TIL_CKLIM_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_TIL_CKLIM_MASK, .index = SAURIA_CFG_OUT_TIL_CKLIM_OFFSET })  
#define SAURIA_CFG_OUT_TIL_CKSTEP_1_MASK 0xff   //TIL_CKSTEP is splitted between 2 registers
#define SAURIA_CFG_OUT_TIL_CKSTEP_1_OFFSET 24
#define SAURIA_CFG_OUT_TIL_CKSTEP_1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_TIL_CKSTEP_1_MASK, .index = SAURIA_CFG_OUT_TIL_CKSTEP_1_OFFSET })
//-------------------------------------------------------- 

#define SAURIA_CFG_OUT_IDX4_OFFSET 0x810
#define SAURIA_CFG_OUT_TIL_CKSTEP_2_MASK 0x7f
#define SAURIA_CFG_OUT_TIL_CKSTEP_2_OFFSET 0
#define SAURIA_CFG_OUT_TIL_CKSTEP_2_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_TIL_CKSTEP_2_MASK, .index = SAURIA_CFG_OUT_TIL_CKSTEP_2_OFFSET })
#define SAURIA_CFG_OUT_INACTIVE_COLS_MASK 0xff
#define SAURIA_CFG_OUT_INACTIVE_COLS_OFFSET 7
#define SAURIA_CFG_OUT_INACTIVE_COLS_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_INACTIVE_COLS_MASK, .index = SAURIA_CFG_OUT_INACTIVE_COLS_OFFSET })  
#define SAURIA_CFG_OUT_PRELOAD_EN_BIT 15

//--------------------------------------------------------  

// ------------------------------------------------------------
//SAURIA SRAMA (IFMAPS)
// ------------------------------------------------------------

#define SAURIA_SRAMA_OFFSET 0x10000

//-------------------------------------------------------- 

// ------------------------------------------------------------
//SAURIA SRAMB (WEIGHTS)
// ------------------------------------------------------------

#define SAURIA_SRAMB_OFFSET 0x20000

//-------------------------------------------------------- 

// ------------------------------------------------------------
//SAURIA SRAMC (PSUMS)
// ------------------------------------------------------------

#define SAURIA_SRAMC_OFFSET 0x30000

//-------------------------------------------------------- 


#ifdef __cplusplus
}  // extern "C"
#endif
#endif  // _SAURIA_REG_DEFS_


/*
#ifndef _SAURIA_REG_DEFS_
#define _SAURIA_REG_DEFS_

#ifdef __cplusplus
extern "C" {
#endif
// Register width
#define SAURIA_PARAM_REG_WIDTH 32

// ------------------------------------------------------------
//SAURIA Control & Status registers
// ------------------------------------------------------------

//SAURIA Control signals
#define SAURIA_CFG_REGS_IDX0_OFFSET 0x0
#define SAURIA_CFG_REGS_IDX0_START_BIT 0
#define SAURIA_CFG_REGS_IDX0_DONE_BIT 1
#define SAURIA_CFG_REGS_IDX0_IDLE_BIT 2
#define SAURIA_CFG_REGS_IDX0_READY_BIT 3
#define SAURIA_CFG_REGS_IDX0_AUTO_RESTART_BIT 7
#define SAURIA_CFG_REGS_IDX0_MEM_SWITCH_BIT 16
#define SAURIA_CFG_REGS_IDX0_MEM_KEEP_A_BIT 17
#define SAURIA_CFG_REGS_IDX0_MEM_KEEP_B_BIT 18
#define SAURIA_CFG_REGS_IDX0_MEM_KEEP_C_BIT 19
#define SAURIA_CFG_REGS_IDX0_SOFT_RST_BIT 23

//SAURIA Global Interrupt Enable
#define SAURIA_CFG_REGS_IDX1_OFFSET 0x4
#define SAURIA_CFG_REGS_GLOBAL_IEN_BIT 0

//SAURIA IP Interrupt Enable
#define SAURIA_CFG_REGS_IDX2_OFFSET 0x8
#define SAURIA_CFG_REGS_DONE_IEN_BIT 0

//SAURIA IP Interrupt Status
#define SAURIA_CFG_REGS_IDX3_OFFSET 0xC
#define SAURIA_CFG_REGS_DONE_INTR_BIT 0

//SAURIA Status flags
#define SAURIA_CFG_REGS_IDX4_OFFSET 0x10

//SAURIA Cycle Counter
#define SAURIA_CFG_REGS_IDX5_OFFSET 0x14

//SAURIA Stalls Counter
#define SAURIA_CFG_REGS_IDX6_OFFSET 0x18


// ------------------------------------------------------------
//SAURIA Control Config region (Main FSM) registers
// ------------------------------------------------------------

//SAURIA Control signals
#define SAURIA_CFG_CON_IDX0_OFFSET 0x200
#define SAURIA_CFG_CON_INCTLIM_MASK 0x7fff
#define SAURIA_CFG_CON_INCTLIM_OFFSET 0
#define SAURIA_CFG_CON_INCTLIM_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_CON_INCTLIM_MASK, .index = SAURIA_CFG_CON_INCTLIM_OFFSET })
#define SAURIA_CFG_CON_ACT_REPS_MASK 0x7fff
#define SAURIA_CFG_CON_ACT_REPS_OFFSET 15
#define SAURIA_CFG_CON_ACT_REPS_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_CON_ACT_REPS_MASK, .index = SAURIA_CFG_CON_ACT_REPS_OFFSET })
#define SAURIA_CFG_CON_WEI_REPS_1_MASK 0x3   //WEI_REPS is splitted between 2 registers
#define SAURIA_CFG_CON_WEI_REPS_1_OFFSET 30
#define SAURIA_CFG_CON_WEI_REPS_1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_CON_WEI_REPS_1_MASK, .index = SAURIA_CFG_CON_WEI_REPS_1_OFFSET })
//--------------------------------------------------------

#define SAURIA_CFG_CON_IDX1_OFFSET 0x204
#define SAURIA_CFG_CON_WEI_REPS_2_MASK 0x1fff
#define SAURIA_CFG_CON_WEI_REPS_2_OFFSET 0
#define SAURIA_CFG_CON_WEI_REPS_2_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_CON_WEI_REPS_2_MASK, .index = SAURIA_CFG_CON_WEI_REPS_2_OFFSET })    
#define SAURIA_CFG_CON_THRES_MASK 0x3
#define SAURIA_CFG_CON_THRES_OFFSET 13
#define SAURIA_CFG_CON_THRES_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_CON_THRES_MASK, .index = SAURIA_CFG_CON_THRES_OFFSET })
#define SAURIA_CFG_CON_RES_MASK_MASK 0xfff
#define SAURIA_CFG_CON_RES_MASK_OFFSET 15
#define SAURIA_CFG_CON_RES_MASK_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_CON_RES_MASK_MASK, .index = SAURIA_CFG_CON_RES_MASK_OFFSET })
#define SAURIA_CFG_CON_APPR_MASK_1_MASK 0x1f  //APPR_MASK is splitted between 2 registers
#define SAURIA_CFG_CON_APPR_MASK_1_OFFSET 27
#define SAURIA_CFG_CON_APPR_MASK_1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_CON_APPR_MASK_1_MASK, .index = SAURIA_CFG_CON_APPR_MASK_1_OFFSET })  
//--------------------------------------------------------

#define SAURIA_CFG_CON_IDX2_OFFSET 0x208
#define SAURIA_CFG_CON_APPR_MASK_2_MASK 0x7  
#define SAURIA_CFG_CON_APPR_MASK_2_OFFSET 0
#define SAURIA_CFG_CON_APPR_MASK_2_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_CON_APPR_MASK_2_MASK, .index = SAURIA_CFG_CON_APPR_MASK_2_OFFSET })
//--------------------------------------------------------
#define SAURIA_CFG_CON_SRAM_DEEPSLEEP_BIT 3
#define SAURIA_CFG_CON_SRAM_POWERGATE_BIT 4


// ------------------------------------------------------------
//SAURIA Activation config region registers
// ------------------------------------------------------------

#define SAURIA_CFG_ACT_IDX0_OFFSET 0x400
#define SAURIA_CFG_ACT_XLIM_MASK 0x7fff
#define SAURIA_CFG_ACT_XLIM_OFFSET 0
#define SAURIA_CFG_ACT_XLIM_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_XLIM_MASK, .index = SAURIA_CFG_ACT_XLIM_OFFSET })
#define SAURIA_CFG_ACT_XSTEP_MASK 0x7fff
#define SAURIA_CFG_ACT_XSTEP_OFFSET 15
#define SAURIA_CFG_ACT_XSTEP_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_XSTEP_MASK, .index = SAURIA_CFG_ACT_XSTEP_OFFSET })
#define SAURIA_CFG_ACT_YLIM_1_MASK 0x3   //YLIM is splitted between 2 registers
#define SAURIA_CFG_ACT_YLIM_1_OFFSET 30
#define SAURIA_CFG_ACT_YLIM_1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_YLIM_1_MASK, .index = SAURIA_CFG_ACT_YLIM_1_OFFSET })
//--------------------------------------------------------

#define SAURIA_CFG_ACT_IDX1_OFFSET 0x404
#define SAURIA_CFG_ACT_YLIM_2_MASK 0x1fff
#define SAURIA_CFG_ACT_YLIM_2_OFFSET 0
#define SAURIA_CFG_ACT_YLIM_2_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_YLIM_2_MASK, .index = SAURIA_CFG_ACT_YLIM_2_OFFSET })    
#define SAURIA_CFG_ACT_YSTEP_MASK 0x7fff
#define SAURIA_CFG_ACT_YSTEP_OFFSET 13
#define SAURIA_CFG_ACT_YSTEP_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_YSTEP_MASK, .index = SAURIA_CFG_ACT_YSTEP_OFFSET })
#define SAURIA_CFG_ACT_CHLIM_1_MASK 0xf   //CHLIM is splitted between 2 registers
#define SAURIA_CFG_ACT_CHLIM_1_OFFSET 28
#define SAURIA_CFG_ACT_CHLIM_1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_CHLIM_1_MASK, .index = SAURIA_CFG_ACT_CHLIM_1_OFFSET })  
//--------------------------------------------------------

#define SAURIA_CFG_ACT_IDX2_OFFSET 0x408
#define SAURIA_CFG_ACT_CHLIM_2_MASK 0x7ff
#define SAURIA_CFG_ACT_CHLIM_2_OFFSET 0
#define SAURIA_CFG_ACT_CHLIM_2_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_CHLIM_2_MASK, .index = SAURIA_CFG_ACT_CHLIM_2_OFFSET })    
#define SAURIA_CFG_ACT_CHSTEP_MASK 0x7fff
#define SAURIA_CFG_ACT_CHSTEP_OFFSET 11
#define SAURIA_CFG_ACT_CHSTEP_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_CHSTEP_MASK, .index = SAURIA_CFG_ACT_CHSTEP_OFFSET })
#define SAURIA_CFG_ACT_TIL_XLIM_1_MASK 0x3f   //TIL_XLIM is splitted between 2 registers
#define SAURIA_CFG_ACT_TIL_XLIM_1_OFFSET 26
#define SAURIA_CFG_ACT_TIL_XLIM_1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_TIL_XLIM_1_MASK, .index = SAURIA_CFG_ACT_TIL_XLIM_1_OFFSET })
//--------------------------------------------------------   

#define SAURIA_CFG_ACT_IDX3_OFFSET 0x40C
#define SAURIA_CFG_ACT_TIL_XLIM_2_MASK 0x1ff
#define SAURIA_CFG_ACT_TIL_XLIM_2_OFFSET 0
#define SAURIA_CFG_ACT_TIL_XLIM_2_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_TIL_XLIM_2_MASK, .index = SAURIA_CFG_ACT_TIL_XLIM_2_OFFSET })    
#define SAURIA_CFG_ACT_TIL_XSTEP_MASK 0x7fff
#define SAURIA_CFG_ACT_TIL_XSTEP_OFFSET 9
#define SAURIA_CFG_ACT_TIL_XSTEP_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_TIL_XSTEP_MASK, .index = SAURIA_CFG_ACT_TIL_XSTEP_OFFSET })
#define SAURIA_CFG_ACT_TIL_YLIM_1_MASK 0xff   //TIL_YLIM is splitted between 2 registers
#define SAURIA_CFG_ACT_TIL_YLIM_1_OFFSET 24
#define SAURIA_CFG_ACT_TIL_YLIM_1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_TIL_YLIM_1_MASK, .index = SAURIA_CFG_ACT_TIL_YLIM_1_OFFSET })
//--------------------------------------------------------  

#define SAURIA_CFG_ACT_IDX4_OFFSET 0x410
#define SAURIA_CFG_ACT_TIL_YLIM_2_MASK 0x7f
#define SAURIA_CFG_ACT_TIL_YLIM_2_OFFSET 0
#define SAURIA_CFG_ACT_TIL_YLIM_2_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_TIL_YLIM_2_MASK, .index = SAURIA_CFG_ACT_TIL_YLIM_2_OFFSET })    
#define SAURIA_CFG_ACT_TIL_YSTEP_MASK 0x7fff
#define SAURIA_CFG_ACT_TIL_YSTEP_OFFSET 7
#define SAURIA_CFG_ACT_TIL_YSTEP_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_TIL_YSTEP_MASK, .index = SAURIA_CFG_ACT_TIL_YSTEP_OFFSET })
#define SAURIA_CFG_ACT_DIL_PAT_BE_1_MASK 0x3ff   //DIL_PAT_BE is splitted between 3 registers
#define SAURIA_CFG_ACT_DIL_PAT_BE_1_OFFSET 22
#define SAURIA_CFG_ACT_DIL_PAT_BE_1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_DIL_PAT_BE_1_MASK, .index = SAURIA_CFG_ACT_DIL_PAT_BE_1_OFFSET })
//--------------------------------------------------------  

//SAURIA_CFG_ACT_DIL_PAT_BE_2
#define SAURIA_CFG_REGS_IDX5_OFFSET 0x414
//--------------------------------------------------------  

#define SAURIA_CFG_ACT_IDX6_OFFSET 0x418
#define SAURIA_CFG_ACT_DIL_PAT_BE_3_MASK 0x3fffff
#define SAURIA_CFG_ACT_DIL_PAT_BE_3_OFFSET 0
#define SAURIA_CFG_ACT_DIL_PAT_BE_3_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_DIL_PAT_BE_3_MASK, .index = SAURIA_CFG_ACT_DIL_PAT_BE_3_OFFSET })    
#define SAURIA_CFG_ACT_ROWS_ACTIVE_BE_MASK 0xff
#define SAURIA_CFG_ACT_ROWS_ACTIVE_BE_OFFSET 22
#define SAURIA_CFG_ACT_ROWS_ACTIVE_BE_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_ROWS_ACTIVE_BE_MASK, .index = SAURIA_CFG_ACT_ROWS_ACTIVE_BE_OFFSET })
#define SAURIA_CFG_ACT_LOC_WOFFS0_1_MASK 0x3   //LOC_WOFFS0 is splitted between 2 registers
#define SAURIA_CFG_ACT_LOC_WOFFS0_1_OFFSET 30
#define SAURIA_CFG_ACT_LOC_WOFFS0_1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_LOC_WOFFS0_1_MASK, .index = SAURIA_CFG_ACT_LOC_WOFFS0_1_OFFSET })
//--------------------------------------------------------  

#define SAURIA_CFG_ACT_IDX7_OFFSET 0x41C
#define SAURIA_CFG_ACT_LOC_WOFFS0_2_MASK 0x3f
#define SAURIA_CFG_ACT_LOC_WOFFS0_2_OFFSET 0
#define SAURIA_CFG_ACT_LOC_WOFFS0_2_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_LOC_WOFFS0_2_MASK, .index = SAURIA_CFG_ACT_LOC_WOFFS0_2_OFFSET })    
#define SAURIA_CFG_ACT_LOC_WOFFS1_MASK 0xff
#define SAURIA_CFG_ACT_LOC_WOFFS1_OFFSET 6
#define SAURIA_CFG_ACT_LOC_WOFFS1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_LOC_WOFFS1_MASK, .index = SAURIA_CFG_ACT_LOC_WOFFS1_OFFSET })
#define SAURIA_CFG_ACT_LOC_WOFFS2_MASK 0xff
#define SAURIA_CFG_ACT_LOC_WOFFS2_OFFSET 14
#define SAURIA_CFG_ACT_LOC_WOFFS2_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_LOC_WOFFS2_MASK, .index = SAURIA_CFG_ACT_LOC_WOFFS2_OFFSET })
#define SAURIA_CFG_ACT_LOC_WOFFS3_MASK 0xff
#define SAURIA_CFG_ACT_LOC_WOFFS3_OFFSET 22
#define SAURIA_CFG_ACT_LOC_WOFFS3_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_LOC_WOFFS3_MASK, .index = SAURIA_CFG_ACT_LOC_WOFFS3_OFFSET })  
#define SAURIA_CFG_ACT_LOC_WOFFS4_1_MASK 0x3   //LOC_WOFFS4 is splitted between 2 registers
#define SAURIA_CFG_ACT_LOC_WOFFS4_1_OFFSET 30
#define SAURIA_CFG_ACT_LOC_WOFFS4_1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_LOC_WOFFS4_1_MASK, .index = SAURIA_CFG_ACT_LOC_WOFFS4_1_OFFSET })  
//-------------------------------------------------------- 

#define SAURIA_CFG_ACT_IDX8_OFFSET 0x420
#define SAURIA_CFG_ACT_LOC_WOFFS4_2_MASK 0x3f
#define SAURIA_CFG_ACT_LOC_WOFFS4_2_OFFSET 0
#define SAURIA_CFG_ACT_LOC_WOFFS4_2_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_LOC_WOFFS4_2_MASK, .index = SAURIA_CFG_ACT_LOC_WOFFS4_2_OFFSET })    
#define SAURIA_CFG_ACT_LOC_WOFFS5_MASK 0xff
#define SAURIA_CFG_ACT_LOC_WOFFS5_OFFSET 6
#define SAURIA_CFG_ACT_LOC_WOFFS5_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_LOC_WOFFS5_MASK, .index = SAURIA_CFG_ACT_LOC_WOFFS5_OFFSET })
#define SAURIA_CFG_ACT_LOC_WOFFS6_MASK 0xff
#define SAURIA_CFG_ACT_LOC_WOFFS6_OFFSET 14
#define SAURIA_CFG_ACT_LOC_WOFFS6_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_LOC_WOFFS6_MASK, .index = SAURIA_CFG_ACT_LOC_WOFFS6_OFFSET })
#define SAURIA_CFG_ACT_LOC_WOFFS7_MASK 0xff
#define SAURIA_CFG_ACT_LOC_WOFFS7_OFFSET 22
#define SAURIA_CFG_ACT_LOC_WOFFS7_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_ACT_LOC_WOFFS7_MASK, .index = SAURIA_CFG_ACT_LOC_WOFFS7_OFFSET })   
//-------------------------------------------------------- 


// ------------------------------------------------------------
//SAURIA Weight config region registers
// ------------------------------------------------------------

#define SAURIA_CFG_WEI_IDX0_OFFSET 0x600
#define SAURIA_CFG_WEI_WLIM_MASK 0x7fff
#define SAURIA_CFG_WEI_WLIM_OFFSET 0
#define SAURIA_CFG_WEI_WLIM_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_WEI_WLIM_MASK, .index = SAURIA_CFG_WEI_WLIM_OFFSET })
#define SAURIA_CFG_WEI_WSTEP_MASK 0x7fff
#define SAURIA_CFG_WEI_WSTEP_OFFSET 15
#define SAURIA_CFG_WEI_WSTEP_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_WEI_WSTEP_MASK, .index = SAURIA_CFG_WEI_WSTEP_OFFSET })
#define SAURIA_CFG_WEI_AUXLIM_1_MASK 0x3   //AUXLIM is splitted between 2 registers
#define SAURIA_CFG_WEI_AUXLIM_1_OFFSET 30
#define SAURIA_CFG_WEI_AUXLIM_1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_WEI_AUXLIM_1_MASK, .index = SAURIA_CFG_WEI_AUXLIM_1_OFFSET })
//--------------------------------------------------------

#define SAURIA_CFG_WEI_IDX1_OFFSET 0x604
#define SAURIA_CFG_WEI_AUXLIM_2_MASK 0x1fff
#define SAURIA_CFG_WEI_AUXLIM_2_OFFSET 0
#define SAURIA_CFG_WEI_AUXLIM_2_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_WEI_AUXLIM_2_MASK, .index = SAURIA_CFG_WEI_AUXLIM_2_OFFSET })    
#define SAURIA_CFG_WEI_AUXSTEP_MASK 0x7fff
#define SAURIA_CFG_WEI_AUXSTEP_OFFSET 13
#define SAURIA_CFG_WEI_AUXSTEP_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_WEI_AUXSTEP_MASK, .index = SAURIA_CFG_WEI_AUXSTEP_OFFSET })
#define SAURIA_CFG_WEI_TIL_KLIM_1_MASK 0xf   //TIL_KLIM is splitted between 2 registers
#define SAURIA_CFG_WEI_TIL_KLIM_1_OFFSET 28
#define SAURIA_CFG_WEI_TIL_KLIM_1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_WEI_TIL_KLIM_1_MASK, .index = SAURIA_CFG_WEI_TIL_KLIM_1_OFFSET })  
//--------------------------------------------------------

#define SAURIA_CFG_WEI_IDX2_OFFSET 0x608
#define SAURIA_CFG_WEI_TIL_KLIM_2_MASK 0x7ff
#define SAURIA_CFG_WEI_TIL_KLIM_2_OFFSET 0
#define SAURIA_CFG_WEI_TIL_KLIM_2_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_WEI_TIL_KLIM_2_MASK, .index = SAURIA_CFG_WEI_TIL_KLIM_2_OFFSET })    
#define SAURIA_CFG_WEI_TIL_KSTEP_MASK 0x7fff
#define SAURIA_CFG_WEI_TIL_KSTEP_OFFSET 11
#define SAURIA_CFG_WEI_TIL_KSTEP_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_WEI_TIL_KSTEP_MASK, .index = SAURIA_CFG_WEI_TIL_KSTEP_OFFSET })
#define SAURIA_CFG_WEI_COLS_ACTIVE_BE_1_MASK 0x3f   //COLS_ACTIVE_BE is splitted between 2 registers
#define SAURIA_CFG_WEI_COLS_ACTIVE_BE_1_OFFSET 26
#define SAURIA_CFG_WEI_COLS_ACTIVE_BE_1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_WEI_COLS_ACTIVE_BE_1_MASK, .index = SAURIA_CFG_WEI_COLS_ACTIVE_BE_1_OFFSET })
//--------------------------------------------------------   

#define SAURIA_CFG_WEI_IDX3_OFFSET 0x60C
#define SAURIA_CFG_WEI_COLS_ACTIVE_BE_2_MASK 0x3
#define SAURIA_CFG_WEI_COLS_ACTIVE_BE_2_OFFSET 0
#define SAURIA_CFG_WEI_COLS_ACTIVE_BE_2_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_WEI_COLS_ACTIVE_BE_2_MASK, .index = SAURIA_CFG_WEI_COLS_ACTIVE_BE_2_OFFSET })    
#define SAURIA_CFG_WEI_WALIGNED_BIT 2
//--------------------------------------------------------  


// ------------------------------------------------------------
//SAURIA Output config region registers  (PS Manager)
// ------------------------------------------------------------

#define SAURIA_CFG_OUT_IDX0_OFFSET 0x800
#define SAURIA_CFG_OUT_NCONTEXTS_MASK 0x7fff
#define SAURIA_CFG_OUT_NCONTEXTS_OFFSET 0
#define SAURIA_CFG_OUT_NCONTEXTS_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_NCONTEXTS_MASK, .index = SAURIA_CFG_OUT_NCONTEXTS_OFFSET })
#define SAURIA_CFG_OUT_CXLIM_MASK 0x7fff
#define SAURIA_CFG_OUT_CXLIM_OFFSET 15
#define SAURIA_CFG_OUT_CXLIM_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_CXLIM_MASK, .index = SAURIA_CFG_OUT_CXLIM_OFFSET })
#define SAURIA_CFG_OUT_CXSTEP_1_MASK 0x3   //CXSTEP is splitted between 2 registers
#define SAURIA_CFG_OUT_CXSTEP_1_OFFSET 30
#define SAURIA_CFG_OUT_CXSTEP_1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_CXSTEP_1_MASK, .index = SAURIA_CFG_OUT_CXSTEP_1_OFFSET })
//--------------------------------------------------------

#define SAURIA_CFG_OUT_IDX1_OFFSET 0x804
#define SAURIA_CFG_OUT_CXSTEP_2_MASK 0x1fff
#define SAURIA_CFG_OUT_CXSTEP_2_OFFSET 0
#define SAURIA_CFG_OUT_CXSTEP_2_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_CXSTEP_2_MASK, .index = SAURIA_CFG_OUT_CXSTEP_2_OFFSET })    
#define SAURIA_CFG_OUT_CKLIM_MASK 0x7fff
#define SAURIA_CFG_OUT_CKLIM_OFFSET 13
#define SAURIA_CFG_OUT_CKLIM_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_CKLIM_MASK, .index = SAURIA_CFG_OUT_CKLIM_OFFSET })
#define SAURIA_CFG_OUT_CKSTEP_1_MASK 0xf   //OUT_CKSTEP is splitted between 2 registers
#define SAURIA_CFG_OUT_CKSTEP_1_OFFSET 28
#define SAURIA_CFG_OUT_CKSTEP_1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_CKSTEP_1_MASK, .index = SAURIA_CFG_OUT_CKSTEP_1_OFFSET })  
//--------------------------------------------------------

#define SAURIA_CFG_OUT_IDX2_OFFSET 0x808
#define SAURIA_CFG_OUT_CKSTEP_2_MASK 0x7ff
#define SAURIA_CFG_OUT_CKSTEP_2_OFFSET 0
#define SAURIA_CFG_OUT_CKSTEP_2_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_CKSTEP_2_MASK, .index = SAURIA_CFG_OUT_CKSTEP_2_OFFSET })    
#define SAURIA_CFG_OUT_TIL_CYLIM_MASK 0x7fff
#define SAURIA_CFG_OUT_TIL_CYLIM_OFFSET 11
#define SAURIA_CFG_OUT_TIL_CYLIM_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_TIL_CYLIM_MASK, .index = SAURIA_CFG_OUT_TIL_CYLIM_OFFSET })
#define SAURIA_CFG_OUT_TIL_CYSTEP_1_MASK 0x3f   //TIL_CYSTEP is splitted between 2 registers
#define SAURIA_CFG_OUT_TIL_CYSTEP_1_OFFSET 26
#define SAURIA_CFG_OUT_TIL_CYSTEP_1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_TIL_CYSTEP_1_MASK, .index = SAURIA_CFG_OUT_TIL_CYSTEP_1_OFFSET })
//--------------------------------------------------------   

#define SAURIA_CFG_OUT_IDX3_OFFSET 0x80C
#define SAURIA_CFG_OUT_TIL_CYSTEP_2_MASK 0x1ff
#define SAURIA_CFG_OUT_TIL_CYSTEP_2_OFFSET 0
#define SAURIA_CFG_OUT_TIL_CYSTEP_2_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_TIL_CYSTEP_2_MASK, .index = SAURIA_CFG_OUT_TIL_CYSTEP_2_OFFSET })
#define SAURIA_CFG_OUT_TIL_CKLIM_MASK 0x7fff
#define SAURIA_CFG_OUT_TIL_CKLIM_OFFSET 9
#define SAURIA_CFG_OUT_TIL_CKLIM_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_TIL_CKLIM_MASK, .index = SAURIA_CFG_OUT_TIL_CKLIM_OFFSET })  
#define SAURIA_CFG_OUT_TIL_CKSTEP_1_MASK 0xff   //TIL_CKSTEP is splitted between 2 registers
#define SAURIA_CFG_OUT_TIL_CKSTEP_1_OFFSET 24
#define SAURIA_CFG_OUT_TIL_CKSTEP_1_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_TIL_CKSTEP_1_MASK, .index = SAURIA_CFG_OUT_TIL_CKSTEP_1_OFFSET })
//-------------------------------------------------------- 

#define SAURIA_CFG_OUT_IDX4_OFFSET 0x810
#define SAURIA_CFG_OUT_TIL_CKSTEP_2_MASK 0x7f
#define SAURIA_CFG_OUT_TIL_CKSTEP_2_OFFSET 0
#define SAURIA_CFG_OUT_TIL_CKSTEP_2_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_TIL_CKSTEP_2_MASK, .index = SAURIA_CFG_OUT_TIL_CKSTEP_2_OFFSET })
#define SAURIA_CFG_OUT_INACTIVE_COLS_MASK 0xff
#define SAURIA_CFG_OUT_INACTIVE_COLS_OFFSET 7
#define SAURIA_CFG_OUT_INACTIVE_COLS_FIELD \
  ((bitfield_field32_t) { .mask = SAURIA_CFG_OUT_INACTIVE_COLS_MASK, .index = SAURIA_CFG_OUT_INACTIVE_COLS_OFFSET })  
#define SAURIA_CFG_OUT_PRELOAD_EN_BIT 15

//--------------------------------------------------------  

// ------------------------------------------------------------
//SAURIA SRAMA (IFMAPS)
// ------------------------------------------------------------

#define SAURIA_SRAMA_OFFSET 0x10000

//-------------------------------------------------------- 

// ------------------------------------------------------------
//SAURIA SRAMB (WEIGHTS)
// ------------------------------------------------------------

#define SAURIA_SRAMB_OFFSET 0x20000

//-------------------------------------------------------- 

// ------------------------------------------------------------
//SAURIA SRAMC (PSUMS)
// ------------------------------------------------------------

#define SAURIA_SRAMC_OFFSET 0x30000

//-------------------------------------------------------- 


#ifdef __cplusplus
}  // extern "C"
#endif
#endif  // _SAURIA_REG_DEFS_
*/