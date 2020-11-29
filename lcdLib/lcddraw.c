/** \file lcddraw.c
 *  \brief Adapted from RobG's EduKit
 */
#include "lcdutils.h"
#include "lcddraw.h"


/** Draw single pixel at x,row 
 *
 *  \param col Column to draw to
 *  \param row Row to draw to
 *  \param colorBGR Color of pixel in BGR
 */
void drawPixel(u_char col, u_char row, u_int colorBGR) 
{
  lcd_setArea(col, row, col, row);
  lcd_writeColor(colorBGR);
}

/** Fill rectangle
 *
 *  \param colMin Column start
 *  \param rowMin Row start
 *  \param width Width of rectangle
 *  \param height height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void fillRectangle(u_char colMin, u_char rowMin, u_char width, u_char height, 
		   u_int colorBGR)
{
  u_char colLimit = colMin + width, rowLimit = rowMin + height;
  lcd_setArea(colMin, rowMin, colLimit - 1, rowLimit - 1);
  u_int total = width * height;
  u_int c = 0;
  while ((c++) < total) {
    lcd_writeColor(colorBGR);
  }
}

/** Clear screen (fill with color)
 *  
 *  \param colorBGR The color to fill screen
 */
void clearScreen(u_int colorBGR) 
{
  u_char w = screenWidth;
  u_char h = screenHeight;
  fillRectangle(0, 0, screenWidth, screenHeight, colorBGR);
}

/** 5x7 font - this function draws background pixels
 *  Adapted from RobG's EduKit
 */
void drawChar5x7(u_char rcol, u_char rrow, char c, 
     u_int fgColorBGR, u_int bgColorBGR) 
{
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0x01;
  u_char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol + 4, rrow + 7); /* relative to requested col/row */
  while (row < 8) {
    while (col < 5) {
      u_int colorBGR = (font_5x7[oc][col] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
    }
    col = 0;
    bit <<= 1;
    row++;
  }
}

void drawChar8x12(u_char rcol, u_char rrow, char c, 
     u_int fgColorBGR, u_int bgColorBGR) 
{
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0x80;
  u_char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol + 8, rrow + 12); /* relative to requested col/row */
  while (row < 13) {
    while (col < 9) {
      u_int colorBGR = (font_8x12[oc][row] & bit) ? fgColorBGR : bgColorBGR;
      u_int color = (col % 2)? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      bit >>= 1;
      col++;
    }
    col = 0;
    bit = 0x80;
    row++;
  }
}

/** Draw string at col,row
 *  Type:
 *  FONT_SM - small (5x8,) FONT_MD - medium (8x12,) FONT_LG - large (11x16)
 *  FONT_SM_BKG, FONT_MD_BKG, FONT_LG_BKG - as above, but with background color
 *  Adapted from RobG's EduKit
 *
 *  \param col Column to start drawing string
 *  \param row Row to start drawing string
 *  \param string The string
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */
void drawString5x7(u_char col, u_char row, char *string,
		u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while (*string) {
    drawChar5x7(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 6;
  }
}

void drawString8x12(u_char col, u_char row, char *string,
		u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while (*string) {
    drawChar8x12(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 10;
  }
}


/** Draw rectangle outline
 *  
 *  \param colMin Column start
 *  \param rowMin Row start 
 *  \param width Width of rectangle
 *  \param height Height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void drawRectOutline(u_char colMin, u_char rowMin, u_char width, u_char height,
		     u_int colorBGR)
{
  /**< top & bot */
  fillRectangle(colMin, rowMin, width, 1, colorBGR);
  fillRectangle(colMin, rowMin + height, width, 1, colorBGR);

  /**< left & right */
  fillRectangle(colMin, rowMin, 1, height, colorBGR);
  fillRectangle(colMin + width, rowMin, 1, height, colorBGR);
}

/*
  This method will draw a field which is suppose to be where the player is going to stand
 */
void drawField(u_char col, u_char row){
  for(int i = 0; i < 50; i++){
    drawPixel(col, i + row, BLACK);
    for(int j = 50 - i; j >= 0; j--){
      drawPixel(col + j, row + i, COLOR_SPRING_GREEN);
      drawPixel(col - j, row + i, COLOR_SPRING_GREEN);
    }
  }
}

void drawCharacter(u_char col, u_char row, u_int color){
  drawPixel(col - 1, row - 6, color);
  drawPixel(col    , row - 6, color);
  drawPixel(col + 1, row - 6, color);

  drawPixel(col - 1, row - 5, color);
  drawPixel(col    , row - 5, color);
  drawPixel(col + 1, row - 5, color);

  drawPixel(col - 1, row - 4, color);
  drawPixel(col    , row - 4, color);
  drawPixel(col + 1, row - 4, color);

  drawPixel(col    , row - 3, color);

  drawPixel(col - 1, row - 2, color);
  drawPixel(col    , row - 2, color);
  drawPixel(col + 4, row - 2, color);
  
  drawPixel(col - 2, row - 1, color);
  drawPixel(col    , row - 1, color);
  drawPixel(col + 1, row - 1, color);
  drawPixel(col + 3, row - 1, color);

  drawPixel(col - 3, row    , color);
  drawPixel(col    , row    , color);
  drawPixel(col + 2, row    , color);

  drawPixel(col - 2, row + 1, color);
  drawPixel(col    , row + 1, color);

  drawPixel(col    , row + 2, color);

  drawPixel(col - 1, row + 3, color);
  drawPixel(col + 1, row + 3, color);

  drawPixel(col - 2, row + 4, color);
  drawPixel(col + 2, row + 4, color);

  drawPixel(col - 3, row + 5, color);
  drawPixel(col + 3, row + 5, color);

  drawPixel(col - 4, row + 6, color);
  drawPixel(col + 4, row + 6, color);
}

void drawCharacter2(u_char col, u_char row, u_int color){
  drawPixel(col - 1, row - 6, color);
  drawPixel(col    , row - 6, color);
  drawPixel(col + 1, row - 6, color);

  drawPixel(col - 1, row - 5, color);
  drawPixel(col    , row - 5, color);
  drawPixel(col + 1, row - 5, color);

  drawPixel(col - 1, row - 4, color);
  drawPixel(col    , row - 4, color);
  drawPixel(col + 1, row - 4, color);

  drawPixel(col    , row - 3, color);

  drawPixel(col + 1, row - 2, color);
  drawPixel(col    , row - 2, color);
  drawPixel(col - 4, row - 2, color);
  
  drawPixel(col + 2, row - 1, color);
  drawPixel(col    , row - 1, color);
  drawPixel(col - 1, row - 1, color);
  drawPixel(col - 3, row - 1, color);

  drawPixel(col + 3, row    , color);
  drawPixel(col    , row    , color);
  drawPixel(col - 2, row    , color);

  drawPixel(col + 2, row + 1, color);
  drawPixel(col    , row + 1, color);

  drawPixel(col    , row + 2, color);

  drawPixel(col - 1, row + 3, color);
  drawPixel(col + 1, row + 3, color);

  drawPixel(col - 2, row + 4, color);
  drawPixel(col + 2, row + 4, color);

  drawPixel(col - 3, row + 5, color);
  drawPixel(col + 3, row + 5, color);

  drawPixel(col - 4, row + 6, color);
  drawPixel(col + 4, row + 6, color);
}
