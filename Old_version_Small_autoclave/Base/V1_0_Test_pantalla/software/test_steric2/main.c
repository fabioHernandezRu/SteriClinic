/********************************************************************************************************
*
* File                : LCD22(main)
* Hardware Environment:
* Build Environment   : Quartus II Version 10.1 / Nios II 10.1
* Version             :
* By                  : Su Wei Feng
*
*                                  (c) Copyright 2005-2011, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/
#include "alt_types.h"
#include <io.h>
#include <stdlib.h>
#include <unistd.h>
#include <system.h>
#include "altera_avalon_pio_regs.h"
#include "LCD32.h"
#include "touch.h"

#define DIRECTION_PA(data)  IOWR_ALTERA_AVALON_PIO_DIRECTION(PA_BASE, data)
#define DATA_PA(data)  IOWR_ALTERA_AVALON_PIO_DATA(PA_BASE, data)
int main(void)
{     
       IOWR_ALTERA_AVALON_PIO_DATA(BL_P_BASE, 1);
       IOWR_ALTERA_AVALON_PIO_DATA(BL_N_BASE, 0);
       
       TP_Init();
	   LCD_Initializtion();
       
//       LCD_Clear(Blue);
//       LCD_Clear(Yellow);
//       LCD_Clear(White);
//       LCD_Clear(Black);
//       LCD_Clear(Magenta);
//       LCD_Clear(Red);
//       LCD_Clear(Green);
//       LCD_Clear(Cyan);
//
//      //LCD_show_test();
//
        TouchPanel_Calibrate();

        LCD_Clear(Black);

    while (1)  
  {
    //getDisplayPoint(&display, Read_Ads7846(), &matrix ) ;
    //TP_DrawPoint(display.x,display.y);
   DrawCross( 17,200);
   //vid_draw_line(1, 1, rand()%320, rand()%240 ,1, RGB565CONVERT(rand()%255,rand()%255,rand()%255) );
   vid_draw_box (0, 0, 100, 100, RED_16);
   vid_print_string(0, 0, WHITE_16, cour10_font, "Hola Peter");
   vid_draw_circle(150, 100, 50, BLUE_16, DO_FILL);
   vid_print_string_alpha(0, 100, YELLOW_16, CLEAR_BACKGROUND, &tahomabold_20, "Fabio Gay");

  }
   

	return 0;
}
