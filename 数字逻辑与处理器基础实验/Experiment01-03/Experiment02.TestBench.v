module testbench1(
  a,
  d);
  
  output [2:0] a;
  output [7:0] d;

  reg [2:0] a;
  wire [7:0] d;
  
  initial
  begin
    a=0;
    #20 a=1;
    #20 a=2;
    #20 a=3;
    #20 a=4;
    #20 a=5;
    #20 a=6;
    #20 a=7;
    #20 $stop;
  end
  
  decoder_3to8 decoder1(a,d);
endmodule

module testbench2(
  x,
  a,
  b,
  c,
  d,
  e,
  f,
  g);
  
  output [3:0] x;
  output a;
  output b;
  output c;
  output d;
  output e;
  output f;
  output g;
  
  reg [3:0] x;
  wire a;
  wire b;
  wire c;
  wire d;
  wire e;
  wire f;
  wire g;
  
  initial
  begin
    x=0;
    #20 x=1;
    #20 x=2;
    #20 x=3;
    #20 x=4;
    #20 x=5;
    #20 x=6;
    #20 x=7;
    #20 x=8;
    #20 x=9;
    #20 x=10;
    #20 x=11;
    #20 x=12;
    #20 x=13;
    #20 x=14;
    #20 x=15;
    #20 $stop;
  end
  
  decoder_segments decoder2(x,a,b,c,d,e,f,g);
endmodule
