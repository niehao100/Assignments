module testbench(clk,reset,in,out,out_enable,state);
  output clk,reset,in;
  output out,out_enable;
  output [1:0] state;
  
  reg clk,reset,in;
  wire  out,out_enable;
  wire [1:0] state;
  
  initial
  begin
    clk<=0;
    reset<=1;
    in<=0;
    #10 reset<=0;
    
    #10 in<=1;
    #10 in<=0;
    #20 in<=1;
    #20 in<=0;
    #10 in<=1;
    #20 in<=0;
    #2480 in<=1;
    
    #10 in<=0;
    #20 in<=1;
    #20 in<=0;
    #10 in<=1;
    #20 in<=0;
    #2480 in<=1;
    
    #10 in<=0;
    #20 in<=1;
    #20 in<=0;
    #10 in<=1;
    #20 in<=0;
    #2480 in<=1;
    
    #10 in<=0;
    #20 in<=1;
    #20 in<=0;
    #10 in<=1;
    #20 in<=0;
    #2480 in<=1;
    
    #10 in<=0;
    #20 in<=1;
    #20 in<=0;
    #10 in<=1;
    #20 in<=0;
    #2480 in<=1;
    
    #10 in<=0;
    #20 in<=1;
    #20 in<=0;
    #10 in<=1;
    #20 in<=0;
    #2480 in<=1;
    
    #2560 in<=1;
    
    #10 in<=0;
    #20 in<=1;
    #20 in<=0;
    #10 in<=1;
    #20 in<=0;
    #2480 in<=1;
    
    #10 in<=0;
    #20 in<=1;
    #20 in<=0;
    #10 in<=1;
    #20 in<=0;
    #2480 in<=1;
    
    #10 in<=0;
    #20 in<=1;
    #20 in<=0;
    #10 in<=1;
    #20 in<=0;
    #2480 in<=1;
    
    #2560 in<=1;
    #2560 in<=1;
    
    #10 in<=0;
    #20 in<=1;
    #20 in<=0;
    #10 in<=1;
    #20 in<=0;
    #2480 in<=1;
    
    #10 in<=0;
    #20 in<=1;
    #20 in<=0;
    #10 in<=1;
    #20 in<=0;
    #2480 in<=1;
    
    #10 in<=0;
    #20 in<=1;
    #20 in<=0;
    #10 in<=1;
    #20 in<=0;
    #2480 in<=1;
    
    #2560 in<=1;
    #2560 in<=1;
    #2560 in<=1;
    
    #10 in<=0;
    #20 in<=1;
    #20 in<=0;
    #10 in<=1;
    #20 in<=0;
    #2480 in<=1;
    
    #10 in<=0;
    #20 in<=1;
    #20 in<=0;
    #10 in<=1;
    #20 in<=0;
    #2480 in<=1;
    
    #10 in<=0;
    #20 in<=1;
    #20 in<=0;
    #10 in<=1;
    #20 in<=0;
    #2480 in<=1;
    
    #10 in<=0;
    #20 in<=1;
    #20 in<=0;
    #10 in<=1;
    #20 in<=0;
    #2480 in<=1;
    
    #2560 in<=1;
    #2560 in<=1;
    #2560 in<=1;
    #2560 in<=1;
    
    #10 in<=0;
    #20 in<=1;
    #20 in<=0;
    #10 in<=1;
    #20 in<=0;
    #2480 in<=1;
    
    #10 in<=0;
    #20 in<=1;
    #20 in<=0;
    #10 in<=1;
    #20 in<=0;
    #2480 in<=1;
    
    #10 in<=0;
    #20 in<=1;
    #20 in<=0;
    #10 in<=1;
    #20 in<=0;
    #2480 in<=1;
    
    #10 in<=0;
    #20 in<=1;
    #20 in<=0;
    #10 in<=1;
    #20 in<=0;
    #2480 in<=1;
    
    #200 $stop;
  end
  
  always @ (*)
  begin
    #5 clk<=~clk;
  end
  
  frame_synchronizer synchronizer1(clk,reset,in,out,out_enable,state);
endmodule

module testbench_all();
  reg sysclk,reset;
  //wire out_enable,data_wrong;
  reg [1:0] mode;
  
  initial
  begin
    mode<=2'b10;
    reset<=1'b1;
    #1 reset<=1'b0;
    
  end
  
  always @ (*)
  begin
    #5 sysclk<=~sysclk;
  end
  
  FrameTrans transmiter(reset,sysclk,mode,clk,in);
  frame_synchronizer synchronizer(clk,reset,in,out,out_enable,state);
  FrameDataCheck checker(reset,clk,out,out_enable,data_wrong);
endmodule
