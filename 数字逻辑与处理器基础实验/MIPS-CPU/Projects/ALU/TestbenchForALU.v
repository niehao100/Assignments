module  TestbenchForALU(A,B,ALUFun,Sign,S);
  output[31:0] A,B,S;
  output[5:0] ALUFun;
  output Sign;
  
  reg Sign;
  reg[5:0] ALUFun;
  reg[31:0] A,B;
  
  initial
  begin
    Sign = 1;
    ALUFun = 6'b000000;
    A = 32'd4;
    B = 32'd36;
    #10 ALUFun = 6'b000001;
    #10 ALUFun = 6'b011000;
    #10 ALUFun = 6'b011110;
    #10 ALUFun = 6'b010110;
    #10 ALUFun = 6'b010001;
    #10 ALUFun = 6'b011010;
    #10 ALUFun = 6'b100000;
    #10 ALUFun = 6'b100001;
    #10 ALUFun = 6'b100011;
    #10 ALUFun = 6'b110011;
    #10 ALUFun = 6'b110001;
    #10 ALUFun = 6'b110101;
    #10 ALUFun = 6'b111101;
    #10 ALUFun = 6'b111001;
    #10 ALUFun = 6'b111111;
    #10 A = 32'd23333;
    B = 32'd23333;
    ALUFun = 6'b000000;
    #10 ALUFun = 6'b000001;
    #10 ALUFun = 6'b011000;
    #10 ALUFun = 6'b011110;
    #10 ALUFun = 6'b010110;
    #10 ALUFun = 6'b010001;
    #10 ALUFun = 6'b011010;
    #10 ALUFun = 6'b100000;
    #10 ALUFun = 6'b100001;
    #10 ALUFun = 6'b100011;
    #10 ALUFun = 6'b110011;
    #10 ALUFun = 6'b110001;
    #10 ALUFun = 6'b110101;
    #10 ALUFun = 6'b111101;
    #10 ALUFun = 6'b111001;
    #10 ALUFun = 6'b111111;
    
  end
  ALU alu(A,B,ALUFun,Sign,S);
endmodule
