
module mi_nios (
	bl_n_export,
	bl_p_export,
	clk_clk,
	flash_dclk,
	flash_sce,
	flash_sdo,
	flash_data0,
	lcd32_data_export,
	lcd_cs_export,
	lcd_rd_export,
	lcd_rs_export,
	lcd_wr_export,
	led_export,
	reset_reset_n,
	reset_1_export,
	sdram_addr,
	sdram_ba,
	sdram_cas_n,
	sdram_cke,
	sdram_cs_n,
	sdram_dq,
	sdram_dqm,
	sdram_ras_n,
	sdram_we_n,
	sdram_clk_clk,
	spi_touch_MISO,
	spi_touch_MOSI,
	spi_touch_SCLK,
	spi_touch_SS_n,
	sw_export,
	touch_cs_export,
	touch_irq_export);	

	output		bl_n_export;
	output		bl_p_export;
	input		clk_clk;
	output		flash_dclk;
	output		flash_sce;
	output		flash_sdo;
	input		flash_data0;
	inout	[15:0]	lcd32_data_export;
	output		lcd_cs_export;
	output		lcd_rd_export;
	output		lcd_rs_export;
	output		lcd_wr_export;
	output	[7:0]	led_export;
	input		reset_reset_n;
	output		reset_1_export;
	output	[11:0]	sdram_addr;
	output	[1:0]	sdram_ba;
	output		sdram_cas_n;
	output		sdram_cke;
	output		sdram_cs_n;
	inout	[15:0]	sdram_dq;
	output	[1:0]	sdram_dqm;
	output		sdram_ras_n;
	output		sdram_we_n;
	output		sdram_clk_clk;
	input		spi_touch_MISO;
	output		spi_touch_MOSI;
	output		spi_touch_SCLK;
	output		spi_touch_SS_n;
	input	[3:0]	sw_export;
	output		touch_cs_export;
	input		touch_irq_export;
endmodule
