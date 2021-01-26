/////////////////////////////////////////////////////////////////////
// Design unit: ram
//            :
// File name  : ram.sv
//            :
// Description: Synchronous RAM for basic processor
//            :
// Limitations: None
//            : 
// System     : SystemVerilog IEEE 1800-2005
//            :
// Author     : Mark Zwolinski
//            : School of Electronics and Computer Science
//            : University of Southampton
//            : Southampton SO17 1BJ, UK
//            : mz@ecs.soton.ac.uk
//
// Revision   : Version 1.0 05/08/08
//            : Version 1.1 17/12/13
//            : Version 1.2 12/12/14 Only map top half of address range
//            : Version 1.3 14/01/21 Simplified some of the syntax
/////////////////////////////////////////////////////////////////////

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