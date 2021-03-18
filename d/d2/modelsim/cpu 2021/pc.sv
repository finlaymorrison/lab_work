/*
 * Project: cpu 2021
 * File: cpu 2021/pc.sv
 * -----
 * File Created: Sunday, 24th January 2021 12:52:10 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:37:14 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

module pc #(parameter WORD_W = 8, OP_W = 3)
               (input logic clock, n_reset, PC_bus, load_PC, INC_PC, 
                inout wire [WORD_W-1:0] sysbus);
		
logic [WORD_W-OP_W-1:0] count;

assign sysbus = PC_bus ? {{OP_W{1'b0}},count} : 'z;

always_ff @(posedge clock, negedge n_reset)
  begin
  if (!n_reset)
    count <= 0;
  else
    if (load_PC)
      if (INC_PC)
        count <= count + 1;
      else
	count <= sysbus;
  end
endmodule