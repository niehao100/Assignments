module ALU(A,B,ALUFun,Sign,S);
  input [31:0] A;
  input [31:0] B;
  input [5:0] ALUFun;
  input Sign;
  output [31:0] S;
  
  wire Z,V,N;
  wire [31:0] Sadd,Scmp,Slogic,Sshift,A,B;
  
  ALU_ADD ALU_add(A,B,Sign,ALUFun[0],Sadd,Z,V,N);
  ALU_CMP ALU_cmp(Z,N,ALUFun[3:1],Scmp);
  ALU_LOGIC ALU_logic(A,B,ALUFun[3:1],Slogic);
  ALU_SHIFT ALU_shift(A[4:0],B,Sshift,ALUFun[0],ALUFun[1]);
  
  reg [31:0] S;
  always @ (*)
  begin
    case(ALUFun[5:4])
      2'b00:S=Sadd;
      2'b01:S=Slogic;
      2'b10:S=Sshift;
      2'b11:S=Scmp;
    endcase
  end
endmodule
