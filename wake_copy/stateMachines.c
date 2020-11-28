#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"
#include "led.h"

void state_init()
{
  p1col = 30;
  p1row = 83;
  p2col = 90;
  p2row = 83;
  maxHeight = 70;
  minHeight = 83;
}

void jump_advance()
{
  static char state = 0;
  switch(state){
  case 0:
    delete_player1(COLOR_BLUE);
    p1row--;
    if(p1row <= maxHeight){
      state = 1;
    }
    break;
  case 1:
    delete_player1(COLOR_BLUE);
    p1row++;
    if(p1row >= minHeight){
      state = 0;
    }
    break;
  }
}

void delete_player1(u_int bgColor){
  drawCharacter(p1col, p1row, bgColor);
}

