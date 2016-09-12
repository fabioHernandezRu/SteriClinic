#include "LCD32.h" 
#include "AsciiLib.h"
/* Private define ------------------------------------------------------------*/
#define  ILI9320    0  /* 0x9320 */
#define  ILI9325    1  /* 0x9325 */
#define  ILI9328    2  /* 0x9328 */
#define  ILI9331    3  /* 0x9331 */
#define  SSD1298    4  /* 0x8999 */
#define  SSD1289    5  /* 0x8989 */
#define  ST7781     6  /* 0x7783 */
#define  LGDP4531   7  /* 0x4531 */
#define  SPFD5408B  8  /* 0x5408 */
#define  R61505U    9  /* 0x1505 0x0505 */     
#define  HX8347D    10 /* 0x0047 */
#define  HX8347A    11 /* 0x0047 */ 
#define  LGDP4535   12 /* 0x4535 */  
#define  SSD2119    13 /* 3.5 LCD 0x9919 */

const alt_u16 colorfol1[]={0xf800,0x07e0,0x001f,0xffe0,0x0000,0xffff,0x07ff,0xf81f};

/* Private variables ---------------------------------------------------------*/
static alt_u8 LCD_Code;

/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    : 
* Input          : - index:
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
__inline void LCD_WriteIndex(alt_u16 index)
{
    Clr_Rs;
    Set_nRd;
    
    IOWR_ALTERA_AVALON_PIO_DIRECTION(LCD32_DATA_BASE, 0XFFFF) ;  /* GPIO_Write(GPIOE,index); */
    IOWR_ALTERA_AVALON_PIO_DATA(LCD32_DATA_BASE, index);
    
    Clr_nWr;
    Set_nWr;
}

/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    : 
* Input          : - index:
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
__inline void LCD_WriteData(alt_u16 data)
{
    Set_Rs;
    
    IOWR_ALTERA_AVALON_PIO_DIRECTION(LCD32_DATA_BASE, 0XFFFF) ;  /* GPIO_Write(GPIOE,index); */
    IOWR_ALTERA_AVALON_PIO_DATA(LCD32_DATA_BASE, data);
    
    Clr_nWr;
    Set_nWr;
}

/*******************************************************************************
* Function Name  : LCD_ReadData
* Description    : 
* Input          : None
* Output         : None
* Return         : 
* Attention      : None
*******************************************************************************/
__inline alt_u16 LCD_ReadData(void)
{
    alt_u16 value;

    Set_Rs;
    Set_nWr;
    Clr_nRd;

/* 
    PE.00(D0), PE.01(D1), PE.02(D2), PE.03(D3), PE.04(D4), PE.05(D5), PE.06(D6), PE.07(D7), PE.08(D8)
    PE.09(D9), PE.10(D10), PE.11(D11), PE.12(D12), PE.13(D13), PE.14(D14), PE.15(D15)   */
/* 
    GPIO_InitTypeDef GPIO_InitStructure; 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
*/
    IOWR_ALTERA_AVALON_PIO_DIRECTION(LCD32_DATA_BASE, 0X0000) ;  /* GPIO_Write(GPIOE,index); */
    value=IORD_ALTERA_AVALON_PIO_DATA(LCD32_DATA_BASE);
     value=IORD_ALTERA_AVALON_PIO_DATA(LCD32_DATA_BASE);
    
    IOWR_ALTERA_AVALON_PIO_DIRECTION(LCD32_DATA_BASE, 0XFFFF) ;

    Set_nRd;

    return value;
}

/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    : Writes to the selected LCD register.
* Input          : - LCD_Reg: address of the selected register.
*                  - LCD_RegValue: value to write to the selected register.
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
__inline void LCD_WriteReg(alt_u16 LCD_Reg,alt_u16 LCD_RegValue)
{ 
    /* Write 16-bit Index, then Write Reg */  
    Clr_Cs;
    LCD_WriteIndex(LCD_Reg);         
    /* Write 16-bit Reg */
    LCD_WriteData(LCD_RegValue);  
    Set_Cs; 
}

/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    : Reads the selected LCD Register.
* Input          : None
* Output         : None
* Return         : LCD Register Value.
* Attention      : None
*******************************************************************************/
__inline alt_u16 LCD_ReadReg(alt_u16 LCD_Reg)
{
    alt_u16 LCD_RAM;
    
    /* Write 16-bit Index (then Read Reg) */
    Clr_Cs;
    LCD_WriteIndex(LCD_Reg);
    /* Read 16-bit Reg */
    LCD_RAM = LCD_ReadData();       
    Set_Cs;
    return LCD_RAM;
}

      

void LCD_SetCursor( alt_u16 Xpos, alt_u16 Ypos )
{
    #if  ( DISP_ORIENTATION == 90 ) || ( DISP_ORIENTATION == 270 )
    
    alt_u16 temp = Xpos;

             Xpos = Ypos;
             Ypos = ( MAX_X - 1 ) - temp;  

    #elif  ( DISP_ORIENTATION == 0 ) || ( DISP_ORIENTATION == 180 )
        
    #endif

  switch( LCD_Code )
  {
     default:        /* 0x9320 0x9325 0x9328 0x9331 0x5408 0x1505 0x0505 0x7783 0x4531 0x4535 */
          LCD_WriteReg(0x0020, Xpos );     
          LCD_WriteReg(0x0021, Ypos );     
          break; 

     case SSD1298:   /* 0x8999 */
     case SSD1289:   /* 0x8989 */
          LCD_WriteReg(0x004e, Xpos );      
        LCD_WriteReg(0x004f, Ypos );          
          break;  

     case HX8347A:   /* 0x0047 */
     case HX8347D:   /* 0x0047 */
          LCD_WriteReg(0x02, Xpos>>8 );                                                  
          LCD_WriteReg(0x03, Xpos );  

          LCD_WriteReg(0x06, Ypos>>8 );                           
          LCD_WriteReg(0x07, Ypos );    
    
          break;     
     case SSD2119:   /* 3.5 LCD 0x9919 */
          break; 
  }
}




/*******************************************************************************
* Function Name  : delay_ms
* Description    : Delay Time
* Input          : - cnt: Delay Time
* Output         : None
* Return         : None
* Return         : None
* Attention      : None
*******************************************************************************/
/*void delay_ms(alt_u16 ms)    
{ 
    alt_u16 i,j; 
    for( i = 0; i < ms; i++ )
    { 
        for( j = 0; j < 1141; j++ );
    }
} 
*/
/*******************************************************************************
* Function Name  : LCD_Initializtion
* Description    : SSD1963 Resets
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void LCD_Initializtion(void)
{
    alt_u16 DeviceCode;

   // LCD_Configuration();
     Clr_RST ;      /* LCD_RESET *////0
    delay_ms(100);
     Set_RST;    /////////1

    /* Set MN(multipliers) of PLL, VCO = crystal freq * (N+1) */
    /* PLL freq = VCO/M with 250MHz < VCO < 800MHz */
    /* The max PLL freq is around 120MHz. To obtain 120MHz as the PLL freq */

    DeviceCode = LCD_ReadReg(0x0000);       /* Read LCD ID  */                 
    
    /*For ILI9325*/ 
    if( DeviceCode == 0x9325 || DeviceCode == 0x9328 )  
    {
        LCD_Code = ILI9325;
        LCD_WriteReg(0x00e7,0x0010);      
        LCD_WriteReg(0x0000,0x0001);    /* start internal osc */
        LCD_WriteReg(0x0001,0x0100);     
        LCD_WriteReg(0x0002,0x0700);    /* power on sequence */
        LCD_WriteReg(0x0003,(1<<12)|(1<<5)|(1<<4)|(0<<3) );     /* importance */
        LCD_WriteReg(0x0004,0x0000);                                   
        LCD_WriteReg(0x0008,0x0207);               
        LCD_WriteReg(0x0009,0x0000);         
        LCD_WriteReg(0x000a,0x0000);    /* display setting */        
        LCD_WriteReg(0x000c,0x0001);    /* display setting */        
        LCD_WriteReg(0x000d,0x0000);                    
        LCD_WriteReg(0x000f,0x0000);
        /* Power On sequence */
        LCD_WriteReg(0x0010,0x0000);   
        LCD_WriteReg(0x0011,0x0007);
        LCD_WriteReg(0x0012,0x0000);                                                                 
        LCD_WriteReg(0x0013,0x0000);                 
        delay_ms(50);  /* delay 50 ms */        
        LCD_WriteReg(0x0010,0x1590);   
        LCD_WriteReg(0x0011,0x0227);
        delay_ms(50);  /* delay 50 ms */        
        LCD_WriteReg(0x0012,0x009c);                  
        delay_ms(50);  /* delay 50 ms */        
        LCD_WriteReg(0x0013,0x1900);   
        LCD_WriteReg(0x0029,0x0023);
        LCD_WriteReg(0x002b,0x000e);
        delay_ms(50);  /* delay 50 ms */        
        LCD_WriteReg(0x0020,0x0000);                                                            
        LCD_WriteReg(0x0021,0x0000);           
        delay_ms(50);  /* delay 50 ms */        
        LCD_WriteReg(0x0030,0x0007); 
        LCD_WriteReg(0x0031,0x0707);   
        LCD_WriteReg(0x0032,0x0006);
        LCD_WriteReg(0x0035,0x0704);
        LCD_WriteReg(0x0036,0x1f04); 
        LCD_WriteReg(0x0037,0x0004);
        LCD_WriteReg(0x0038,0x0000);        
        LCD_WriteReg(0x0039,0x0706);     
        LCD_WriteReg(0x003c,0x0701);
        LCD_WriteReg(0x003d,0x000f);
        delay_ms(50);  /* delay 50 ms */        
        LCD_WriteReg(0x0050,0x0000);        
        LCD_WriteReg(0x0051,0x00ef);   
        LCD_WriteReg(0x0052,0x0000);     
        LCD_WriteReg(0x0053,0x013f);
        LCD_WriteReg(0x0060,0xa700);        
        LCD_WriteReg(0x0061,0x0001); 
        LCD_WriteReg(0x006a,0x0000);
        LCD_WriteReg(0x0080,0x0000);
        LCD_WriteReg(0x0081,0x0000);
        LCD_WriteReg(0x0082,0x0000);
        LCD_WriteReg(0x0083,0x0000);
        LCD_WriteReg(0x0084,0x0000);
        LCD_WriteReg(0x0085,0x0000);
          
        LCD_WriteReg(0x0090,0x0010);     
        LCD_WriteReg(0x0092,0x0000);  
        LCD_WriteReg(0x0093,0x0003);
        LCD_WriteReg(0x0095,0x0110);
        LCD_WriteReg(0x0097,0x0000);        
        LCD_WriteReg(0x0098,0x0000);  
        /* display on sequence */    
        LCD_WriteReg(0x0007,0x0133);
        
        LCD_WriteReg(0x0020,0x0000);
        LCD_WriteReg(0x0021,0x0000);
    }
    else if( DeviceCode == 0x8989 )  /*For SSD1289*/
    {
        LCD_Code = SSD1289;
        LCD_WriteReg(0x0000,0x0001);    delay_ms(50);   /* Enable LCD Oscillator */
        LCD_WriteReg(0x0003,0xA8A4);    delay_ms(50);   
        LCD_WriteReg(0x000C,0x0000);    delay_ms(50);   
        LCD_WriteReg(0x000D,0x080C);    delay_ms(50);   
        LCD_WriteReg(0x000E,0x2B00);    delay_ms(50);   
        LCD_WriteReg(0x001E,0x00B0);    delay_ms(50);   
        LCD_WriteReg(0x0001,0x2B3F);    delay_ms(50);   /* 320*240 0x2B3F */
        LCD_WriteReg(0x0002,0x0600);    delay_ms(50);
        LCD_WriteReg(0x0010,0x0000);    delay_ms(50);
        LCD_WriteReg(0x0011,0x6070);    delay_ms(50);
        LCD_WriteReg(0x0005,0x0000);    delay_ms(50);
        LCD_WriteReg(0x0006,0x0000);    delay_ms(50);
        LCD_WriteReg(0x0016,0xEF1C);    delay_ms(50);
        LCD_WriteReg(0x0017,0x0003);    delay_ms(50);
        LCD_WriteReg(0x0007,0x0133);    delay_ms(50);         
        LCD_WriteReg(0x000B,0x0000);    delay_ms(50);
        LCD_WriteReg(0x000F,0x0000);    delay_ms(50);
        LCD_WriteReg(0x0041,0x0000);    delay_ms(50);
        LCD_WriteReg(0x0042,0x0000);    delay_ms(50);
        LCD_WriteReg(0x0048,0x0000);    delay_ms(50);
        LCD_WriteReg(0x0049,0x013F);    delay_ms(50);
        LCD_WriteReg(0x004A,0x0000);    delay_ms(50);
        LCD_WriteReg(0x004B,0x0000);    delay_ms(50);
        LCD_WriteReg(0x0044,0xEF00);    delay_ms(50);
        LCD_WriteReg(0x0045,0x0000);    delay_ms(50);
        LCD_WriteReg(0x0046,0x013F);    delay_ms(50);
        LCD_WriteReg(0x0030,0x0707);    delay_ms(50);
        LCD_WriteReg(0x0031,0x0204);    delay_ms(50);
        LCD_WriteReg(0x0032,0x0204);    delay_ms(50);
        LCD_WriteReg(0x0033,0x0502);    delay_ms(50);
        LCD_WriteReg(0x0034,0x0507);    delay_ms(50);
        LCD_WriteReg(0x0035,0x0204);    delay_ms(50);
        LCD_WriteReg(0x0036,0x0204);    delay_ms(50);
        LCD_WriteReg(0x0037,0x0502);    delay_ms(50);
        LCD_WriteReg(0x003A,0x0302);    delay_ms(50);
        LCD_WriteReg(0x003B,0x0302);    delay_ms(50);
        LCD_WriteReg(0x0023,0x0000);    delay_ms(50);
        LCD_WriteReg(0x0024,0x0000);    delay_ms(50);
        LCD_WriteReg(0x0025,0x8000);    delay_ms(50);
        LCD_WriteReg(0x004f,0);
        LCD_WriteReg(0x004e,0);
    }
     
    delay_ms(50);   /* delay 50 ms */       
}

/*******************************************************************************
* Function Name  : LCD_Clear
* Description    : 
* Input          : - Color: Screen Color
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void LCD_Clear(alt_u16 Color)
{
    alt_u32 index=0;
    
    if( LCD_Code == HX8347D || LCD_Code == HX8347A )
    {
        LCD_WriteReg(0x02,0x00);                                                  
        LCD_WriteReg(0x03,0x00);  
                        
        LCD_WriteReg(0x04,0x00);                           
        LCD_WriteReg(0x05,0xEF);  
                         
        LCD_WriteReg(0x06,0x00);                           
        LCD_WriteReg(0x07,0x00);    
                       
        LCD_WriteReg(0x08,0x01);                           
        LCD_WriteReg(0x09,0x3F);     
    }
    else
    {   
        LCD_SetCursor(0,0); 
    }   
    Clr_Cs; 
    LCD_WriteIndex(0x0022);
    for( index = 0; index < MAX_X * MAX_Y; index++ )
    {
        LCD_WriteData(Color);
    }
    Set_Cs;
}
void LCD_show_test()
{ alt_u32 index=0,i;
    if( LCD_Code == HX8347D || LCD_Code == HX8347A )
    {
        LCD_WriteReg(0x02,0x00);                                                  
        LCD_WriteReg(0x03,0x00);  
                        
        LCD_WriteReg(0x04,0x00);                           
        LCD_WriteReg(0x05,0xEF);  
                         
        LCD_WriteReg(0x06,0x00);                           
        LCD_WriteReg(0x07,0x00);    
                       
        LCD_WriteReg(0x08,0x01);                           
        LCD_WriteReg(0x09,0x3F);     
    }
    else
    {   
        LCD_SetCursor(0,0); 
    }   
    Clr_Cs; 
    LCD_WriteIndex(0x0022);
  for( i = 0; i< 8; i++ )
    for( index = i*40 * 240; index < (i+1)*40 * 240; index++ )
    {
        LCD_WriteData(colorfol1[i]);
    }
    while(1);
    Set_Cs;         
         
         
         
}        
   
/******************************************************************************
* Function Name  : LCD_BGR2RGB
* Description    : RRRRRGGGGGGBBBBB convert to BBBBBGGGGGGRRRRR
* Input          : RGB color
* Output         : None
* Return         : RGB color
* Attention      :
*******************************************************************************/
alt_u16 LCD_BGR2RGB(alt_u16 color)
{
    alt_u16  r, g, b, rgb;
    
    b = ( color>>0 )  & 0x1f;
    g = ( color>>5 )  & 0x3f;
    r = ( color>>11 ) & 0x1f;
    
    rgb =  (b<<11) + (g<<5) + (r<<0);
    
    return( rgb );
}


/******************************************************************************
* Function Name  : LCD_GetPoint
* Description    : Get color of the point
* Input          : - Xpos: Row Coordinate
*                  - Ypos: Line Coordinate 
* Output         : None
* Return         : Screen Color
* Attention      : None
*******************************************************************************/
alt_u16 LCD_GetPoint(alt_u16 Xpos,alt_u16 Ypos)
{
    alt_u16 dummy;
    
    LCD_SetCursor(Xpos,Ypos);
    Clr_Cs;
    LCD_WriteIndex(0x0022);  
    
    switch( LCD_Code )
    {
        case ST7781:
        case LGDP4531:
        case LGDP4535:
        case SSD1289:
        case SSD1298:
      dummy = LCD_ReadData();
      dummy = LCD_ReadData(); 
      Set_Cs;   
          return  dummy;          
    case HX8347A:
      case HX8347D:
    {
      alt_u8 red,green,blue;
      red = LCD_ReadData()>>3;
      green = LCD_ReadData()>>3; 
      blue = LCD_ReadData()>>2; 
      dummy = ( green << 11 ) | (blue << 5 ) | red;
        }
      Set_Cs;   
      return  dummy;
    default:    /* 0x9320 0x9325 0x9328 0x9331 0x5408 0x1505 0x0505 0x9919 */
      dummy = LCD_ReadData();
      dummy = LCD_ReadData(); 
      Set_Cs;   
      return  LCD_BGR2RGB( dummy );
    }
}

/******************************************************************************
* Function Name  : LCD_SetPoint
* Description    : 
* Input          : - Xpos: Row Coordinate
*                  - Ypos: Line Coordinate 
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/



/******************************************************************************
* Function Name  : LCD_SetPoint
* Description    : 
* Input          : - Xpos: Row Coordinate
*                  - Ypos: Line Coordinate 
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void LCD_SetPoint(alt_u16 Xpos,alt_u16 Ypos,alt_u16 point)
{
    if( Xpos >= MAX_X || Ypos >= MAX_Y )
    {
        return;
    }
    LCD_SetCursor(Xpos,Ypos);
    LCD_WriteReg(0x0022,point);
}


/******************************************************************************
* Function Name  : LCD_DrawLine
* Description    : Bresenham's line algorithm
* Input          : - x0:
*                  - y0:
*                          - x1:
*                      - y1:
*                  - color:
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/     
void LCD_DrawLine( alt_u16 x0, alt_u16 y0, alt_u16 x1, alt_u16 y1 , alt_u16 color )
{
  short dx,dy;
  short temp;

  if( x0 > x1 )
  {
    temp = x1;
    x1 = x0;
    x0 = temp;   
  }
  if( y0 > y1 )
  {
    temp = y1;
    y1 = y0;
    y0 = temp;   
  }

  dx = x1-x0;
  dy = y1-y0;

  if( dx == 0 )
  {
    do
    { 
      LCD_SetPoint(x0, y0, color);
      y0++;
    }
    while( y1 >= y0 ); 
    return; 
  }
  if( dy == 0 )
  {
    do
    {
      LCD_SetPoint(x0, y0, color);
      x0++;
    }
    while( x1 >= x0 ); 
        return;
  }

    /* Bresenham's line algorithm  */
  if( dx > dy )
  {
    temp = 2 * dy - dx;
    while( x0 != x1 )
    {
        LCD_SetPoint(x0,y0,color);
        x0++;
        if( temp > 0 )
        {
          y0++;
          temp += 2 * dy - 2 * dx; 
          }
      else         
      {
              temp += 2 * dy;
            }       
    }
    LCD_SetPoint(x0,y0,color);
  }  
  else
  {
    temp = 2 * dx - dy;
    while( y0 != y1 )
    {
          LCD_SetPoint(x0,y0,color);     
      y0++;                 
      if( temp > 0 )           
      {
        x0++;               
        temp+=2*dy-2*dx; 
      }
      else
            {
        temp += 2 * dy;
            }
    } 
    LCD_SetPoint(x0,y0,color);
    }
} 

/******************************************************************************
* Function Name  : PutChar
* Description    : 
* Input          : - Xpos:
*                  - Ypos:
*                          - ASCI:
*                          - charColor:
*                          - bkColor:
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void PutChar( alt_u16 Xpos, alt_u16 Ypos, alt_u8 ASCI, alt_u16 charColor, alt_u16 bkColor )
{
    alt_u16 i, j;
    alt_u8 buffer[16], tmp_char;
    GetASCIICode(buffer,ASCI);
    for( i=0; i<16; i++ )
    {
        tmp_char = buffer[i];
        for( j=0; j<8; j++ )
        {
            if( (tmp_char >> 7 - j) & 0x01 == 0x01 )
            {
                LCD_SetPoint( Xpos + j, Ypos + i, charColor );
            }
            else
            {
                LCD_SetPoint( Xpos + j, Ypos + i, bkColor );
            }
        }
    }
}

/******************************************************************************
* Function Name  : GUI_Text
* Description    : 
* Input          : - Xpos: 
*                  - Ypos: 
*                          - str:
*                          - charColor:
*                          - bkColor:
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void GUI_Text(alt_u16 Xpos, alt_u16 Ypos, alt_u8 *str,alt_u16 Color, alt_u16 bkColor)
{
    alt_u8 TempChar;
    do
    {
        TempChar = *str++;  
        PutChar( Xpos, Ypos, TempChar, Color, bkColor );    
        if( Xpos < MAX_X - 8 )
        {
            Xpos += 8;
        } 
        else if ( Ypos < MAX_Y - 16 )
        {
            Xpos = 0;
            Ypos += 16;
        }   
        else
        {
            Xpos = 0;
            Ypos = 0;
        }    
    }
    while ( *str != 0 );
}

__inline__ void vid_draw_line(int horiz_start, int vert_start, int horiz_end, int vert_end, int width, int color)
{

  if( vert_start == vert_end )
  {
//    c2h_draw_horiz_line( (unsigned short)horiz_start,
//                         (unsigned short)horiz_end,
//                         (unsigned short)vert_start,
//                         color,
//                         display->buffer_ptrs[display->buffer_being_written]->buffer);

    vid_draw_horiz_line( (unsigned short)horiz_start,
                         (unsigned short)horiz_end,
                         (unsigned short)vert_start,
                         color);
  }
  else
  {
    vid_draw_sloped_line( (unsigned short)horiz_start,
                          (unsigned short)vert_start,
                          (unsigned short)horiz_end,
                          (unsigned short)vert_end,
                          (unsigned short)width,
                          color );
  }
}


void vid_set_pixel(int horiz, int vert, unsigned int color){
	LCD_SetPoint(horiz,vert,color);
}

void vid_draw_horiz_line (short Hstart, short Hend, int V, int color)
{
	int x;
	for(x=Hstart;x<Hend;x++){
		vid_set_pixel(x, V, color);
	}
}

void vid_draw_sloped_line( unsigned short horiz_start,
                           unsigned short vert_start,
                           unsigned short horiz_end,
                           unsigned short vert_end,
                           unsigned short width,
                           int color)
{
  // Find the vertical and horizontal distance between the two points
  int horiz_delta = abs(horiz_end-horiz_start);
  int vert_delta = abs(vert_end-vert_start);

  // Find out what direction we are going
  int horiz_incr, vert_incr;
  if (horiz_start > horiz_end) { horiz_incr=-1; } else { horiz_incr=1; }
  if (vert_start > vert_end) { vert_incr=-1; } else { vert_incr=1; }

  // Find out which axis is always incremented when drawing the line
  // If it's the horizontal axis
  if (horiz_delta >= vert_delta) {
    int dPr   = vert_delta<<1;
    int dPru  = dPr - (horiz_delta<<1);
    int P     = dPr - horiz_delta;

    // Process the line, one horizontal point at at time
    for (; horiz_delta >= 0; horiz_delta--) {
      // plot the pixel
      LCD_SetPoint(horiz_start,vert_start,color);
      // If we're moving both up and right
      if (P > 0) {
        horiz_start+=horiz_incr;
        vert_start+=vert_incr;
        P+=dPru;
      } else {
        horiz_start+=horiz_incr;
        P+=dPr;
      }
    }
  // If it's the vertical axis
  } else {
    int dPr   = horiz_delta<<1;
    int dPru  = dPr - (vert_delta<<1);
    int P     = dPr - vert_delta;

    // Process the line, one vertical point at at time
    for (; vert_delta>=0; vert_delta--) {
      // plot the pixel
      LCD_SetPoint(horiz_start,vert_start,color);
      // If we're moving both up and right
      if (P > 0) {
        horiz_start+=horiz_incr;
        vert_start+=vert_incr;
        P+=dPru;
      } else {
        vert_start+=vert_incr;
        P+=dPr;
      }
    }
  }
}

/******************************************************************
*  Function: vid_draw_box
*
*  Purpose: Draws a box on the screen with the specified corner
*  points.  The fill parameter tells the function whether or not
*  to fill in the box.  1 = fill, 0 = do not fill.
*
******************************************************************/
int vid_draw_box (int horiz_start, int vert_start, int horiz_end, int vert_end, int color,int fill)
{

  // If we want to fill in our box
  if (fill) {
     vid_paint_block (horiz_start, vert_start, horiz_end, vert_end, color);
  // If we're not filling in the box, just draw four lines.
  } else {
    vid_draw_line(horiz_start, vert_start, horiz_start, vert_end-1, 1, color);
    vid_draw_line(horiz_end-1, vert_start, horiz_end-1, vert_end-1, 1, color);
    vid_draw_line(horiz_start, vert_start, horiz_end-1, vert_start, 1, color);
    vid_draw_line(horiz_start, vert_end-1, horiz_end-1, vert_end-1, 1, color);
  }

  return (0);
}

/******************************************************************
*  Function: vid_paint_block
*
*  Purpose: Paints a block of the screen the specified color.
*           Note: works with two pixels at a time to maintain high
*           bandwidth.  Therefore, corner points must be even
*           numbered coordinates.  Use vid_draw_solid_box() for
*           areas with odd-numbered corner points.
*           The color parameter must contain two pixel's worth
*           (32 bits).
*
******************************************************************/
void vid_paint_block (int Hstart,int Vstart, int Hend, int Vend, int color)
{
	int x,y;
	for(y=Vstart;y<Vend;y++){
		for(x=Hstart;x<Hend;x++){
			vid_set_pixel(x, y, color);
		}
	}
}


/******************************************************************
*  Function: vid_print_char
*
*  Purpose: Prints a character to the specified location of the
*           screen using the specified font and color.
*
******************************************************************/

int vid_print_char (int horiz_offset, int vert_offset, int color, char character, char *font)
{

  int i, j;

  char temp_char, char_row;

  // Convert the ASCII value to an array offset
  temp_char = (character - 0x20);

  //Each character is 8 pixels wide and 11 tall.
  for(i = 0; i < 11; i++) {
      char_row = *(font + (temp_char * FONT_10PT_ROW) + i);
    for (j = 0; j < 8; j++) {
      //If the font table says the pixel in this location is on for this character, then set it.
      if (char_row & (((unsigned char)0x80) >> j)) {
        vid_set_pixel((horiz_offset + j), (vert_offset + i), color); // plot the pixel
      }
    }
  }
  return(0);
}


/******************************************************************
*  Function: vid_print_string
*
*  Purpose: Prints a string to the specified location of the screen
*           using the specified font and color.
*           Calls vid_print_char
*
******************************************************************/
int vid_print_string(int horiz_offset, int vert_offset, int color, char *font, char string[])
{
  int i = 0;
  int original_horiz_offset;

  original_horiz_offset = horiz_offset;

  // Print until we hit the '\0' char.
  while (string[i]) {
    //Handle newline char here.
    if (string[i] == '\n') {
      horiz_offset = original_horiz_offset;
      vert_offset += 12;
      i++;
      continue;
    }
    // Lay down that character and increment our offsets.
    vid_print_char (horiz_offset, vert_offset, color, string[i], font);
    i++;
    horiz_offset += 8;
  }
  return (0);
}


/******************************************************************
*  Function: vid_draw_circle
*
*  Purpose: Draws a circle on the screen with the specified center
*  and radius.  Draws symetric circles only.  The fill parameter
*  tells the function whether or not to fill in the box.  1 = fill,
*  0 = do not fill.
*
******************************************************************/
int vid_draw_circle(int Hcenter, int Vcenter, int radius, int color, char fill)
{
  int x = 0;
  int y = radius;
  int p = (5 - radius*4)/4;

  // Start the circle with the top, bottom, left, and right pixels.
  vid_round_corner_points(Hcenter, Vcenter, x, y, 0, 0, color, fill);

  // Now start moving out from those points until the lines meet
  while (x < y) {
    x++;
    if (p < 0) {
      p += 2*x+1;
    } else {
      y--;
      p += 2*(x-y)+1;
    }
    vid_round_corner_points(Hcenter, Vcenter, x, y, 0, 0, color, fill);
  }
  return (0);
}

/******************************************************************
*  Function: vid_round_corner_points
*
*  Purpose: Called by vid_draw_round_corner_box() and
*  vid_draw_circle() to plot the actual points of the round corners.
*  Draws horizontal lines to fill the shape.
*
******************************************************************/

void vid_round_corner_points( int cx, int cy, int x, int y,
                              int straight_width, int straight_height, int color,
                              char fill)
{

    // If we're directly above, below, left and right of center (0 degrees), plot those 4 pixels
    if (x == 0) {
        // bottom
        vid_set_pixel(cx, cy + y + straight_height, color);
        vid_set_pixel(cx + straight_width, cy + y + straight_height, color);
        // top
        vid_set_pixel(cx, cy - y, color);
        vid_set_pixel(cx + straight_width, cy - y, color);

        if(fill) {
          vid_draw_line(cx - y, cy, cx + y + straight_width, cy, 1, color);
          vid_draw_line(cx - y, cy + straight_height, cx + y + straight_width, cy + straight_height, 1, color);
        } else {
          //right
          vid_set_pixel(cx + y + straight_width, cy, color);
          vid_set_pixel(cx + y + straight_width, cy + straight_height, color);
          //left
          vid_set_pixel(cx - y, cy, color);
          vid_set_pixel(cx - y, cy + straight_height, color);
        }

    } else
    // If we've reached the 45 degree points (x=y), plot those 4 pixels
    if (x == y) {
      if(fill) {
        vid_draw_line(cx - x, cy + y + straight_height, cx + x + straight_width, cy + y + straight_height, 1, color); // lower
        vid_draw_line(cx - x, cy - y, cx + x + straight_width, cy - y, 1, color); // upper

      } else {
        vid_set_pixel(cx + x + straight_width, cy + y + straight_height, color); // bottom right
        vid_set_pixel(cx - x, cy + y + straight_height, color); // bottom left
        vid_set_pixel(cx + x + straight_width, cy - y, color); // top right
        vid_set_pixel(cx - x, cy - y, color); // top left
      }
    } else
    // If we're between 0 and 45 degrees plot 8 pixels.
    if (x < y) {
        if(fill) {
          vid_draw_line(cx - x, cy + y + straight_height, cx + x + straight_width, cy + y + straight_height, 1, color);
          vid_draw_line(cx - y, cy + x + straight_height, cx + y + straight_width, cy + x + straight_height, 1, color);
          vid_draw_line(cx - y, cy - x, cx + y + straight_width, cy - x, 1, color);
          vid_draw_line(cx - x, cy - y, cx + x + straight_width, cy - y, 1, color);
        } else {
          vid_set_pixel(cx + x + straight_width, cy + y + straight_height, color);
          vid_set_pixel(cx - x, cy + y + straight_height, color);
          vid_set_pixel(cx + x + straight_width, cy - y, color);
          vid_set_pixel(cx - x, cy - y, color);
          vid_set_pixel(cx + y + straight_width, cy + x + straight_height, color);
          vid_set_pixel(cx - y, cy + x + straight_height, color);
          vid_set_pixel(cx + y + straight_width, cy - x, color);
          vid_set_pixel(cx - y, cy - x, color);
        }
    }
}


void delay_ms(alt_u16 ms){
	int msd=1000*ms;
	while(msd<0){
		usleep(1);
		msd--;
	}
}


/******************************************************************
*  Data: cour10_font
*
*  Purpose: Data array that represents a 10-point courier font.
*
******************************************************************/
char cour10_font_array[95][11] =

 {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
 {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x10, 0x00, 0x00},
 {0x28, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
 {0x14, 0x14, 0x7E, 0x28, 0x28, 0x28, 0xFC, 0x50, 0x50, 0x00, 0x00},
 {0x10, 0x38, 0x44, 0x40, 0x38, 0x04, 0x44, 0x38, 0x10, 0x00, 0x00},
 {0x40, 0xA2, 0x44, 0x08, 0x10, 0x20, 0x44, 0x8A, 0x04, 0x00, 0x00},
 {0x30, 0x40, 0x40, 0x20, 0x60, 0x92, 0x94, 0x88, 0x76, 0x00, 0x00},
 {0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
 {0x08, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x08},
 {0x20, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x08, 0x10, 0x10, 0x20},
 {0x00, 0x00, 0x6C, 0x38, 0xFE, 0x38, 0x6C, 0x00, 0x00, 0x00, 0x00},
 {0x00, 0x10, 0x10, 0x10, 0xFE, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x20, 0x00},
 {0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00},
 {0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00},
 {0x38, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x38, 0x00, 0x00},
 {0x10, 0x70, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x7C, 0x00, 0x00},
 {0x38, 0x44, 0x04, 0x04, 0x08, 0x10, 0x20, 0x40, 0x7C, 0x00, 0x00},
 {0x38, 0x44, 0x04, 0x04, 0x18, 0x04, 0x04, 0x44, 0x38, 0x00, 0x00},
 {0x08, 0x18, 0x18, 0x28, 0x28, 0x48, 0x7C, 0x08, 0x1C, 0x00, 0x00},
 {0x7C, 0x40, 0x40, 0x40, 0x78, 0x04, 0x04, 0x44, 0x38, 0x00, 0x00},
 {0x18, 0x20, 0x40, 0x40, 0x78, 0x44, 0x44, 0x44, 0x38, 0x00, 0x00},
 {0x7C, 0x44, 0x04, 0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0x00, 0x00},
 {0x38, 0x44, 0x44, 0x44, 0x38, 0x44, 0x44, 0x44, 0x38, 0x00, 0x00},
 {0x38, 0x44, 0x44, 0x44, 0x3C, 0x04, 0x04, 0x08, 0x30, 0x00, 0x00},
 {0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00},
 {0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x20, 0x00, 0x00, 0x00},
 {0x00, 0x04, 0x08, 0x10, 0x20, 0x10, 0x08, 0x04, 0x00, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0x7C, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00},
 {0x00, 0x20, 0x10, 0x08, 0x04, 0x08, 0x10, 0x20, 0x00, 0x00, 0x00},
 {0x38, 0x44, 0x04, 0x04, 0x08, 0x10, 0x10, 0x00, 0x10, 0x00, 0x00},
 {0x3C, 0x42, 0x9A, 0xAA, 0xAA, 0xAA, 0x9C, 0x40, 0x38, 0x00, 0x00},
 {0x30, 0x10, 0x10, 0x28, 0x28, 0x44, 0x7C, 0x44, 0xEE, 0x00, 0x00},
 {0xFC, 0x42, 0x42, 0x42, 0x7C, 0x42, 0x42, 0x42, 0xFC, 0x00, 0x00},
 {0x3C, 0x42, 0x80, 0x80, 0x80, 0x80, 0x80, 0x42, 0x3C, 0x00, 0x00},
 {0xF8, 0x44, 0x42, 0x42, 0x42, 0x42, 0x42, 0x44, 0xF8, 0x00, 0x00},
 {0xFE, 0x42, 0x40, 0x48, 0x78, 0x48, 0x40, 0x42, 0xFE, 0x00, 0x00},
 {0xFE, 0x42, 0x40, 0x48, 0x78, 0x48, 0x40, 0x40, 0xF0, 0x00, 0x00},
 {0x3C, 0x42, 0x80, 0x80, 0x80, 0x8E, 0x82, 0x42, 0x3C, 0x00, 0x00},
 {0xEE, 0x44, 0x44, 0x44, 0x7C, 0x44, 0x44, 0x44, 0xEE, 0x00, 0x00},
 {0x7C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x7C, 0x00, 0x00},
 {0x1E, 0x04, 0x04, 0x04, 0x04, 0x04, 0x44, 0x44, 0x38, 0x00, 0x00},
 {0xE6, 0x44, 0x48, 0x48, 0x50, 0x70, 0x48, 0x44, 0xE6, 0x00, 0x00},
 {0xF8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x22, 0xFE, 0x00, 0x00},
 {0xC6, 0x44, 0x6C, 0x6C, 0x54, 0x54, 0x44, 0x44, 0xEE, 0x00, 0x00},
 {0xCE, 0x44, 0x64, 0x64, 0x54, 0x4C, 0x4C, 0x44, 0xE4, 0x00, 0x00},
 {0x38, 0x44, 0x82, 0x82, 0x82, 0x82, 0x82, 0x44, 0x38, 0x00, 0x00},
 {0xFC, 0x42, 0x42, 0x42, 0x7C, 0x40, 0x40, 0x40, 0xF0, 0x00, 0x00},
 {0x38, 0x44, 0x82, 0x82, 0x82, 0x82, 0x82, 0x44, 0x38, 0x36, 0x00},
 {0xFC, 0x42, 0x42, 0x42, 0x7C, 0x48, 0x48, 0x44, 0xE6, 0x00, 0x00},
 {0x7C, 0x82, 0x80, 0x80, 0x7C, 0x02, 0x02, 0x82, 0x7C, 0x00, 0x00},
 {0xFE, 0x92, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x38, 0x00, 0x00},
 {0xEE, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x38, 0x00, 0x00},
 {0xEE, 0x44, 0x44, 0x44, 0x28, 0x28, 0x28, 0x10, 0x10, 0x00, 0x00},
 {0xEE, 0x44, 0x44, 0x44, 0x54, 0x54, 0x54, 0x28, 0x28, 0x00, 0x00},
 {0xEE, 0x44, 0x28, 0x28, 0x10, 0x28, 0x28, 0x44, 0xEE, 0x00, 0x00},
 {0xEE, 0x44, 0x44, 0x28, 0x28, 0x10, 0x10, 0x10, 0x38, 0x00, 0x00},
 {0xFE, 0x84, 0x08, 0x08, 0x10, 0x20, 0x20, 0x42, 0xFE, 0x00, 0x00},
 {0x38, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x38, 0x00, 0x00},
 {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00},
 {0x1C, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x1C, 0x00, 0x00},
 {0x10, 0x28, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00},
 {0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0x78, 0x04, 0x7C, 0x84, 0x84, 0x7A, 0x00, 0x00},
 {0xC0, 0x40, 0x40, 0x7C, 0x42, 0x42, 0x42, 0x42, 0xFC, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0x7C, 0x82, 0x80, 0x80, 0x82, 0x7C, 0x00, 0x00},
 {0x0C, 0x04, 0x04, 0x7C, 0x84, 0x84, 0x84, 0x84, 0x7E, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0x7C, 0x82, 0xFE, 0x80, 0x82, 0x7C, 0x00, 0x00},
 {0x30, 0x40, 0x40, 0xF0, 0x40, 0x40, 0x40, 0x40, 0xF0, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0x7E, 0x84, 0x84, 0x84, 0x7C, 0x04, 0x04, 0x78},
 {0xC0, 0x40, 0x40, 0x58, 0x64, 0x44, 0x44, 0x44, 0xEE, 0x00, 0x00},
 {0x08, 0x00, 0x00, 0x38, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00},
 {0x08, 0x00, 0x00, 0x78, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x70},
 {0xC0, 0x40, 0x40, 0x4C, 0x48, 0x50, 0x70, 0x48, 0xC6, 0x00, 0x00},
 {0x30, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x7C, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0xE8, 0x54, 0x54, 0x54, 0x54, 0xD6, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0xD8, 0x64, 0x44, 0x44, 0x44, 0xEE, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0x7C, 0x82, 0x82, 0x82, 0x82, 0x7C, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0xFC, 0x42, 0x42, 0x42, 0x42, 0x7C, 0x40, 0xE0},
 {0x00, 0x00, 0x00, 0x7E, 0x84, 0x84, 0x84, 0x7C, 0x04, 0x0E, 0x00},
 {0x00, 0x00, 0x00, 0xEC, 0x32, 0x20, 0x20, 0x20, 0xF8, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0x7C, 0x82, 0x70, 0x0C, 0x82, 0x7C, 0x00, 0x00},
 {0x00, 0x20, 0x20, 0x78, 0x20, 0x20, 0x20, 0x24, 0x18, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0xCC, 0x44, 0x44, 0x44, 0x4C, 0x36, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0xEE, 0x44, 0x44, 0x28, 0x28, 0x10, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0xEE, 0x44, 0x54, 0x54, 0x28, 0x28, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0xEE, 0x44, 0x38, 0x38, 0x44, 0xEE, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0xEE, 0x44, 0x44, 0x28, 0x28, 0x10, 0x10, 0x60},
 {0x00, 0x00, 0x00, 0xFC, 0x88, 0x10, 0x20, 0x44, 0xFC, 0x00, 0x00},
 {0x0C, 0x10, 0x10, 0x10, 0x10, 0x60, 0x10, 0x10, 0x10, 0x10, 0x0C},
 {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10},
 {0x60, 0x10, 0x10, 0x10, 0x10, 0x0C, 0x10, 0x10, 0x10, 0x10, 0x60},
 {0x00, 0x00, 0x62, 0x92, 0x8C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }};

//Pointer to our font table
char* cour10_font = &cour10_font_array[0][0];




/******************************************************************
*  Function: vid_print_string_alpha
*
*  Purpose: Prints a string to the specified location of the screen
*           using the specified font and color.
*           Calls vid_print_char_alpha
*
*           The color formats are as follows:
*           16 bit - R(5):G(6):B(5)  (packed)
*           24 bit - R(8):G(8):B(8)  (packed)
*           32 bit - 0 : R(8):G(8):B(8) (unpacked)
******************************************************************/

int vid_print_string_alpha(int horiz_offset, int vert_offset, int color, int background_color, struct abc_font_struct font[], char string[])
{
  int i = 0;
  int tab;
  int original_horiz_offset;

  original_horiz_offset = horiz_offset;

  // Print until we hit the '\0' char.
  while (string[i]) {
    //Handle newline char here.
    if (string[i] == '\n') {
      horiz_offset = original_horiz_offset;
      vert_offset += font['|' - 33].bounds_height;  // we'll use "|" to add the line to line spacing
      i++;
      continue;
    }
    // Lay down that character and increment our offsets.
    if(string[i] == 32)  // this is a space in ASCII
    {
      if(background_color != CLEAR_BACKGROUND)  // need to fill in this spot (setting foreground to background color so that it looks like a drawn in box)
      {
        vid_print_char_alpha (horiz_offset, vert_offset, background_color, '-', background_color, font);
      }
      horiz_offset += font[45 - 33].bounds_width;  // using the width of the '-' character for the space width since it's not present in the font
    }
    else if(string[i] == '\t')  // this is a tab
    {
      for( tab = 0; tab < TAB_SPACING; tab++ )
      {
        if(background_color != CLEAR_BACKGROUND)  // need to fill in this spot (setting foreground to background color so that it looks like a drawn in box)
        {
          vid_print_char_alpha (horiz_offset, vert_offset, background_color, '-', background_color, font);
        }
        horiz_offset += font[45 - 33].bounds_width;  // using the width of the '-' character for the space width since it's not present in the font
      }
    }
    else
    {
      vid_print_char_alpha (horiz_offset, vert_offset, color, string[i], background_color, font);
      horiz_offset += font[string[i] - 33].bounds_width;
    }
    i++;
  }
  return (0);
}





/******************************************************************
*  Function: seperate_colour_channels
*
*  Author:  JCJB
*
*  Purpose: Takes a single colour pointer and break the value into
*           seperate channels.  It supports 16/24(packed/unpacked)
*           formats as inputs.  The results are passed back by
*           the function working on pointers.
*
******************************************************************/

__inline__ int seperate_color_channels(int color_depth, unsigned char * color, unsigned char * red, unsigned char * green, unsigned char * blue)
{
  int return_value;  // error checking in case anyone is listening
  unsigned short temp_color = 0;

  if (color_depth == 16)  // R(5):G(6):B(5)
  {
    temp_color = *color++;        // get the first half of the 16 bit color
    temp_color += (*color << 8);  // get the second half of the 16 bit color
    *blue = temp_color & 0x1F;
    *green = (temp_color >> 5) & 0x3F;
    *red = (temp_color >> 11) & 0x1F;
    return_value = 1;
  }
  else if ((color_depth == 24) || (color_depth == 32))  // R(8):G(8):B(8) packed/unpacked
  {
    *blue = *color++;
    *green = *color++;
    *red = *color;
    return_value = 1;
  }
  else  // not a valid color depth for this function
  {
    *red = 0;
    *green = 0;
    *blue = 0;
    return_value = 0;
  }
  return return_value;
}

/******************************************************************
*  Function: merge_color_channels
*
*  Author:  JCJB
*
*  Purpose: Takes the seperate RGB channels and merges them into
*           a single 16/24/32 bit location.  The caller must
*           use an unsigned char * pointer to the destination
*           color allowing the same function to be used for
*           different color formats and packing.
*
******************************************************************/

__inline__ int merge_color_channels(int color_depth, unsigned char red, unsigned char green, unsigned char blue, unsigned char * color)
{
  int return_value;  // error checking in case anyone is listening
  unsigned short temp_color;

  if (color_depth == 16)  // R(5):G(6):B(5)
  {
    temp_color = (blue & 0x1F) | ((green & 0x3F) << 5) | ((red & 0x1F) << 11);  // 16 bit color format
    *color++ = temp_color & 0xFF;
    *color = (temp_color >> 8) & 0xFF;
    return_value = 1;
  }
  else if ((color_depth == 24) || (color_depth == 32))  // R(8):G(8):B(8) packed/unpacked
  {
    *color++ = blue;
    *color++ = green;
    *color = red;
    return_value = 1;
  }
  else  // not a valid color depth for this function
  {
    *color++ = 0;
    *color++ = 0;
    *color = 0;
    return_value = 0;
  }
  return return_value;
}





/******************************************************************
*  Function: alpha_blending
*
*  Purpose: Takes in the alpha value (0-255) and uses that to mix
*           the font color with the background color.
*
******************************************************************/

__inline__ int alpha_blending (int horiz_offset, int vert_offset, int background_color, unsigned char alpha, unsigned char *red, unsigned char *green, unsigned char *blue)
{
  int return_value;
  unsigned char background_red, background_green, background_blue;
  unsigned int blended_red, blended_green, blended_blue;  // short since there may be overflow to be clipped

  // set red, green, and blue of the background color
  if(background_color == CLEAR_BACKGROUND)
  {
	alt_u16 color= LCD_GetPoint(horiz_offset ,vert_offset);
	background_red=(color>>11) & 0x1F;
	background_green=(color>>5) &0x3F;
	background_blue=(color) &0x1F;
  }
  else
  {
    seperate_color_channels(16, (unsigned char *)&background_color, &background_red, &background_green, &background_blue);
  }

  // these blended colors may need to be clipped to the maximum amounts the color depth supports
  blended_red = (((*red) * alpha) + (background_red * (255 - alpha)))/255;
  blended_green = (((*green) * alpha) + (background_green * (255 - alpha)))/255;
  blended_blue = (((*blue) * alpha) + (background_blue * (255 - alpha)))/255;



    *red = (blended_red > 0x1F)? 0x1F: blended_red;
    *green = (blended_green > 0x3F)? 0x3F: blended_green;
    *blue = (blended_blue > 0x1F)? 0x1F: blended_blue;
    return_value = 1;


  return return_value;
}



/******************************************************************
*  Function: vid_print_char_alpha
*
*  Purpose: Prints a character to the specified location of the
*           screen using the specified font and color.
*
******************************************************************/

int vid_print_char_alpha (int horiz_offset, int vert_offset, int color, char character, int background_color, struct abc_font_struct font[])
{

  int i, j;
  unsigned char * alpha;
  unsigned char original_red, original_blue, original_green;
  unsigned char red, green, blue;
  int new_color;

  // Assign the pointer of the font bitmap
  alpha = font[character-33].char_alpha_map;

  // set red, green, and blue of the font color
  seperate_color_channels(16, (char *)&color, &original_red, &original_green, &original_blue);

  for(i = 0; i < font[character-33].bounds_height; i++) {
    for (j = 0; j < font[character-33].bounds_width; j++) {
      red = original_red;
      green = original_green;
      blue = original_blue;

      // send in the font alpha channel and the colour channels for the blending to occur
      alpha_blending ((horiz_offset + j), (vert_offset + i), background_color, *alpha, &red, &green, &blue);

      // take the blended pixel and merge the color channels back into a single pixel value
      merge_color_channels(16, red, green, blue, (char *)&new_color);

      // write the new pixel value out to memory overwriting the current background
      vid_set_pixel((horiz_offset + j), (vert_offset + i), new_color);

      alpha++;
    }
  }

  return(0);
}

/******************************************************************
*  Function: vid_string_pixel_length_alpha
*
*  Purpose: Gets the length in pixels of a string in the specified
*           font.  Useful for centering text, and determining the
*           appropriate size of a text box or button.
*
******************************************************************/
int vid_string_pixel_length_alpha( struct abc_font_struct font[], char string[] )
{
  int i = 0;
  int length = 0;

  // Count the length of the string
  for( i = 0; string[i] != '\0'; i++ )
  {
    if( string[i] == ' ' )
    {
      // Here we just add the length of the '-' character
      length += font[45 - 33].bounds_width;
    }
    else
    {
      length += font[string[i] - 33].bounds_width;
    }
  }
  return( length );
}



/*********************************************************************************************************
      END FILE
*********************************************************************************************************/













