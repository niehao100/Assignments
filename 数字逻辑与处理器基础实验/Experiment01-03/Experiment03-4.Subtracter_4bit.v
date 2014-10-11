module subtracter_4bit(
  a,
  b,
  s,
  sign);
  
  input [3:0] a;
  input [3:0] b;
  
  output [3:0] s;
  output sign;
  
  wire [3:0] a;
  wire [3:0] b;
  wire [3:0] b_inverse;
  wire [3:0] temp1;
  wire [3:0] temp2;
  wire [3:0] s;
  wire sign;
  wire carry;
  
  assign b_inverse=~b;
  
  adder_4bit_lookahead adder1(a[3:0],b_inverse[3:0],1'b1,temp1[3:0],carry);
  assign sign=!carry;
  assign temp2=temp1^{4{~carry}};
  adder_4bit_lookahead adder2(temp2[3:0],4'b0,~carry,s[3:0]);
  
endmodule
