module d_latch(d,enable,reset,clk,q,q_inverse);
  input d;
  input enable; //低电平有效
  input reset;  //高电平有效
  input clk;
  output q;
  output q_inverse;

  wire d;
  wire enable;
  wire reset;
  wire clk;
  reg q;
  reg q_inverse;

  always @ (posedge clk,posedge reset)
  begin
    q<=reset?1'b0:(enable&q|~enable&d);
    q_inverse<=reset?1'b1:(enable&q_inverse|~enable&~d);
  end
endmodule

module synchronous_up_counter(clk,reset,count);
  input clk;
  input reset;
  output [3:0] count;

  wire clk;
  wire reset;
  wire [3:0] count;

  d_latch d0(q_inverse0,1'b0,reset,clk,count[0],q_inverse0);
  d_latch d1(q_inverse1,q_inverse0,reset,clk,count[1],q_inverse1);
  d_latch d2(q_inverse2,enable2,reset,clk,count[2],q_inverse2);
  d_latch d3(q_inverse3,enable3,reset,clk,count[3],q_inverse3);
  nand nand_gate1(enable2,count[1],count[0]);
  nand nand_gate2(enable3,count[2],count[1],count[0]);

endmodule

module synchronous_up_counter_debounced(sysclk,clk,reset,count);
  input sysclk;
  input clk;
  input reset;
  output [3:0] count;

  wire sysclk;
  wire clk;
  wire reset;
  wire [3:0] count;
  debounce (sysclk,clk,clk_o);
  synchronous_up_counter counter1(clk_o,reset,count);
endmodule
