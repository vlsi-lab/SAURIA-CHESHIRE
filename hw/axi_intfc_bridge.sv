/*
 * Copyright 2025 PoliTo
 * Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
 * SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
 *
 * Author: Tommaso Terzano <tommaso.terzano@polito.it> 
 *                         <tommaso.terzano@gmail.com>
 *  
 * Info: Bridge between interface-based AXI protocol and structure based AXI protocol.
 */

module axi_intfc_bridge #(
  /* Request struct of the AXI4 port */
  parameter type axi_req_t = logic,
  /* Response struct of the AXI4 port */
  parameter type axi_resp_t = logic
)(
  /* From the struct side: */
  input  axi_req_t                axi_req_i,
  output axi_resp_t               axi_rsp_o,

  /* To the interface side: the interface is master-side, because the bridge is connecting the input requests
   * from the struct side (CHESHIRE) to the interface side.
   */
  AXI_BUS.Master axi_o
);

  `include "axi/typedef.svh"
  `include "axi/assign.svh"
  
  // Assign from interface => local_req
  `AXI_ASSIGN_FROM_REQ(axi_o, axi_req_i)

  // Assign local_rsp => interface
  `AXI_ASSIGN_TO_RESP(axi_rsp_o, axi_o)

endmodule
