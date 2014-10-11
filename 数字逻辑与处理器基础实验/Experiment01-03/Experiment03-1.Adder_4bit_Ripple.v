module adder_1bit(
  a,
  b,
  cin,
  s,
  cout);
  
  input a;
  input b;
  input cin;

  output s;
  output cout;

  wire a;
  wire b;
  wire cin;
  wire s;
  wire cout;

  assign s=a^b^cin;
  assign cout=(a^b)&cin|a&b;

endmodule

module adder_4bit_ripple(
  a,
  b,
  cin,
  s,
  cout);
  
  input [3:0] a;
  input [3:0] b;
  input cin;
  
  output [3:0] s;
  output cout;
  
  wire [3:0] a;
  wire [3:0] b;
  wire cin;
  wire [3:0] s;
  wire cout;
  wire [2:0] temp;
  
  adder_1bit adder1(a[0],b[0],cin,s[0],temp[0]);
  adder_1bit adder2(a[1],b[1],temp[0],s[1],temp[1]);
  adder_1bit adder3(a[2],b[2],temp[1],s[2],temp[2]);
  adder_1bit adder4(a[3],b[3],temp[2],s[3],cout);
  
endmodule
