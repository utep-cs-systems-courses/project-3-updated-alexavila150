#ifndef led_included
#define led_included

#define LED_RED BIT6               // P1.0
#define LED_GREEN BIT0             // P1.6
#define LEDS (BIT0 | BIT6)

void led_init();		/* initialize LEDs */
void led_update();		/* update leds */
void turn_red_on();
void turn_red_off();
void turn_green_on();
void turn_green_off();
void turn_green_dim();
void turn_green_middle();
int turn_green_bright(int count);

#endif
