module controller (input logic clk, input logic [2:0] func,
                   output logic ROMO, RAMO, RAMW, SWBEN, LEDLTCH);
                   
enum {start, xfer} present_state, next_state;

always_ff @(posedge clk)
  present_state <= next_state;
  
always_comb
  begin
  ROMO = '0;
  RAMO = '0;
  RAMW = '0;
  SWBEN = '0;
  LEDLTCH = '0;
  next_state = present_state;
  case (present_state)
  start: 
    begin
    /* ROM0 */
    if ((func == 0) || (func == 4) || (func == 6))
      begin
      ROMO = '1;
      end

    /* RAMO */
    if ((func == 1) || (func == 7))
      begin
      RAMO = '1;
      end

     /* SWBEN */
    if ((func == 2) || (func == 3) || (func == 5))
      begin
      SWBEN = '1;
      end

    /* RAMW, write from bus */
    if ((func == 3) || (func == 4))
      begin
      RAMW = '1;
      next_state = xfer;
      end

    /* LEDLTCH, write from bus */
    if ((func == 5) || (func == 6) || (func == 7))
      begin
      LEDLTCH = '1;
      next_state = xfer;
      end;
    end  
  xfer : next_state = start;
    endcase
  end 
                   
endmodule