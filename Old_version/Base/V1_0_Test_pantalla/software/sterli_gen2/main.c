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



void init_system_();


int main(void)
{     
    char event_touch=-1;
    int screen_x,screen_y;

    init_system_();
    LCD_Clear(White);
    while (1)  
   {

    	event_touch=event_is_up(&screen_x, &screen_y);
    	if(event_touch==0){// event down
    		TP_DrawPoint(screen_x,screen_y,RGB565CONVERT(rand()%255,rand()%255,rand()%255) );
    	}
    	else if(event_touch==1){// event up
    		LCD_Clear(White);
    	}
    	delay_ms(5);//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    	//   DrawCross( 17,200);
    	//   vid_draw_line(1, 1, rand()%320, rand()%240 ,1, RGB565CONVERT(rand()%255,rand()%255,rand()%255) );
    	//   vid_draw_box (0, 0, 100, 100, RED_16,DO_FILL);
    	//   vid_print_string(0, 0, WHITE_16, cour10_font, "Hola Peter");
    	//   vid_draw_circle(150, 100, 50, BLUE_16, DO_FILL);
    	//   vid_print_string_alpha(0, 100, YELLOW_16, CLEAR_BACKGROUND, &tahomabold_20, "Fabio Gay");

  }
   

	return 0;
}

void init_system_(){
    IOWR_ALTERA_AVALON_PIO_DATA(BL_P_BASE, 1);
    IOWR_ALTERA_AVALON_PIO_DATA(BL_N_BASE, 0);

    TP_Init();
	LCD_Initializtion();

    LCD_Clear(Blue);
    LCD_Clear(Yellow);
    LCD_Clear(White);
    LCD_Clear(Black);
    LCD_Clear(Magenta);
    LCD_Clear(Red);
    LCD_Clear(Green);
    LCD_Clear(Cyan);

    auto_calibration();

    LCD_Clear(Black);
}
