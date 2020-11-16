/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_ROYAL_BLUE);

  //drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);

  //drawChar8x12(5,  00, 'a', COLOR_BLACK, COLOR_BLUE);
  //drawChar8x12(5,  20, 'b', COLOR_BLACK, COLOR_BLUE);
  //drawChar8x12(5,  40, 'c', COLOR_BLACK, COLOR_BLUE);
  //drawChar8x12(5,  60, 'A', COLOR_BLACK, COLOR_BLUE);
  //drawChar8x12(5,  80, '!', COLOR_BLACK, COLOR_BLUE);
  //drawChar8x12(5, 100, '-', COLOR_BLACK, COLOR_BLUE);
  //drawChar5x7(5, 120, '!', COLOR_BLACK, COLOR_BLUE);
  //fillRectangle(30,30, 60, 60, COLOR_ORANGE);
  drawField(60, 100);
}
