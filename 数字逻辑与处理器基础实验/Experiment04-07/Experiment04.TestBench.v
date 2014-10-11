module testbench1(d,set,reset,q,q_inverse,clk);
  output d;
  output set;
  output reset;
  output clk;
  output q;
  output q_inverse;

  reg d;
  reg set;
  reg reset;
  reg clk;
  wire q;
  wire q_inverse;
  
  initial
  begin
    set<=0;
    clk<=0;
    d<=0;
    reset<=0;
    #20 d<=1;
    #20 d<=0;
    #20 set<=1;
    #5 set<=0;
    #20 d<=0;
    #20 d<=1;
    #20 reset<=1;
    #7 reset<=0;
    #20 $stop;
  end
  
  always @ (*)
  begin
    #2 clk<=~clk;
  end
  
  flipflop_gate ff1(d,set,reset,q,q_inverse,clk);
endmodule

module testbench2(d,set,reset,q,q_inverse,clk);
  output d;
  output set;
  output reset;
  output clk;
  output q;
  output q_inverse;

  reg d;
  reg set;
  reg reset;
  reg clk;
  wire q;
  wire q_inverse;
  
  initial
  begin
    set<=0;
    clk<=0;
    d<=0;
    reset<=0;
    #20 d<=1;
    #20 d<=0;
    #20 set<=1;
    #5 set<=0;
    #20 d<=0;
    #20 d<=1;
    #20 reset<=1;
    #7 reset<=0;
    #20 $stop;
  end
  
  always @ (*)
  begin
    #2 clk<=~clk;
  end
  
  flipflop_rtl ff2(d,set,reset,q,q_inverse,clk);
endmodule

module testbench3(serial_in,parallel_in,set,reset,serial_out,parallel_out,clk);
  output serial_in;
  output [3:0] parallel_in;
  output serial_out;
  output [3:0] parallel_out;
  output set;
  output reset;
  output clk;

  reg serial_in;
  reg [3:0] parallel_in;
  wire serial_out;
  wire [3:0] parallel_out;
  reg set;
  reg reset;
  reg clk;
  
  initial
  begin
    set<=0;
    reset<=1;
    clk<=0;
    serial_in<=0;
    parallel_in<=4'b0000;
    #2 reset<=0;
    #10 serial_in<=1;
    #8 serial_in<=0;
    #16 parallel_in<=4'b1001;
    #4 set<=1;
    #4 set<=0;
    #8 reset<=1;
    #10 $stop;
  end
  
  always @ (*)
  begin
    #2 clk<=~clk;
  end
  
  shift_register sr1(serial_in,parallel_in,set,reset,serial_out,parallel_out,clk);
endmodule
