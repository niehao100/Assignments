module testbench1(addin,clk,enable,reset,sum,overflow);
  output [3:0] addin;
  output clk;
  output enable; //低电平使能
  output reset;  //高电平重置
  output [3:0] sum;
  output overflow;

  reg [3:0] addin;
  reg clk;
  reg enable;
  reg reset;
  wire [3:0] sum;
  wire overflow;

  initial
  begin
    clk<=0;
    reset<=1;
    enable<=0;
    addin<=4'b0011;
    #1 reset<=0;
    #20 addin<=4'b0010;
    #10 reset<=1;
    #1 reset<=0;
    #20 enable<=1;
    #20 enable<=0;
    #20 reset<=1;
    #1 reset<=0;
    #20 $stop;
  end

  always @ (*)
  begin
    #2 clk<=~clk;
  end

  accumulator accumulator1(addin,clk,enable,reset,sum,overflow);
endmodule

module testbench2(a,b,clk,reset,product,done);
  output [1:0] a;
  output [1:0] b;
  output clk;
  output reset;
  output [3:0] product;
  output done;  //高电平表示计算完成,低电平使能

  reg [1:0] a;
  reg [1:0] b;
  reg clk;
  reg reset;
  wire [3:0] product;
  wire done;

  initial
  begin
    clk<=0;
    a<=2'b00;
    b<=2'b00;
    reset<=1;
    #1 reset<=0;
    #15 a<=2'b01;reset<=1;
    #5 reset<=0;
    #15 a<=2'b10;reset<=1;
    #5 reset<=0;
    #15 a<=2'b11;reset<=1;
    #5 reset<=0;
    #15 b<=2'b01;a<=2'b00;reset<=1;
    #5 reset<=0;
    #15 a<=2'b01;reset<=1;
    #5 reset<=0;
    #15 a<=2'b10;reset<=1;
    #5 reset<=0;
    #15 a<=2'b11;reset<=1;
    #5 reset<=0;
    #15 b<=2'b10;a<=2'b00;reset<=1;
    #5 reset<=0;
    #15 a<=2'b01;reset<=1;
    #5 reset<=0;
    #15 a<=2'b10;reset<=1;
    #5 reset<=0;
    #15 a<=2'b11;reset<=1;
    #5 reset<=0;
    #15 b<=2'b11;a<=2'b00;reset<=1;
    #5 reset<=0;
    #15 a<=2'b01;reset<=1;
    #5 reset<=0;
    #15 a<=2'b10;reset<=1;
    #5 reset<=0;
    #15 a<=2'b11;reset<=1;
    #5 reset<=0;
    #15 $stop;
  end

  always @ (*)
  begin
    #2 clk<=~clk;
  end

  mutiplier mutiplier1(a,b,clk,reset,product,done);
endmodule
