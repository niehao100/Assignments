module flipflop_gate(d,set,reset,q,q_inverse,clk);
  input d;
  input set;
  input reset;
  input clk;
  output q;
  output q_inverse;
  
  wire d;
  wire set;
  wire reset;
  wire q;
  wire q_inverse;
  wire clk;
    
  nand (temp1,~set,temp4,temp2);
  nand (temp2,temp1,~reset,clk);
  nand (temp3,temp2,clk,temp4);
  nand (temp4,temp3,~reset,d);
  nand (q,~set,temp2,q_inverse);
  nand (q_inverse,q,~reset,temp3);
  
endmodule

module flipflop_gate_debounced(sysclk,clk,d,set,reset,q);
  input sysclk;
  input clk;
  input d;
  input set;
  input reset;
  output q;
  debounce (sysclk,clk,clk_o);
  flipflop_gate (d,set,reset,q,,clk_o);
endmodule
