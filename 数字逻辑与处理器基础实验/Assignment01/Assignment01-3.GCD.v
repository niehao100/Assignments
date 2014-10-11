module gcd(
  a_in,
  b_in,
  clk,
  out);

  input a_in;
  input b_in;
  input clk;
  output out;

  wire [6:0] a_in;
  wire [6:0] b_in;
  wire clk;
  reg flag;
  reg [6:0] a;
  reg [6:0] b;
  reg [6:0] c;
  reg [6:0] out;

  always @ (a_in,b_in)
  begin
    a<=a_in>b_in?a_in:b_in;
    b<=a_in>b_in?b_in:a_in;
    c<=a_in>b_in?a_in:b_in;
    out<=7'd0;
  end
  always @ (posedge clk)
  begin
    if(7'd0==out)
    begin
      c<=a>b?a-b:b-a;
      flag<=1'b1;
    end
  end
  always @ (posedge flag)
  begin
    if(7'b0==c)
    begin
      out<=b;
    end
    else
    begin
      a<=b>c?b:c;
      b<=b>c?c:b;
    end
    flag<=1'b0;
  end
endmodule //gcd

module test_bench_for_gcd(a_in,b_in,clk,out);
    output a_in;
    output b_in;
    output clk;
    output out;
    
    reg [6:0] a_in;
    reg [6:0] b_in;
    reg clk;
    wire [6:0] out;

    initial
    begin
        $display("time\ta\tb\tout");
        $monitor("%g\t%d\t%d\t%d",$time,a_in,b_in,out);
        clk=1;
        a_in=12;
        b_in=18;
        #40 a_in=21;
        #40 b_in=52;
        #40 a_in=0;
        #40 a_in=7;
        #40 b_in=77;
        #40 a_in=99;
        #40 $finish;
    end
    
    always
    begin
      #1 clk=~clk;
    end
    
    gcd U_gcd(a_in,b_in,clk,out);
endmodule