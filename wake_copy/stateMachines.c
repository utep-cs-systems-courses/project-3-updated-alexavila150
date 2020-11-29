#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"


void state_init()
{
  p1col = 30;
  p1row = 83;
  p2col = 90;
  p2row = 83;
  maxHeight = 70;
  minHeight = 83;
  leftLimit = 80;
  rightLimit = 100;
  note_index = 0;
  song_state = 0;
  s0IsPressed = 1;
  s1IsPressed = 1;
  s2IsPressed = 1;
  s3IsPressed = 1;
  buttonState = 4;
  buttonChanged = 0;
  led_state = 0;
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

void move_advance()
{
  static char state = 0;
  switch(state){
  case 0:
    delete_player2(COLOR_LIGHT_BLUE);
    p2col--;
    if(p2col <= leftLimit){
      state = 1;
    }
    break;
  case 1:
    delete_player2(COLOR_LIGHT_BLUE);
    p2col++;
    if(p2col >= rightLimit){
      state = 0;
    }
    break;
  }
}

void delete_player1(u_int bgColor){
  drawCharacter(p1col, p1row, bgColor);
}

void delete_player2(u_int bgColor){
  drawCharacter2(p2col, p2row, bgColor);
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

void rombusStateAdvance(){
  static char state = 0;
  switch(state){
  case 0:
    drawRombus(10, COLOR_BLUE);
    break;
  case 1:
    drawRombus(20, COLOR_BLUE);
    break;
  case 2:
    drawRombus(30, COLOR_BLUE);
    break;
  case 3:
    drawRombus(40, COLOR_BLUE);
    break;
  case 4:
    drawRombus(10, COLOR_RED);
    break;
  case 5:
    drawRombus(20, COLOR_RED);
    break;
  case 6:
    drawRombus(30, COLOR_RED);
    break;
  case 7:
    drawRombus(40, COLOR_RED);
    break;
  }

  state = (state + 1) % 8;
}

void init_smash(){
  clearScreen(COLOR_LIGHT_BLUE);;
  drawField(60, 90);
}

void playSmashBros(int secCount){
  jump_advance();
  move_advance();
  drawString8x12(10,20, "Smash Bros!", COLOR_RED, COLOR_LIGHT_BLUE);
  drawCharacter(p1col, p1row, COLOR_RED);
  drawCharacter2(p2col, p2row, COLOR_BLUE);
}

void resetStates(){
  turn_green_off();
  buzzer_set_period(0);
  clearScreen(COLOR_WHITE);
}
