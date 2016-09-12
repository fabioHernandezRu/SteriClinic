	mi_nios u0 (
		.bl_n_export       (<connected-to-bl_n_export>),       //       bl_n.export
		.bl_p_export       (<connected-to-bl_p_export>),       //       bl_p.export
		.clk_clk           (<connected-to-clk_clk>),           //        clk.clk
		.flash_dclk        (<connected-to-flash_dclk>),        //      flash.dclk
		.flash_sce         (<connected-to-flash_sce>),         //           .sce
		.flash_sdo         (<connected-to-flash_sdo>),         //           .sdo
		.flash_data0       (<connected-to-flash_data0>),       //           .data0
		.lcd32_data_export (<connected-to-lcd32_data_export>), // lcd32_data.export
		.lcd_cs_export     (<connected-to-lcd_cs_export>),     //     lcd_cs.export
		.lcd_rd_export     (<connected-to-lcd_rd_export>),     //     lcd_rd.export
		.lcd_rs_export     (<connected-to-lcd_rs_export>),     //     lcd_rs.export
		.lcd_wr_export     (<connected-to-lcd_wr_export>),     //     lcd_wr.export
		.led_export        (<connected-to-led_export>),        //        led.export
		.reset_reset_n     (<connected-to-reset_reset_n>),     //      reset.reset_n
		.reset_1_export    (<connected-to-reset_1_export>),    //    reset_1.export
		.sdram_addr        (<connected-to-sdram_addr>),        //      sdram.addr
		.sdram_ba          (<connected-to-sdram_ba>),          //           .ba
		.sdram_cas_n       (<connected-to-sdram_cas_n>),       //           .cas_n
		.sdram_cke         (<connected-to-sdram_cke>),         //           .cke
		.sdram_cs_n        (<connected-to-sdram_cs_n>),        //           .cs_n
		.sdram_dq          (<connected-to-sdram_dq>),          //           .dq
		.sdram_dqm         (<connected-to-sdram_dqm>),         //           .dqm
		.sdram_ras_n       (<connected-to-sdram_ras_n>),       //           .ras_n
		.sdram_we_n        (<connected-to-sdram_we_n>),        //           .we_n
		.sdram_clk_clk     (<connected-to-sdram_clk_clk>),     //  sdram_clk.clk
		.spi_touch_MISO    (<connected-to-spi_touch_MISO>),    //  spi_touch.MISO
		.spi_touch_MOSI    (<connected-to-spi_touch_MOSI>),    //           .MOSI
		.spi_touch_SCLK    (<connected-to-spi_touch_SCLK>),    //           .SCLK
		.spi_touch_SS_n    (<connected-to-spi_touch_SS_n>),    //           .SS_n
		.sw_export         (<connected-to-sw_export>),         //         sw.export
		.touch_cs_export   (<connected-to-touch_cs_export>),   //   touch_cs.export
		.touch_irq_export  (<connected-to-touch_irq_export>)   //  touch_irq.export
	);

