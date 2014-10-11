module testbench1(
  a,
  b,
  cin,
  s,
  cout);
  
  output [3:0] a;
  output [3:0] b;
  output cin;
  output [3:0] s;
  output cout;
  
  reg [3:0] a;
  reg [3:0] b;
  reg cin;
  wire [3:0] s;
  wire cout;
  
  initial
  begin
    a=0;
    b=0;
    cin=0;
    #20 a=1;
    #20 b=1;
    #20 b=2;
    #20 cin=1;
    #20 b=3;
    #20 a=2;
    #20 a=8;
    #20 cin=0;
    #20 b=15;
    #20 $stop;
  end
  
  adder_4bit_ripple adder1(a,b,cin,s,cout);
endmodule

module testbench2(
  a,
  b,
  cin,
  s,
  cout);
  
  output [3:0] a;
  output [3:0] b;
  output cin;
  output [3:0] s;
  output cout;
  
  reg [3:0] a;
  reg [3:0] b;
  reg cin;
  wire [3:0] s;
  wire cout;
  
  initial
  begin
    a=0;
    b=0;
    cin=0;
    #20 a=1;
    #20 b=1;
    #20 b=2;
    #20 cin=1;
    #20 b=3;
    #20 a=2;
    #20 a=8;
    #20 cin=0;
    #20 b=15;
    #20 $stop;
  end
  
  adder_4bit_lookahead adder1(a,b,cin,s,cout);
endmodule

module testbench3(
  a,
  b,
  cin,
  s,
  cout);
  
  output [7:0] a;
  output [7:0] b;
  output cin;
  output [7:0] s;
  output cout;
  
  reg [7:0] a;
  reg [7:0] b;
  reg cin;
  wire [7:0] s;
  wire cout;
  
  initial
  begin
    a=0;
    b=0;
    cin=0;
    #20 a=6;
    #20 b=8;
    #20 b=232;
    #20 cin=1;
    #20 b=23;
    #20 a=2;
    #20 a=77;
    #20 cin=0;
    #20 b=15;
    #20 $stop;
  end
  
  adder_8bit adder1(a,b,cin,s,cout);
endmodule

module testbench4(
  a,
  b,
  s,
  sign);
  
  output [3:0] a;
  output [3:0] b;
  output [3:0] s;
  output sign;
  
  reg [3:0] a;
  reg [3:0] b;
  wire [3:0] s;
  wire sign;
  
  initial
  begin
    a=0;
    b=0;
    #20 a=1;
    #20 b=1;
    #20 b=7;
    #20 b=3;
    #20 a=3;
    #20 a=8;
    #20 b=15;
    #20 $stop;
  end
  
  subtracter_4bit subtracter(a,b,s,sign);
endmodule
