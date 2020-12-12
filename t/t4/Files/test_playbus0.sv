module test_playbus0;

logic [6:0] disp0, disp1;  
logic [3:0] sw0;
logic RAMO, ROMO, SWBEN, RAMW, LEDLTCH, n_clk;

playbus0 p0 (.*);

initial
  begin
  /* Initial values */
  RAMO = 0;
  ROMO = 0;
  SWBEN = 0;
  RAMW = 0;
  LEDLTCH = 0;
  sw0 = 4'b0000;
  n_clk = 0;

  #20ns

  /* Read data from EPROM at address 5 onto bus */
  ROMO = 1;
  #10ns ROMO = 0;

  #20ns

  /* Read data from RAM at address 5 onto bus */
  RAMO = 1;
  #10ns RAMO = 0;

  #20ns

  sw0 = 4'b0010;
  /* Read data from Switches onto bus */
  SWBEN = 1;
  #10ns SWBEN = 0;

  #20ns

  sw0 = 4'b0001;
  /* Copy data from Switches into RAM address 5 */
  n_clk = 1;
  SWBEN = 1;
  RAMW = 1;
  #10ns n_clk = 0;
  #10ns SWBEN = 0;
  RAMW = 0;

  #20ns

  /* Checking RAM value */
  RAMO = 1;
  #10ns RAMO = 0;

  #20ns

  /* Copy data from EPROM into RAM address 5 */
  n_clk = 1;
  ROMO = 1;
  RAMW = 1;
  #10ns n_clk = 0;
  #10ns ROMO = 0;
  RAMW = 0;

  #20ns

  /* Checking RAM value */
  RAMO = 1;
  #10ns RAMO = 0;

  #20ns

  sw0 = 4'b0110;
  /* Copy data from Switches into LEDs */
  n_clk = 1;
  SWBEN = 1;
  LEDLTCH = 1;
  #10ns n_clk = 0;
  #10ns SWBEN = 0;
  LEDLTCH = 0;

  #20ns

  /* Copy data from EPROM at address into LEDs */
  n_clk = 1;
  ROMO = 1;
  LEDLTCH = 1;
  #10ns n_clk = 0;
  #10ns ROMO = 0;
  LEDLTCH = 0;

  #20ns

  /* Copy data from RAM at address into LEDs */
  n_clk = 1;
  RAMO = 1;
  LEDLTCH = 1;
  #10ns n_clk = 0;
  #10ns RAMO = 0;
  LEDLTCH = 0;

  end 
  
endmodule
  