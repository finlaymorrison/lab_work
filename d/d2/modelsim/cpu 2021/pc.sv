/////////////////////////////////////////////////////////////////////
// Design unit: pc
//            :
// File name  : pc.sv
//            :
// Description: Program counter for basic processor
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
//            : Version 1.2 14/01/21 Simplified some of the syntax
/////////////////////////////////////////////////////////////////////

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