/*
 * SAURIA demonstrator test-bench
 * � loads NUM_MATS reference tensors (16 � 16 � int32) from .mem files
 * � lets the DUT run
 * � compares matrix m with SRAM lines  m*64 � m*64+63
 *
 * Copyright 2025 PoliTo � Apache-2.0 WITH SHL-2.1
 */

module tb_sauria_demo_soc #(
  //---------------------------------------------------------------------------
  // Generic / infrastructure
  //---------------------------------------------------------------------------
  parameter int unsigned SelectedCfg = 32'd0,
  parameter bit          UseDramSys  = 1'b0,

  //---------------------------------------------------------------------------
  // Reference-matrix control
  //---------------------------------------------------------------------------
  parameter int unsigned NUM_MATS = 8,
  parameter string       REF_FILES [0:NUM_MATS-1] = '{
        "verification/matrix1.mem", "verification/matrix2.mem",
        "verification/matrix3.mem", "verification/matrix4.mem",
        "verification/matrix5.mem", "verification/matrix6.mem",
        "verification/matrix7.mem", "verification/matrix8.mem"
  }
);

  //---------------------------------------------------------------------------
  // DUT fixture
  //---------------------------------------------------------------------------
  fixture_sauria_demo_soc #(
    .SelectedCfg (SelectedCfg),
    .UseDramSys  (UseDramSys)
  ) fix();

  localparam int ROWS            = 16;
  localparam int COLS            = 16;
  localparam int WORDS_PER_LINE  = 4;
  localparam int LINES_PER_CH   = ROWS * COLS / WORDS_PER_LINE; // = 64
  localparam int WORDS_PER_CH   = ROWS * COLS;                  // = 256

  int signed ref_flat [0:NUM_CHS-1][0:WORDS_PER_CH-1];

  string      preload_elf;
  string      boot_hex;
  logic [1:0] boot_mode;
  logic [1:0] preload_mode;
  bit [31:0]  exit_code;

  //---------------------------------------------------------------------------
  // Test sequence
  //---------------------------------------------------------------------------
  initial begin
    int               m, row, col, errors;
    int               flat_idx, line_idx, word_sel;
    int  signed       dut_word, ref_word;
    logic [127:0]     mem_line;

    for (m = 0; m < NUM_CHS; m++) begin
      $display("[TB] Loading Channel %0d from \"%s\"",
               m+1, REF_FILES[m]);
      $readmemh(REF_FILES[m], ref_flat[m]);
    end

    if (!$value$plusargs("BOOTMODE=%d", boot_mode))     boot_mode     = 0;
    if (!$value$plusargs("PRELMODE=%d", preload_mode))  preload_mode  = 0;
    if (!$value$plusargs("BINARY=%s",   preload_elf))   preload_elf   = "";
    if (!$value$plusargs("IMAGE=%s",    boot_hex))      boot_hex      = "";

    fix.vip.set_boot_mode(boot_mode);
    fix.vip.i2c_eeprom_preload(boot_hex);
    fix.vip.spih_norflash_preload(boot_hex);
    fix.vip.wait_for_reset();

    if (boot_mode == 0) begin
      case (preload_mode)
        0: begin fix.vip.jtag_init();
                 fix.vip.jtag_elf_run(preload_elf);
                 fix.vip.jtag_wait_for_eoc(exit_code); end
        1: begin fix.vip.slink_elf_run(preload_elf);
                 fix.vip.slink_wait_for_eoc(exit_code); end
        2: begin fix.vip.uart_debug_elf_run_and_wait(preload_elf,
                                                     exit_code);     end
        default: $fatal(1,
                 "[TB] Unsupported PRELMODE %0d", preload_mode);
      endcase
    end else if (boot_mode == 1) begin
      $fatal(1, "[TB] Unsupported BOOTMODE 1 (SD Card)");
    end else begin
      fix.vip.jtag_init();
      fix.vip.jtag_wait_for_eoc(exit_code);
    end

    // Verification against the reference data
    for (m = 0; m < NUM_CHS; m++) begin
      errors = 0;
      $display("\n[TB] === Checking Channel %0d ===", m+1);

      for (row = 0; row < ROWS; row++) begin
        for (col = 0; col < COLS; col++) begin
          line_idx  = m*LINES_PER_CH + row*WORDS_PER_LINE + (col/WORDS_PER_LINE);
          word_sel  = col % WORDS_PER_LINE;
          mem_line  = fix.dut.sauria_core_i.sram_top_i.SRAMC_i.sram_0_i.mem[line_idx];
          dut_word  = $signed(mem_line >> (word_sel*32));

          flat_idx  = row*COLS + col;           // 0‥255
          ref_word  = ref_flat[m][flat_idx];

          if (dut_word !== ref_word) begin
            $display("  M%0d[%0d][%0d] : DUT=%0d  EXP=%0d",
                     m+1, row, col, dut_word, ref_word);
            errors++;
          end
        end
      end

      if (errors == 0)
        $display("[TB] *** Channel %0d PASS ***", m+1);
      else
        $display("[TB] *** Channel %0d FAIL – %0d mismatch(es) ***",
                 m+1, errors);
    end
    
    $display("\n[TB] All %0d matrices checked – simulation finished.", NUM_CHS);
    $finish;
  end

endmodule
