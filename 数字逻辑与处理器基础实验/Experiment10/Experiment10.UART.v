module universal_asynchronous_receiver(clk,reset,receive,data,status);
  input clk,receive,reset;
  output [7:0] data;
  output status;
  
  wire clk,receive,reset;
  reg [7:0] data;
  reg status;
  
  reg sample_enable;
  reg [4:0] sample_counter;
  reg [2:0] counter;
  
  
  always @ (posedge clk or posedge reset)
  begin
    if(reset)
    begin
      data<=8'd0;
      status<=1'b0;
      sample_counter<=5'd0;
      sample_enable<=1'b0;
      counter<=3'd0;
    end
    else if(!sample_enable)
    begin
      if(sample_counter!=0) sample_counter<=sample_counter-4'd1;
      else
      begin
        status<=1'b0;
        if(~receive)
        begin
          sample_enable<=1'b1;
          sample_counter<=5'd23;
        end
      end
    end
    else
    begin
      if(sample_counter==5'd0)
      begin
        sample_counter<=5'd15;
        data<={receive,data[7:1]};
        counter<=counter+3'd1;
        if(counter==3'd7)
        begin
          status<=1'b1;
          sample_enable<=1'b0;
        end
      end
      else
      begin
        sample_counter<=sample_counter-5'd1;
      end
    end
  end
endmodule

module universal_asynchronous_transmitter(clk,reset,enable,data,status,transmit);
  input clk,enable,reset;
  input [7:0] data;
  output reg status,transmit;
  
  reg [3:0] frequency_counter;
  reg [7:0] register;
  reg [3:0] counter;
  
  always @ (posedge clk or posedge reset)
  begin
    if(reset)
    begin
      register<=8'd0;
      counter<=4'd0;
      frequency_counter<=4'd0;
      status<=1'b1;
      transmit<=1'b1;
    end
    else if(enable)
    begin
      register<=data;
      counter<=4'd0;
      frequency_counter<=4'd0;
      status<=4'd0;
    end
    else if(~status)
    begin
      frequency_counter<=frequency_counter+4'd1;
      if(frequency_counter==4'd0)
      begin
        counter<=counter+4'd1;
        if(counter==4'd0)
        begin
          transmit<=1'b0;
        end
        else if(counter==4'd9)
        begin
          transmit<=1'b1;
          status<=1'b1;
        end
        else
        begin
          transmit<=register[0];
          register<={1'b1,register[7:1]};
        end
      end
    end
  end
endmodule

module baud_rate_generator(sysclk,clk,reset);
  input sysclk,reset;
  output clk;
  
  wire sysclk,reset;
  reg clk;
  
  reg [9:0] counter=10'd0;
  always @ (posedge sysclk or posedge reset)
  begin
    if(reset)
    begin
      counter<=10'd0;
      clk<=1'd0;
    end
    else
    begin
      if(counter==10'd325)
      begin
        clk<=1'b1;
        counter<=counter+10'd1;
      end
      else if(counter==10'd650)
      begin
        clk<=1'b0;
        counter<=10'd0;
      end
      else
      begin
        counter<=counter+10'd1;
      end
    end
  end
endmodule

module controller(clk,reset,rx_data,rx_status,tx_data,tx_status,tx_enable);
  input clk,reset;
  input [7:0] rx_data;
  input rx_status;
  input tx_status;
  output reg [7:0] tx_data;
  output reg tx_enable;
  
  reg [7:0] data;
  reg rx_ready;
  reg [3:0] counter;
  
  always @ (posedge clk or posedge reset)
  begin
    if(reset)
    begin
      counter<=4'd0;
      data<=8'd0;
      tx_data<=8'd0;
      tx_enable<=1'b0;
    end
    else if(rx_status)
    begin
      rx_ready<=1'b1;
      data<=rx_data;
    end
    else if(rx_ready)
    begin
      counter<=counter+4'd1;
      if(counter==4'd15)
      begin
        rx_ready<=1'b0;
        tx_enable<=1'b0;
      end
      else
      begin
        tx_enable<=1'b1;
        tx_data<=(data[7]==1'b1)?(data^8'b11111111):data;
      end
    end
  end
endmodule

module UART(uart_rx,uart_tx,reset,sysclk);
  input uart_rx,reset,sysclk;
  output uart_tx;
  
  wire uart_rx,reset,sysclk,uart_tx;
  
  wire clk;
  wire [7:0] rx_data,tx_data;
  universal_asynchronous_receiver rx(clk,reset,uart_rx,rx_data,rx_status);
  universal_asynchronous_transmitter tx(clk,reset,tx_enable,tx_data,tx_status,uart_tx);
  controller ctrl(clk,reset,rx_data,rx_status,tx_data,tx_status,tx_enable);
  baud_rate_generator gen(sysclk,clk,reset);
endmodule

module UART_debounced(uart_rx,uart_tx,reset,sysclk);
  input uart_rx,reset,sysclk;
  output uart_tx;
  
  wire uart_tx,reset,sysclk,uart_rx;
  
  wire reset_debounced;
  
  debounce reset_debounce(sysclk,reset,reset_debounced);
  UART uart1(uart_rx,uart_tx,reset_debounced,sysclk);
endmodule
