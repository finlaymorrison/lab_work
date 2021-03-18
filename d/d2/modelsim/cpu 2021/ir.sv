/*
 * Project: cpu 2021
 * File: cpu 2021/ir.sv
 * -----
 * File Created: Sunday, 24th January 2021 12:52:10 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:37:07 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

module ir  #(parameter WORD_W = 8, OP_W = 3)
             (input logic clock, n_reset, Addr_bus, load_IR,
              inout wire [WORD_W-1:0] sysbus,
              output logic [OP_W-1:0] op);
	      
logic  [WORD_W-1:0] instr_reg;

assign sysbus = Addr_bus ? {{OP_W{1'b0}},instr_reg[WORD_W-OP_W-1:0]} : 'z;

assign op = instr_reg[WORD_W-1:WORD_W-OP_W];

always_ff @(posedge clock, negedge n_reset)
  begin
  if (!n_reset)
    instr_reg <= 0;
  else
    if (load_IR)
      instr_reg <= sysbus;
  end
endmodule