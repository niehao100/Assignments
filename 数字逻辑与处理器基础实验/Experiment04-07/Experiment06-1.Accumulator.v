`include "../Experiment01-03/Experiment03-2.Adder_4bit_Lookahead.v"
module d_latch(d,enable,reset,clk,q,q_inverse);
  input d;
  input enable; //低电平使能
  input reset;  //高电平重置
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

module accumulator(addin,clk,enable,reset,sum,overflow);
  input [3:0] addin;
  input clk;
  input enable; //低电平使能
  input reset;  //高电平重置
  output [3:0] sum;
  output overflow;

  wire [3:0] addin;
  wire clk;
  wire enable;
  wire reset;
  wire [3:0] sum;
  wire [3:0] temp;
  wire overflow;

  adder_4bit_lookahead adder0(addin,sum,1'b0,temp,temp_overflow);

  d_latch d0(temp[0],enable,reset,clk,sum[0],);
  d_latch d1(temp[1],enable,reset,clk,sum[1],);
  d_latch d2(temp[2],enable,reset,clk,sum[2],);
  d_latch d3(temp[3],enable,reset,clk,sum[3],);
  d_latch d_overflow(temp_overflow,enable,reset,clk,overflow,);

endmodule

module accumulator_debounced(sysclk,addin,clk,enable,reset,sum,overflow);
  input sysclk;
  input [3:0] addin;
  input clk;
  input enable; //低电平使能
  input reset;  //高电平重置
  output [3:0] sum;
  output overflow;

  wire sysclk;
  wire [3:0] addin;
  wire clk;
  wire enable;
  wire reset;
  wire [3:0] sum;
  wire overflow;

  debounce (sysclk,clk,clk_o);
  accumulator accumulator1(addin,clk_o,enable,reset,sum,overflow);
endmodule
