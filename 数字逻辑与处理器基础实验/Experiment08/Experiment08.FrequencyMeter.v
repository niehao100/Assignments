module ten_frequency_divider(in,out);
  input in;
  output out;
  
  wire in;
  reg out=1'b0;
  
  reg [3:0] count=4'd0;
  
  always @ (posedge in)
  begin
    if(count!=4'd4)
    begin
      count<=count+4'd1;
    end
    else
    begin
      count<=4'd0;
      out<=~out;
    end
  end
endmodule

module system_frequency_divider(sysclk,scan,control);
  input sysclk;
  output scan;
  output control;
  
  wire sysclk;
  reg scan=1'b0;
  reg control=1'b0;
  
  reg [15:0] count_scan=16'b0;
  reg [26:0] count_control=26'b0;
  
  always @ (posedge sysclk)
  begin
    if(count_scan!=16'd49999)
    begin
      count_scan<=count_scan+16'd1;
    end
    else
    begin
      count_scan<=16'd0;
      scan<=~scan;
    end
    if(count_control==27'd999)
    begin
      control<=1'b0;
      count_control<=count_control+27'd1;
    end
    else if(count_control==27'd99999999+27'd999)
    begin
      control<=1'b1;
      count_control<=27'd0;
    end
    else
    begin
      count_control<=count_control+27'd1;
    end
  end
endmodule

module decoder(clk,number,anodes,cathodes);
  input clk;
  input [15:0] number;
  output [3:0] anodes;
  output [7:0] cathodes;
  
  wire clk;
  wire [15:0] number;
  reg [3:0] anodes=4'b0001;
  reg [7:0] cathodes;
  reg [3:0] current;
  
  always @ (posedge clk)
  begin
    case (anodes)
      4'b1110:begin anodes<=4'b1101; current<=number[11:8];end
      4'b1101:begin anodes<=4'b1011; current<=number[15:12];end
      4'b1011:begin anodes<=4'b0111; current<=number[3:0];end
      4'b0111:begin anodes<=4'b1110; current<=number[7:4];end
      default: anodes<=4'b1110; 
    endcase
    case (current)
      4'd0: cathodes<=8'b0000_0011;
      4'd1: cathodes<=8'b1001_1111;
      4'd2: cathodes<=8'b0010_0101;
      4'd3: cathodes<=8'b0000_1101;
      4'd4: cathodes<=8'b1001_1001;
      4'd5: cathodes<=8'b0100_1001;
      4'd6: cathodes<=8'b0100_0001;
      4'd7: cathodes<=8'b0001_1111;
      4'd8: cathodes<=8'b0000_0001;
      4'd9: cathodes<=8'b0000_1001;
      default: cathodes<=8'b1111_1111;
    endcase
  end
endmodule

module counter(clk,enable,reset,count);
  input clk,enable,reset;
  output [15:0] count;
  
  wire clk,enable,reset;
  reg [15:0] count=16'b0;
  reg [15:0] next;
  
  always @(count)
  begin
    if(count[3:0]==4'd9)
    begin
      if(count[7:4]==4'd9)
      begin
        if(count[11:8]==4'd9)
        begin
          if(count[15:12]==4'd9)
          begin
            next<=16'd0;
          end
          else
          begin
            next<=count+16'h1000-16'h0999;
          end
        end
        else
        begin
          next<=count+16'h0100-16'h0099;
        end
      end
      else
      begin
        next<=count+16'h0010-16'd0009;
      end
    end
    else
    begin
      next<=count+16'h0001;
    end
  end
  
  always @ (posedge clk or posedge reset)
  begin
    if (reset) begin
      count = 16'd0;
    end
    else if (!enable)
    begin
      count = next;
    end
  end
endmodule

module frequency_meter(in,sysclk,range,range_display,cathodes,anodes);
  input in,sysclk,range;  //高量程为1
  output range_display;
  output [7:0] cathodes;
  output [3:0] anodes;
  
  wire in,sysclk,range,range_display;
  wire [7:0] cathodes;
  wire [3:0] anodes;
  
  reg [15:0] count=16'd0;
  wire [15:0] count_output;
  reg reset;
  assign range_display=range;
  ten_frequency_divider divider1(in,in1);
  assign signal=range?in1:in;
  
  system_frequency_divider divider2(sysclk,scan,control);
  counter counter1(signal,1'b0,control,count_output);
  
  always @ (posedge control)
  begin
      count<=count_output;
  end
  
  decoder d1(scan,count,anodes,cathodes);
endmodule

module frequency_test(select,sysclk,range,range_display,cathodes,anodes);
  input [1:0] select;
  input sysclk,range;  //高量程为1
  output range_display;
  output [7:0] cathodes;
  output [3:0] anodes;
  
  wire [1:0] select;
  wire sysclk,range,range_display;
  wire [7:0] cathodes;
  wire [3:0] anodes;
  
  signal_input generator1(select,sysclk,signal);
  frequency_meter meter1(signal,sysclk,range,range_display,cathodes,anodes);
endmodule
