/////////////////////////////////////////////////////////////////////
// Design unit: cpu2
//            :
// File name  : cpu2.sv
//            :
// Description: Top level of basic processor
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
//            : Version 1.2 11/12/14
//            : Version 1.3 15/01/18
//            : Version 1.4 08/01/21 - For remote working
/////////////////////////////////////////////////////////////////////

module cpu_3_sevenseg #(parameter WORD_W = 8, OP_W = 3)
             (input logic clock, n_reset,
              inout wire [WORD_W-1:0] sysbus,
              input logic [WORD_W-1:0] switches,
              output logic[6:0] HEX0, HEX1);
		   
logic ACC_bus, load_ACC, PC_bus, load_PC, load_IR, load_MAR,
MDR_bus, load_MDR, ALU_ACC, ALU_add, ALU_sub, INC_PC,
Addr_bus, CS, R_NW, z_flag, ALU_xor;

logic [OP_W-1:0] op;

logic [WORD_W-1:0] display;

twodigit d0 (.address(display), .HEX0(HEX0), .HEX1(HEX1));

register #(.WORD_W(WORD_W), .OP_W(OP_W)) r3 (.*);

buffer #(.WORD_W(WORD_W), .OP_W(OP_W)) b1 (.*);

sequencer #(.WORD_W(WORD_W), .OP_W(OP_W)) s1  (.*);

ir #(.WORD_W(WORD_W), .OP_W(OP_W)) i1  (.*);

pc #(.WORD_W(WORD_W), .OP_W(OP_W)) p1 (.*);

alu #(.WORD_W(WORD_W), .OP_W(OP_W)) a1 (.*);

ram #(.WORD_W(WORD_W), .OP_W(OP_W)) r1 (.*);

rom #(.WORD_W(WORD_W), .OP_W(OP_W)) r2 (.*);


endmodule