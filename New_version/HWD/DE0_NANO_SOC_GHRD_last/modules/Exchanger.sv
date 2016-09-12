module interchanger(
	input clk,
	input [31:0]ARM_DATA_FROM,
	output [31:0]ARM_DATA_TO,
	input [3:0]ARM_SEL,
	input ARM_WR,//deben ser sincronos a CLK
	input [31:0]NIOS_DATA_FROM,
	output [31:0]NIOS_DATA_TO,
	input [3:0]NIOS_SEL,
	input NIOS_WR////deben ser sincronos a CLK
);
 
 
Ram_exchanger	Ram_exchanger_inst (
	.address_a ( ARM_SEL[3:0] ),
	.data_a ( ARM_DATA_FROM[31:0] ),
	.wren_a ( ARM_WR ),
	.q_a ( ARM_DATA_TO[31:0] ),
	
	
	.address_b ( NIOS_SEL[3:0] ),
	.clock ( clk),
	.data_b ( NIOS_DATA_FROM[31:0] ),
	.wren_b ((NIOS_SEL[3:0] >= 4'd8)? NIOS_WR:1'b0 ),
	.q_b ( NIOS_DATA_TO[31:0] )
	);


endmodule
