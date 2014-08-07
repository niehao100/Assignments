module ALU_LOGIC(A,B,ALUFunc,S);
  input [31:0] A;
  input [31:0] B;
  input [2:0] ALUFunc;
  output [31:0] S;
  
  wire [31:0] A,B,S,Sand,Sor,Sxor,Snor;
  
  AND ALU_and(A,B,Sand);
  OR  ALU_or (A,B,Sor);
  XOR ALU_xor(A,B,Sxor);
  NOR ALU_nor(A,B,Snor);
  
  assign S=(ALUFunc==4'b100)?Sand:
           (ALUFunc==4'b111)?Sor:
           (ALUFunc==4'b011)?Sxor:
           (ALUFunc==4'b000)?Snor:A;
endmodule

module AND(A,B,S);
  input [31:0]A;
  input [31:0]B;
  output [31:0]S;
  
  and a0(S[0],A[0],B[0]);
  and a1(S[1],A[1],B[1]);
  and a2(S[2],A[2],B[2]);
  and a3(S[3],A[3],B[3]);
  and a4(S[4],A[4],B[4]);
  and a5(S[5],A[5],B[5]);
  and a6(S[6],A[6],B[6]);
  and a7(S[7],A[7],B[7]);
  and a8(S[8],A[8],B[8]);
  and a9(S[9],A[9],B[9]);
  and a10(S[10],A[10],B[10]);
  and a11(S[11],A[11],B[11]);
  and a12(S[12],A[12],B[12]);
  and a13(S[13],A[13],B[13]);
  and a14(S[14],A[14],B[14]);
  and a15(S[15],A[15],B[15]);
  and a16(S[16],A[16],B[16]);
  and a17(S[17],A[17],B[17]);
  and a18(S[18],A[18],B[18]);
  and a19(S[19],A[19],B[19]);
  and a20(S[20],A[20],B[20]);
  and a21(S[21],A[21],B[21]);
  and a22(S[22],A[22],B[22]);
  and a23(S[23],A[23],B[23]);
  and a24(S[24],A[24],B[24]);
  and a25(S[25],A[25],B[25]);
  and a26(S[26],A[26],B[26]);
  and a27(S[27],A[27],B[27]);
  and a28(S[28],A[28],B[28]);
  and a29(S[29],A[29],B[29]);
  and a30(S[30],A[30],B[30]);
  and a31(S[31],A[31],B[31]);
endmodule


module OR(A,B,S);
  input [31:0]A;
  input [31:0]B;
  output [31:0]S;
  
  or o0(S[0],A[0],B[0]);
  or o1(S[1],A[1],B[1]);
  or o2(S[2],A[2],B[2]);
  or o3(S[3],A[3],B[3]);
  or o4(S[4],A[4],B[4]);
  or o5(S[5],A[5],B[5]);
  or o6(S[6],A[6],B[6]);
  or o7(S[7],A[7],B[7]);
  or o8(S[8],A[8],B[8]);
  or o9(S[9],A[9],B[9]);
  or o10(S[10],A[10],B[10]);
  or o11(S[11],A[11],B[11]);
  or o12(S[12],A[12],B[12]);
  or o13(S[13],A[13],B[13]);
  or o14(S[14],A[14],B[14]);
  or o15(S[15],A[15],B[15]);
  or o16(S[16],A[16],B[16]);
  or o17(S[17],A[17],B[17]);
  or o18(S[18],A[18],B[18]);
  or o19(S[19],A[19],B[19]);
  or o20(S[20],A[20],B[20]);
  or o21(S[21],A[21],B[21]);
  or o22(S[22],A[22],B[22]);
  or o23(S[23],A[23],B[23]);
  or o24(S[24],A[24],B[24]);
  or o25(S[25],A[25],B[25]);
  or o26(S[26],A[26],B[26]);
  or o27(S[27],A[27],B[27]);
  or o28(S[28],A[28],B[28]);
  or o29(S[29],A[29],B[29]);
  or o30(S[30],A[30],B[30]);
  or o31(S[31],A[31],B[31]);
endmodule


module XOR(A,B,S);
  input [31:0]A;
  input [31:0]B;
  output [31:0]S;
  
  xor x0(S[0],A[0],B[0]);
  xor x1(S[1],A[1],B[1]);
  xor x2(S[2],A[2],B[2]);
  xor x3(S[3],A[3],B[3]);
  xor x4(S[4],A[4],B[4]);
  xor x5(S[5],A[5],B[5]);
  xor x6(S[6],A[6],B[6]);
  xor x7(S[7],A[7],B[7]);
  xor x8(S[8],A[8],B[8]);
  xor x9(S[9],A[9],B[9]);
  xor x10(S[10],A[10],B[10]);
  xor x11(S[11],A[11],B[11]);
  xor x12(S[12],A[12],B[12]);
  xor x13(S[13],A[13],B[13]);
  xor x14(S[14],A[14],B[14]);
  xor x15(S[15],A[15],B[15]);
  xor x16(S[16],A[16],B[16]);
  xor x17(S[17],A[17],B[17]);
  xor x18(S[18],A[18],B[18]);
  xor x19(S[19],A[19],B[19]);
  xor x20(S[20],A[20],B[20]);
  xor x21(S[21],A[21],B[21]);
  xor x22(S[22],A[22],B[22]);
  xor x23(S[23],A[23],B[23]);
  xor x24(S[24],A[24],B[24]);
  xor x25(S[25],A[25],B[25]);
  xor x26(S[26],A[26],B[26]);
  xor x27(S[27],A[27],B[27]);
  xor x28(S[28],A[28],B[28]);
  xor x29(S[29],A[29],B[29]);
  xor x30(S[30],A[30],B[30]);
  xor x31(S[31],A[31],B[31]);
endmodule


module NOR(A,B,S);
  input [31:0]A;
  input [31:0]B;
  output [31:0]S;
  nor n0(S[0],A[0],B[0]);
  nor n1(S[1],A[1],B[1]);
  nor n2(S[2],A[2],B[2]);
  nor n3(S[3],A[3],B[3]);
  nor n4(S[4],A[4],B[4]);
  nor n5(S[5],A[5],B[5]);
  nor n6(S[6],A[6],B[6]);
  nor n7(S[7],A[7],B[7]);
  nor n8(S[8],A[8],B[8]);
  nor n9(S[9],A[9],B[9]);
  nor n10(S[10],A[10],B[10]);
  nor n11(S[11],A[11],B[11]);
  nor n12(S[12],A[12],B[12]);
  nor n13(S[13],A[13],B[13]);
  nor n14(S[14],A[14],B[14]);
  nor n15(S[15],A[15],B[15]);
  nor n16(S[16],A[16],B[16]);
  nor n17(S[17],A[17],B[17]);
  nor n18(S[18],A[18],B[18]);
  nor n19(S[19],A[19],B[19]);
  nor n20(S[20],A[20],B[20]);
  nor n21(S[21],A[21],B[21]);
  nor n22(S[22],A[22],B[22]);
  nor n23(S[23],A[23],B[23]);
  nor n24(S[24],A[24],B[24]);
  nor n25(S[25],A[25],B[25]);
  nor n26(S[26],A[26],B[26]);
  nor n27(S[27],A[27],B[27]);
  nor n28(S[28],A[28],B[28]);
  nor n29(S[29],A[29],B[29]);
  nor n30(S[30],A[30],B[30]);
  nor n31(S[31],A[31],B[31]);
endmodule
