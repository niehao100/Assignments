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

module UART(reset,sysclk,clk,rd,wr,addr,wdata,rdata,transmit,receive);
  input sysclk,clk,reset,rd,wr;
  input [31:0] addr,wdata;
  input receive;
  output [31:0] rdata;
  output transmit;
  
  reg [7:0] UART_TXD;
  reg [7:0] UART_RXD;
  reg [3:0] UART_CON;
  wire [7:0] rx_data;
  reg tx_former_status,rx_former_status;
  reg tx_enable;
  
  assign rdata[31:8] = {24{1'b0}};
  assign rdata[7:0] = addr==32'h40000018 ? UART_TXD :
    addr==32'h4000001C ? UART_RXD :
    addr==32'h40000020 ? {4'b0,UART_CON} : 8'b0;
  universal_asynchronous_receiver UAR(baud_clk,reset,receive,rx_data,rx_status);
  universal_asynchronous_transmitter UAT(baud_clk,reset,tx_enable,UART_TXD,tx_status,transmit);
  baud_rate_generator BAUD(sysclk,baud_clk,reset);
  always @ (posedge baud_clk or posedge reset)
  begin
    if(reset)
    begin
      tx_former_status <= 1'b0;
    end
    else
    begin
      tx_former_status <= tx_status;
    end
  end
  
  always @ (posedge clk or posedge reset)
  begin
    if(reset)
    begin
      UART_TXD<=8'b0;
      UART_RXD<=8'b0;
      UART_CON<=4'b0;
      rx_former_status <= 1'b0;
      tx_enable <= 1'b0;
    end
    else
    begin
      rx_former_status <= rx_status;
      if(~tx_former_status & tx_status) UART_CON[2]<=1'b1;
      if(~rx_former_status & rx_status)
      begin
        UART_RXD <= rx_data;
        UART_CON[3] <= 1'b1;
      end
      else
      begin
        if(rd && addr==32'h40000020)
        begin
          UART_CON[3:2] <= 2'b00;
        end
      end
      if(wr)
      begin
        case(addr)
          32'h40000018:
          begin
            if(tx_status)
            begin
              UART_TXD <= wdata[7:0];
              tx_enable <= 1'b1;
            end
          end
          32'h40000020:
          begin
            UART_CON[1:0] <= wdata[1:0];
          end
          default: ;
        endcase
      end
      else
      begin
        if(tx_former_status&~tx_status)
        begin
          tx_enable <= 1'b0;
        end
      end
    end
  end
endmodule

