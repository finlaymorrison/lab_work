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