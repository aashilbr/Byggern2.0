/*
 * pingpong.h
 *
 * Created: 31.10.2020 14:13:04
 *  Author: sandrgl
 */


#ifndef PINGPONG_H_
#define PINGPONG_H_
#include <avr/io.h>

//void pingpong_play(void);

/**
* @brief Checks if the game is over due to lost ping pong ball.
* @returns 1 if the ball is lost.
*          0 if the ball is not lost.
* @details If the message received from the CAN bus matches
* the message of ball detected by the IR diodes, then the game is over.
*/
int check_if_game_over(void);

/**
* @brief Move the game board racket by using the touch sliders as reference.
* @details Sends the position of the sliders and right touch button
* over the CAN bus and checks if the game is over due to lost ball
* or pressing the left button for BACK option. Prints score
* on the OLED screen while playing.
*/
void pingpong_move_with_sliders(void);

/**
* @brief Move the game board racket by using the joystick as reference.
* @details Sends the position of the joystick and right touch button
* over the CAN bus and checks if the game is over due to lost ball
* or pressing the left button for BACK option. Prints score
* on the OLED screen while playing.
*/
void pingpong_move_with_joystick(void);

/**
* @brief Prints the score to the OLED-screen.
*/
void pingpong_print_score();

/**
* @brief Initializes the ping pong game.
* @details Sends message over the CAN bus so the game can
* start. Starts the timer for counting the score.
*/
void pingpong_init(void);

/**
* @brief Play ping pong by using the touch sliders as reference.
* @details Initalizes the game and uses the sliders to control
* the position of the game board racket.
* Saves the high score when game over.
*/
void pingpong_play_with_sliders(void);

/**
* @brief Play ping pong by using the joystick as reference.
* @details Initalizes the game and uses the joystick to control
* the position of the game board racket.
* Saves the high score when game over.
*/
void pingpong_play_with_joystick(void);

/**
* @brief Saves the highscore to SRAM if the new high score is
* larger than the original high score.
*/
void pingpong_save_highscore(uint8_t score);

/**
* @brief Resets the high score.
*/
void reset_highscore(void);

#endif /* PINGPONG_H_ */
