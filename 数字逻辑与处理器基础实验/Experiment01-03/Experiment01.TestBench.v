module testbench1(
  a,  //Input 1
  b,  //Input 2
  s,  //Switch 1
  y); //Output
  
  output a;
  output b;
  output s;
  output y;

  reg a;
  reg b;
  reg s;
  wire y;
  
  initial
  begin
    $display("time\ta\tb\ts\ty");
    $monitor("%g\t%b\t%b\t%b\t%b",$time,a,b,s,y);
    a=0;
    b=1;
    s=0;
    #20 a=1;
    #20 a=0;
    #20 b=0;
    #20 b=1;
    #20 s=1;
    #20 a=1;
    #20 a=0;
    #20 b=0;
    #20 b=1;
    #20 a=1;
    #20 s=0;
    #20 s=1;
    #20 b=0;
    s=0;
    #20 a=0;b=1;s=1;
    #20 a=~a;b=~b;s=~s;
    #20 $stop;
  end
  
  multiplexer_2to1_hazard mux1(a,b,s,y);
endmodule

module testbench2(
  a,  //Input 1
  b,  //Input 2
  s,  //Switch 1
  y); //Output
  
  output a;
  output b;
  output s;
  output y;

  reg a;
  reg b;
  reg s;
  wire y;
  
  initial
  begin
    $display("time\ta\tb\ts\ty");
    $monitor("%g\t%b\t%b\t%b\t%b",$time,a,b,s,y);
    a=0;
    b=1;
    s=0;
    #20 a=1;
    #20 a=0;
    #20 b=0;
    #20 b=1;
    #20 s=1;
    #20 a=1;
    #20 a=0;
    #20 b=0;
    #20 b=1;
    #20 a=1;
    #20 s=0;
    #20 s=1;
    #20 b=0;
    s=0;
    #20 a=0;b=1;s=1;
    #20 a=~a;b=~b;s=~s;
    #20 $stop;
  end
  
  multiplexer_2to1 mux1(a,b,s,y);
endmodule

module testbench3(
  c,
  s,
  y);
  
  output [3:0] c;
  output [1:0] s;
  output y;

  reg [3:0] c;
  reg [1:0] s;
  wire y;
  
  initial
  begin
    $display("time\tc0\tc1\tc2\tc3\ts0\ts1\ty");
    $monitor("%g\t%b\t%b\t%b\t%b\t%b\t%b\t%b",$time,c[0],c[1],c[2],c[3],s[0],s[1],y);
    c=4'b0000;
    s=2'b00;
    #1 c=1;
    #3 c=0;
    #1 c=2;
    #3 c=0;
    #1 c=4;
    #3 c=0;
    #1 c=8;
    #3 c=0;
    #10 s=1;
    #1 c=1;
    #3 c=0;
    #1 c=2;
    #3 c=0;
    #1 c=4;
    #3 c=0;
    #1 c=8;
    #3 c=0;
    #10 s=3;
    #1 c=1;
    #3 c=0;
    #1 c=2;
    #3 c=0;
    #1 c=4;
    #3 c=0;
    #1 c=8;
    #3 c=0;
    #10 s=2;
    #1 c=1;
    #3 c=0;
    #1 c=2;
    #3 c=0;
    #1 c=4;
    #3 c=0;
    #1 c=8;
    #3 c=0;
    #10 $stop;
  end
  
  multiplexer_4to1 mux1(c,s,y);
endmodule
