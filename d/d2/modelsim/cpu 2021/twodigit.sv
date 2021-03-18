/*
 * Project: cpu 2021
 * File: cpu 2021/twodigit.sv
 * -----
 * File Created: Sunday, 24th January 2021 10:59:42 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:37:39 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

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