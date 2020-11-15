/*
 * tictactoe.h
 *
 * Created: 27.09.2020 14:54:28
 *  Author: aashilbr
 */ 


#ifndef TICTACTOE_H_
#define TICTACTOE_H_

#include "menu.h"

typedef enum {
	X_PLAY,
	O_PLAY,
	X_WIN,
	O_WIN,
	NO_WIN,
	TIE
} Game_state;
	
typedef enum {X,O,NONE} Grid_state;

typedef struct Turn_s{
	Game_state turn;
}Turn;

void ttt_grid(void);

void ttt_print_o(uint8_t grid);

void ttt_print_x(uint8_t grid);

void ttt_print_line(uint8_t index);

void ttt_erase_line(uint8_t index);

void ttt_mark(uint8_t index, Grid_state mark);

Game_state ttt_game_status();

void ttt_winner(Game_state game_state);

void ttt_tie();

void ttt_main(direction dir, uint8_t* index, Turn* turn);

void ttt_menu_game();

#endif /* TICTACTOE_H_ */