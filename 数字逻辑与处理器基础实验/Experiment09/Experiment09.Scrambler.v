
module scrambler(clk, rst, frame_start,scramb_en, din, dout, scramb_out_en);
    input clk;
    input rst;
    input scramb_en;
    input din;
    input frame_start;
    output dout;
    output scramb_out_en;

    wire dout;
    reg scramb_out_en;
    reg [14:0] regarr;
    
    wire temp;
    
    parameter SEED = 15'h2566;
    
    assign dout = din^regarr[14]^regarr[13];
	assign temp = regarr[14]^regarr[13];
    
    always@(posedge clk, posedge rst)
	begin
		if(rst)
        begin
			  regarr <= SEED;
            //dout <= 0;
           scramb_out_en <= 0;
        end
    else if(frame_start)
      begin
        regarr <= SEED;
        //dout <= 0;
        scramb_out_en <= 0;
      end
        else 
        begin
            scramb_out_en <= scramb_en;
      
            if (scramb_en)
            begin
                regarr <= {regarr[13:0],temp};
                //dout <= din^temp;
            end
        end
    end
endmodule
