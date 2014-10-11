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

module mutiplier(a,b,clk,reset,product,done);
  input [1:0] a;
  input [1:0] b;
  input clk;
  input reset;
  output [3:0] product;
  output done;  //高电平表示计算完成,低电平使能

  wire [1:0] a;
  wire [1:0] b;
  wire clk;
  wire reset;
  wire [3:0] product;
  wire done;

  wire [3:0] count;

  accumulator accumulator1({2'b00,a},clk,done,reset,product,);

  synchronous_up_counter counter1(clk|done,reset,count);

  assign done=(count[1:0]==b);


endmodule

module mutiplier_debounced(sysclk,a,b,clk,reset,product,done);
  input sysclk;
  input [1:0] a;
  input [1:0] b;
  input clk;
  input reset;
  output [3:0] product;
  output done;  //高电平表示计算完成,低电平使能

  wire sysclk;
  wire [1:0] a;
  wire [1:0] b;
  wire clk;
  wire reset;
  wire [3:0] product;
  wire done;

  debounce debounce_clk(sysclk,clk,clk_o);
  mutiplier mutiplier1(a,b,clk_o,reset,product,done);
endmodule
