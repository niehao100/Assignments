module ALU_ADD(A,B,Sign,ALUFunc0,S,Z,V,N);
    input [31:0] A,B;
    input Sign,ALUFunc0;
    output [31:0] S;
    output Z,V,N;
    
    wire [31:0] A,B,S;
    wire Sign,ALUFunc0,Z,V,N;
    wire [1:0] cout;
    
    KS_ADD ks(A,B^{32{ALUFunc0}},S,cout,ALUFunc0);
    
    assign Z=cout[1]&~|S;
    assign V=Sign&(^cout)|~Sign&(cout[1]^ALUFunc0);
    assign AxorB=A[31]^B[31];
    assign N=Sign&(ALUFunc0&(~AxorB&(S[31])|AxorB&(A[31]))
      |~ALUFunc0&(AxorB&S[31]|~AxorB&A[31]))
      |~Sign&~cout[1]&ALUFunc0;
endmodule

