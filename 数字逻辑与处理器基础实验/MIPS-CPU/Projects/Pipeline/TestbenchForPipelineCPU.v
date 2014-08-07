module TestbenchForPipelineCPU(sysclk,reset_in,LED,SWITCH,DIGIT,TX,RX);
  output reg reset_in,sysclk,RX;
  output TX;
  output [7:0] LED;
  output reg [7:0] SWITCH;
  output [11:0] DIGIT;
  
  initial 
  begin
    reset_in<=1'b1;
    RX<=1'b1;
    sysclk<=1'b1;
    SWITCH<=8'b0;
    #1 reset_in<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b0;
    #104167 RX<=1'b0;
    #104167 RX<=1'b1;
    #104167 RX<=1'b1;
  end
  
  always @ (*)
  begin
    #5 sysclk<=~sysclk;
  end
  
  PipelineCPUImplementation cpu0(sysclk,reset_in,LED,SWITCH,DIGIT,TX,RX);
endmodule
