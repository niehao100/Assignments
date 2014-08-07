module TestbenchForShift(A,B,S,right,Sign);
  output [31:0] A,B,S;
  output right,Sign;
  
  reg [31:0] A,B;
  reg right,Sign;
  
  initial
  begin
    right = 0;
    Sign = 0;
    A = 32'd24;
    B = 32'd4;
    #10 right = 1;
    #10 A = 32'd4;
    #10 B = 32'd88888;
    #10 A = 32'd9;
    #10 right = 0;
    #10 B = 32'd2644546165;
    #10 A = 32'd25;
    #10 right = 1;
    #10 B = -123456789;
    #10 Sign = 1;
  end
  ALU_SHIFT shift(A,B,S,right,Sign);
endmodule
