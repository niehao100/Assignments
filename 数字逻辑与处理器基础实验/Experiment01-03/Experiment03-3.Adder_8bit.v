module adder_8bit(
  a,
  b,
  cin,
  s,
  cout);
  
  input [7:0] a;
  input [7:0] b;
  input cin;
  
  output [7:0] s;
  output cout;
  
  wire [7:0] a;
  wire [7:0] b;
  wire cin;
  wire [7:0] s;
  wire cout;
  wire c;
  
  adder_4bit_lookahead adder1(a[3:0],b[3:0],cin,s[3:0],c);
  adder_4bit_lookahead adder2(a[7:4],b[7:4],c,s[7:4],cout);
  
endmodule
