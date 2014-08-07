module ALU_SHIFT(A,B,S,right,Sign);
  input [4:0] A;
  input [31:0] B;
  input Sign,right;
  output [31:0] S;
  
  wire [63:0] phase1,phase2,phase3,phase4,phase5,phase6;
  wire [4:0] shamt;
  assign shamt[4:0] = A[4:0]^{5{right}};
  
  wire [63:0] phase0 = right?{B,{32{Sign&B[31]}}}:{32'd0,B};
  
  sll_1  shift__1bit(shamt[0],phase0,phase1);
  sll_2  shift__2bit(shamt[1],phase1,phase2);
  sll_4  shift__4bit(shamt[2],phase2,phase3);
  sll_8  shift__8bit(shamt[3],phase3,phase4);
  sll_16 shift_16bit(shamt[4],phase4,phase5);
  sll_1  shift_right(right   ,phase5,phase6);
  
  assign S = phase6[31:0];
  
endmodule

module sll_1(flag,B,S);
  input [63:0] B;
  input flag;
  output [63:0] S;
  
  assign S[63:0] = flag?{B[62:0],B[63]}:B[63:0];
endmodule

module sll_2(flag,B,S);
  input [63:0] B;
  input flag;
  output [63:0] S;
  
  assign S[63:0] = flag?{B[61:0],B[63:62]}:B[63:0];
endmodule

module sll_4(flag,B,S);
  input [63:0] B;
  input flag;
  output [63:0] S;
  
  assign S[63:0] = flag?{B[59:0],B[63:60]}:B[63:0];
endmodule

module sll_8(flag,B,S);
  input [63:0] B;
  input flag;
  output [63:0] S;
  
  assign S[63:0] = flag?{B[55:0],B[63:56]}:B[63:0];
endmodule

module sll_16(flag,B,S);
  input [63:0] B;
  input flag;
  output [63:0] S;
  
  assign S[63:0] = flag?{B[47:0],B[63:48]}:B[63:0];
endmodule
