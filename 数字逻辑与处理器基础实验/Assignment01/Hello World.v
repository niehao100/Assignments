module hello_world;
  initial begin
    $display("Hello World!");
    #10 $finish;
  end //initial
endmodule //hello_world