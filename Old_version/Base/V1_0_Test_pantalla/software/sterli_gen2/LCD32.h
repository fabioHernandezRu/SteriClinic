/*********************************************************************************************************
*
* File                : LCD.h
* Hardware Environment: 
* Build Environment   : RealView MDK-ARM  Version: 4.20
* Version             : V1.0
* By                  : 
*
*                                  (c) Copyright 2005-2011, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/

#ifndef __LCD32_H 
#define __LCD32_H

#include <io.h>
#include <system.h>
#include <unistd.h>
#include "alt_types.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_spi_regs.h"
#include "altera_avalon_spi.h"
#include "fonts.h"  // modify this file to add/remove fonts

// use this background colour when you don't want a filled in box behind the alpha blended text
#define CLEAR_BACKGROUND -1

#define TAB_SPACING 2

#define RGB 1 // set to 0 if you need BGR instead

#define DO_FILL 1
#define DO_NOT_FILL 0

#define BLACK_8 0x00

#define FONT_10PT_ROW 11
#define FONT_10PT_COLUMN 8
extern char* cour10_font;

/* Includes ------------------------------------------------------------------*/
//#include <math.h>


//#define DISP_HOR_RESOLUTION               320
//#define DISP_VER_RESOLUTION               240

//#define DISP_ORIENTATION                  0
#define DISP_ORIENTATION                    90
//#define DISP_ORIENTATION                  180
//#define DISP_ORIENTATION                  270

#if  ( DISP_ORIENTATION == 90 ) || ( DISP_ORIENTATION == 270 )

#define  MAX_X  320
#define  MAX_Y  240   

#elif  ( DISP_ORIENTATION == 0 ) || ( DISP_ORIENTATION == 180 )

#define  MAX_X  240
#define  MAX_Y  320   

#endif

#define DIRECTION_PA(data)  IOWR_ALTERA_AVALON_PIO_DIRECTION(PA_BASE, data)
#define DATA_PA(data)  IOWR_ALTERA_AVALON_PIO_DATA(PA_BASE, data)

#define Set_Cs        IOWR_ALTERA_AVALON_PIO_DATA(LCD_CS_BASE, 1)
#define Clr_Cs        IOWR_ALTERA_AVALON_PIO_DATA(LCD_CS_BASE, 0)

#define Set_Rs        IOWR_ALTERA_AVALON_PIO_DATA(LCD_RS_BASE, 1)
#define Clr_Rs        IOWR_ALTERA_AVALON_PIO_DATA(LCD_RS_BASE, 0)

#define Set_nWr       IOWR_ALTERA_AVALON_PIO_DATA(LCD_WR_BASE, 1)
#define Clr_nWr       IOWR_ALTERA_AVALON_PIO_DATA(LCD_WR_BASE, 0)

#define Set_nRd       IOWR_ALTERA_AVALON_PIO_DATA(LCD_RD_BASE, 1)
#define Clr_nRd       IOWR_ALTERA_AVALON_PIO_DATA(LCD_RD_BASE, 0)

#define Set_RST       IOWR_ALTERA_AVALON_PIO_DATA(RESET_BASE, 1)
#define Clr_RST       IOWR_ALTERA_AVALON_PIO_DATA(RESET_BASE, 0)

/* LCD color */
#define ALICEBLUE_16  0xFFDE
#define ANTIQUEWHITE_16 0xD75F
#define AQUA_16 0xFFC0
#define AQUAMARINE_16 0xD7CF
#define AZURE_16  0xFFDE
#define BEIGE_16  0xDF9E
#define BISQUE_16 0xC71F
#define BLACK_16  0x0000
#define BLANCHEDALMOND_16 0xCF5F
#define BLUE_16 0xF800
#define BLUEVIOLET_16 0xE151
#define BROWN_16  0x2954
#define BURLYWOOD_16  0x85DB
#define CADETBLUE_16  0xA4CB
#define CHARTREUSE_16 0x07CF
#define CHOCOLATE_16  0x1B5A
#define CORAL_16  0x53DF
#define CORNFLOWERBLUE_16 0xEC8C
#define CORNSILK_16 0xDFDF
#define CRIMSON_16  0x389B
#define CYAN_16 0xFFC0
#define DARKBLUE_16 0x8800
#define DARKCYAN_16 0x8C40
#define DARKGOLDENROD_16  0xC17
#define DARKGRAY_16 0xAD55
#define DARKGREEN_16  0x300
#define DARKKHAKI_16  0x6D97
#define DARKMAGENTA_16  0x8811
#define DARKOLIVEGREEN_16 0x2B4A
#define DARKORANGE_16 0x045F
#define DARKORCHID_16 0xC993
#define DARKRED_16  0x0011
#define DARKSALMON_16 0x7C9D
#define DARKSEAGREEN_16 0x8DD1
#define DARKSLATEBLUE_16  0x89C9
#define DARKSLATEGRAY_16  0x4A45
#define DARKTURQUOISE_16  0xD640
#define DARKVIOLET_16 0xD012
#define DEEPPINK_16 0x909F
#define DEEPSKYBLUE_16  0xFDC0
#define DIMGRAY_16  0x6B4D
#define DODGERBLUE_16 0xFC83
#define FELDSPAR_16 0x749A
#define FIREBRICK_16  0x2116
#define FLORALWHITE_16  0xF7DF
#define FORESTGREEN_16  0x2444
#define FUCHSIA_16  0xF81F
#define GAINSBORO_16  0xDEDB
#define GHOSTWHITE_16 0xFFDF
#define GOLD_16 0x069F
#define GOLDENROD_16  0x251B
#define GRAY_16 0x8410
#define GRAY25_16 0x4208
#define GRAY50_16 0x7BCF
#define GRAY75_16 0xC618
#define GREEN_16  0x0400
#define GREENYELLOW_16  0x2FD5
#define HONEYDEW_16 0xF7DE
#define HOTPINK_16  0xB35F
#define INDIANRED_16  0x5AD9
#define INDIGO_16 0x8009
#define IVORY_16  0xF7DF
#define KHAKI_16  0x8F1E
#define LAVENDER_16 0xFF1C
#define LAVENDERBLUSH_16  0xF79F
#define LAWNGREEN_16  0x07CF
#define LEMONCHIFFON_16 0xCFDF
#define LIGHTBLUE_16  0xE6D5
#define LIGHTCORAL_16 0x841E
#define LIGHTCYAN_16  0xFFDC
#define LIGHTGOLDENRODYELLOW_16 0xD7DF
#define LIGHTGREEN_16 0x9752
#define LIGHTGREY_16  0xD69A
#define LIGHTPINK_16  0xC59F
#define LIGHTSALMON_16  0x7D1F
#define LIGHTSEAGREEN_16  0xAD84
#define LIGHTSKYBLUE_16 0xFE50
#define LIGHTSLATEBLUE_16 0xFB90
#define LIGHTSLATEGRAY_16 0x9C4E
#define LIGHTSTEELBLUE_16 0xDE16
#define LIGHTYELLOW_16  0xE7DF
#define LIME_16 0x7C0
#define LIMEGREEN_16  0x3646
#define LINEN_16  0xE79F
#define MAGENTA_16  0xF81F
#define MAROON_16 0x0010
#define MEDIUMAQUAMARINE_16 0xAE4C
#define MEDIUMBLUE_16 0xC800
#define MEDIUMORCHID_16 0xD297
#define MEDIUMPURPLE_16 0xDB92
#define MEDIUMSEAGREEN_16 0x7587
#define MEDIUMSLATEBLUE_16  0xEB4F
#define MEDIUMSPRINGGREEN_16  0x9FC0
#define MEDIUMTURQUOISE_16  0xCE89
#define MEDIUMVIOLETRED_16  0x8098
#define MIDNIGHTBLUE_16 0x70C3
#define MINTCREAM_16  0xFFDE
#define MISTYROSE_16  0xE71F
#define MOCCASIN_16 0xB71F
#define NAVAJOWHITE_16  0xAEDF
#define NAVY_16 0x8000
#define OLDLACE_16  0xE79F
#define OLIVE_16  0x0410
#define OLIVEDRAB_16  0x244D
#define ORANGE_16 0x051F
#define ORANGERED_16  0x021F
#define ORCHID_16 0xD39B
#define PALEGOLDENROD_16  0xAF5D
#define PALEGREEN_16  0x9FD3
#define PALETURQUOISE_16  0xEF55
#define PALEVIOLETRED_16  0x939B
#define PAPAYAWHIP_16 0xD75F
#define PEACHPUFF_16  0xBEDF
#define PERU_16 0x3C19
#define PINK_16 0xCE1F
#define PLUM_16 0xDD1B
#define POWDERBLUE_16 0xE716
#define PURPLE_16 0x8010
#define RED_16  0x001F
#define ROSYBROWN_16  0x8C57
#define ROYALBLUE_16  0x9080
#define SADDLEBROWN_16  0x1211
#define SALMON_16 0x741F
#define SANDYBROWN_16 0x651E
#define SEAGREEN_16 0x5445
#define SEASHELL_16 0xEF9F
#define SIENNA_16 0x2A94
#define SILVER_16 0xC618
#define SKYBLUE_16  0xEE50
#define SLATEBLUE_16  0xCACD
#define SLATEGRAY_16  0x940E
#define SNOW_16 0xFFDF
#define SPRINGGREEN_16  0x7FC0
#define STEELBLUE_16  0xB408
#define TAN_16  0x8D9A
#define TEAL_16 0x8400
#define THISTLE_16  0xDDDB
#define TOMATO_16 0x431F
#define TURQUOISE_16  0xD708
#define VIOLET_16 0xEC1D
#define VIOLETRED_16  0x911A
#define WHEAT_16  0xB6DE
#define WHITE_16  0xFFDF
#define WHITESMOKE_16 0xF79E
#define YELLOW_16 0x07DF
#define YELLOWGREEN_16  0x3653
#define White          0xFFFF
#define Black          0x0000
#define Grey           0xF7DE
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

#define RGB565CONVERT(red, green, blue) (int) (((red >> 3) << 11) | ((green >> 2) << 5) | (blue >> 3))

/* Private function prototypes -----------------------------------------------*/
void LCD_Initializtion(void);
void LCD_Clear(alt_u16 Color); 
alt_u16 LCD_BGR2RGB(alt_u16 color);
//void LCD_SetBacklight(uint8_t intensity);
alt_u16 LCD_GetPoint(alt_u16 Xpos,alt_u16 Ypos);
void LCD_SetPoint(alt_u16 Xpos,alt_u16 Ypos,alt_u16 point);
void PutChar(alt_u16 Xpos,alt_u16 Ypos,alt_u8 c,alt_u16 charColor,alt_u16 bkColor);
void LCD_DrawLine( alt_u16 x0, alt_u16 y0, alt_u16 x1, alt_u16 y1 , alt_u16 color );
//void PutChinese(alt_u16 Xpos,alt_u16 Ypos,alt_u8 *str,alt_u16 Color,alt_u16 bkColor); 
void GUI_Text(alt_u16 Xpos, alt_u16 Ypos, alt_u8 *str,alt_u16 Color, alt_u16 bkColor);
__inline__ void vid_draw_line(int horiz_start, int vert_start, int horiz_end, int vert_end, int width, int color);
void vid_set_pixel(int horiz, int vert, unsigned int color);
void vid_draw_horiz_line (short Hstart, short Hend, int V, int color);
int vid_print_char (int horiz_offset, int vert_offset, int color, char character, char *font);
void vid_paint_block (int Hstart,int Vstart, int Hend, int Vend, int color);
int vid_draw_box (int horiz_start, int vert_start, int horiz_end, int vert_end, int color,int fill);
int vid_print_string(int horiz_offset, int vert_offset, int color, char *font, char string[]);
void vid_round_corner_points( int cx, int cy, int x, int y,
                              int straight_width, int straight_height, int color,
                              char fill);
int vid_draw_circle(int Hcenter, int Vcenter, int radius, int color, char fill);

int vid_print_string_alpha(int horiz_offset, int vert_offset, int color, int background_color, struct abc_font_struct font[], char string[]);
int vid_print_char_alpha (int horiz_offset, int vert_offset, int color, char character, int background_color, struct abc_font_struct font[]);
//void GUI_Chinese(alt_u16 Xpos, alt_u16 Ypos, alt_u8 *str,alt_u16 Color, alt_u16 bkColor);  
//void LCD_DrawPicture(alt_u16 StartX,alt_u16 StartY,alt_u16 EndX,alt_u16 EndY,alt_u16 *pic);


__inline void LCD_WriteIndex(alt_u16 index);
__inline void LCD_WriteData(alt_u16 data);
__inline alt_u16 LCD_ReadData(void);
__inline alt_u16 LCD_ReadReg(alt_u16 LCD_Reg);
__inline void LCD_WriteReg(alt_u16 LCD_Reg,alt_u16 LCD_RegValue);
void LCD_SetCursor( alt_u16 Xpos, alt_u16 Ypos );
void delay_ms(alt_u16 ms);

#endif 

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

