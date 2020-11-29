#include <msp430.h>
#include "stateMachines.h"
#include "led.h"

int ledStateAdvance(int count){
  static char state = 0; //determines if led is dim medium or bright

  switch(state){
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

  if (count > 250){
    state = (state + 1) % 3;
    count = 0;
  }

  return count;
}
