module testbench_counter(clk,enable,reset,count);
  output clk,enable,reset;
  output [15:0] count;
  
  reg clk,enable,reset;
  wire [15:0] count;
  
  initial
  begin
    clk<=0;
    reset<=1;
    enable<=0;
    #1 reset<=0;
    #100 enable<=1;
    #100 enable<=0;
    #100 reset<=1;
    #100 reset<=0;
    #200000 $stop;
  end
  
  always @ (*)
  begin
    #5 clk<=~clk;
  end
  
  counter counter1(clk,enable,reset,count);
endmodule

module testbench_ten_divider(in,out);
  output in,out;
  
  reg in;
  wire out;
  
  initial
  begin
    in<=0;
    #500 $stop;
  end
  
  always @ (*)
  begin
    #5 in<=~in;
  end
  
  ten_frequency_divider divider1(in,out);
endmodule

module testbench_system_divider(clk,scan,control);
  output clk,scan,control;
  
  reg clk;
  wire scan,control;
  
  initial
  begin
    clk<=0;
    #500000000 $stop;
  end
  
  always @ (*)
  begin
    #1 clk<=~clk;
  end
  
  system_frequency_divider divider2(clk,scan,control);
endmodule

module testbench(in,clk,range,range_display,cathodes,anodes);
  output in,clk,range;  //高量程为1
  output range_display;
  output [7:0] cathodes;
  output [3:0] anodes;
  
  reg in,clk,range;
  wire range_display;
  wire [7:0] cathodes;
  wire [3:0] anodes;
  
  initial
  begin
    in<=0;
    clk<=0;
    range<=0;
    #2000000000 $stop;
    //#2147483647
  end
  
  always @ (*)
  begin
    #200000 in<=~in; //500Hz
  end

  always @ (*)
  begin
    #1 clk<=~clk; //100MHz
  end
  
  frequency_meter meter(in,clk,range,range_display,cathodes,anodes);
endmodule

