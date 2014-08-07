module ALU_CMP(Z,N,ALUFunc,S);
  input Z;
  input N;
  input [2:0] ALUFunc;
  output [31:0] S;
  
  assign S=(ALUFunc==3'b001&  Z   |
            ALUFunc==3'b000& ~Z   |
            ALUFunc==3'b010&  N   |
            ALUFunc==3'b110& (N|Z)|
            ALUFunc==3'b100& ~N   |
            ALUFunc==3'b111&~N&~Z)?32'd1:32'd0;
  
endmodule
