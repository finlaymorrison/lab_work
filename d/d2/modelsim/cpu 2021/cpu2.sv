/*
 * Project: cpu 2021
 * File: cpu 2021/cpu2.sv
 * -----
 * File Created: Sunday, 24th January 2021 12:52:10 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:37:01 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

module cpu2 #(parameter WORD_W = 8, OP_W = 3)
             (input logic clock, n_reset,
              inout wire [WORD_W-1:0] sysbus,
              input logic [WORD_W-1:0] switches,
              output logic [WORD_W-1:0] display);
		   
logic ACC_bus, load_ACC, PC_bus, load_PC, load_IR, load_MAR,
MDR_bus, load_MDR, ALU_ACC, ALU_add, ALU_sub, INC_PC,
Addr_bus, CS, R_NW, z_flag;

logic [OP_W-1:0] op;

register #(.WORD_W(WORD_W), .OP_W(OP_W)) r3 (.*);

buffer #(.WORD_W(WORD_W), .OP_W(OP_W)) b1 (.*);

sequencer #(.WORD_W(WORD_W), .OP_W(OP_W)) s1  (.*);

ir #(.WORD_W(WORD_W), .OP_W(OP_W)) i1  (.*);

pc #(.WORD_W(WORD_W), .OP_W(OP_W)) p1 (.*);

alu #(.WORD_W(WORD_W), .OP_W(OP_W)) a1 (.*);

ram #(.WORD_W(WORD_W), .OP_W(OP_W)) r1 (.*);

rom #(.WORD_W(WORD_W), .OP_W(OP_W)) r2 (.*);


endmodule