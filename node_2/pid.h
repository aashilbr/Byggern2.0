/**
* @file pid.h
* @author andrschn
* @date  28.10.2020
* @brief Driver for PID regulator.
*/


#ifndef PID.H_H_
#define PID.H_H_
#include "sam.h"
#include "joystick.h"
#include "motor_controller.h"

/**
 * @brief A structure to represent a person.
 */
typedef struct Pid_s{
	double p_factor; /** < The proportional factor in PID regulator */
	double i_factor; /** < The integral factor in PID regulator */
	double d_factor; /** < The derivative factor in PID regulator */
	int16_t error; /** < Error between the reference and actual state */
	int16_t sum_error; /** < Sum of error */
	int16_t last_error; /** < The value of error last run */
	int control_signal; /** < The calculated control signal */
	int8_t ref; /** < Reference value for the position, from joystick */
	int8_t measured; /** < The measured value from the encoder */

}Pid;

/**
* @brief Function for returning the stored control signal from Pid struct
* @return The control signal
*/
int get_control_signal(void);

/**
* @brief Initialization of Pid stuct
* @details Init function for setting tuned PID values and
* initializing the rest of the values in Pid struct to be zero
*  at start-up.
*/
void pid_init(void);

/**
* @brief Calculating the control signal using discrete PID regulator
* @details The function calculates the values needed in the regulator
* and stores them in the Pid struct.
*/
void pid_regulator();

/**
* @brief Function for choosing the difficulity of controlling the
* motor.
* @param [in] diff 0 for hard and easy otherwise
* @details the function stores the new PID regulator constants in Pid struct.
*/
void set_pid_difficulty(uint8_t diff);

/**
* @brief Sets the error values in Pid struct to zero, as well as control_signal,
* ref and measured.
* @details To be used if the program is starting over, but we don't want to
* change the P, I and D factor.
*/
void pid_error_init();

#endif  PID.H_H_
