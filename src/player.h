#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_STATE_STOP 0
#define PLAYER_STATE_PLAYING 1
#define PLAYER_STATE_PAUSE 2


void player_state_set(int state);
void player_file_load(char *file);
void init_player();
void player_position_set(double position);
double player_position_get();



#endif 
