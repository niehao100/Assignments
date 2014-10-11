module adder_4bit_lookahead(
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
  wire [3:0] g;
  wire [3:0] p;
  
  assign g=a&b;
  assign p=a^b;
  
  assign cout=g[3] | p[3]&g[2] | p[3]&p[2]&g[1] | p[3]&p[2]&p[1]&g[0] | p[3]&p[2]&p[1]&p[0]&cin;
  assign s[0]=p[0]^cin;
  assign s[1]=p[1]^(g[0]|p[0]&cin);
  assign s[2]=p[2]^(g[1]|p[1]&g[0]|p[1]&p[0]&cin);
  assign s[3]=p[3]^(g[2]|p[2]&g[1]|p[2]&p[1]&g[0]|p[2]&p[1]&p[0]&cin);
  
endmodule
