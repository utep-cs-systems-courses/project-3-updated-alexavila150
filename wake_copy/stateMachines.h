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
int rightLimit;
int leftLimit;

void state_init();
void jump_advance();
void move_advance();
void delete_player1();
void delete_player2();
void songStateAdvance();
void ledStateAdvance();
void resetStates();

#endif
