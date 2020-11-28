#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"


void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  random_num++;
  //run the sequence of leds corresponding to the current turn
  if(sequence_running){

    if(++blink_count == 1){
      // if it is the last turn then play the winner song
      if(turn == 6){
	play_song();
	return;
      }

      //play the corresponding led in sequence every second
      if(led_index < turn){
	switch(sequence[led_index++]){
	case 1:
	  turn_red_on();
	  break;
	case 2:
	  turn_green_on();
	  break;
	}
      }else{
	end_sequence();
      }
    }

    //turn leds off after half a second
    if(blink_count == 125){
      turn_red_off();
      turn_green_off();
    }

    //restart blink count every second
    if(blink_count == 250){
      blink_count = 0;
    }
  }

  if(song_playing){
    //change note every 200 miliseconds
    if(++blink_count == duration[note_index] * 50 && note_index < 42){
      note_index++;
      buzzer_set_period(2000000 / notes[note_index]);
      blink_count = 0;
    }

    //make pause when node is ending
    if(blink_count == duration[note_index] * 50 - 5){
      buzzer_set_period(0);
    }

    //first 15 seconds led is dim
    if(note_index < 15){
      turn_red_dim();
      return;
    }

    //next 15 seconds led is simi dim
    if(note_index < 30){
      turn_red_middle();
      return;
    }

    //led is bright at the end of the song
    if(note_index < 42){
      turn_red_bright();
      return;
    }

    //end song
    if(note_index == 42){
      buzzer_set_period(0);
      turn_red_off();
    }
  }
}
