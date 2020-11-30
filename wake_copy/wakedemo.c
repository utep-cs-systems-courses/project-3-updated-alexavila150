#include <msp430.h>
#include <libTimer.h>
#include <p2switches.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;

void wdt_c_handler()
{
  static int secCount = 0;
  secCount ++;

  u_int switches = p2sw_read();

  //Checks if s1 has change
  if((switches & BIT8)){
    //button is pressed every two senses
    s0IsPressed = (s0IsPressed) ? 0 : 1;

    //checks if the button press was the same as the last one
    if(buttonState != 0){
      buttonChanged = 1;
    }
    
    if(s0IsPressed){
      buttonState = 0;
    }
  }

  if((switches & 512)){
    s1IsPressed = (s1IsPressed) ? 0 : 1;

    if(buttonState != 1){
      buttonChanged = 1;
    }

    if(s1IsPressed){
      buttonState = 1;
    }
  }

  if((switches & 1024)){
    s2IsPressed = (s2IsPressed) ? 0 : 1;

    if(buttonState != 2){
      buttonChanged = 1;
    }

    if(s2IsPressed){
      buttonState = 2;
    }
  }

  if((switches & 2048)){
    s3IsPressed = (s3IsPressed) ? 0 : 1;

    if(buttonState != 3){
      buttonChanged = 1;
    }

    if(s3IsPressed){
      buttonState = 3;
    }
  }

  switch(buttonState){
  case 0:
    if(secCount % 25 == 0) redrawScreen = 1; //draws every .1 seconds
    break;
  case 1:
    redrawScreen = 1; //led is updated constantly
    break;
  case 2:
    redrawScreen = 1; //song is updated constantly
    break;
  case 3:
    if(secCount % 250 == 0) redrawScreen = 1; // rhombus is updated every second
    break;
  }
  
  if(secCount % 250 == 0){
    secCount == 0;
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
  static int led_count = 0;

  clearScreen(COLOR_WHITE);
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */

  while (1) {			/* forever */
    if (redrawScreen) {
      switch(buttonState){
      case 0:
	if(buttonChanged){ //reset states when button changed state
	  resetStates();
	  init_smash();
	}
	playSmashBros(); // draws next step in the animation
	break;
      case 1:
	if(buttonChanged){
	  resetStates();
	}
	led_count = ledStateAdvance(led_count); // advance the state and returns incremented count
	break;
      case 2:
	if(buttonChanged){
	  resetStates();
	}
	songStateAdvance(); // plays song note by note in an infinite cycle
	break;
      case 3:
	if(buttonChanged){
	  resetStates();
	  drawString8x12(25,20, "Rhombus :D", COLOR_ORANGE, COLOR_WHITE);
	}
	rombusStateAdvance(); // draws a new rhombus every time
	break;
      }
      buttonChanged = 0;
      redrawScreen = 0;
    }
    P1OUT &= ~LED_RED;	        /* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_RED;		/* green on */
  }
}
