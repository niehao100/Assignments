module pcm(
  set,
  clk,
  q1,
  q2,
  q3);

  input set;
  input clk;
  output q1;
  output q2;
  output q3;

  wire set;
  wire clk;
  reg q1;
  reg q2;
  reg q3;
  reg [1:0] q1_counter;
  reg [1:0] q2_counter;
  reg [1:0] q3_counter;
    
  always @ (posedge clk)
  begin
    if(1'b1==set)
    begin
      q1_counter<=2'b11;
    end
    else if(q1_counter>0)
    begin
      if(2'b01==q1_counter)
      begin
        q2_counter<=2'b11;
      end
      else
      begin
        q1<=1'b1;
        q2<=1'b0;
        q3<=1'b0;
      end
      q1_counter<=q1_counter-1;
    end
    else if(q2_counter>0)
    begin
      if(2'b01==q2_counter)
      begin
        q3_counter<=2'b11;
      end
      else
      begin
        q1<=1'b0;
        q2<=1'b1;
        q3<=1'b0;
      end
      q2_counter<=q2_counter-1;
    end
    else if(q3_counter>0)
    begin
      q1<=1'b0;
      q2<=1'b0;
      q3<=1'b1;
      q3_counter<=q3_counter-1;
    end
    else
    begin
      q1<=1'b0;
      q2<=1'b0;
      q3<=1'b0;
      q1_counter<=2'b00;
      q2_counter<=2'b00;
      q3_counter<=2'b00;
    end
  end    
endmodule //pcm

module test_bench_for_pcm(set,clk,q1,q2,q3);
    output set;
    output clk;
    output q1;
    output q2;
    output q3;
    
    reg set;
    reg clk;
    wire q1;
    wire q2;
    wire q3;

    initial
    begin
        $display("time\tclk\tset\tq1\tq2\tq3");
        $monitor("%g\t%b\t%b\t%b\t%b\t\%b",$time,clk,set,q1,q2,q3);
        clk=1;
        set=0;
        #10 set=1;
        #10 set=0;
        #100 $finish;
    end
    
    always
    begin
      #5 clk=~clk;
    end
    
    pcm U_pcm(set,clk,q1,q2,q3);
endmodule