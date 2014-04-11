module bcd_counter(
    reset,      //低电平有效
    up_enable,  //高电平有效
    clk,
    count,      //1-bit 计数脉冲
    bcd);       //4-bit BCD数

    input reset;
    input up_enable;
    input clk;
    output count;
    output [3:0] bcd;

    wire reset;
    wire up_enable;
    wire clk;
    reg count;
    reg [3:0] bcd;
    
    always @ (reset)
    begin
      if(1'b0==reset)
      begin
        count<=1'b0;
        bcd<=4'b0000;
      end
    end

    always @ (posedge clk)
    begin
        if(1'b1==up_enable && 1'b1==reset)
        begin            
            if(4'b1001==bcd)
            begin
              bcd<=4'b0000;
            end
            else
            begin
              bcd<=bcd+1;
            end
        end
    end
    
    always @ (bcd)
    begin
      if(4'b1001==bcd)
      begin
        count<=1'b1;
      end
      else
      begin
        count<=1'b0;
      end
    end
    
endmodule //bcd_counter

module test_bench_for_bcd_counter(reset,up_enable,clk,count,bcd);
    output reset;
    output up_enable;
    output clk;
    output count;
    output [3:0] bcd;
    
    reg reset;
    reg up_enable;
    reg clk;
    wire count;
    wire [3:0] bcd;

    initial
    begin
        $display("time\tclk\treset\tup_enable\tcount\tbcd");
        $monitor("%g\t%b\t%b\t%b\t%b\%b",$time,clk,reset,up_enable,count,bcd);
        clk=1;
        reset=0;
        up_enable=0;
        #5 reset=1;
        #20 reset=0;
        #20 reset=1;
        #10 up_enable=1;
        #30 reset=0;
        #30 reset=1;
        #170 up_enable=0;
        #20 $finish;
    end
    
    always
    begin
      #5 clk=~clk;
    end
    
    bcd_counter U_count(reset,up_enable,clk,count,bcd);
endmodule