module cpu1 #(parameter WORD_W = 8, OP_W = 3)
                  (input logic clock, n_reset,
                   inout wire [WORD_W-1:0] sysbus);
		   
logic ACC_bus, load_ACC, PC_bus, load_PC, load_IR, load_MAR,
MDR_bus, load_MDR, ALU_ACC, ALU_add, ALU_sub, INC_PC,
Addr_bus, CS, R_NW, z_flag;

logic [OP_W-1:0] op;


sequencer #(.WORD_W(WORD_W), .OP_W(OP_W)) s1  (.*);

ir #(.WORD_W(WORD_W), .OP_W(OP_W)) i1  (.*);

pc #(.WORD_W(WORD_W), .OP_W(OP_W)) p1 (.*);

alu #(.WORD_W(WORD_W), .OP_W(OP_W)) a1 (.*);

ram #(.WORD_W(WORD_W), .OP_W(OP_W)) r1 (.*);

rom #(.WORD_W(WORD_W), .OP_W(OP_W)) r2 (.*);


endmodule