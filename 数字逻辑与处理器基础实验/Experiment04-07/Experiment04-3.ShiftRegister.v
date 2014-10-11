module shift_register(serial_in,parallel_in,set,reset,serial_out,parallel_out,clk);
  input serial_in;
  input [3:0] parallel_in;
  output serial_out;
  output [3:0] parallel_out;
  input set;
  input reset;
  input clk;

  wire serial_in;
  wire [3:0] parallel_in;
  wire serial_out;
  wire [3:0] parallel_out;
  wire set;
  wire reset;
  wire clk;

  flipflop_rtl ff1(set?parallel_in[0]:serial_in,0,reset,parallel_out[0],,clk);
  flipflop_rtl ff2(set?parallel_in[1]:parallel_out[0],0,reset,parallel_out[1],,clk);
  flipflop_rtl ff3(set?parallel_in[2]:parallel_out[1],0,reset,parallel_out[2],,clk);
  flipflop_rtl ff4(set?parallel_in[3]:parallel_out[2],0,reset,parallel_out[3],,clk);
  
  assign serial_out=parallel_out[3];
  
endmodule

module shift_register_debounced(sysclk,serial_in,parallel_in,set,reset,serial_out,parallel_out,clk);
  input sysclk;
  input serial_in;
  input [3:0] parallel_in;
  output serial_out;
  output [3:0] parallel_out;
  input set;
  input reset;
  input clk;

  wire sysclk;
  wire serial_in;
  wire [3:0] parallel_in;
  wire serial_out;
  wire [3:0] parallel_out;
  wire set;
  wire reset;
  wire clk;

  debounce debounce_clk(sysclk,clk,clk_o);
  debounce debounce_reset(sysclk,reset,reset_o);
  shift_register sr1(serial_in,parallel_in,set,reset_o,serial_out,parallel_out,clk_o);
endmodule
