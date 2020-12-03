#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"

void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
}

//turns red on with unique sound
void turn_red_on()
{
  P1OUT |= LED_RED;
}

//turns led and sound off
void turn_red_off()
{
  P1OUT &= ~LED_RED;
}

//turns green and unique sound on
void turn_green_on()
{
  P1OUT |= LED_GREEN;
}

//turns led and sound off
void turn_green_off()
{
  P1OUT &= ~LED_GREEN;
}

//call function multiple times to produce a dim red light
void turn_green_dim()
{
  static char state = 0;
  switch(state){
  case 0:
    P1OUT &= ~LED_GREEN;
    break;
  case 3:
    P1OUT |= LED_GREEN;
    break;
  }

  state = (state + 1) % 4;
}

//call function multiple times to produce a semi dim light
void turn_green_middle()
{
  static char state = 0;
  switch(state){
  case 0:
    P1OUT |= LED_GREEN;
    break;
  case 2:
    P1OUT &= ~LED_GREEN;
    break;
  }

  state = (state + 1) % 4;
}

//call function multiple times to produce a bright light
int turn_green_bright(int count)
{
  static char state = 0;
  switch(state){
  case 0:
    P1OUT |= LED_GREEN;
    break;
  case 3:
    P1OUT &= ~LED_GREEN;
    break;
  }

  state = (state + 1) % 4;
  return count + 1;
}
