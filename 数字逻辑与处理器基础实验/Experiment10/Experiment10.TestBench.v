module testbench_for_receriver();  
  reg clk,receive,reset;
  wire [7:0] data;
  wire status;
  
  initial
  begin
    clk=1'b0;
    receive=1'b1;
    reset=1'b1;
    #1 reset=1'b0;
    #104167 receive=1'b0;
    #104167 receive=1'b1;
    #104167 receive=1'b0;
    #104167 receive=1'b1;
    #104167 receive=1'b1;
    #104167 receive=1'b0;
    #104167 receive=1'b1;
    #104167 receive=1'b0;
    #104167 receive=1'b1;
    #104167 receive=1'b1;
    
    #104167 receive=1'b0;
    
    #104167 receive=1'b0;
    #104167 receive=1'b1;
    #104167 receive=1'b0;
    #104167 receive=1'b1;
    #104167 receive=1'b1;
    #104167 receive=1'b0;
    #104167 receive=1'b0;
    #104167 receive=1'b0;
    #104167 receive=1'b1;
    #104167 receive=1'b1;
    
    #200000 $stop;
  end
  
  always @ (*)
  begin
    #3255 clk<=~clk;
  end
  
  universal_asynchronous_receiver rx(clk,reset,receive,data,status);
endmodule

module testbench_for_baud_generator();  
  reg sysclk,reset;
  wire clk;
  
  initial
  begin
    sysclk=1'b0;
    reset=1'b1;
    #1 reset=1'b0;
    
    #20000 $stop;
  end
  
  always @ (*)
  begin
    #5 sysclk<=~sysclk;
  end
  
  baud_rate_generator generator(sysclk,clk,reset);
endmodule

module testbench_for_transmitter();  
  reg sysclk,enable,reset;
  reg [7:0] data;
  wire status,clk;
  
  initial
  begin
    sysclk<=1'b0;
    reset=1'b1;
    data=8'b10110101;
    #1 reset<=1'b0;
    #100 enable<=1'b1;
    #1 enable<=1'b0;
    #2000000 enable<=1'b1;
    #1 enable<=1'b0;
    
    #2000000 $stop;
  end
  
  always @ (*)
  begin
    #5 sysclk<=~sysclk;
  end
  
  
  baud_rate_generator generator(sysclk,clk,reset);
  
  universal_asynchronous_transmitter tx(clk,reset,enable,data,status,transmit);
endmodule

module testbench_for_uart();  
  reg sysclk,receive,reset;
  
  initial
  begin
    sysclk=1'b0;
    receive=1'b1;
    reset=1'b1;
    #1 reset=1'b0;
    #104167 receive=1'b0;
    #104167 receive=1'b1;
    #104167 receive=1'b0;
    #104167 receive=1'b1;
    #104167 receive=1'b1;
    #104167 receive=1'b0;
    #104167 receive=1'b1;
    #104167 receive=1'b0;
    #104167 receive=1'b1;
    #104167 receive=1'b1;
    
    #104167 receive=1'b0;
    #104167 receive=1'b1;
    #104167 receive=1'b0;
    #104167 receive=1'b0;
    #104167 receive=1'b1;
    #104167 receive=1'b0;
    #104167 receive=1'b0;
    #104167 receive=1'b0;
    #104167 receive=1'b1;
    #104167 receive=1'b1;
    
    #2000000 $stop;
  end
  
  always @ (*)
  begin
    #5 sysclk<=~sysclk;
  end
  
  UART uart1(receive,uart_tx,reset,sysclk);
endmodule