module sequence_detector_shift(in,clk,reset,out,register);
  input in;
  input clk;
  input reset;
  output out;
  output [5:0] register;

  wire in;
  wire clk;
  wire reset;
  wire out;
  wire [5:0] register;

  flipflop_rtl ff0(in,0,reset,register[0],,clk);
  flipflop_rtl ff1(register[0],0,reset,register[1],,clk);
  flipflop_rtl ff2(register[1],0,reset,register[2],,clk);
  flipflop_rtl ff3(register[2],0,reset,register[3],,clk);
  flipflop_rtl ff4(register[3],0,reset,register[4],,clk);
  flipflop_rtl ff5(register[4],0,reset,register[5],,clk);

  flipflop_rtl ff(register==6'b101011,0,reset,out,,clk);

endmodule

module sequence_detector_shift_debounced(sysclk,in,clk,reset,out,register);
  input sysclk;
  input in;
  input clk;
  input reset;
  output out;
  output [5:0] register;

  wire sysclk;
  wire in;
  wire clk;
  wire reset;
  wire out;
  wire [5:0] register;

  debounce debounce_clk(sysclk,clk,clk_o);
  debounce debounce_reset(sysclk,reset,reset_o);
  sequence_detector_shift sd1(in,clk_o,reset_o,out,register);
endmodule
