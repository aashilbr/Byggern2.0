
/**
* @file tictactoe.h
* @author sandrgl
* @date 27.09.2020 14:54:28
* @brief tic tac toe game for the oled screen
*/


#ifndef TICTACTOE_H_
#define TICTACTOE_H_

#include "menu.h"


/**
* The enumeration of the game state; which player's turn it is if someone has won or not
*/

typedef enum {
	X_PLAY,/**<x-player's turn*/
	O_PLAY,/**<o-player's turn*/
	O_WIN,/**<o-player won*/
	X_WIN,/**<x-player won*/
	NO_WIN,/**<game not finished*/
	TIE/**<a tie*/
} Game_state;

/**
*The enumeration of the grid slot state
*/
typedef enum {
	X,/**<x placed in the grid*/
	O,/**<o placed in the grid*/
	NONE/**<grid is empty*/
} Grid_state;

/**
*The typedefined structure of who's turn it is
*/
typedef struct Turn_s{
	Game_state turn;/**<Game_state object that holds who's turn it is */
}Turn;

/**
* @brief Draws the 3x3 grid on the oled
*/
void ttt_grid(void);

/**
* @brief Draws a circle in @p grid
* @param [in] grid The grid number to be drawn in
* @warning @p grid has to be a number between 0 and 8
*/
void ttt_print_o(uint8_t grid);

/**
* @brief Draws a x in @p grid
* @param [in] grid The grid number to be drawn in
* @warning @p grid has to be a number between 0 and 8
*/
void ttt_print_x(uint8_t grid);

/**
* @brief Draws a line in the top left corner of the @p index grid
* @param [in] index The grid index to be drawn in
* @warning @p index has to be a number between 0 and 8
*/
void ttt_print_line(uint8_t index);


/**
* @brief Erases a line in the top left corner of the @p index grid
* @param [in] index The index of the grid where the line should be erased
* @warning @p index has to be a number between 0 and 8
*/
void ttt_erase_line(uint8_t index);


/**
* @brief Updates the game_board in @p index to the grid state @p mark
* @param [in] index The grid index to be drawn in
* @param [in] mark The players mark
* @warning @p index has to be a number between 0 and 8
*/

void ttt_mark(uint8_t index, Grid_state mark);

/**
* @brief Checks what the state of the game is
* @return Returns a Game_state element describing wether it's a tie, if someone has won, if so which player, or if the game is still in progress
*/
Game_state ttt_game_status();

/**
* @brief Prints the results of the game to the oled
* @param [in] game_state The end state of the game, describing who won
*/
void ttt_winner(Game_state game_state);

/**
* @brief Prints a tie to the oled
*/
void ttt_tie();

/**
* @brief A state machine for the game based on the joystick direction
* @param [in] dir Direction of the joystick
* @param [in] index Current index in the grid
* @param [in] turn Who's turn it is
*/
void ttt_main(direction dir, uint8_t* index, Turn* turn);


/**
*@brief The driver of the game, runs as long as the players dont press @c BACK
*@details Resets the game_board to @c NONE in all slots
*/
void ttt_menu_game();

#endif /* TICTACTOE_H_ */
