// ============================================================================
// Copyright (c) 2014 by Terasic Technologies Inc.
// ============================================================================
//
// Permission:
//
//   Terasic grants permission to use and modify this code for use
//   in synthesis for all Terasic Development Boards and Altera Development 
//   Kits made by Terasic.  Other use of this code, including the selling 
//   ,duplication, or modification of any portion is strictly prohibited.
//
// Disclaimer:
//
//   This VHDL/Verilog or C/C++ source code is intended as a design reference
//   which illustrates how these types of functions can be implemented.
//   It is the user's responsibility to verify their design for
//   consistency and functionality through the use of formal
//   verification methods.  Terasic provides no warranty regarding the use 
//   or functionality of this code.
//
// ============================================================================
//           
//  Terasic Technologies Inc
//  9F., No.176, Sec.2, Gongdao 5th Rd, East Dist, Hsinchu City, 30070. Taiwan
//  
//  
//                     web: http://www.terasic.com/  
//                     email: support@terasic.com
//
// ============================================================================
//Date:  Tue Dec  2 09:28:38 2014
// ============================================================================

`define ENABLE_HPS
//`define ENABLE_CLK

module ghrd(

      ///////// ADC /////////
      output             ADC_CONVST,
      output             ADC_SCK,
      output             ADC_SDI,
      input              ADC_SDO,

      ///////// ARDUINO /////////
      inout       [15:0] ARDUINO_IO,
      inout              ARDUINO_RESET_N,

`ifdef ENABLE_CLK
      ///////// CLK /////////
      output             CLK_I2C_SCL,
      inout              CLK_I2C_SDA,
`endif /*ENABLE_CLK*/

      ///////// FPGA /////////
      input              FPGA_CLK1_50,
      input              FPGA_CLK2_50,
      input              FPGA_CLK3_50,

      ///////// GPIO /////////
      inout       [35:0] GPIO_0,
      inout       [35:0] GPIO_1,

`ifdef ENABLE_HPS
      ///////// HPS /////////
      inout              HPS_CONV_USB_N,
      output      [14:0] HPS_DDR3_ADDR,
      output      [2:0]  HPS_DDR3_BA,
      output             HPS_DDR3_CAS_N,
      output             HPS_DDR3_CKE,
      output             HPS_DDR3_CK_N,
      output             HPS_DDR3_CK_P,
      output             HPS_DDR3_CS_N,
      output      [3:0]  HPS_DDR3_DM,
      inout       [31:0] HPS_DDR3_DQ,
      inout       [3:0]  HPS_DDR3_DQS_N,
      inout       [3:0]  HPS_DDR3_DQS_P,
      output             HPS_DDR3_ODT,
      output             HPS_DDR3_RAS_N,
      output             HPS_DDR3_RESET_N,
      input              HPS_DDR3_RZQ,
      output             HPS_DDR3_WE_N,
      output             HPS_ENET_GTX_CLK,
      inout              HPS_ENET_INT_N,
      output             HPS_ENET_MDC,
      inout              HPS_ENET_MDIO,
      input              HPS_ENET_RX_CLK,
      input       [3:0]  HPS_ENET_RX_DATA,
      input              HPS_ENET_RX_DV,
      output      [3:0]  HPS_ENET_TX_DATA,
      output             HPS_ENET_TX_EN,
      inout              HPS_GSENSOR_INT,
//      inout              HPS_I2C0_SCLK,
//      inout              HPS_I2C0_SDAT,
//      inout              HPS_I2C1_SCLK,
//      inout              HPS_I2C1_SDAT,
      inout              HPS_KEY,
      inout              HPS_LED,
      inout              HPS_LTC_GPIO,
      output             HPS_SD_CLK,
      inout              HPS_SD_CMD,
      inout       [3:0]  HPS_SD_DATA,
//      output             HPS_SPIM_CLK,
//      input              HPS_SPIM_MISO,
//      output             HPS_SPIM_MOSI,
//      inout              HPS_SPIM_SS,
      input              HPS_UART_RX,
      output             HPS_UART_TX,
      input              HPS_USB_CLKOUT,
      inout       [7:0]  HPS_USB_DATA,
      input              HPS_USB_DIR,
      input              HPS_USB_NXT,
      output             HPS_USB_STP,
`endif /*ENABLE_HPS*/

      ///////// KEY /////////
      input       [1:0]  KEY,

      ///////// LED /////////
      output      [7:0]  LED,

      ///////// SW /////////
      input       [3:0]  SW
);


//=======================================================
//  REG/WIRE declarations
//=======================================================
  wire  hps_fpga_reset_n;
  wire [1:0] fpga_debounced_buttons;
  wire [6:0]  fpga_led_internal;
  wire [2:0]  hps_reset_req;
  wire        hps_cold_reset;
  wire        hps_warm_reset;
  wire        hps_debug_reset;
  wire [27:0] stm_hw_events;
  wire 		  fpga_clk_50;
// connection of internal logics

  assign fpga_clk_50=FPGA_CLK1_50;
  assign stm_hw_events    = {{15{1'b0}}, SW, fpga_led_internal, fpga_debounced_buttons};

 
//=======================================================
//  Structural coding
//=======================================================

/*--------------Impresora UART, TX, RX, CTS, RTS-------------------*/
wire printer_CTS;
wire sel_lcd_printer;
wire tx_uart;
//	printer  rx
wire rx_uart = GPIO_1[28];
//printer tx
assign GPIO_1[29] = tx_uart;

/*--------------Los puertos para el PWM del MOSFET, IGBTs-------------------*/
	/*--------------mosfet_control_data[7:0]=>pwm1-------------------*/
	/*--------------mosfet_control_data[15:8]=>pwm2-------------------*/
	/*--------------mosfet_control_data[23:16]=>pwm3-------------------*/
	/*--------------mosfet_control_data[31:24]=>pwm4-------------------*/
wire [31:0]mosfet_control_data;
wire mosfet_control_en;// habilitador de los canales PWM
wire PWMs_CLK;//señal para el contro de pwm q es de 120 Hz


/*--------------MAX6675 o termocuplas tipo K-------------------*/
wire [15:0]temp_max6675_1;
wire [15:0]temp_max6675_2;
wire [15:0]max6675_data= max6675_sel? temp_max6675_2[15:0]: temp_max6675_1[15:0];
wire max6675_sel;


/*--------------Audio-------------------*/
wire [31:0]alarm_div_32_audio;
wire audio_alarma;
wire audio_alarma2;

/*--------------UART LCD Nextion-------------------*/
wire rx_lcd_uart_ready;
wire [7:0]uart_data;
wire wait_fifo_uart_write;
wire [31:0]read_data_fifo;
reg [7:0]tx_data;
wire wait_a_while_tx;
wire read_fifo;


//ADC
wire [2:0]adc_ch;
wire [11:0]adc_data;


//Valvulas
wire valvula_escape,valvula1,valvula2;

//parado de emergencia
wire parado_emer= (GPIO_1[3] & SW[0]) | SW[1];

//asignacion de valvulas
assign GPIO_0[1]= valvula_escape |parado_emer;
assign GPIO_0[5]= valvula1;
assign GPIO_0[3]= valvula2;

//ALARMA
wire start_alarm=alarm_div_32_audio[31];
wire checker;
wire checker_sync2;

//RTC -HPS I2C-0
// i2c connection
  wire scl_o_e;
  wire scl_o;
  wire sda_o_e;
  wire sda_o; 
  
// salida de sonido
assign GPIO_1[22]=FPGA_CLK1_50? (audio_alarma2 & parado_emer):(audio_alarma & checker_sync2);


alarma alarma_parado_emergencia
(
	.clk(FPGA_CLK1_50) ,	// input  clk_sig
	.speaker(audio_alarma2) 	// output  speaker_sig
);


  
 soc_system u0 (
		//Clock&Reset
	  .clk_clk                               (FPGA_CLK1_50 ),                               //                            clk.clk
	  .reset_reset_n                         (hps_fpga_reset_n ),                         //                          reset.reset_n
	  //HPS ddr3
	  .memory_mem_a                          ( HPS_DDR3_ADDR),                       //                memory.mem_a
	  .memory_mem_ba                         ( HPS_DDR3_BA),                         //                .mem_ba
	  .memory_mem_ck                         ( HPS_DDR3_CK_P),                       //                .mem_ck
	  .memory_mem_ck_n                       ( HPS_DDR3_CK_N),                       //                .mem_ck_n
	  .memory_mem_cke                        ( HPS_DDR3_CKE),                        //                .mem_cke
	  .memory_mem_cs_n                       ( HPS_DDR3_CS_N),                       //                .mem_cs_n
	  .memory_mem_ras_n                      ( HPS_DDR3_RAS_N),                      //                .mem_ras_n
	  .memory_mem_cas_n                      ( HPS_DDR3_CAS_N),                      //                .mem_cas_n
	  .memory_mem_we_n                       ( HPS_DDR3_WE_N),                       //                .mem_we_n
	  .memory_mem_reset_n                    ( HPS_DDR3_RESET_N),                    //                .mem_reset_n
	  .memory_mem_dq                         ( HPS_DDR3_DQ),                         //                .mem_dq
	  .memory_mem_dqs                        ( HPS_DDR3_DQS_P),                      //                .mem_dqs
	  .memory_mem_dqs_n                      ( HPS_DDR3_DQS_N),                      //                .mem_dqs_n
	  .memory_mem_odt                        ( HPS_DDR3_ODT),                        //                .mem_odt
	  .memory_mem_dm                         ( HPS_DDR3_DM),                         //                .mem_dm
	  .memory_oct_rzqin                      ( HPS_DDR3_RZQ),                        //                .oct_rzqin                                  
	  //HPS ethernet		
	  .hps_0_hps_io_hps_io_emac1_inst_TX_CLK ( HPS_ENET_GTX_CLK),       //                             hps_0_hps_io.hps_io_emac1_inst_TX_CLK
	  .hps_0_hps_io_hps_io_emac1_inst_TXD0   ( HPS_ENET_TX_DATA[0] ),   //                             .hps_io_emac1_inst_TXD0
	  .hps_0_hps_io_hps_io_emac1_inst_TXD1   ( HPS_ENET_TX_DATA[1] ),   //                             .hps_io_emac1_inst_TXD1
	  .hps_0_hps_io_hps_io_emac1_inst_TXD2   ( HPS_ENET_TX_DATA[2] ),   //                             .hps_io_emac1_inst_TXD2
	  .hps_0_hps_io_hps_io_emac1_inst_TXD3   ( HPS_ENET_TX_DATA[3] ),   //                             .hps_io_emac1_inst_TXD3
	  .hps_0_hps_io_hps_io_emac1_inst_RXD0   ( HPS_ENET_RX_DATA[0] ),   //                             .hps_io_emac1_inst_RXD0
	  .hps_0_hps_io_hps_io_emac1_inst_MDIO   ( HPS_ENET_MDIO ),         //                             .hps_io_emac1_inst_MDIO
	  .hps_0_hps_io_hps_io_emac1_inst_MDC    ( HPS_ENET_MDC  ),         //                             .hps_io_emac1_inst_MDC
	  .hps_0_hps_io_hps_io_emac1_inst_RX_CTL ( HPS_ENET_RX_DV),         //                             .hps_io_emac1_inst_RX_CTL
	  .hps_0_hps_io_hps_io_emac1_inst_TX_CTL ( HPS_ENET_TX_EN),         //                             .hps_io_emac1_inst_TX_CTL
	  .hps_0_hps_io_hps_io_emac1_inst_RX_CLK ( HPS_ENET_RX_CLK),        //                             .hps_io_emac1_inst_RX_CLK
	  .hps_0_hps_io_hps_io_emac1_inst_RXD1   ( HPS_ENET_RX_DATA[1] ),   //                             .hps_io_emac1_inst_RXD1
	  .hps_0_hps_io_hps_io_emac1_inst_RXD2   ( HPS_ENET_RX_DATA[2] ),   //                             .hps_io_emac1_inst_RXD2
	  .hps_0_hps_io_hps_io_emac1_inst_RXD3   ( HPS_ENET_RX_DATA[3] ),   //                             .hps_io_emac1_inst_RXD3		  
	  //HPS SD card 
	  .hps_0_hps_io_hps_io_sdio_inst_CMD     ( HPS_SD_CMD    ),           //                               .hps_io_sdio_inst_CMD
	  .hps_0_hps_io_hps_io_sdio_inst_D0      ( HPS_SD_DATA[0]     ),      //                               .hps_io_sdio_inst_D0
	  .hps_0_hps_io_hps_io_sdio_inst_D1      ( HPS_SD_DATA[1]     ),      //                               .hps_io_sdio_inst_D1
	  .hps_0_hps_io_hps_io_sdio_inst_CLK     ( HPS_SD_CLK   ),            //                               .hps_io_sdio_inst_CLK
	  .hps_0_hps_io_hps_io_sdio_inst_D2      ( HPS_SD_DATA[2]     ),      //                               .hps_io_sdio_inst_D2
	  .hps_0_hps_io_hps_io_sdio_inst_D3      ( HPS_SD_DATA[3]     ),      //                               .hps_io_sdio_inst_D3
	  //HPS USB 		  
	  .hps_0_hps_io_hps_io_usb1_inst_D0      ( HPS_USB_DATA[0]    ),      //                               .hps_io_usb1_inst_D0
	  .hps_0_hps_io_hps_io_usb1_inst_D1      ( HPS_USB_DATA[1]    ),      //                               .hps_io_usb1_inst_D1
	  .hps_0_hps_io_hps_io_usb1_inst_D2      ( HPS_USB_DATA[2]    ),      //                               .hps_io_usb1_inst_D2
	  .hps_0_hps_io_hps_io_usb1_inst_D3      ( HPS_USB_DATA[3]    ),      //                               .hps_io_usb1_inst_D3
	  .hps_0_hps_io_hps_io_usb1_inst_D4      ( HPS_USB_DATA[4]    ),      //                               .hps_io_usb1_inst_D4
	  .hps_0_hps_io_hps_io_usb1_inst_D5      ( HPS_USB_DATA[5]    ),      //                               .hps_io_usb1_inst_D5
	  .hps_0_hps_io_hps_io_usb1_inst_D6      ( HPS_USB_DATA[6]    ),      //                               .hps_io_usb1_inst_D6
	  .hps_0_hps_io_hps_io_usb1_inst_D7      ( HPS_USB_DATA[7]    ),      //                               .hps_io_usb1_inst_D7
	  .hps_0_hps_io_hps_io_usb1_inst_CLK     ( HPS_USB_CLKOUT    ),       //                               .hps_io_usb1_inst_CLK
	  .hps_0_hps_io_hps_io_usb1_inst_STP     ( HPS_USB_STP    ),          //                               .hps_io_usb1_inst_STP
	  .hps_0_hps_io_hps_io_usb1_inst_DIR     ( HPS_USB_DIR    ),          //                               .hps_io_usb1_inst_DIR
	  .hps_0_hps_io_hps_io_usb1_inst_NXT     ( HPS_USB_NXT    ),          //                               .hps_io_usb1_inst_NXT
//		//HPS SPI 		  
//	  .hps_0_hps_io_hps_io_spim1_inst_CLK    ( HPS_SPIM_CLK  ),           //                               .hps_io_spim1_inst_CLK
//	  .hps_0_hps_io_hps_io_spim1_inst_MOSI   ( HPS_SPIM_MOSI ),           //                               .hps_io_spim1_inst_MOSI
//	  .hps_0_hps_io_hps_io_spim1_inst_MISO   ( HPS_SPIM_MISO ),           //                               .hps_io_spim1_inst_MISO
//	  .hps_0_hps_io_hps_io_spim1_inst_SS0    ( HPS_SPIM_SS   ),             //                               .hps_io_spim1_inst_SS0
		//HPS UART		
	  .hps_0_hps_io_hps_io_uart0_inst_RX     ( HPS_UART_RX   ),          //                               .hps_io_uart0_inst_RX
	  .hps_0_hps_io_hps_io_uart0_inst_TX     ( HPS_UART_TX   ),          //                               .hps_io_uart0_inst_TX
//		//HPS I2C1
//	  .hps_0_hps_io_hps_io_i2c0_inst_SDA     ( HPS_I2C0_SDAT  ),        //                               .hps_io_i2c0_inst_SDA
//	  .hps_0_hps_io_hps_io_i2c0_inst_SCL     ( HPS_I2C0_SCLK  ),        //                               .hps_io_i2c0_inst_SCL
//		//HPS I2C2
//	  .hps_0_hps_io_hps_io_i2c1_inst_SDA     ( HPS_I2C1_SDAT  ),        //                               .hps_io_i2c1_inst_SDA
//	  .hps_0_hps_io_hps_io_i2c1_inst_SCL     ( HPS_I2C1_SCLK  ),        //                               .hps_io_i2c1_inst_SCL
		//GPIO 
	  .hps_0_hps_io_hps_io_gpio_inst_GPIO09  ( HPS_CONV_USB_N ),  //                               .hps_io_gpio_inst_GPIO09
	  .hps_0_hps_io_hps_io_gpio_inst_GPIO35  ( HPS_ENET_INT_N ),  //                               .hps_io_gpio_inst_GPIO35
	  .hps_0_hps_io_hps_io_gpio_inst_GPIO40  ( HPS_LTC_GPIO   ),  //                               .hps_io_gpio_inst_GPIO40
	  .hps_0_hps_io_hps_io_gpio_inst_GPIO53  ( HPS_LED   ),  //                               .hps_io_gpio_inst_GPIO53
	  .hps_0_hps_io_hps_io_gpio_inst_GPIO54  ( HPS_KEY   ),  //                               .hps_io_gpio_inst_GPIO54
	  .hps_0_hps_io_hps_io_gpio_inst_GPIO61  ( HPS_GSENSOR_INT ),  //                               .hps_io_gpio_inst_GPIO61
		//FPGA Partion
	  .led_pio_external_connection_export    ( fpga_led_internal 	),    //    led_pio_external_connection.export
	  .dipsw_pio_external_connection_export  ( SW	),  //  dipsw_pio_external_connection.export
	   
	  .hps_0_h2f_reset_reset_n               ( hps_fpga_reset_n ),                //                hps_0_h2f_reset.reset_n
	  .hps_0_f2h_cold_reset_req_reset_n      (~hps_cold_reset ),      //       hps_0_f2h_cold_reset_req.reset_n
     .hps_0_f2h_debug_reset_req_reset_n     (~hps_debug_reset ),     //      hps_0_f2h_debug_reset_req.reset_n
     .hps_0_f2h_stm_hw_events_stm_hwevents  (stm_hw_events ),  //        hps_0_f2h_stm_hw_events.stm_hwevents
     .hps_0_f2h_warm_reset_req_reset_n      (~hps_warm_reset ),      //       hps_0_f2h_warm_reset_req.reset_n
		
		 
		// impresora - HPS UART1
	  .printer_uart_cts                      (1'b1),                      //                   printer_uart.cts
	  .printer_uart_dsr                      (1'b1),                      //                               .dsr
	  .printer_uart_dcd                      (1'b1),                      //                               .dcd
	  .printer_uart_ri                       (1'b1),                       //                               .ri
	  .printer_uart_dtr                      (),                      //                               .dtr
	  .printer_uart_rts                      (printer_CTS),                      //                               .rts
	  .printer_uart_rxd                      (rx_uart),                      //                               .rxd
	  .printer_uart_txd                      (tx_uart),                      //                               .txd
	  
	  //ADC - FPGA side., canal axi lw
	  .adc_sel_channel_export                   (adc_ch[2:0]),                   //                   adc_sel_channel.export
	  .adc_input_data_export                    (adc_data[11:0]) ,                    //    
	
	  //MOSFET control - FPGA side axi lw
	  .mosfet_control_export                    (mosfet_control_data[31:0]),                    //                    mosfet_control.export
	  .mosfet_en_export                         (mosfet_control_en),                         //                         mosfet_en.export
	  
	  //Valves Control  FPGA side axi lw
	  .valves_control_export                    ({valvula1,valvula2,valvula_escape}),                    //                    valves_control.export
	  
	  // Electro Control FPGA side axi lw
	  .electro_control_export                   ({GPIO_0[33],GPIO_0[31],GPIO_0[29],GPIO_0[27]}),                   //                   electro_control.export
	  
	  //alarm FPGA side axi lw
	  .alarm_div_32_export                      (alarm_div_32_audio[31:0]),                      //                      alarm_div_32.export
	  
	  //Input buttons control FPGA side axi lw
	  .buttons_inicio_emer_final_control_export ({GPIO_1[3],GPIO_1[0],GPIO_1[1]}), // buttons_inicio_emer_final_control.export
	  
	  //Max 6675 Acquisition  FPGA side axi lw
	  .max6675_temp_export                      (max6675_data[15:0]),                      //                      max6675_temp.export
	  .sel_max6675_export                       (max6675_sel),                        //                       sel_max6675.export
	  
	  //UART LCD Nextion - FPGA side axi
     .uart_rx_lcd_in_writedata                 ({24'd0,uart_data[7:0]}),                 //                    uart_rx_lcd_in.writedata
	  .uart_rx_lcd_in_write                     ( rx_lcd_uart_ready),                     //                                  .write
	  .uart_rx_lcd_in_waitrequest               (wait_fifo_uart_write ),              //                                  .waitrequest
	  .uart_tx_lcd_out_readdata                 (read_data_fifo[31:0]),                 //                   uart_tx_lcd_out.readdata
	  .uart_tx_lcd_out_read                     (read_fifo),                     //                                  .read
	  .uart_tx_lcd_out_waitrequest              (wait_a_while_tx),

		//RTC - HPS I2C0
	  .hps_0_i2c0_out_data					(sda_o_e),                   
	  .hps_0_i2c0_sda							(sda_o),                  
	  .hps_0_i2c0_clk_clk					(scl_o_e),						
	  .hps_0_i2c0_scl_in_clk				(scl_o)		
	
 );
 
 //RTC provides
  // I2C interface from HPS export to FPGA
  ALT_IOBUF scl_iobuf (.i(1'b0), .oe(scl_o_e), .o(scl_o), .io(GPIO_1[6])); //declared bi-directional buffer for scl
  ALT_IOBUF sda_iobuf (.i(1'b0), .oe(sda_o_e), .o(sda_o), .io(GPIO_1[7])); //declared bi-directional buffer for sda
 

 
// Source/Probe megawizard instance
hps_reset hps_reset_inst (
  .source_clk (fpga_clk_50),
  .source     (hps_reset_req)
);

altera_edge_detector pulse_cold_reset (
  .clk       (fpga_clk_50),
  .rst_n     (hps_fpga_reset_n),
  .signal_in (hps_reset_req[0]),
  .pulse_out (hps_cold_reset)
);
  defparam pulse_cold_reset.PULSE_EXT = 6;
  defparam pulse_cold_reset.EDGE_TYPE = 1;
  defparam pulse_cold_reset.IGNORE_RST_WHILE_BUSY = 1;

altera_edge_detector pulse_warm_reset (
  .clk       (fpga_clk_50),
  .rst_n     (hps_fpga_reset_n),
  .signal_in (hps_reset_req[1]),
  .pulse_out (hps_warm_reset)
);
  defparam pulse_warm_reset.PULSE_EXT = 2;
  defparam pulse_warm_reset.EDGE_TYPE = 1;
  defparam pulse_warm_reset.IGNORE_RST_WHILE_BUSY = 1;
  
altera_edge_detector pulse_debug_reset (
  .clk       (fpga_clk_50),
  .rst_n     (hps_fpga_reset_n),
  .signal_in (hps_reset_req[2]),
  .pulse_out (hps_debug_reset)
);
  defparam pulse_debug_reset.PULSE_EXT = 32;
  defparam pulse_debug_reset.EDGE_TYPE = 1;
  defparam pulse_debug_reset.IGNORE_RST_WHILE_BUSY = 1;

  
  
// PWMS  
wire pwm_secado1,pwm_secado2,pwm_camara1, pwm_camara2;
assign GPIO_0[13]= mosfet_control_en ? (pwm_secado1 & ~parado_emer) : 0;
assign GPIO_0[15]= mosfet_control_en ? (pwm_secado2 & ~parado_emer): 0;
assign GPIO_0[17]= mosfet_control_en ? (pwm_camara1 & ~parado_emer): 0;
assign GPIO_0[19]= mosfet_control_en ? (pwm_camara2 & ~parado_emer): 0;


// DEBUG PWM
assign ARDUINO_IO[0]=GPIO_0[13];
assign ARDUINO_IO[1]=GPIO_0[15];
assign ARDUINO_IO[2]=GPIO_0[17];
assign ARDUINO_IO[3]=GPIO_0[19];

//DEBUG
assign LED[7:0] = mosfet_control_en? {pwm_secado1,pwm_secado2,pwm_camara1,pwm_camara2,4'd0}: {valvula1,valvula2,valvula_escape,5'd0};
	 
PWM PWM_RSecado1
(
	.clk(PWMs_CLK) ,	// input  clk_sig
	.reset(1'b1),
	.motor(pwm_secado1) ,	// output  motor_sig
	.duty_cycle(mosfet_control_data[7:0]) 	// input [Bits_counter-1:0] duty_cycle_sig
);

PWM PWM_RSecado2
(
	.clk(PWMs_CLK) ,	// input  clk_sig
	.reset(1'b1),
	.motor(pwm_secado2) ,	// output  motor_sig
	.duty_cycle(mosfet_control_data[15:8]) 	// input [Bits_counter-1:0] duty_cycle_sig
);

PWM PWM_RCamara1
(
	.clk(PWMs_CLK) ,	// input  clk_sig
	.reset(1'b1),
	.motor(pwm_camara1) ,	// output  motor_sig
	.duty_cycle(mosfet_control_data[23:16]) 	// input [Bits_counter-1:0] duty_cycle_sig
);

PWM PWM_Camara2
(
	.clk(PWMs_CLK) ,	// input  clk_sig
	.reset(1'b1),
	.motor(pwm_camara2) ,	// output  motor_sig
	.duty_cycle(mosfet_control_data[31:24]) 	// input [Bits_counter-1:0] duty_cycle_sig
);


frecGen frecGen_PWMs
(
	.reset(1'b1) ,	// input  reset_sig
	.clock(FPGA_CLK1_50) ,	// input  clock_sig
	.IN(32'd400) ,	// input [31:0] IN_sig
	.OUT(PWMs_CLK) 	// output  OUT_sig
);


// habilitador automatico de sonido, a 0.5hz
frecGen frecGen_CHECKER
(
	.reset(1'b1) ,	// input  reset_sig
	.clock(FPGA_CLK1_50) ,	// input  clock_sig
	.IN(32'd50000000) ,	// input [31:0] IN_sig
	.OUT(checker) 	// output  OUT_sig
);

reg [31:0]div_val[1:0];
assign checker_sync2= ((div_val[0][31:0] == div_val[1][31:0]) &&  (div_val[1][31:0]==alarm_div_32_audio[31:0]))?1'b0:1'b1;
always@(posedge checker)
begin	
	div_val[0][31:0]<=alarm_div_32_audio[31:0];
	div_val[1][31:0]<=div_val[0][31:0];
end

frecGen frecGen_AUDIO
(
	.reset(1'b1) ,	// input  reset_sig
	.clock(FPGA_CLK1_50) ,	// input  clock_sig
	.IN(alarm_div_32_audio[31:0]) ,	// input [31:0] IN_sig
	.OUT(audio_alarma) 	// output  OUT_sig
);


//MAX 6675 

max6675_decoder max6675_decoder1
(
	.clk(FPGA_CLK1_50) ,	// input  clk_sig
	.start(1'b1) ,	// input  start_sig
	//control signals
	.miso(GPIO_1[18]) ,	// input  miso_sig
	.cs(GPIO_1[17]) ,	// output  cs_sig
	.sclk(GPIO_1[16]) ,	// output  sclk_sig
	//data max6675
	.temp_max6675(temp_max6675_1[15:0]) 	// output [15:0] temp_max6675_sig
);



max6675_decoder max6675_decoder2
(
	.clk(FPGA_CLK1_50) ,	// input  clk_sig
	.start(1'b1) ,	// input  start_sig
	//control signals
	.miso(GPIO_1[4]) ,	// input  miso_sig
	.cs(GPIO_1[5]) ,	// output  cs_sig
	.sclk(GPIO_1[2]) ,	// output  sclk_sig
	//data max6675
	.temp_max6675(temp_max6675_2[15:0]) 	// output [15:0] temp_max6675_sig
);


//ADC
ADC_System ADC_System_inst
(
	.clk_50Mhz(FPGA_CLK1_50) ,	// input  clk_50Mhz_sig
	.selected_channel(adc_ch[2:0]) ,	// input [2:0] selected_channel_sig
	.ADC_data(adc_data[11:0]) ,	// output [11:0] ADC_data_sig
	.ADC_CONVST(ADC_CONVST) ,	// output  ADC_CONVST_sig
	.ADC_SCK(ADC_SCK) ,	// output  ADC_SCK_sig
	.ADC_SDI(ADC_SDI) ,	// output  ADC_SDI_sig
	.ADC_SDO(ADC_SDO) 	// input  ADC_SDO_sig
);


//UART LCD
async_receiver async_receiver_inst
(
	.clk(FPGA_CLK1_50) ,	// input  clk_sig
	.RxD(GPIO_1[26]) ,	// input  RxD_sig
	.RxD_data_ready(rx_lcd_uart_ready) ,	// output  RxD_data_ready_sig
	.RxD_data(uart_data[7:0]) ,	// output [7:0] RxD_data_sig
	.RxD_idle() ,	// output  RxD_idle_sig
	.RxD_endofpacket() 	// output  RxD_endofpacket_sig
);

defparam async_receiver_inst.ClkFrequency = 50000000;
defparam async_receiver_inst.Baud = 9600;
defparam async_receiver_inst.Oversampling = 8;


wire busy_tx;
wire start_transmission;
 //tx
async_transmitter async_transmitter_inst
(
	.clk(FPGA_CLK1_50) ,	// input  clk_sig
	.TxD_start(start_transmission) ,	// input  TxD_start_sig
	.TxD_data(tx_data[7:0]) ,	// input [7:0] TxD_data_sig
	.TxD(GPIO_1[27]) ,	// output  TxD_sig
	.TxD_busy(busy_tx) 	// output  TxD_busy_sig
);

defparam async_transmitter_inst.ClkFrequency = 50000000;
defparam async_transmitter_inst.Baud = 9600;


									// read, state
localparam IDLE		   =	5'b0_____0001;	   
localparam REQUEST_READ =	5'b1_____0010;	
localparam READ_DATA	   =	5'b0_____0100;	
localparam WAIT_UNTIL   =	5'b0_____1000;	

reg [4:0]state=IDLE;
wire get_sample=state[2];
assign start_transmission=state[3];
assign read_fifo=state[4];

always@(posedge FPGA_CLK1_50)
begin
	case(state[4:0])
	IDLE:
		begin
			state[4:0]<=IDLE;
			if(busy_tx==1'b0 && wait_a_while_tx==1'b0)
			begin
				state[4:0]<=REQUEST_READ;
			end
		end
	REQUEST_READ:
		begin
			state[4:0]<=READ_DATA;
		end
	READ_DATA:
		begin
			state[4:0]<=WAIT_UNTIL;
		end
	WAIT_UNTIL:
		begin
			state[4:0]<=IDLE;
		end
	endcase
end

always@(posedge FPGA_CLK1_50)
begin
	if(get_sample)
	begin
		tx_data[7:0]<=read_data_fifo[7:0];
	end
end



  
endmodule
