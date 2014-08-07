module PipelineHazard(RegWrite_EX,RegWrite_Mem,RegWrite_Wb,AdderC_EX,AdderC_Mem,AdderC_Wb,
                       Rs,Rt,Rs_Ex,Rt_Ex,forwardA,forwardB,stall,MemRead_Ex);
  
  input RegWrite_EX,RegWrite_Mem,RegWrite_Wb;
  input MemRead_Ex;
  input[4:0] AdderC_EX,AdderC_Mem,AdderC_Wb,Rs,Rt,Rs_Ex,Rt_Ex;
  output[1:0] forwardA,forwardB;
  output stall;
  
  assign forwardA[0] = RegWrite_Wb&&(AdderC_Wb!=0)&&(AdderC_Mem!=Rs_Ex)&&(AdderC_Wb==Rs_Ex);
  assign forwardA[1] = RegWrite_Mem&&(AdderC_Mem!=0)&&(AdderC_Mem==Rs_Ex);
  assign forwardB[0] = RegWrite_Wb&&(AdderC_Wb!=0)&&(AdderC_Mem!=Rt_Ex)&&(AdderC_Wb==Rt_Ex);
  assign forwardB[1] = RegWrite_Mem&&(AdderC_Mem!=0)&&(AdderC_Mem==Rt_Ex);
  assign stall = MemRead_Ex&&((AdderC_EX == Rs)||(AdderC_EX == Rt));
  
endmodule