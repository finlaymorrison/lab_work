module tristate (output logic C, input logic A, B)

always_comb
    C = B ? A : 'z;

endmodule

