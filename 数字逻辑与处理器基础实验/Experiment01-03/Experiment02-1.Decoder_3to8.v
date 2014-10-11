module decoder_3to8(
  a,
  d);
  
  input [2:0] a;

  output [7:0] d;

  wire [2:0] a;
  reg [7:0] d;

  always @(*)
  begin
    d[0]<=a==3'b000;
    d[1]<=a==3'b001;
    d[2]<=a==3'b010;
    d[3]<=a==3'b011;
    d[4]<=a==3'b100;
    d[5]<=a==3'b101;
    d[6]<=a==3'b110;
    d[7]<=a==3'b111;
  end

endmodule
