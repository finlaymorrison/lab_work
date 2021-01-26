module buffer #(parameter WORD_W = 8, OP_W = 3)
               (inout wire [WORD_W-1:0] sysbus, input logic [WORD_W-1:0] switches, 
                input logic load_MAR, MDR_bus, R_NW, clock, n_reset);

logic [WORD_W-OP_W-1:0] mar;

//The buffer is hard-wired at address 30

assign sysbus = (MDR_bus & (mar==30)) ? switches : 'z;

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

  
endmodule