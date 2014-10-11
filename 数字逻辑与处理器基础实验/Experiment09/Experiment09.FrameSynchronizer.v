module frame_synchronizer(clk,reset,in,out,out_enable,state);
  input clk;
  input reset;
  input in;
  output out;
  output out_enable;
  output [1:0] state;
  
  wire clk;
  wire reset;
  wire in;
  reg out;
  wire out_enable;
  
  parameter FRAME_ENABLE=8'b10011011;
  
  reg [1:0] state=2'b00;  //有限状态机状态
  reg [9:0] counter=10'd0;  //记录帧序数的计数器
  reg [7:0] frame=8'd0; //帧状态移位寄存器
  
  always @ (posedge clk)
  begin
    out<=in;
  end
  
  always @ (posedge clk or posedge reset)
  begin
    if(reset==1'b1)
    begin
      state<=2'b00;
      counter<=10'd0;
      frame<=8'd0;
    end
    else case (state)
      2'b00:
      begin
        if(frame!=FRAME_ENABLE)
        begin
          frame<={frame[6:0],in};
        end
        else
        begin
          counter<=10'd8;
          frame<={frame[6:0],in};
          state<=2'b01;
        end
      end
      2'b01:
      begin
        frame<={frame[6:0],in};
        if(counter==10'd511)
        begin
          counter<=10'd0;
        end
        else
        begin
          counter<=counter+10'd1;
          if(counter[7:0]==8'd7)
          begin
            if(frame!=FRAME_ENABLE)
            begin
              state<=2'b00;
            end
            else
            begin
              if(counter==10'd7)
              begin
                state<=2'b10;
              end
              else
              begin
                state<=state;
              end
            end
          end
        end
        
      end
      2'b10:
      begin
        frame<={frame[6:0],in};
        if(counter==10'd255)
        begin
          counter<=10'd0;
        end
        else
        begin
          counter<=counter+10'd1;
          if(counter==10'd7)
          begin
            if(frame!=FRAME_ENABLE)
            begin
              state<=2'b11;
            end
            else
            begin
              state<=state;
            end
          end
        end
      end
      2'b11:
      begin
        frame<={frame[6:0],in};
        if(counter==10'd255+10'd512)
        begin
          counter<=10'd0;
        end
        else
        begin
          counter<=counter+10'd1;
          if(counter[7:0]==8'd7)
          begin
            if(frame==FRAME_ENABLE)
            begin
              state<=2'b10;
            end
            else if(counter==10'd7)
            begin
              state<=2'b00;
            end
            else
            begin
              state<=state;
            end
          end
          else
          begin
            state<=state;
          end
        end
      end
    endcase
    
  end
  
  //assign out=in;
  assign out_enable=state[1]&(counter[7:0]>7);
endmodule

module frame_synchronizer_test(sysclk,reset,mode_select,mode_confirm,state,out_enable,data_wrong,mode_display);
  input sysclk,reset,mode_select,mode_confirm;
  output [1:0] mode_display;
  output [3:0] state;
  output out_enable,data_wrong;
  
  wire sysclk,reset,out_enable,data_wrong;
  wire [1:0] state_2bit;
  wire [3:0] state;
  reg [1:0] mode_display;
  reg [1:0] mode;
  
  debounce debounce_select(sysclk,mode_select,mode_select_debounced);
  debounce debounce_confirm(sysclk,mode_confirm,mode_confirm_debounced);
  debounce debounce_reset(sysclk,reset,reset_debounced);
  
  always @ (posedge mode_confirm_debounced or posedge reset)
  begin
    if(reset)
    begin
      mode<=1'b0;
    end
    else
    begin
      mode<=mode_display;
    end
  end
  
  always @ (posedge mode_select_debounced or posedge reset)
  begin
    if(reset)
    begin
      mode_display<=1'b0;
    end
    else
    begin
      mode_display<=mode_display+2'b01;
    end
  end
  
  
  assign state[0]=(state_2bit==2'b00);
  assign state[1]=(state_2bit==2'b01);
  assign state[2]=(state_2bit==2'b10);
  assign state[3]=(state_2bit==2'b11);
  
  FrameTrans transmiter(reset_debounced,sysclk,mode,clk,in);
  frame_synchronizer synchronizer(clk,reset_debounced,in,out,out_enable,state_2bit);
  FrameDataCheck checker(reset_debounced,clk,out,out_enable,data_wrong);
endmodule
