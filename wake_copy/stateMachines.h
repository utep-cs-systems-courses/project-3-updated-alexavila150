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
int note_index;
int song_state;
char s0IsPressed;
char s1IsPressed;
char s2IsPressed;
char s3IsPressed;
char buttonState;
char buttonChanged;

void state_init();
void jump_advance();
void move_advance();
void delete_player1();
void delete_player2();
void songStateAdvance();
int ledStateAdvance(int count);
void resetStates();
void rombusStateAdvance();
void init_smash();
void playSmashBros();

#endif
