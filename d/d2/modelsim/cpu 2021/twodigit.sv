module twodigit(input logic[5:0] address,
                output logic [6:0] HEX0, HEX1);

logic [3:0] tensbcd, onesbcd;

sevenseg s0 (.data(HEX0), .address(onesbcd));
sevenseg s1 (.data(HEX1), .address(tensbcd));

always_comb
begin
    onesbcd = address % 10;
    tensbcd = address / 10;  
end

endmodule