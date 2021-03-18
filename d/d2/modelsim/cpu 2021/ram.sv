/*
 * Project: cpu 2021
 * File: cpu 2021/ram.sv
 * -----
 * File Created: Sunday, 24th January 2021 12:52:10 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:37:17 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

module ram #(parameter WORD_W = 8, OP_W = 3)
               (input logic clock, n_reset, MDR_bus, load_MDR, load_MAR, CS, R_NW,
                inout wire [WORD_W-1:0] sysbus);

logic [WORD_W-1:0] mdr;
logic [WORD_W-OP_W-1:0] mar;
logic [WORD_W-1:0] mem [0:(2**(WORD_W-OP_W-1))-1]; //top half of address range
//logic [WORD_W-1:0] mem [0:15]; //top half of address range expressed as integer
//Note that we are using 4 bits of the address, not 5. Most significant bit is used to 
//determine if we use ROM or RAM

assign sysbus = ((MDR_bus & mar[WORD_W-OP_W-1]) && (mar < 5'b11110)) ? mdr : 'z;
// mar[WORD_W-OP_W-1] is most significant bit of address

always_ff @(posedge clock, negedge n_reset)
  begin
  if (!n_reset)
    begin 
    mdr <= 0;
    mar <= 0;
    end
  else
    if (load_MAR)
      mar <= sysbus[WORD_W-OP_W-1:0]; 
    else if (load_MDR)
      mdr <= sysbus;
    else if (CS & mar[WORD_W-OP_W-1])
      if (R_NW)
        mdr <= mem[mar[WORD_W-OP_W-2:0]];
      else
        mem[mar[WORD_W-OP_W-2:0]] <= mdr;
  end


endmodule