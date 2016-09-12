// Copyright (C) 1991-2015 Altera Corporation. All rights reserved.
// Your use of Altera Corporation's design tools, logic functions 
// and other software and tools, and its AMPP partner logic 
// functions, and any output files from any of the foregoing 
// (including device programming or simulation files), and any 
// associated documentation or information are expressly subject 
// to the terms and conditions of the Altera Program License 
// Subscription Agreement, the Altera Quartus II License Agreement,
// the Altera MegaCore Function License Agreement, or other 
// applicable license agreement, including, without limitation, 
// that your use is for the sole purpose of programming logic 
// devices manufactured by Altera and sold by Altera or its 
// authorized distributors.  Please refer to the applicable 
// agreement for further details.


// Generated by Quartus II 64-Bit Version 15.0 (Build Build 145 04/22/2015)
// Created on Thu Aug 25 08:54:10 2016

adc_ltc2308 adc_ltc2308_inst
(
	.clk(clk_sig) ,	// input  clk_sig
	.measure_start(measure_start_sig) ,	// input  measure_start_sig
	.measure_ch(measure_ch_sig) ,	// input [2:0] measure_ch_sig
	.measure_done(measure_done_sig) ,	// output  measure_done_sig
	.measure_dataread(measure_dataread_sig) ,	// output [11:0] measure_dataread_sig
	.ADC_CONVST(ADC_CONVST_sig) ,	// output  ADC_CONVST_sig
	.ADC_SCK(ADC_SCK_sig) ,	// output  ADC_SCK_sig
	.ADC_SDI(ADC_SDI_sig) ,	// output  ADC_SDI_sig
	.ADC_SDO(ADC_SDO_sig) 	// input  ADC_SDO_sig
);
