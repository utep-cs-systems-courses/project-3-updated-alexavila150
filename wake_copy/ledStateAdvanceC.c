#include <msp430.h>
#include "stateMachines.h"
#include "led.h"

int ledStateAdvance(int count){
  //static char state = 0; //determines if led is dim medium or bright

  switch(led_state){
  case 0:
    turn_green_dim();
    count++;
    break;
  case 1:
    turn_green_middle();
    count++;
    break;
  case 2:
    count = turn_green_bright(count);
    break;
  }

  if (count < 250) goto endif2;
  led_state = led_state + 1;
  if(led_state != 3) goto endif;
  led_state = 0;
endif:
  count = 0;
endif2:

  return count;
}
