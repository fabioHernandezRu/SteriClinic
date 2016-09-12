// --------------------------------------------------------------------
// Copyright (c) 2015 by Semillero ADT. 
// --------------------------------------------------------------------
//
// --------------------------------------------------------------------
//
//                     web: https://sites.google.com/site/semilleroadt/
//                     email: semilleroadtupb@gmail.com
//
// --------------------------------------------------------------------
//
// Major Functions:	BE-MICRO MAX10 TOP
//
// --------------------------------------------------------------------
//
// Revision History :
// --------------------------------------------------------------------
//   Ver  :| Author:Fabian Humberto Castillo Pineda | Mod. Date :18-May-2015 7:16:08 PM
//| Changes Made:

// --------------------------------------------------------------------



module practica4( //CLOCKS
						CLK_50,
						USER_CLK,
						
                                                //LED
						LED,

                                              //SW
						SW,

			                            //FLASH
						SFLASH_DCLK,
						SFLASH_ASDI,
						SFLASH_CSn, 
						SFLASH_DATA,

                                            //SDRAM
						SDRAM_A,
						SDRAM_BA,
						SDRAM_CASn,
						SDRAM_CKE,
						SDRAM_CLK,
						SDRAM_CSn,
						SDRAM_DQ,
						SDRAM_RASn,
						SDRAM_WEn,
						SDRAM_DQM,

                                          //PMOD_A
						PMOD_A,

                                              //PMOD_B
						PMOD_B,

                                             //PMOD_C
						PMOD_C,

                                         //PMOD_D
						PMOD_D,

                                        //GPIO_0/DIFF
						GPIO_0,

);



//CLOCKS
input CLK_50;
input USER_CLK;

//LED
output [7:0]LED;

//SW
input [3:0]SW;

//FLASH
output SFLASH_DCLK;
output SFLASH_ASDI;
output SFLASH_CSn;
input SFLASH_DATA;

//SDRAM
output [12:0]SDRAM_A;
output [1:0]SDRAM_BA;
output SDRAM_CASn;
output SDRAM_CKE;
output SDRAM_CLK;
output SDRAM_CSn;
inout [15:0]SDRAM_DQ;
output SDRAM_RASn;
output SDRAM_WEn;
output [1:0]SDRAM_DQM;

//PMOD_A
inout [3:0]PMOD_A;

//PMOD_B
inout [3:0]PMOD_B;

//PMOD_C
inout [3:0]PMOD_C;

//PMOD_D
inout [3:0]PMOD_D;

//GPIO_0/DIFF/J3
inout [35:0]GPIO_0;

//=======================================================
//  REG/WIRE declarations
//======================================================= 
wire BLP,BLN;
 //=======================================================
//  Structural coding
//======================================================= 
assign GPIO_0[21]=BLP;

    mi_nios u0 (
        .clk_clk       (CLK_50),       //       clk.clk
		  .reset_reset_n (1'b1), //     reset.reset_n
		  
		  //Flash
        .flash_dclk    (SFLASH_DCLK),    //     flash.dclk
        .flash_sce     (SFLASH_CSn),     //          .sce
        .flash_sdo     (SFLASH_ASDI),     //          .sdo
        .flash_data0   (SFLASH_DATA),   //          .data0
        //LED AND SW
        .led_export    (LED[7:0]),    //       led.export
		  .sw_export     (SW[3:0]),      //        sw.export
		  
		  //SDRAM
        .sdram_addr    (SDRAM_A),    //     sdram.addr
        .sdram_ba      (SDRAM_BA),      //          .ba
        .sdram_cas_n   (SDRAM_CASn),   //          .cas_n
        .sdram_cke     (SDRAM_CKE),     //          .cke
        .sdram_cs_n    (SDRAM_CSn),    //          .cs_n
        .sdram_dq      (SDRAM_DQ),      //          .dq
        .sdram_dqm     (SDRAM_DQM),     //          .dqm
        .sdram_ras_n   (SDRAM_RASn),   //          .ras_n
        .sdram_we_n    (SDRAM_WEn),    //          .we_n
        .sdram_clk_clk (SDRAM_CLK), // sdram_clk.clk
			
			//TOUCH
		  .spi_touch_MISO    (GPIO_0[22]),    //  spi_touch.MISO
        .spi_touch_MOSI    (GPIO_0[23]),    //           .MOSI
        .spi_touch_SCLK    (GPIO_0[24]),    //           .SCLK
        //.spi_touch_SS_n    (GPIO_0[25]),    //           .SS_n
		  .touch_cs_export   (GPIO_0[26]),   //   touch_cs.export
        .touch_irq_export  (GPIO_0[27]),  //  touch_irq.export
		  
		  //LCD
        .lcd_cs_export     (GPIO_0[16]),     //     lcd_cs.export
        .lcd_rs_export     (GPIO_0[17]),     //     lcd_rs.export        
        .reset_1_export    (GPIO_0[20]),    //    reset_1.export
        .lcd_wr_export     (GPIO_0[18]),     //     lcd_wr.export
        .lcd32_data_export (GPIO_0[15:0]), // lcd32_data.export
        .lcd_rd_export     (GPIO_0[19]),     //     lcd_rd.export
        .bl_p_export       (BLP),       //       bl_p.export
        .bl_n_export       (BLN)        //       bl_n.export
        
    );


 endmodule   