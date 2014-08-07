module Pipeline_RegisterFile(reset,clk,addr1,data1,addr2,data2,wr,addr3,data3,RegWrite_Wb,AdderC_Wb,ALUOut_Wb);
  input reset,clk;
  input wr;
  input [4:0] addr1,addr2,addr3;
  output [31:0] data1,data2;
  input [31:0] data3;
  input RegWrite_Wb;
  input [4:0] AdderC_Wb;
  input [31:0] ALUOut_Wb;

  reg [31:0] RF_DATA[31:1];
  integer i;

  assign data1=(addr1==5'b0)?32'b0:((RegWrite_Wb&&(AdderC_Wb == addr1))?ALUOut_Wb:RF_DATA[addr1]);
  assign data2=(addr2==5'b0)?32'b0:((RegWrite_Wb&&(AdderC_Wb == addr2))?ALUOut_Wb:RF_DATA[addr2]);

  always@(posedge reset or posedge clk) begin
    if(reset)
    begin
      for(i=1;i<29;i=i+1) RF_DATA[i] <= 32'b0;
      RF_DATA[29] <= 32'h3fc;
      for(i=30;i<32;i=i+1) RF_DATA[i] <= 32'b0;
    end
    else
    begin
      if(wr&&addr3) RF_DATA[addr3] <= data3;
    end
  end
endmodule
