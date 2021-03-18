/*
 * Project: cpu 2021
 * File: cpu 2021/testcpu.sv
 * -----
 * File Created: Sunday, 24th January 2021 12:52:10 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:37:37 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

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