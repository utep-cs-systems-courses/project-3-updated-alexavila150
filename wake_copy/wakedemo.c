#include <msp430.h>
#include <libTimer.h>
#include <p2switches.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

void init_smash();
void playSmashBros(int secCount);

short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;

char s0IsPressed = 0;
char s1IsPressed = 0;
char s2IsPressed = 0;
char s3IsPressed = 0;
char buttonState = 4;

void wdt_c_handler()
{
  static int secCount = 0;
  secCount ++;

  u_int switches = p2sw_read();
    
  if((switches & BIT8)){
    //clearScreen(COLOR_YELLOW);
    s0IsPressed = (s0IsPressed) ? 0 : 1;
    buttonState = 0;
    if(s0IsPressed){
      init_smash();
      buttonState = 0;
    }
  }

  if((switches & 512)){
    s1IsPressed = (s1IsPressed) ? 0 : 1;
    if(s1IsPressed){
      buttonState = 1;
    }
  }

  if((switches & 1024)){
    s2IsPressed = (s2IsPressed) ? 0 : 1;
    if(s2IsPressed){
      buttonState = 2;
    }
  }
  
  if((switches & 2048)){
    s3IsPressed = (s3IsPressed) ? 0 : 1;
    if(s3IsPressed){
      buttonState = 3;
    }
  }

  switch(buttonState){
  case 0:
    playSmashBros(secCount);
    break;
  case 1:
    if(secCount % 25 == 0){
      clearScreen(COLOR_PINK);
      buzzer_set_period(0);
    }
    break;
  case 2:
    if(secCount % 25 == 0){
      clearScreen(COLOR_BLACK);
      buzzer_set_period(0);
    }
    break;
  case 3:
    songStateAdvance();
    break;
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
  p2sw_init(15);
  buzzer_init();
  
  clearScreen(COLOR_BLUE);
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */

  clearScreen(COLOR_BLUE);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
    }
    P1OUT &= ~LED_RED;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_RED;		/* green on */
  }
}

void init_smash(){
  clearScreen(COLOR_BLUE);
  drawCharacter2(p2col, p2row, COLOR_YELLOW);
  drawField(60, 90);
}

void playSmashBros(int secCount){
  if (secCount % 25 == 0){
    jump_advance();
    drawString5x7(20,20, "Smash Ultimate!", fontFgColor, COLOR_BLUE);
    drawCharacter(p1col, p1row, COLOR_RED);
    drawCharacter2(p2col, p2row, COLOR_YELLOW);
  }
} 
    



