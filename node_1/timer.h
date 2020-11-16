/**
* @file node_1/timer.h
* @author sandrgl
* @date 11.11.2020 11:22:32
* @brief Library for timer functions.
*/

#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
/**
* Timer:
* @count An integer containing how long the timer has been counting, in seconds.
* @details The variable counts how many times the timer calls the interrupt
* service routine.
*/
typedef struct Timer_s{
	int count;
}Timer;

Timer timer;
/**
* @brief Initializes the timer.
* @details Starts the timer. Sets clock prescalar to  64, enables interrupts and
* compare match on 90.
*/
void timer_init(void);

/**
* @brief Starts the timer.
* @details Initializes the timer count to be 0.
*/
void start_timer(void);

/**
* @brief Retrieves the timer count.
* @return The value the timer has counted to.
*/
uint8_t get_count(void);

#endif /* TIMER_H_ */
