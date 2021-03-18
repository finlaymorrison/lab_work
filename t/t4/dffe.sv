/*
 * Project: t4
 * File: t4/dffe.sv
 * -----
 * File Created: Sunday, 24th January 2021 11:10:01 am
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:38:14 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

module dffe (output logic Q, input logic D, enable, clock)

always_ff @(posedge clock)
    if (enable)
        D <= Q;

endmodule

