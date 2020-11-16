/*
 * pingpong_states.h
 *
 * Created: 28.10.2020 11:37:09
 *  Author: sandrgl
 */
/**
* @file pingpong_states.h
* @author sandrgl
* @date 15 Nov 2020
* @brief For updating the score until game over
*/


#ifndef PINGPONG_STATES_H_
#define PINGPONG_STATES_H_

#define THRESHOLD_ADC 1000

/**
*The typedefined structure describing if the ball has been detected, and the score
*/
typedef struct pingpong_s{
	int ball_detected;/**<if the ball has been detected or not*/
	int score;/**<The score of the game*/
}pingpong;

pingpong pingpong_state;
/**
* @brief sets pingpong_state.score and pingpong_state.ball_detected to 0
*/
void init_ppstate();


/**
* @brief Increases the score if a ball is detected and has not been detected before
*/
void count_score(void);

/**
* @brief Sends a CAN message to node 2, informing that a ball is detected, implying game over
*/
void check_if_game_over(void);

#endif /* PINGPONG_STATES_H_ */
