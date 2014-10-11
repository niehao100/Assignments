module multiplexer_2to1_hazard(
  a,  //Input 1
  b,  //Input 2
  s,  //Switch 1
  y); //Output
  
  input a;
  input b;
  input s;

  output y;

  wire a;
  wire b;
  wire s;
  reg y;
  reg t0;
  reg t1;
  reg t2;
  
  always @(*)
  begin
    //y<=a&!s|b&s;
    t0<=~s;
    t1<=a&t0;
    t2<=b&s;
    y<=t1|t2;
  end
  
endmodule

module multiplexer_2to1(
  a,  //Input 1
  b,  //Input 2
  s,  //Switch 1
  y, //Output
  aa,
  bb,
  ss);
  
  input a;
  input b;
  input s;

  output aa;
  output bb;
  output ss;
  output y;

  wire a;
  wire b;
  wire s;
  wire aa;
  wire bb;
  wire ss;
  reg y;
  reg t0;
  reg t1;
  reg t2;
  reg t3;
  
  assign aa=a;
  assign bb=b;
  assign ss=s;
  
  always @(*)
  begin
    //y<=a&!s|b&s;
    t0<=~s;
    t1<=a&t0;
    t2<=b&s;
    t3<=a&b;
    y<=t1|t2|t3;
  end
  
endmodule
