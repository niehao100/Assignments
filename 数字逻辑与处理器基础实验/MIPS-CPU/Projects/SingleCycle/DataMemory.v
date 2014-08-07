module DataMemory(reset,sysclk,clk,rd,wr,addr,wdata,rdata,LED,SWITCH,DIGIT,TX,RX,IRQ);
  input reset,sysclk,clk;
  input rd,wr;
  input [31:0] addr;
  output [31:0] rdata;
  input [31:0] wdata;
  
  output [7:0] LED;
  input [7:0] SWITCH;
  output [11:0] DIGIT;
  output TX,IRQ;
  input RX;
  
  //parameter RAM_SIZE = 256; //RAM address from 32'h00000000 to 32'h000003FF
  parameter RAM_SIZE = 256; //RAM address from 32'h00000000 to 32'h000003FF
  parameter RAM_END = 32'h40000000;
  parameter PERIPHERIAL_END = 32'h40000018;
  parameter UART_END = 32'h40000024;
  reg [31:0] RAM_DATA [RAM_SIZE-1:0];
  
  wire [7:0] LED;
  wire [11:0] DIGIT;
  wire [31:0] PERIPHERIAL_DATA;
  wire [31:0] UART_DATA;
  
  assign rdata = rd ? 
    (~(|addr[31:10]) ? RAM_DATA[addr[9:2]] :
      /*addr>=RAM_END && addr<PERIPHERIAL_END ? PERIPHERIAL_DATA[addr[4:2]] :
      addr<UART_END ? UART_DATA : 32'd0)*/
      addr==32'h40000018 | addr==32'h4000001c | addr==32'h40000020 ? UART_DATA : PERIPHERIAL_DATA[addr[4:2]])
    :32'd0;
    
  always@(posedge clk)
  begin
    if(wr&&(~|addr[31:10])) RAM_DATA[addr[9:2]]<=wdata;
  end
  
  assign peripheral_write = wr&&addr>=RAM_END&&addr<PERIPHERIAL_END;
  Peripheral p0(reset,clk,rd,peripheral_write,addr,wdata,PERIPHERIAL_DATA,LED,SWITCH,DIGIT,IRQ);
  assign uart_write = wr&&addr>=PERIPHERIAL_END&&addr<UART_END;
  assign uart_read = rd&&addr>=PERIPHERIAL_END&&addr<UART_END;
  UART uart0(reset,sysclk,clk,uart_read,uart_write,addr,wdata,UART_DATA,TX,RX);
endmodule
