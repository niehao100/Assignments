module sequence_detector_fsm(in,clk,reset,out,fsm);
  input in;
  input clk;
  input reset;
  output out;
  output [2:0] fsm;

  wire in;
  wire clk;
  wire reset;
  reg out;
  wire [2:0] fsm;
  
  wire in_reg;
  reg [2:0] fsm_out;

  flipflop_rtl ff_in(in,0,reset,in_reg,,clk);
  flipflop_rtl ff0(fsm_out[0],0,reset,fsm[0],,clk);
  flipflop_rtl ff1(fsm_out[1],0,reset,fsm[1],,clk);
  flipflop_rtl ff2(fsm_out[2],0,reset,fsm[2],,clk);

  always @ (negedge clk,negedge reset,negedge in_reg,negedge fsm[0],negedge fsm[1],negedge fsm[2])
  begin
    case (fsm)
      0: begin fsm_out<=reset?0:(in_reg?1:0);out<=0;end
      1: begin fsm_out<=reset?0:(in_reg?1:2);out<=0;end
      2: begin fsm_out<=reset?0:(in_reg?3:0);out<=0;end
      3: begin fsm_out<=reset?0:(in_reg?1:4);out<=0;end
      4: begin fsm_out<=reset?0:(in_reg?5:0);out<=0;end
      5: begin fsm_out<=reset?0:(in_reg?6:4);out<=0;end
      6: begin fsm_out<=reset?0:(in_reg?1:2);out<=1;end
      default: begin fsm_out<=0;out<=0;end
    endcase
  end

endmodule

module sequence_detector_fsm_debounced(sysclk,in,clk,reset,out,fsm);
  input sysclk;
  input in;
  input clk;
  input reset;
  output out;
  output [2:0] fsm;

  wire sysclk;
  wire in;
  wire clk;
  wire reset;
  wire out;
  wire [2:0] fsm;

  debounce debounce_clk(sysclk,clk,clk_o);
  debounce debounce_reset(sysclk,reset,reset_o);
  sequence_detector_fsm sd1(in,clk_o,reset_o,out,fsm);
endmodule
