/*
 * Project: cpu 2021
 * File: cpu 2021/alu.sv
 * -----
 * File Created: Sunday, 24th January 2021 12:52:10 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:36:44 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

module alu #(parameter WORD_W = 8, OP_W = 3)
            (input logic clock, n_reset, ACC_bus, load_ACC, ALU_ACC, ALU_add, ALU_sub, ALU_xor,
             inout wire [WORD_W-1:0] sysbus,
             output logic z_flag);
		    
logic [WORD_W-1:0] acc;

assign sysbus = ACC_bus ? acc : 'z;
assign z_flag = acc == 0 ? 1'b1 :1'b0;

always_ff @(posedge clock, negedge n_reset)
  begin
  if (!n_reset)
    acc <= 0;
  else
    if (load_ACC)
      if (ALU_ACC)
        begin
        if (ALU_add)
          acc <= acc + sysbus;
        else if (ALU_sub)
          acc <= acc - sysbus;
        else if (ALU_xor)
          acc <= acc ^ sysbus;
        end
      else
        acc <= sysbus;
  end
endmodule