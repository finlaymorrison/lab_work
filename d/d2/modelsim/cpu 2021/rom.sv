module rom #(parameter WORD_W = 8, OP_W = 3)
               (input logic clock, n_reset, MDR_bus, load_MDR, load_MAR, CS, R_NW,
                inout wire [WORD_W-1:0] sysbus);

`include "opcodes.h"
		
logic [WORD_W-OP_W-1:0] mar;
logic [WORD_W-1:0] mdr;


assign sysbus = (MDR_bus & ~mar[WORD_W-OP_W-1]) ? mdr : 'z;
// mar[WORD_W-OP_W-1] is most significant bit of address
//See comments in RAM and notice the difference here

always_ff @(posedge clock, negedge n_reset)
  begin
  if (!n_reset)
    begin 
    mar <= 0;
    end
  else
    if (load_MAR)
      mar <= sysbus[WORD_W-OP_W-1:0];
  end


always_comb
  begin
  mdr = 0;
  case (mar)
    0: mdr = {`LOAD, 5'd30};
    1: mdr = {`XOR, 5'd15};
    2: mdr = {`STORE, 5'd31};
    3: mdr = {`LOAD, 5'd15};
    4: mdr = {`BNE, 5'd14};
    14: mdr = 0;
    15: mdr = 10;
    default: mdr = 0;
  endcase
  end
  
endmodule