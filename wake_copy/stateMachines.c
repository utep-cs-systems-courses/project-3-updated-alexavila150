#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

int note_index = 0;
int song_state = 0;

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
    delete_player1(COLOR_LIGHT_BLUE);
    p1row--;
    if(p1row <= maxHeight){
      state = 1;
    }
    break;
  case 1:
    delete_player1(COLOR_LIGHT_BLUE);
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

void songStateAdvance(){
  static int state = 0;
  
  //change note every 200 miliseconds
  if(++state == duration[note_index] * 50 && note_index < 42){
    note_index++;
    buzzer_set_period(2000000 / notes[note_index]);
    state = 0;
  }
  
  //make pause when node is ending
  if(state == duration[note_index] * 50 - 5){
    buzzer_set_period(0);
  }
  
  //repeat song
  if(note_index == 42){
    buzzer_set_period(0);
    note_index = 0;
  }
}

void ledStateAdvance(int count){
  static char state = 0;
  switch(state){
  case 0:
    turn_green_dim();
    break;
  case 1:
    turn_green_middle();
    break;
  case 2:
    turn_green_bright();
    break;
  }

  if (count == 250){
    state = (state + 1) % 3;
  }
}
