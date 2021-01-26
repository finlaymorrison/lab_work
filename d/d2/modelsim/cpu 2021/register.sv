module register #(parameter WORD_W = 8, OP_W = 3)
                 (output logic [WORD_W-1:0] display, inout wire [WORD_W-1:0] sysbus, 
                  input logic CS, load_MDR, load_MAR, R_NW, clock, n_reset);

logic [WORD_W-1:0] mdr;
logic [WORD_W-OP_W-1:0] mar;

//The register is "hard-wired" at address 31

always_ff @(posedge clock, negedge n_reset)
  begin
  if (!n_reset)
    begin
    mdr <= 0;
    mar <= 0;
    display <= 0;
    end
  else
    if (load_MAR)
      mar <= sysbus[WORD_W-OP_W-1:0]; 
    else if (load_MDR)
      mdr <= sysbus;
    else if (CS && (mar==31)) // look for address 31 
      if (!R_NW) // Writing, so this signal needs to be low
        display <= mdr;
  end
    
endmodule