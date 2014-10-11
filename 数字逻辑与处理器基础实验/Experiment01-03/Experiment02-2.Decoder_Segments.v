module decoder_segments(
  x,
  a,
  b,
  c,
  d,
  e,
  f,
  g);
  
  input [3:0] x;
  
  output a;
  output b;
  output c;
  output d;
  output e;
  output f;
  output g;
  
  wire [3:0] x;
  reg a;
  reg b;
  reg c;
  reg d;
  reg e;
  reg f;
  reg g;
  
  always @ (*)
  begin
    a <= !x[3]&!x[2]&!x[1]&x[0] | !x[3]&x[2]&!x[1]&!x[0] | x[3]&x[2]&!x[1]&x[0] | x[3]&!x[2]&x[1]&x[0];
    b <= !x[3]&x[2]&!x[1]&x[0] | x[2]&x[1]&!x[0] | x[3]&x[2]&x[1] | x[3]&x[2]&!x[0] | x[3]&x[1]&x[0];
    c <= !x[3]&!x[2]&x[1]&!x[0] | x[3]&x[2]&x[1] | x[3]&x[2]&!x[0];
    d <= !x[3]&!x[2]&!x[1]&x[0] | !x[3]&x[2]&!x[1]&!x[0] | x[2]&x[1]&x[0] | x[3]&!x[2]&x[1]&!x[0];
    e <= !x[3]&x[0] | !x[3]&x[2]&!x[1] | x[3]&!x[2]&!x[1]&x[0];
    f <= !x[3]&!x[2]&x[0] | !x[3]&!x[2]&x[1] | !x[3]&x[1]&x[0] | x[3]&x[2]&!x[1]&x[0];
    g <= !x[3]&!x[2]&!x[1] | !x[3]&x[2]&x[1]&x[0] | x[3]&x[2]&!x[1]&!x[0];
  end
  
endmodule

