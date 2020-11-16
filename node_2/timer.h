
/**
* @file node_2/timer.h
* @author sandrgl
* @date 21.10.2020 08:35:17
* @brief A timer module for a pwm signal of 50Hz
*/
#ifndef TIMER_H_
#define TIMER_H_

#include "sam.h"

int c;
/**
* @brief Initializes a pwm signal with interrups
* @details PWM signal on PB25(PWM2) and Initializes the TC0_HANDLER
*/
void timer_init(void);

/**
* @brief Initializes a pwm signal with interrups
* @details Initializes the TC1_HANDLER
*/
void pwm2_init(void);


/**
* @brief  Sets the dutycycle of the PWM signal to @p percent %
* @param [in] percent Percent of the period the signal is set
* @details Will set the duty cycle to be more than 10,5% or less than 4,5%
*/
void set_duty_cycle(double percent);

/**
* @brief  Convert a position measurement to duty cyle and sets it
* @param [in] pos The measured position to be converted to pwm
* @details @p pos should be between -100 and 100
*/

void pos_to_duty_cycle(int8_t pos);

#endif /* TIMER_H_ */
