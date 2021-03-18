/*
 * Project: t4
 * File: t4/tristate.sv
 * -----
 * File Created: Sunday, 24th January 2021 11:10:01 am
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:38:16 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

module tristate (output logic C, input logic A, B)

always_comb
    C = B ? A : 'z;

endmodule

