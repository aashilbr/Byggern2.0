/**
* @file node_2/motor_controller.h
* @author andrschn
* @date 28.10.2020
* @brief Driver for motor controll and encoder reading
*/

#include "sam.h"
#include "joystick.h"
#ifndef MOTOR_CONTROLLER_H_
#define MOTOR_CONTROLLER_H_

/**
* @brief Initialization of the motor
* @details the function first initializes the PMC and DACC.
* Then sets the motor mox pins as output enable. The data
* pins are set to be input pins for reading the encoder value.
* Calibrating the encoder on the lect side of the box to get a
* known zero.
* Enables PC19 as solenoid pin.
*/
void motor_init(void);

/**
* @brief Reads the encoder returns the position as a nubmer between -100,100.
* @return The encoder position as a value between -100, 100. -100 is far left
* @details Follows the procedure for reading the encoder. Uses 17 000 as the
* differation between min and max encoder position, and converts the measured value
* to wanted interval to correspond with values recieved from the joystick.
*/
int8_t read_encoder(void);

/**
* @brief Sets the direction of the motor
* @param [in] reference The sign of the reference decides the direction
* @details Negative reference sets direction to the left, positive sets the direction
* to the rigth.
*/
void set_direction(int reference);

/**
* @brief Desiced the speed of the controller
* @param [in] control_signal Used in set_direction to decide the direction, and sets the
* controller speed.
* @details When the function i called, it sets the direction according to the sign of
* the input and sets the speed to be the absolute value of @p control_signal.
*/
void controller_speed(int control_signal);

/**
* @brief Sets IO pin PC19 high if shoot button is pressed, else low.
* @param [in] pressed Takes in a value that is 1 if shoot button is pressed and
* zero otherwise.
* @details If @p pressed is one, PC19 is set, else it is cleared.
*/
void shoot(uint8_t pressed);


#endif /* MOTOR_CONTROLLER_H_ */
