// Copyright 2024 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Paul Scheffler <paulsc@iis.ee.ethz.ch>

/// A simple Regbus to AXI4-Lite adapter. Blocks until response (B/R) is received.
/// Data width must match in both types! Address is truncated or zero-extended.
/// Sends requests with ID 0 and user signals 0.
module reg_to_axi_lite #(
  /// Datawidth of both incoming Regbus and outgoing AXI4-Lite.
  parameter int unsigned DataWidth = 0,
  /// Cache signal assigned to Ax requests.
  parameter axi_pkg::cache_t AxiCache = axi_pkg::CACHE_MODIFIABLE,
  /// Incoming Regbus request type.
  parameter type reg_req_t = logic,
  /// Incoming Regbus response type.
  parameter type reg_rsp_t = logic,
  /// Outgoing AXI4-Lite request type.
  parameter type axi_lite_req_t = logic,
  /// Incoming AXI4-Lite response type.
  parameter type axi_lite_rsp_t = logic
) (
  input  logic     clk_i,
  input  logic     rst_ni,
  input  reg_req_t reg_req_i,
  output reg_rsp_t reg_rsp_o,
  output axi_lite_req_t axi_lite_req_o,
  input  axi_lite_rsp_t axi_lite_rsp_i
);
  `include "common_cells/registers.svh"

  // Set request pending flags on handshakes to block further requests until response.
  // Clear request pending flags (with in-cycle precedence over set!) on response.
  logic ar_pnd_q, aw_pnd_q, w_pnd_q;

  `FFLARNC(ar_pnd_q, axi_lite_rsp_i.ar_ready, axi_lite_req_o.ar_valid, axi_lite_rsp_i.r_valid, 1'b0, clk_i, rst_ni)
  `FFLARNC(aw_pnd_q, axi_lite_rsp_i.aw_ready, axi_lite_req_o.aw_valid, axi_lite_rsp_i.b_valid, 1'b0, clk_i, rst_ni)
  `FFLARNC(w_pnd_q,  axi_lite_rsp_i.w_ready,  axi_lite_req_o.w_valid,  axi_lite_rsp_i.b_valid, 1'b0, clk_i, rst_ni)

  // AR: Forward locked-in read requests
  assign axi_lite_req_o.ar = '{
    addr:   reg_req_i.addr,
    default: '0
  };

  assign axi_lite_req_o.r_ready  = reg_req_i.valid & ~reg_req_i.write;
  assign axi_lite_req_o.ar_valid = axi_lite_req_o.r_ready & ~ar_pnd_q;

  // AW: Forward locked-in write requests
  assign axi_lite_req_o.aw = '{
    addr:   reg_req_i.addr,
    default: '0
  };

  assign axi_lite_req_o.b_ready  = reg_req_i.valid & reg_req_i.write;
  assign axi_lite_req_o.aw_valid = axi_lite_req_o.b_ready & ~aw_pnd_q;

  // W: lock control flow to AW requests
  assign axi_lite_req_o.w = '{
    data:   reg_req_i.wdata,
    strb:   reg_req_i.wstrb,
    default:  '0
  };

  assign axi_lite_req_o.w_valid = axi_lite_req_o.b_ready & ~w_pnd_q;

  // Regbus response
  assign reg_rsp_o = '{
    rdata:  axi_lite_rsp_i.r.data,
    error:  (reg_req_i.write ? axi_lite_rsp_i.b.resp : axi_lite_rsp_i.r.resp) == axi_pkg::RESP_OKAY,
    ready:  axi_lite_rsp_i.r_valid | axi_lite_rsp_i.b_valid
  };

endmodule

`include "axi/typedef.svh"
`include "axi/assign.svh"

/// Interface wrapper.
module reg_to_axi_lite_intf #(
  /// The width of the address.
  parameter int ADDR_WIDTH = -1,
  /// The width of the data.
  parameter int DATA_WIDTH = -1,
  /// Incoming Regbus request type.
  parameter type reg_req_t = logic,
  /// Incoming Regbus response type.
  parameter type reg_rsp_t = logic
) (
  input  logic   clk_i,
  input  logic   rst_ni,
  input  reg_req_t reg_req_i,
  output reg_rsp_t reg_rsp_o,
  AXI_LITE.Master axi_o
);

  typedef logic [ADDR_WIDTH-1:0] addr_t;
  typedef logic [DATA_WIDTH-1:0] data_t;
  typedef logic [DATA_WIDTH/8-1:0] strb_t;

  `AXI_LITE_TYPEDEF_AW_CHAN_T(aw_chan_t, addr_t)
  `AXI_LITE_TYPEDEF_W_CHAN_T(w_chan_t, data_t, strb_t)
  `AXI_LITE_TYPEDEF_B_CHAN_T(b_chan_t)
  `AXI_LITE_TYPEDEF_AR_CHAN_T(ar_chan_t, addr_t)
  `AXI_LITE_TYPEDEF_R_CHAN_T(r_chan_t, data_t)
  `AXI_LITE_TYPEDEF_REQ_T(axi_req_t, aw_chan_t, w_chan_t, ar_chan_t)
  `AXI_LITE_TYPEDEF_RESP_T(axi_resp_t, b_chan_t, r_chan_t)

  axi_req_t  axi_req;
  axi_resp_t axi_resp;

  `AXI_LITE_ASSIGN_FROM_REQ(axi_o, axi_req)
  `AXI_LITE_ASSIGN_TO_RESP(axi_resp, axi_o)

  reg_to_axi_lite #(
    .DataWidth (DATA_WIDTH),
    .reg_req_t (reg_req_t),
    .reg_rsp_t (reg_rsp_t),
    .axi_lite_req_t (axi_req_t),
    .axi_lite_rsp_t (axi_resp_t)
  ) i_reg_to_axi_lite (
    .clk_i (clk_i),
    .rst_ni (rst_ni),
    .reg_req_i (reg_req_i),
    .reg_rsp_o (reg_rsp_o),
    .axi_lite_req_o (axi_req),
    .axi_lite_rsp_i (axi_resp)
  );

endmodule

