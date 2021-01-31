/////////////////////////////////////////////////////////////////////
// Design unit: TestCPU
//            :
// File name  : testcpu.sv
//            :
// Description: Simple testbench for basic processor
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
//            : Version 1.2 19/12/17
//            : Version 1.3 08/01/21 - For remote working
/////////////////////////////////////////////////////////////////////

module testcpu;

parameter int WORD_W = 8, OP_W = 3;

logic  clock, n_reset;
wire [WORD_W-1:0] sysbus;
logic [WORD_W-1:0] switches;
logic [WORD_W-1:0] display;

cpu3 #(.WORD_W(WORD_W), .OP_W(OP_W)) c1 (.*);

always
  begin
#10ns clock = 1'b1;
#10ns clock = 1'b0;
end

initial
begin
switches = 8'b00000001;
n_reset = 1'b1;
#1ns n_reset = 1'b0;
#2ns n_reset = 1'b1;

switches = 5'b01111;
#1ms switches = 5'b01001;
#1ms switches = 5'b11001;
#1ms switches = 5'b10100;
#1ms switches = 5'b01101;
#1ms switches = 5'b01101;
#1ms switches = 5'b10110;
#1ms switches = 5'b01011;

end

endmodule