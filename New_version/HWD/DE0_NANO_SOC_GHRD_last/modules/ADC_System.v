module ADC_System(
			input clk_50Mhz,
			input [2:0]selected_channel,
			output [11:0]ADC_data,
			
			//ADC Side
			
			output ADC_CONVST,	// output  ADC_CONVST_sig
			output ADC_SCK,	// output  ADC_SCK_sig
			output ADC_SDI,	// output  ADC_SDI_sig
			input ADC_SDO 	// input  ADC_SDO_sig
);

										//start____counter_clk___ state
localparam IDLE 		      =		5'b0_____0_____________000;
localparam SET_CHANNEL     =		5'b0_____0_____________010;
localparam GET_DATA_SAMPLE =		5'b1_____0_____________011;
localparam INCREASE_COUNTER=		5'b0_____1_____________100;

//ADC 
reg [4:0]state= IDLE;
reg [11:0]data_channels[7:0];
reg [2:0]channelADC=3'd0;
wire [11:0]measure_dataread;
wire start_measure=state[4];
wire counter_clk=state[3];
wire measure_done;
wire clk_fsm;

pll_adc_40mhz  pll_adc(
		.refclk(clk_50Mhz),   //  refclk.clk
		.rst(1'b0),      //   reset.reset
		.outclk_0(clk_fsm), // outclk0.clk
	);
	
	
assign ADC_data[11:0]=data_channels[selected_channel[2:0]][11:0];

always@(posedge measure_done)	
begin
	data_channels[channelADC[2:0]][11:0]<=measure_dataread[11:0];
end
	
	 
always@(posedge counter_clk)	
begin
	channelADC[2:0]<=channelADC[2:0]+1'b1;

end

always@(posedge clk_fsm)
begin
	case(state[4:0])
	IDLE 		       :
	begin
		state[4:0]<=SET_CHANNEL;
	end
	SET_CHANNEL     :
	begin
		state[4:0]<=GET_DATA_SAMPLE;
	end
	GET_DATA_SAMPLE :
	begin
		state[4:0]<=GET_DATA_SAMPLE;
		if(measure_done==1'b1)
		begin
			state[4:0]<=INCREASE_COUNTER;
		end
	end
	INCREASE_COUNTER:
	begin
		state[4:0]<=IDLE;
	end
	default:
	begin
		state[4:0]<=IDLE;
	end
	endcase
end
	
	
//ADC
adc_ltc2308 adc_ltc2308_inst
(
	.clk(clk_fsm) ,	// input  clk_sig
	.measure_start(start_measure) ,	// input  measure_start_sig
	.measure_ch(channelADC[2:0]) ,	// input [2:0] measure_ch_sig
	.measure_done(measure_done) ,	// output  measure_done_sig
	.measure_dataread(measure_dataread[11:0]) ,	// output [11:0] measure_dataread_sig
	.ADC_CONVST(ADC_CONVST) ,	// output  ADC_CONVST_sig
	.ADC_SCK(ADC_SCK) ,	// output  ADC_SCK_sig
	.ADC_SDI(ADC_SDI) ,	// output  ADC_SDI_sig
	.ADC_SDO(ADC_SDO) 	// input  ADC_SDO_sig
);



endmodule

