module PipelineCPU(sysclk,clk,reset,LED,SWITCH,DIGIT,TX,RX);
  input sysclk,clk,reset,RX;
  input [7:0] SWITCH;
  output TX;
  output [7:0] LED;
  output [11:0] DIGIT;
  
  wire reset,ALUSrc1,ALUSrc2,LUOp,EXTOp,IRQ;
  wire [31:0] DataBusA,DataBusB,DataBusC,ALUOut,PCplus4,PCadd,BranchAdd,
    Instruct,ALU_A,ALU_B,LUIin,ExtImm,ConBA,PCin,ILLOP,XADR,MemReadData;
  wire [5:0] ALUFun;
  wire [4:0] AddrC,Rs,Rt,Rd,Shamt,Xp,Ra;
  wire [25:0] JT;
  wire [15:0] Imm16;
  wire [2:0] PCSrc;
  wire [1:0] RegDst,MemToReg;
  wire RegWr,MemRd,MemWr,Sign;
  reg [31:0] PC;
  
  reg[31:0] Instruct_Id;
  reg ALUSrc1_Ex,ALUSrc2_Ex;
  //reg[31:0] ExtImm_Ex;
  reg[4:0] Shamt_Ex;
  reg[31:0] LUIin_Ex;
  reg[31:0] /*DataBusA_Mem,*/DataBusA_Ex,DataBusB_Ex,DataBusB_Mem;
  reg[5:0] ALUFun_Ex;
  reg[2:0] PCSrc_Ex,PCSrc_Mem;//,PCSrc_Wb;
  reg Sign_Ex;
  reg[1:0] MemToReg_Ex,MemToReg_Mem,MemToReg_Wb;
  reg[31:0] ConBA_Ex;
  reg[31:0] PCplus4_Mem,PCplus4_Ex,PCplus4_Wb,PCplus4_Id;
  reg[31:0] MemReadData_Wb;
  reg[25:0] /*JT_Mem,*/JT_Ex;
  
  reg MemWr_Mem,MemWr_Ex;
  reg RegWr_Ex,RegWr_Mem,RegWr_Wb;
  reg MemRd_Ex,MemRd_Mem;
  reg[4:0] AddrC_Ex,AddrC_Mem,AddrC_Wb;
  reg[4:0] Rs_Ex,Rt_Ex,Rt_Mem;
  wire[1:0] forwardA,forwardB;
  reg[31:0] ALUOut_Mem,ALUOut_Wb;
  wire stall;
  wire IF_flush,ID_flush,EX_flush;
  assign IF_flush = (PCSrc[2]^PCSrc[1])|(~PCSrc_Ex[2]&~PCSrc_Ex[1]&PCSrc_Ex[0]&ALUOut[0]);
  assign ID_flush = stall|(~PCSrc_Ex[2]&~PCSrc_Ex[1]&PCSrc_Ex[0]&ALUOut[0]);
  assign EX_flush = 0;
  
  
  PipelineHazard ph(RegWr_Ex,RegWr_Mem,RegWr_Wb,AddrC_Ex,AddrC_Mem,AddrC_Wb,Rs,Rt,Rs_Ex,Rt_Ex,forwardA,forwardB,stall,MemRd_Ex);
  
  
  always @ (posedge clk or posedge reset)
  begin
    if(reset)
    begin
      PC <= 0;
      PCplus4_Id <= 0;
      Instruct_Id <= 0;
      
      ALUSrc1_Ex <= 0;
      ALUSrc2_Ex <= 0;
      Shamt_Ex <= 0;
      LUIin_Ex <= 0;
      ALUFun_Ex <= 0;
      PCSrc_Ex <= 0;
      RegWr_Ex <= 0;
      Sign_Ex <= 0;
      MemWr_Ex <= 0;
      MemRd_Ex <= 0;
      MemToReg_Ex <= 0;
      DataBusA_Ex <= 0;
      DataBusB_Ex <= 0;
      Rt_Ex <= 0;
      Rs_Ex <= 0;
      AddrC_Ex <= 0;
      PCplus4_Ex <= 0;
      JT_Ex <= 0;
      ConBA_Ex <= 0;
      
      MemRd_Mem <= 0;
      MemWr_Mem <= 0;
      PCSrc_Mem <= 0;
      MemToReg_Mem <= 0;
      RegWr_Mem <= 0;
      MemRd_Mem <= 0;
      MemWr_Mem <= 0;
      MemToReg_Mem <= 0;
      RegWr_Mem <= 0;
      DataBusB_Mem <= 0;
      PCplus4_Mem <= 0;
      AddrC_Mem <= 0;
      ALUOut_Mem <= 0;
      
      MemToReg_Wb <= 0;
      PCplus4_Wb <= 0;
      MemReadData_Wb <= 0;
      RegWr_Wb <= 0;
      AddrC_Wb <= 0;
      ALUOut_Wb <= 0;
    end
    else
    begin
      //IF/ID
       if(stall)
          begin
            Instruct_Id <= 0;
          end
        else if(IF_flush)
          begin
            PC <= PCin;
            PCplus4_Id <= PCplus4;
            Instruct_Id <= 0;
          end
        else
          begin
            PC <= PCin;
            PCplus4_Id <= PCplus4;
            Instruct_Id <= Instruct;
          end
            
        //ID/EX
        if(ID_flush)
          begin
            ALUSrc1_Ex <= 0;
            ALUSrc2_Ex <= 0;
            ALUFun_Ex <= 0;
            PCSrc_Ex <= 0;
            RegWr_Ex <= 0;
            Sign_Ex <= 0;
            MemWr_Ex <= 0;
            MemRd_Ex <= 0;
            MemToReg_Ex <= 0;
            Rt_Ex <= 0;
            Rs_Ex <= 0;
            AddrC_Ex <= 0;
          end
        else
          begin
            //ExtImm_Ex <= ExtImm;
            ALUSrc1_Ex <= ALUSrc1;
            ALUSrc2_Ex <= ALUSrc2;
            Shamt_Ex <= Shamt;
            LUIin_Ex <= LUIin;
            Rt_Ex <= Rt;
            Rs_Ex <= Rs;
            DataBusA_Ex <= DataBusA;
            DataBusB_Ex <= DataBusB;
            AddrC_Ex <= AddrC;
            PCplus4_Ex <= (IRQ&~PCSrc_Mem[2]&~PCSrc_Mem[1]&PCSrc_Mem[0]&ALUOut_Mem[0])?PCplus4:PCplus4_Id;
            ALUFun_Ex <= ALUFun;
            PCSrc_Ex <= PCSrc;
            RegWr_Ex <= RegWr;
            Sign_Ex <= Sign;
            MemWr_Ex <= MemWr;
            MemRd_Ex <= MemRd;
            MemToReg_Ex <= MemToReg;
            JT_Ex <= JT;
            ConBA_Ex <= ConBA;
          end
        //EX/MEM
        if(EX_flush)
          begin
            MemRd_Mem <= 0;
            MemWr_Mem <= 0;
            PCSrc_Mem <= 0;
            MemToReg_Mem <= 0;
            RegWr_Mem <= 0;
          end
        else
          begin
            Rt_Mem <= Rt_Ex;
            ALUOut_Mem <= ALUOut;
            //DataBusA_Mem <= DataBusA_Ex;
            DataBusB_Mem <= (MemWr_Ex&&(Rt_Ex == AddrC_Wb))?DataBusC:DataBusB_Ex;
            //ConBA_Mem <= ConBA;
            PCplus4_Mem <= (IRQ&~PCSrc_Ex[2]&~PCSrc_Ex[1]&PCSrc_Ex[0]&ALUOut[0])?ConBA_Ex+4:PCplus4_Ex;
            MemRd_Mem <= MemRd_Ex;
            MemWr_Mem <= MemWr_Ex;
            PCSrc_Mem <= PCSrc_Ex;
            MemToReg_Mem <= MemToReg_Ex;
            RegWr_Mem <= RegWr_Ex;
            AddrC_Mem <= AddrC_Ex;
            //JT_Mem <= JT_Ex;
          end
        //MEM/WB
        ALUOut_Wb <= ALUOut_Mem;
        PCplus4_Wb <= PCplus4_Mem;
        MemReadData_Wb <= MemReadData;
        MemToReg_Wb <= MemToReg_Mem;
        //PCSrc_Wb <= PCSrc_Mem;
        RegWr_Wb <= RegWr_Mem;
        AddrC_Wb <= AddrC_Mem;
    end
  end
  
  assign PCin = PCSrc_Ex==3'd1 ? (ALUOut[0] ? ConBA_Ex : PCplus4) :
                PCSrc==3'd1|PCSrc==3'd0 ? PCplus4 :
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
  wire[31:0] ALU_A_in,ALU_B_in;
  assign ALU_A = forwardA[1]?ALUOut_Mem:(forwardA[0]?DataBusC:DataBusA_Ex);
  assign ALU_B = forwardB[1]?ALUOut_Mem:(forwardB[0]?DataBusC:DataBusB_Ex);
  assign ALU_A_in = ALUSrc1_Ex ? {27'd0,Shamt_Ex} : ALU_A;
  assign ALU_B_in = ALUSrc2_Ex ? LUIin_Ex         : ALU_B;
  ALU alu0(ALU_A_in,ALU_B_in,ALUFun_Ex,Sign_Ex,ALUOut);
  
  assign LUIin = LUOp ? {Imm16,16'd0} : ExtImm;
  assign ExtImm = {{16{EXTOp&Imm16[15]}},Imm16};
  assign DataBusC = MemToReg_Wb==2'd0 ? ALUOut_Wb :
                    MemToReg_Wb==2'd1 ? MemReadData_Wb : PCplus4_Wb;

  KS_ADD PCadder(PC,32'd4,PCadd,,1'b0);
  assign PCplus4 = {PC[31],PCadd[30:0]};
  KS_ADD BranchAdder({2'd0,PCplus4_Id[31:2]},ExtImm,BranchAdd,,1'b0);
  assign ConBA = {PCplus4_Id[31],BranchAdd[28:0],2'b0};
  
  Pipeline_RegisterFile reg0(reset,clk,Rs,DataBusA,Rt,DataBusB,RegWr_Wb,AddrC_Wb,DataBusC,RegWr_Wb,AddrC_Wb,ALUOut_Wb);
  
  InstructionMemory mem0(PC,Instruct);
  assign JT = Instruct_Id[25:0];
  assign Imm16 = Instruct_Id[15:0];
  assign Shamt = Instruct_Id[10:6];
  assign Rd = Instruct_Id[15:11];
  assign Rt = Instruct_Id[20:16];
  assign Rs = Instruct_Id[25:21];
  
  wire[31:0] DataBusB_Mem_in;
  assign DataBusB_Mem_in = (MemWr_Mem&&(Rt_Mem == AddrC_Wb))?DataBusC:DataBusB_Mem;
  DataMemory mem1(reset,sysclk,clk,MemRd_Mem,MemWr_Mem,ALUOut_Mem,DataBusB_Mem_in,MemReadData,LED,SWITCH,DIGIT,TX,RX,IRQ);
  SingleCycleControl ctrl(Instruct_Id,IRQ&~PC[31],PCSrc,RegDst,RegWr,ALUSrc1,ALUSrc2,ALUFun,Sign,MemWr,MemRd,MemToReg,EXTOp,LUOp);
endmodule

module PipelineCPUImplementation(sysclk,reset,LED,SWITCH,DIGIT,TX,RX);
  input sysclk,reset,RX;
  input [7:0] SWITCH;
  output TX;
  output [7:0] LED;
  output [11:0] DIGIT;
  PipelineCPU cpu0(sysclk,sysclk,reset,LED,SWITCH,DIGIT,TX,RX);
endmodule


