module multiplexer_4to1(
  c,
  s,
  y,
  cc,
  ss);
  
  input [3:0] c;
  input [1:0] s;
  
  output [3:0] cc;
  output [1:0] ss;
  output y;
  
  wire [3:0] c;
  wire [1:0] s;
  wire [3:0] cc;
  wire [1:0] ss;
  wire y;
  wire [1:0]t;
  
  assign cc=c;
  assign ss=s;
  
  multiplexer_2to1 mux1(c[0],c[1],s[0],t[0]);
  multiplexer_2to1 mux2(c[2],c[3],s[0],t[1]);
  multiplexer_2to1 mux3(t[0],t[1],s[1],y);
  
endmodule

