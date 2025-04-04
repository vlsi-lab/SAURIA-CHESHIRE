/*
 * Copyright 2025 PoliTo
 * Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
 * SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
 *
 * Author: Tommaso Terzano <tommaso.terzano@polito.it> 
 *                         <tommaso.terzano@gmail.com>
 *  
 * Info: Top module of the SAURIA demonstrator, integrated with the Cheshire MCU. It
         has the same ports as the Cheshire MCU, to facilitate integration.
 */

 module sauria_demo_soc import sauria_demo_pkg::*; import cheshire_pkg::*; #(
  parameter type axi_ext_llc_req_t  = logic,
  parameter type axi_ext_llc_rsp_t  = logic,
  parameter type axi_ext_mst_req_t  = logic,
  parameter type axi_ext_mst_rsp_t  = logic,
  parameter type axi_ext_slv_req_t  = logic,
  parameter type axi_ext_slv_rsp_t  = logic,
  parameter type reg_ext_req_t      = logic,
  parameter type reg_ext_rsp_t      = logic,

  /* Cheshire configuration */
  parameter cheshire_cfg_t Cfg = '0,

  // Debug info for external harts
  parameter dm::hartinfo_t [iomsb(Cfg.NumExtDbgHarts):0] ExtHartinfo = '0,

  /* SAURIA's parameters */
  parameter CFG_AXI_DATA_WIDTH    = 32,       // Configuration AXI4-Lite Slave data width
  parameter CFG_AXI_ADDR_WIDTH    = 32,       // Configuration AXI4-Lite Slave address width
  parameter DATA_AXI_DATA_WIDTH   = 128,      // Data AXI4 Slave data width
  parameter DATA_AXI_ADDR_WIDTH   = 32,       // Data AXI4 Slave address width
  parameter DATA_AXI_ID_WIDTH     = 2,        // Data AXI4 Slave ID width
  localparam  BYTE = 8,
  localparam  CFG_AXI_BYTE_NUM = CFG_AXI_DATA_WIDTH/BYTE,
  localparam  DATA_AXI_BYTE_NUM = DATA_AXI_DATA_WIDTH/BYTE
  ) (
	input  logic        clk_i,
  input  logic        rst_ni,
  input  logic        test_mode_i,
  input  logic [1:0]  boot_mode_i,
  input  logic        rtc_i,
  // External AXI LLC (DRAM) port
  output axi_ext_llc_req_t axi_llc_mst_req_o,
  input  axi_ext_llc_rsp_t axi_llc_mst_rsp_i,
  // External AXI crossbar ports
  input  axi_ext_mst_req_t [iomsb(Cfg.AxiExtNumMst):0] axi_ext_mst_req_i,
  output axi_ext_mst_rsp_t [iomsb(Cfg.AxiExtNumMst):0] axi_ext_mst_rsp_o,
  output axi_ext_slv_req_t [iomsb(Cfg.AxiExtNumSlv):0] axi_ext_slv_req_o,
  input  axi_ext_slv_rsp_t [iomsb(Cfg.AxiExtNumSlv):0] axi_ext_slv_rsp_i,
  // External reg demux slaves
  output reg_ext_req_t [iomsb(Cfg.RegExtNumSlv):0] reg_ext_slv_req_o,
  input  reg_ext_rsp_t [iomsb(Cfg.RegExtNumSlv):0] reg_ext_slv_rsp_i,
  // Interrupts from and to external targets
  input  logic [iomsb(Cfg.NumExtInIntrs):0]                                   intr_ext_i,
  output logic [iomsb(Cfg.NumExtOutIntrTgts):0][iomsb(Cfg.NumExtOutIntrs):0]  intr_ext_o,
  // Interrupt requests to external harts
  output logic [iomsb(NumIrqCtxts*Cfg.NumExtIrqHarts):0] xeip_ext_o,
  output logic [iomsb(Cfg.NumExtIrqHarts):0]             mtip_ext_o,
  output logic [iomsb(Cfg.NumExtIrqHarts):0]             msip_ext_o,
  // Debug interface to external harts
  output logic                                dbg_active_o,
  output logic [iomsb(Cfg.NumExtDbgHarts):0]  dbg_ext_req_o,
  input  logic [iomsb(Cfg.NumExtDbgHarts):0]  dbg_ext_unavail_i,
  // JTAG interface
  input  logic  jtag_tck_i,
  input  logic  jtag_trst_ni,
  input  logic  jtag_tms_i,
  input  logic  jtag_tdi_i,
  output logic  jtag_tdo_o,
  output logic  jtag_tdo_oe_o,
  // UART interface
  output logic  uart_tx_o,
  input  logic  uart_rx_i,
  // UART modem flow control
  output logic  uart_rts_no,
  output logic  uart_dtr_no,
  input  logic  uart_cts_ni,
  input  logic  uart_dsr_ni,
  input  logic  uart_dcd_ni,
  input  logic  uart_rin_ni,
  // I2C interface
  output logic  i2c_sda_o,
  input  logic  i2c_sda_i,
  output logic  i2c_sda_en_o,
  output logic  i2c_scl_o,
  input  logic  i2c_scl_i,
  output logic  i2c_scl_en_o,
  // SPI host interface
  output logic                  spih_sck_o,
  output logic                  spih_sck_en_o,
  output logic [SpihNumCs-1:0]  spih_csb_o,
  output logic [SpihNumCs-1:0]  spih_csb_en_o,
  output logic [ 3:0]           spih_sd_o,
  output logic [ 3:0]           spih_sd_en_o,
  input  logic [ 3:0]           spih_sd_i,
  // GPIO interface
  input  logic [31:0] gpio_i,
  output logic [31:0] gpio_o,
  output logic [31:0] gpio_en_o,
  // Serial link interface
  input  logic [SlinkNumChan-1:0]                     slink_rcv_clk_i,
  output logic [SlinkNumChan-1:0]                     slink_rcv_clk_o,
  input  logic [SlinkNumChan-1:0][SlinkNumLanes-1:0]  slink_i,
  output logic [SlinkNumChan-1:0][SlinkNumLanes-1:0]  slink_o,
  // VGA interface
  output logic                          vga_hsync_o,
  output logic                          vga_vsync_o,
  output logic [Cfg.VgaRedWidth  -1:0]  vga_red_o,
  output logic [Cfg.VgaGreenWidth-1:0]  vga_green_o,
  output logic [Cfg.VgaBlueWidth -1:0]  vga_blue_o,
  // USB interface
  input  logic                   usb_clk_i,
  input  logic                   usb_rst_ni,
  input  logic [UsbNumPorts-1:0] usb_dm_i,
  output logic [UsbNumPorts-1:0] usb_dm_o,
  output logic [UsbNumPorts-1:0] usb_dm_oe_o,
  input  logic [UsbNumPorts-1:0] usb_dp_i,
  output logic [UsbNumPorts-1:0] usb_dp_o,
  output logic [UsbNumPorts-1:0] usb_dp_oe_o
 );

  /*_________________________________________________________________________________________________________________________________ */

  /* Imports and parameters */

  `include "axi/typedef.svh"
  `include "common_cells/registers.svh"
  `include "common_cells/assertions.svh"
  `include "cheshire/typedef.svh"
  `include "axi/assign.svh"
  
  `CHESHIRE_TYPEDEF_ALL(, Cfg)

  /*_________________________________________________________________________________________________________________________________ */

  /* Signals declaration */

  /* Sauria done interrupt signal */
  logic sauria_doneintr;

  /* AXI lite interface */
  AXI_LITE #(
  .AXI_ADDR_WIDTH (CFG_AXI_ADDR_WIDTH),
  .AXI_DATA_WIDTH (CFG_AXI_DATA_WIDTH)
  ) sauria_cfg_port_mst(), sauria_cfg_port_slv();

  /* AXI interface */
  AXI_BUS #(
    .AXI_ADDR_WIDTH (DATA_AXI_ADDR_WIDTH),
    .AXI_DATA_WIDTH (DATA_AXI_DATA_WIDTH),
    .AXI_ID_WIDTH   (DATA_AXI_ID_WIDTH+1),
    .AXI_USER_WIDTH (1) // Unused, but 0 can cause compilation errors
  ) sauria_mem_port_mst(), sauria_mem_port_slv();

  /* Cheshire AXI-lite-like (regintfc) signals */
  reg_req_t cheshire_ext_reg_req;
  reg_rsp_t cheshire_ext_reg_rsp;

  /* Cheshire AXI signals*/
  axi_ext_slv_req_t cheshire_ext_slv_req;
  axi_ext_slv_rsp_t cheshire_ext_slv_rsp;
  
  /* Connection of slave (sauria core) to master interfaces (axi_intf_to_regs) */
  `AXI_LITE_ASSIGN(sauria_cfg_port_slv, sauria_cfg_port_mst)
  `AXI_ASSIGN(sauria_mem_port_slv, sauria_mem_port_mst)

  /*_________________________________________________________________________________________________________________________________ */

  /* Module instantiation */

  /* SAURIA Core */
  sauria_core #(
      .CFG_AXI_DATA_WIDTH (CFG_AXI_DATA_WIDTH),
      .CFG_AXI_ADDR_WIDTH (CFG_AXI_ADDR_WIDTH),
      .DATA_AXI_DATA_WIDTH (DATA_AXI_DATA_WIDTH),
      .DATA_AXI_ADDR_WIDTH(DATA_AXI_ADDR_WIDTH),
      .DATA_AXI_ID_WIDTH (DATA_AXI_ID_WIDTH+1)
  ) sauria_core_i(
      .i_clk      (clk_i),
      .i_rstn     (rst_ni),
      .cfg_slv    (sauria_cfg_port_slv),
      .mem_slv    (sauria_mem_port_slv),
      .o_doneintr (sauria_doneintr)
  );

  /* Cheshire
   * Additional info: the axi_llc_mst_req and axi_llc_mst_rsp signals are needed for the testbench, but are not used in the design.
   */
  cheshire_soc #(
    .Cfg(Cfg),
    .ExtHartinfo('0),
    .axi_ext_llc_req_t(axi_ext_llc_req_t),
    .axi_ext_llc_rsp_t(axi_ext_llc_rsp_t),
    .axi_ext_mst_req_t(axi_ext_mst_req_t),
    .axi_ext_mst_rsp_t(axi_ext_mst_rsp_t),
    .axi_ext_slv_req_t(axi_ext_slv_req_t),
    .axi_ext_slv_rsp_t(axi_ext_slv_rsp_t),
    .reg_ext_req_t(reg_ext_req_t),
    .reg_ext_rsp_t(reg_ext_rsp_t)
  ) cheshire_soc_i (
    .clk_i,
    .rst_ni,
    .test_mode_i,
    .boot_mode_i,
    .rtc_i,
    // External AXI LLC (DRAM) port
    .axi_llc_mst_req_o,
    .axi_llc_mst_rsp_i,
    // External AXI crossbar ports
    .axi_ext_mst_req_i,
    .axi_ext_mst_rsp_o,
    .axi_ext_slv_req_o (cheshire_ext_slv_req),
    .axi_ext_slv_rsp_i (cheshire_ext_slv_rsp),
    // External reg demux slaves
    .reg_ext_slv_req_o (cheshire_ext_reg_req),
    .reg_ext_slv_rsp_i (cheshire_ext_reg_rsp),
    // Interrupts from external devices
    .intr_ext_i (sauria_doneintr),
    .intr_ext_o,
    // Interrupts to external harts
    .xeip_ext_o,
    .mtip_ext_o,
    .msip_ext_o,
    // Debug interface to external harts
    .dbg_active_o     ,
    .dbg_ext_req_o    ,
    .dbg_ext_unavail_i,
    // JTAG interface
    .jtag_tck_i   ,
    .jtag_trst_ni ,
    .jtag_tms_i   ,
    .jtag_tdi_i   ,
    .jtag_tdo_o   ,
    .jtag_tdo_oe_o,
    // UART interface
    .uart_tx_o,
    .uart_rx_i,
    // UART Modem flow control
    .uart_rts_no,
    .uart_dtr_no,
    .uart_cts_ni,
    .uart_dsr_ni,
    .uart_dcd_ni,
    .uart_rin_ni,
    // I2C interface
    .i2c_sda_o   ,
    .i2c_sda_i   ,
    .i2c_sda_en_o,
    .i2c_scl_o   ,
    .i2c_scl_i   ,
    .i2c_scl_en_o,
    // SPI host interface
    .spih_sck_o   ,
    .spih_sck_en_o,
    .spih_csb_o   ,
    .spih_csb_en_o,
    .spih_sd_o    ,
    .spih_sd_en_o ,
    .spih_sd_i    ,
    // GPIO interface
    .gpio_i   ,
    .gpio_o   ,
    .gpio_en_o,
    // Serial link interface
    .slink_rcv_clk_i,
    .slink_rcv_clk_o,
    .slink_i        ,
    .slink_o        ,
    // VGA interface
    .vga_hsync_o,
    .vga_vsync_o,
    .vga_red_o  ,
    .vga_green_o,
    .vga_blue_o
  );

  /* AXI4 interface bridge module
   * This module is necessary because SAURIA's core works with an AXI interface, while the Cheshire
   * project is built using structures to handle the AXI protocol.
   */
  axi_intfc_bridge # (
    .axi_req_t(axi_ext_slv_req_t),
    .axi_resp_t(axi_ext_slv_rsp_t)
  ) axi_bridge_i (
    // struct side
    .axi_req_i (cheshire_ext_slv_req),
    .axi_rsp_o (cheshire_ext_slv_rsp),
    // interface-based side
    .axi_o (sauria_mem_port_mst)
  );

  /* AXI4 Lite interface bridge module
   * Same idea as before, but for AXI4 Lite protocol. More complex module, as there isn't a direct
   * correspondence between the interface-based of SAURIA and the register interface of Cheshire.
   */
  reg_to_axi_lite_intf #(
  .ADDR_WIDTH(CFG_AXI_ADDR_WIDTH),
  .DATA_WIDTH(CFG_AXI_DATA_WIDTH),
  .reg_req_t(reg_req_t), //.reg_req_t(reg_pkg::reg_req_t),
  .reg_rsp_t(reg_rsp_t)  //.reg_rsp_t(reg_pkg::reg_rsp_t)
  ) axi_lite_bridge_i (
    .clk_i,
    .rst_ni,
    // struct side
    .reg_req_i (cheshire_ext_reg_req),
    .reg_rsp_o (cheshire_ext_reg_rsp),
    // interface-based side
    .axi_o (sauria_cfg_port_mst)
  );

 endmodule
