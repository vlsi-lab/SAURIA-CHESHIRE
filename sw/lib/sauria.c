#include <stddef.h>
#include <stdint.h>

#include "sauria.h"
#include "sauria_regs.h" 


// ---------------------------------------------------------------------------
// REGISTER REGION : Control & Status
// ---------------------------------------------------------------------------

void sauria_start(const sauria_t *sauria, bool start, bool auto_restart, bool mem_switch, bool mem_keep_A, bool mem_keep_B, bool mem_keep_C, bool soft_rst) {
  uint32_t reg = 0;
  reg = mmio_region_read32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_REGS_IDX0_OFFSET));
  reg = bitfield_bit32_write(reg, SAURIA_CFG_REGS_IDX0_START_BIT, start);
  reg = bitfield_bit32_write(reg, SAURIA_CFG_REGS_IDX0_AUTO_RESTART_BIT, auto_restart);
  reg = bitfield_bit32_write(reg, SAURIA_CFG_REGS_IDX0_MEM_SWITCH_BIT, mem_switch);
  reg = bitfield_bit32_write(reg, SAURIA_CFG_REGS_IDX0_MEM_KEEP_A_BIT, mem_keep_A);
  reg = bitfield_bit32_write(reg, SAURIA_CFG_REGS_IDX0_MEM_KEEP_B_BIT, mem_keep_B);
  reg = bitfield_bit32_write(reg, SAURIA_CFG_REGS_IDX0_MEM_KEEP_C_BIT, mem_keep_C);
  reg = bitfield_bit32_write(reg, SAURIA_CFG_REGS_IDX0_SOFT_RST_BIT, soft_rst);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_REGS_IDX0_OFFSET), reg);
}

uint32_t sauria_read_reg0x0(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_REGS_IDX0_OFFSET);
  return reg;
}

bool sauria_done(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_REGS_IDX0_OFFSET);
  return bitfield_bit32_read(reg, (ptrdiff_t)(SAURIA_CFG_REGS_IDX0_DONE_BIT));
}

bool sauria_idle(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_REGS_IDX0_OFFSET);
  return bitfield_bit32_read(reg, (ptrdiff_t)(SAURIA_CFG_REGS_IDX0_IDLE_BIT));
}

bool sauria_ready(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_REGS_IDX0_OFFSET);
  return bitfield_bit32_read(reg, (ptrdiff_t)(SAURIA_CFG_REGS_IDX0_READY_BIT));
}

void sauria_global_ien(const sauria_t *sauria, bool global_ien) {
  uint32_t reg = 0;
  reg = bitfield_bit32_write(reg, SAURIA_CFG_REGS_GLOBAL_IEN_BIT, global_ien);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_REGS_IDX1_OFFSET), reg);
}

bool sauria_read_global_ien(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_REGS_IDX1_OFFSET);
  return bitfield_bit32_read(reg, (ptrdiff_t)(SAURIA_CFG_REGS_GLOBAL_IEN_BIT));
}

void sauria_done_ien(const sauria_t *sauria, bool done_ien) {
  uint32_t reg = 0;
  reg = bitfield_bit32_write(reg, SAURIA_CFG_REGS_DONE_IEN_BIT, done_ien);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_REGS_IDX2_OFFSET), reg);
}

bool sauria_read_done_ien(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_REGS_IDX2_OFFSET);
  return bitfield_bit32_read(reg, (ptrdiff_t)(SAURIA_CFG_REGS_DONE_IEN_BIT));
}

void sauria_done_interrupt_status(const sauria_t *sauria, bool done_intr_status) {
  uint32_t reg = 0;
  reg = bitfield_bit32_write(reg, SAURIA_CFG_REGS_DONE_INTR_BIT, done_intr_status);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_REGS_IDX3_OFFSET), reg);
}

bool sauria_read_done_interrupt_status(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_REGS_IDX3_OFFSET);
  return bitfield_bit32_read(reg, (ptrdiff_t)(SAURIA_CFG_REGS_DONE_INTR_BIT));
}

uint32_t sauria_status_flags(const sauria_t *sauria) {
  return mmio_region_read32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_REGS_IDX4_OFFSET));
}

uint32_t sauria_cycle_counter(const sauria_t *sauria) {
  return mmio_region_read32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_REGS_IDX5_OFFSET));
}

uint32_t sauria_stalls_counter(const sauria_t *sauria) {
  return mmio_region_read32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_REGS_IDX6_OFFSET));
}

// ---------------------------------------------------------------------------
// REGISTER REGION : Main FSM
// ---------------------------------------------------------------------------

void sauria_reg0x200(const sauria_t *sauria, uint16_t incntlim, uint16_t act_reps, uint16_t wei_reps) {
  uint32_t reg = 0;
  reg = bitfield_field32_write(reg, SAURIA_CFG_CON_INCNTLIM_FIELD, incntlim);
  reg = bitfield_field32_write(reg, SAURIA_CFG_CON_ACT_REPS_FIELD, act_reps);
  reg = bitfield_field32_write(reg, SAURIA_CFG_CON_WEI_REPS_1_FIELD, wei_reps);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_CON_IDX0_OFFSET), reg);
}

uint32_t sauria_read_reg0x200(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_CON_IDX0_OFFSET);
  return reg;
}

void sauria_reg0x204(const sauria_t *sauria, uint16_t wei_reps, uint8_t neg_thres, uint16_t res_mask, uint8_t appr_mask) {
  uint32_t reg = 0;
  uint16_t wei_reps_shifted = wei_reps >> 1;
  reg = bitfield_field32_write(reg, SAURIA_CFG_CON_WEI_REPS_2_FIELD, wei_reps_shifted);
  reg = bitfield_field32_write(reg, SAURIA_CFG_CON_THRES_FIELD, neg_thres);
  reg = bitfield_field32_write(reg, SAURIA_CFG_CON_RES_MASK_FIELD, res_mask);
  reg = bitfield_field32_write(reg, SAURIA_CFG_CON_APPR_MASK_1_FIELD, appr_mask);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_CON_IDX1_OFFSET), reg);
}

uint32_t sauria_read_reg0x204(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_CON_IDX1_OFFSET);
  return reg;
}

void sauria_reg0x208(const sauria_t *sauria, uint8_t appr_mask, bool sram_deepsleep, bool sram_powergate) {
  uint32_t reg = 0;
  uint8_t appr_mask_shifted = appr_mask >> 4;
  reg = bitfield_field32_write(reg, SAURIA_CFG_CON_APPR_MASK_2_FIELD, appr_mask_shifted);
  reg = bitfield_bit32_write(reg, SAURIA_CFG_CON_SRAM_DEEPSLEEP_BIT, sram_deepsleep);
  reg = bitfield_bit32_write(reg, SAURIA_CFG_CON_SRAM_POWERGATE_BIT, sram_powergate);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_CON_IDX2_OFFSET), reg);
}

uint32_t sauria_read_reg0x208(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_CON_IDX2_OFFSET);
  return reg;
}

// ---------------------------------------------------------------------------
// REGISTER REGION : Ifmap Feeder
// ---------------------------------------------------------------------------

void sauria_reg0x400(const sauria_t *sauria, uint16_t xlim, uint16_t xstep) {
  uint32_t reg = 0;
  reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_XLIM_FIELD, xlim);
  reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_XSTEP_FIELD, xstep);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_ACT_IDX0_OFFSET), reg);
}

uint32_t sauria_read_reg0x400(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_ACT_IDX0_OFFSET);
  return reg;
}

void sauria_reg0x404(const sauria_t *sauria, uint16_t ylim, uint16_t ystep) {
  uint32_t reg = 0;
  reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_YLIM_FIELD, ylim);
  reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_YSTEP_FIELD, ystep);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_ACT_IDX1_OFFSET), reg);
}

uint32_t sauria_read_reg0x404(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_ACT_IDX1_OFFSET);
  return reg;
}

void sauria_reg0x408(const sauria_t *sauria, uint16_t chlim, uint16_t chstep) {
  uint32_t reg = 0;
  reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_CHLIM_FIELD, chlim);
  reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_CHSTEP_FIELD, chstep);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_ACT_IDX2_OFFSET), reg);
}

uint32_t sauria_read_reg0x408(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_ACT_IDX2_OFFSET);
  return reg;
}

void sauria_reg0x40C(const sauria_t *sauria, uint16_t til_xlim, uint16_t til_xstep) {
  uint32_t reg = 0;
  reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_TIL_XLIM_FIELD, til_xlim);
  reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_TIL_XSTEP_FIELD, til_xstep);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_ACT_IDX3_OFFSET), reg);
}

uint32_t sauria_read_reg0x40C(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_ACT_IDX3_OFFSET);
  return reg;
}

void sauria_reg0x410(const sauria_t *sauria, uint16_t til_ylim, uint16_t til_ystep) {
  uint32_t reg = 0;
  reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_TIL_YLIM_FIELD, til_ylim);
  reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_TIL_YSTEP_FIELD, til_ystep);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_ACT_IDX4_OFFSET), reg);
}

uint32_t sauria_read_reg0x410(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_ACT_IDX4_OFFSET);
  return reg;
}

void sauria_reg0x414(const sauria_t *sauria, uint64_t dil_pat) {
  uint32_t reg = 0;
  reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_DIL_PAT_BE_FIELD, dil_pat);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_ACT_IDX5_OFFSET), reg);
}

uint32_t sauria_read_reg0x414(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_ACT_IDX5_OFFSET);
  return reg;
}

void sauria_reg0x418(const sauria_t *sauria, uint64_t dil_pat) {
  uint32_t reg = 0;
  uint32_t dil_pat_shifted = dil_pat >> 32;
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_ACT_IDX6_OFFSET), dil_pat_shifted);
}

uint32_t sauria_read_reg0x418(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_ACT_IDX6_OFFSET);
  return reg;
}

void sauria_reg0x41C(const sauria_t *sauria, uint8_t rows_active, uint8_t loc_woffs0, uint8_t loc_woffs1, uint8_t loc_woffs2) {
  uint32_t reg = 0;
  reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_ROWS_ACTIVE_BE_FIELD, rows_active);
  reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_LOC_WOFFS0_FIELD, loc_woffs0);
  reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_LOC_WOFFS1_FIELD, loc_woffs1);
  reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_LOC_WOFFS2_FIELD, loc_woffs2);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_ACT_IDX7_OFFSET), reg);
}

uint32_t sauria_read_reg0x41C(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_ACT_IDX7_OFFSET);
  return reg;
}

void sauria_reg0x420(const sauria_t *sauria, uint8_t loc_woffs3, uint8_t loc_woffs4, uint8_t loc_woffs5, uint8_t loc_woffs6) {
  uint32_t reg = 0;
  reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_LOC_WOFFS3_FIELD, loc_woffs3);
  reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_LOC_WOFFS4_FIELD, loc_woffs4);
  reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_LOC_WOFFS5_FIELD, loc_woffs5);
  reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_LOC_WOFFS6_FIELD, loc_woffs6);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_ACT_IDX8_OFFSET), reg);
}

uint32_t sauria_read_reg0x420(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_ACT_IDX8_OFFSET);
  return reg;
}

void sauria_reg0x424(const sauria_t *sauria, uint8_t loc_woffs7) {
  uint32_t reg = 0;
  reg = bitfield_field32_write(reg, SAURIA_CFG_ACT_LOC_WOFFS7_FIELD, loc_woffs7);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_ACT_IDX9_OFFSET), reg);
}

uint32_t sauria_read_reg0x424(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_ACT_IDX9_OFFSET);
  return reg;
}

// ---------------------------------------------------------------------------
// REGISTER REGION : Weight Feeder
// ---------------------------------------------------------------------------

void sauria_reg0x600(const sauria_t *sauria, uint16_t wlim, uint16_t wstep) {
  uint32_t reg = 0;
  reg = bitfield_field32_write(reg, SAURIA_CFG_WEI_WLIM_FIELD, wlim);
  reg = bitfield_field32_write(reg, SAURIA_CFG_WEI_WSTEP_FIELD, wstep);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_WEI_IDX0_OFFSET), reg);
}

uint32_t sauria_read_reg0x600(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_WEI_IDX0_OFFSET);
  return reg;
}

void sauria_reg0x604(const sauria_t *sauria, uint16_t auxlim, uint16_t auxstep) {
  uint32_t reg = 0;
  reg = bitfield_field32_write(reg, SAURIA_CFG_WEI_AUXLIM_FIELD, auxlim);
  reg = bitfield_field32_write(reg, SAURIA_CFG_WEI_AUXSTEP_FIELD, auxstep);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_WEI_IDX1_OFFSET), reg);
}

uint32_t sauria_read_reg0x604(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_WEI_IDX1_OFFSET);
  return reg;
}

void sauria_reg0x608(const sauria_t *sauria, uint16_t til_klim, uint16_t til_kstep) {
  uint32_t reg = 0;
  reg = bitfield_field32_write(reg, SAURIA_CFG_WEI_TIL_KLIM_FIELD, til_klim);
  reg = bitfield_field32_write(reg, SAURIA_CFG_WEI_TIL_KSTEP_FIELD, til_kstep);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_WEI_IDX2_OFFSET), reg);
}

uint32_t sauria_read_reg0x608(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_WEI_IDX2_OFFSET);
  return reg;
}

void sauria_reg0x60C(const sauria_t *sauria, uint8_t cols_active, bool waligned) {
  uint32_t reg = 0;
  reg = bitfield_field32_write(reg, SAURIA_CFG_WEI_COLS_ACTIVE_BE_FIELD, cols_active);
  reg = bitfield_bit32_write(reg, SAURIA_CFG_WEI_WALIGNED_BIT, waligned);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_WEI_IDX3_OFFSET), reg);
}

uint32_t sauria_read_reg0x60C(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_WEI_IDX3_OFFSET);
  return reg;
}

// ---------------------------------------------------------------------------
// REGISTER REGION : PS Manager
// ---------------------------------------------------------------------------

void sauria_reg0x800(const sauria_t *sauria, uint16_t ncontexts, uint16_t cxlim, uint16_t cxstep) {
  uint32_t reg = 0;
  reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_NCONTEXTS_FIELD, ncontexts);
  reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_CXLIM_FIELD, cxlim);
  reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_CXSTEP_1_FIELD, cxstep);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_OUT_IDX0_OFFSET), reg);
}

uint32_t sauria_read_reg0x800(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_OUT_IDX0_OFFSET);
  return reg;
}

void sauria_reg0x804(const sauria_t *sauria, uint16_t cxstep, uint16_t cklim, uint16_t ckstep) {
  uint32_t reg = 0;
  uint16_t cxstep_shifted = cxstep >> 2;
  reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_CXSTEP_2_FIELD, cxstep_shifted);
  reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_CKLIM_FIELD, cklim);
  reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_CKSTEP_1_FIELD, ckstep);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_OUT_IDX1_OFFSET), reg);
}

uint32_t sauria_read_reg0x804(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_OUT_IDX1_OFFSET);
  return reg;
}

void sauria_reg0x808(const sauria_t *sauria, uint16_t ckstep, uint16_t til_cylim, uint16_t til_cystep) {
  uint32_t reg = 0;
  uint16_t ckstep_shifted = ckstep >> 4;
  reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_CKSTEP_2_FIELD, ckstep_shifted);
  reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_TIL_CYLIM_FIELD, til_cylim);
  reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_TIL_CYSTEP_1_FIELD, til_cystep);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_OUT_IDX2_OFFSET), reg);
}

uint32_t sauria_read_reg0x808(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_OUT_IDX2_OFFSET);
  return reg;
}

void sauria_reg0x80C(const sauria_t *sauria, uint16_t til_cystep, uint16_t til_cklim, uint16_t til_ckstep) {
  uint32_t reg = 0;
  uint16_t til_cystep_shifted = til_cystep >> 6;
  reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_TIL_CYSTEP_2_FIELD, til_cystep_shifted);
  reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_TIL_CKLIM_FIELD, til_cklim);
  reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_TIL_CKSTEP_1_FIELD, til_ckstep);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_OUT_IDX3_OFFSET), reg);
}

uint32_t sauria_read_reg0x80C(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_OUT_IDX3_OFFSET);
  return reg;
}

void sauria_reg0x810(const sauria_t *sauria, uint16_t til_ckstep, uint8_t inactive_cols, bool preload_en) {
  uint32_t reg = 0;
  uint8_t til_ckstep_shifted = til_ckstep >> 8;
  reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_TIL_CKSTEP_2_FIELD, til_ckstep_shifted);
  reg = bitfield_field32_write(reg, SAURIA_CFG_OUT_INACTIVE_COLS_FIELD, inactive_cols);
  reg = bitfield_bit32_write(reg, SAURIA_CFG_OUT_PRELOAD_EN_BIT, preload_en);
  mmio_region_write32(sauria->base_addr, (ptrdiff_t)(SAURIA_CFG_OUT_IDX4_OFFSET), reg);
}

uint32_t sauria_read_reg0x810(const sauria_t *sauria) {
  uint32_t reg = mmio_region_read32(sauria->base_addr, SAURIA_CFG_OUT_IDX4_OFFSET);
  return reg;
}