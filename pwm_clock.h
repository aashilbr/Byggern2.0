 /**
* @file pwm_clock.h
* @author andrschn
*/



#ifndef PWM_CLOCK_H_
#define PWM_CLOCK_H_
#include <avr/io.h>

/**
* @brief Initializes pulse width modulation
* @details Sets the clock signel we need for the ADC.
* Sets port PD4 on the MCU as an output port. @c TCCR3A and @c TCCR3B is the timer counter
* control register. @c ICR3 and @c OCR3A are used to define the top value
* for the counter.
* The values are set so that we access Fast PWM mode.
*/
void pwm_init();




#endif /* PWM_CLOCK_H_ */
