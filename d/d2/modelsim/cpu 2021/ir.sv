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