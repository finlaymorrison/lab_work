module dffe (output logic Q, input logic D, enable, clock)

always_ff @(posedge clock)
    if (enable)
        D <= Q;

endmodule

