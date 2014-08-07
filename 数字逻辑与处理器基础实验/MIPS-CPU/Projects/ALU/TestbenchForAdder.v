module TestbenchForAdder(A,B,S,cout,cin);
  output[31:0] A,B,S;
  output cin;
  output [1:0] cout;
  
  reg cin;
  reg[31:0] A,B;
  
  initial
  begin
    cin = 0;
    A = 32'd12345;
    B = 32'd54321;
    #10 cin = 1;
    #10 A = 32'd23333;
    #10 B = 32'd88888;
    #10 A = 32'd2147483647;
    #10 cin = 1;
    #10 B = 32'd2644546165;
    #10 A = 32'd123456789;
    #10 B = -123456789;
  end
  KS_ADD adder(A,B,S,cout,cin);
endmodule
