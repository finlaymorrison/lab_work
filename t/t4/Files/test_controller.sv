module test_controller;

logic clk; 
logic [2:0] func;
logic ROMO, RAMO, RAMW, SWBEN, LEDLTCH;

controller asm (.*);

initial
  begin
  clk = 0;
  func = 0;
  #10ns clk = 1;

  #20ns

  clk = 0;
  func = 1;
  #10ns clk = 1;

  #20ns

  clk = 0;
  func = 2;
  #10ns clk = 1;

  #20ns

  clk = 0;
  func = 3;
  #10ns clk = 1;
  #10ns clk = 0;
  #10ns clk = 1;

  #20ns

  clk = 0;
  func = 4;
  #10ns clk = 1;
  #10ns clk = 0;
  #10ns clk = 1;

  #20ns

  clk = 0;
  func = 5;
  #10ns clk = 1;
  #10ns clk = 0;
  #10ns clk = 1;

  #20ns

  clk = 0;
  func = 6;
  #10ns clk = 1;
  #10ns clk = 0;
  #10ns clk = 1;

  #20ns

  clk = 0;
  func = 7;
  #10ns clk = 1;
  #10ns clk = 0;
  #10ns clk = 1;
  end
  
endmodule