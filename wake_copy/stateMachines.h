#ifndef stateMachines_included
#define stateMachines_included

extern const int notes[42];       //list of notes to be play
extern const char duration[42];   //duration of every corresponding note

int p1col;
int p1row;
int p2col;
int p2row;
int maxHeight;
int minHeight;

void state_init();
void jump_advance();
void delete_player1();
void songStateAdvance();
void ledStateAdvance();

#endif
