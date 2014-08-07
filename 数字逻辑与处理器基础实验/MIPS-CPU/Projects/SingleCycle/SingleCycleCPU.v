module SingleCycleCPU(sysclk,clk,reset,LED,SWITCH,DIGIT,TX,RX);
  input sysclk,clk,reset,RX;
  input [7:0] SWITCH;
  output TX;
  output [7:0] LED;
  output [11:0] DIGIT;
  
  wire reset,ALUSrc1,ALUSrc2,LUOp,EXTOp;
  wire [31:0] DataBusA,DataBusB,DataBusC,ALUOut,PCplus4,PCadd,BranchAdd,
    Instruct,ALU_A,ALU_B,LUIin,ExtImm,ConBA,PCin,ILLOP,XADR,MemReadData;
  wire [5:0] ALUFun;
  wire [4:0] AddrC,Rs,Rt,Rd,Shamt,Xp,Ra;
  wire [25:0] JT;
  wire [15:0] Imm16;
  wire [2:0] PCSrc;
  wire [1:0] RegDst,MemToReg;
  
  reg [31:0] PC;
  
  always @ (posedge clk or posedge reset)
  begin
    if(reset)
    begin
      PC <= 32'b0;
    end
    else
    begin
      PC <= PCin;
    end
  end
  
  assign PCin = PCSrc==3'd0 ? PCplus4 :
                PCSrc==3'd1 ? ALUOut[0] ? ConBA : PCplus4 :
                PCSrc==3'd2 ? {PC[31:26],JT} :
                PCSrc==3'd3 ? DataBusA :
                PCSrc==3'd4 ? ILLOP :XADR;
  
  assign ILLOP = 32'h80000004;
  assign XADR  = 32'h80000008;
  assign Xp = 32'd26;
  assign Ra = 32'd31;
  
  assign AddrC = RegDst==2'd0 ? Rd :
                 RegDst==2'd1 ? Rt :
                 RegDst==2'd2 ? Ra : Xp;
                 
  assign ALU_A = ALUSrc1 ? {27'd0,Shamt} : DataBusA;
  assign ALU_B = ALUSrc2 ? LUIin         : DataBusB;
  assign LUIin = LUOp    ? {Imm16,16'd0} : ExtImm;
  assign ExtImm = {{16{EXTOp&Imm16[15]}},Imm16};
  assign DataBusC = MemToReg==2'd0 ? ALUOut :
                    MemToReg==2'd1 ? MemReadData : PCplus4;
  ALU alu0(ALU_A,ALU_B,ALUFun,Sign,ALUOut);
  KS_ADD PCadder(PC,32'd4,PCadd,,1'b0);
  assign PCplus4 = {PC[31],PCadd[30:0]};
  KS_ADD BranchAdder({2'd0,PC[31:2]},ExtImm,BranchAdd,,1'b1);
  assign ConBA = {PC[31],BranchAdd[28:0],2'b0};
  
  RegisterFile reg0(reset,clk,Rs,DataBusA,Rt,DataBusB,RegWr,AddrC,DataBusC);
  
  InstructionMemory mem0(PC,Instruct);
  assign JT = Instruct[25:0];
  assign Imm16 = Instruct[15:0];
  assign Shamt = Instruct[10:6];
  assign Rd = Instruct[15:11];
  assign Rt = Instruct[20:16];
  assign Rs = Instruct[25:21];
  
  DataMemory mem1(reset,sysclk,clk,MemRd,MemWr,ALUOut,DataBusB,MemReadData,LED,SWITCH,DIGIT,TX,RX,IRQ);
  SingleCycleControl ctrl(Instruct,IRQ&~PC[31],PCSrc,RegDst,RegWr,ALUSrc1,ALUSrc2,ALUFun,Sign,MemWr,MemRd,MemToReg,EXTOp,LUOp);
endmodule

module SingleCycleControl(Instruct,IRQ,PCSrc,RegDst,RegWr,ALUSrc1,ALUSrc2,ALUFun,Sign,MemWr,MemRd,MemToReg,EXTOp,LUOp);
  input [31:0] Instruct;
  input IRQ;
  output [2:0] PCSrc;
  output [1:0] RegDst,MemToReg;
  output RegWr,ALUSrc1,ALUSrc2,Sign,MemWr,MemRd,EXTOp,LUOp;
  output [5:0] ALUFun;
  
  assign {PCSrc,RegDst,ALUFun,MemToReg,EXTOp,LUOp,MemRd,MemWr,Sign,RegWr,ALUSrc1,ALUSrc2}=
    IRQ ? 21'b100_11_000000_10_0_0_0_0_0_1_0_0:
      ~|Instruct[31:26] ? 
        Instruct[ 5:0]==6'h0  ? 21'b000_00_100000_00_10001110 :
        Instruct[ 5:0]==6'h2  ? 21'b000_00_100001_00_10001110 :
        Instruct[ 5:0]==6'h3  ? 21'b000_00_100011_00_10001110 :
        Instruct[ 5:0]==6'h8  ? 21'b011_00_000000_00_10001000 :
        Instruct[ 5:0]==6'h9  ? 21'b011_10_000000_10_10001100 :
        Instruct[ 5:0]==6'h20 ? 21'b000_00_000000_00_10001100 :
        Instruct[ 5:0]==6'h21 ? 21'b000_00_000000_00_10000100 :
        Instruct[ 5:0]==6'h22 ? 21'b000_00_000001_00_10001100 :
        Instruct[ 5:0]==6'h23 ? 21'b000_00_000001_00_10000100 :
        Instruct[ 5:0]==6'h24 ? 21'b000_00_011000_00_10001100 :
        Instruct[ 5:0]==6'h25 ? 21'b000_00_011110_00_10001100 :
        Instruct[ 5:0]==6'h26 ? 21'b000_00_010110_00_10001100 :
        Instruct[ 5:0]==6'h27 ? 21'b000_00_010001_00_10001100 :
        Instruct[ 5:0]==6'h2a ? 21'b000_00_110101_00_10001100 : 21'b101_11_000000_10_0_0_0_0_0_1_0_0
      :Instruct[31:26]==6'h1  ? 21'b001_00_110101_00_10001000 :
       Instruct[31:26]==6'h2  ? 21'b010_00_000000_00_10001000 :
       Instruct[31:26]==6'h3  ? 21'b010_10_000000_10_10001100 :
       Instruct[31:26]==6'h4  ? 21'b001_00_110011_00_10001000 :
       Instruct[31:26]==6'h5  ? 21'b001_00_110001_00_10001000 :
       Instruct[31:26]==6'h6  ? 21'b001_00_111101_00_10001000 :
       Instruct[31:26]==6'h7  ? 21'b001_00_111111_00_10001000 :
       Instruct[31:26]==6'h8  ? 21'b000_01_000000_00_10001101 :
       Instruct[31:26]==6'h9  ? 21'b000_01_000000_00_00000101 :
       Instruct[31:26]==6'ha  ? 21'b000_01_110101_00_10001101 :
       Instruct[31:26]==6'hb  ? 21'b000_01_110101_00_00000101 :
       Instruct[31:26]==6'hc  ? 21'b000_01_011000_00_10001101 :
       Instruct[31:26]==6'hf  ? 21'b000_01_000000_00_11001101 :
       Instruct[31:26]==6'h23 ? 21'b000_01_000000_01_10101101 :
       Instruct[31:26]==6'h2b ? 21'b000_00_000000_00_10011001 : 21'b101_11_000000_10_0_0_0_0_0_1_0_0;
endmodule

module SingleCycleCPUImplementation(sysclk,reset,LED,SWITCH,DIGIT,TX,RX);
  input sysclk,reset,RX;
  input [7:0] SWITCH;
  output TX;
  output [7:0] LED;
  output [11:0] DIGIT;
  reg temp_clk;
  reg clk;
  always @ (posedge reset or posedge sysclk)
  begin
    if(reset) temp_clk<=1'b1;
    else temp_clk<=~temp_clk;
  end
  always @ (posedge reset or posedge temp_clk)
  begin
    if(reset) clk<=1'b1;
    else clk<=~clk;
  end
  //debounce reset_debounce(sysclk,reset,reset_debounced);
  SingleCycleCPU cpu0(sysclk,clk,reset,LED,SWITCH,DIGIT,TX,RX);
endmodule
