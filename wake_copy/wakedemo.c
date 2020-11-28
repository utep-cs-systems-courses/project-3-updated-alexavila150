#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"
#include "led.h"



short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;

  if (secCount % 25 == 0){
    jump_advance();
    drawCharacter(p1col, p1row, COLOR_RED);
    drawCharacter2(p2col, p2row, COLOR_YELLOW);
  }
  
  if (secCount == 250) {		/* once/sec */
    secCount = 0;
    fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
    redrawScreen = 1;
  }
}
  

void main()
{
  P1DIR |= LED_RED;		/**< Green led on when CPU on */		
  P1OUT |= LED_RED;
  configureClocks();

  lcd_init();
  state_init();
  led_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */

  clearScreen(COLOR_BLUE);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      drawString5x7(20,20, "Smash Ultimate!", fontFgColor, COLOR_BLUE);
      drawField(60, 90);
      drawCharacter(p1col, p1row, COLOR_RED);
      drawCharacter2(p2col, p2row, COLOR_YELLOW);
    }
    P1OUT &= ~LED_RED;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_RED;		/* green on */
  }
}

    
    



