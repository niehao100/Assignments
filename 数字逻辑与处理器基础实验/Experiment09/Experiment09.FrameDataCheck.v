module FrameDataCheck(Reset,
					  Clock,
					  DataOut,
					  DataOutEn,
					  DataWrong);
				
	input Reset;
	input Clock;
	input DataOut;
	input DataOutEn;
	
	output reg DataWrong;
	
	reg SyncDataInEnTmp;
	reg SyncDataInTmp;
	
	wire FrameStart;
	wire ScrambOut;
	
	assign FrameStart = !DataOutEn & SyncDataInEnTmp;
	
	always@(posedge Reset or posedge Clock)
	begin
		if(Reset == 1'b1)
		begin
			SyncDataInEnTmp <= 0;
			SyncDataInTmp <= 0;
			DataWrong <= 0;
		end
		else
		begin
			SyncDataInEnTmp <= DataOutEn;
			SyncDataInTmp <= DataOut;	
			DataWrong <= 0;
			if(SyncDataInEnTmp == 1)
			begin
				if(SyncDataInTmp != ScrambOut)
					DataWrong <= 1;
			end
		end
	end
	
	scrambler U1(.clk(Clock), 
			  .rst(Reset),
			  .frame_start(FrameStart),
			  .scramb_en(DataOutEn),
			  .din(0),
			  .dout(ScrambOut),
			  .scramb_out_en());
endmodule 