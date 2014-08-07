module TestbenchForALUAdd(A,B,Sign,ALUFunc0,S,Z,V,N);
  output[31:0] A,B,S;
  output ALUFunc0,Sign,Z,V,N;
  
  reg ALUFunc0,Sign;
  reg[31:0] A,B;
  
  initial
  begin
    ALUFunc0 = 0;
    Sign = 1;
    A = 32'd123456789;
    B = -123456789;
    #10 Sign = 0;
    #10 ALUFunc0 = 1;
    #10 Sign = 1;
    #10 A = 32'd23333;
    #10 Sign = 0;
    #10 ALUFunc0 = 0;
    #10 Sign = 1;
    #10 B = 32'd88888;
    #10 Sign = 0;
    #10 A = 32'd2147483647;
    #10 Sign = 1;
    #10 B = 32'd2644546165;
    #10 Sign = 0;
  end
  ALU_ADD adder(A,B,Sign,ALUFunc0,S,Z,V,N);
endmodule
