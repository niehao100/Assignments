module FrameTrans(Reset,Clock100M,Mode,Clock,DataIn);
	input 		Reset;
	input 		Clock100M;
	input [1:0] Mode;
	output 		Clock;
	output reg	DataIn;
	
	reg [31:0] Counter;
	reg        Clk_10ms;
	
	reg [7:0]  StateCnt256;
	reg [1:0]  FrameCnt4;
	reg 	   FrameStart;
	reg        ScrambEn;
	
	wire	   ScrambOut;
	
	parameter  DELAY_NUM = 500_000-1;
	//parameter  DELAY_NUM = 5;
	parameter  FRAMEHEAD = 8'b1001_1011;
	parameter  FRAMEHEAD_WRONG = 8'b1000_1001;	
	assign Clock = Clk_10ms;
	
//	Generate Clk_400ms Signal;
	always@(posedge Reset or posedge Clock100M)
	begin
		if(Reset == 1'b1)
		begin
			Counter <= 0;
			Clk_10ms <= 0;
		end
		else
		begin
			Counter <= Counter + 1;
			if(Counter == DELAY_NUM)
			begin
				Counter <= 0;
				Clk_10ms <= ~Clk_10ms;
			end
		end
	end

// Transmission Control
	always@(posedge Reset or posedge Clk_10ms)
	begin
		if(Reset == 1'b1)
		begin
			StateCnt256 <= 0;
			DataIn <= 0;
			FrameStart <= 0;
			ScrambEn <= 0;
			FrameCnt4 <= 0;
		end
		else if(Mode > 0)
		begin
			FrameStart <= 0;
			StateCnt256 <= StateCnt256 + 1;
			if(StateCnt256)
				FrameCnt4 <= FrameCnt4 + 1;
			if(StateCnt256 < 8)
			begin
				ScrambEn <= 0;
				
				if(Mode == 3 && FrameCnt4 == 2)
					DataIn <= FRAMEHEAD_WRONG>>(7 - StateCnt256);
				else
					DataIn <= FRAMEHEAD>>(7 - StateCnt256);	
					
				if(StateCnt256 == 5)
					FrameStart<=1;
				else if	(StateCnt256 > 5)
					ScrambEn <= 1;
			end
			else
			begin
				DataIn <= ScrambOut;
				if(StateCnt256 == 255 && Mode == 1)
				begin
					StateCnt256 <= 255;
					ScrambEn <= 0;
					DataIn <= 0;
				end	
			end	
		
		end
		else
		begin
			StateCnt256 <= 0;
			DataIn <= 0;
			FrameStart <= 0;
			ScrambEn <= 0;
			FrameCnt4 <= 0;
		end
	end
	
	scrambler U1(.clk(Clk_10ms), 
			  .rst(Reset),
			  .frame_start(FrameStart),
			  .scramb_en(ScrambEn),
			  .din(0),
			  .dout(ScrambOut),
			  .scramb_out_en());
			  
	
endmodule 