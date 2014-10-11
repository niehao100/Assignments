module testbench1(in,clk,reset,out,fsm);
  output in;
  output clk;
  output reset;
  output out;
  output [2:0] fsm;

  reg in;
  reg clk;
  reg reset;
  wire out;
  wire [2:0] fsm;

  initial
  begin
    clk<=1;
    reset<=1;
    in<=0;
    #3 reset<=0;
    #20 in<=1;
    #10 in<=0;
    #10 in<=1;
    #10 in<=0;
    #10 in<=1;
    #20 in<=0;
    #10 in<=1;
    #10 in<=0;
    #10 in<=1;
    #30 in<=0;
    #30 in<=1;
    #10 in<=0;
    #10 in<=1;
    #10 in<=0;
    #10 in<=1;
    #20 in<=0;
    #20 $stop;
  end

  always @ (*)
  begin
    #5 clk<=~clk;
  end

  sequence_detector_fsm sd1(in,clk,reset,out,fsm);
endmodule

module testbench2(in,clk,reset,out,register);
  output in;
  output clk;
  output reset;
  output out;
  output [5:0] register;

  reg in;
  reg clk;
  reg reset;
  wire out;
  wire [5:0] register;

  initial
  begin
    clk<=0;
    reset<=1;
    in<=0;
    #5 reset<=0;
    #20 in<=1;
    #10 in<=0;
    #10 in<=1;
    #10 in<=0;
    #10 in<=1;
    #20 in<=0;
    #10 in<=1;
    #10 in<=0;
    #10 in<=1;
    #30 in<=0;
    #30 in<=1;
    #10 in<=0;
    #10 in<=1;
    #10 in<=0;
    #10 in<=1;
    #20 in<=0;
    #20 $stop;
  end

  always @ (*)
  begin
    #5 clk<=~clk;
  end

  sequence_detector_shift sd2(in,clk,reset,out,register);
endmodule
