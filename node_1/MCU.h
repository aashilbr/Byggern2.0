/**
* @file MCU.h
* @author andrschn
* @date 16.09.2020 16:56:25
* @brief Library for the MCU inputs and outputs.
*/
#include <avr/io.h>

#ifndef MCU_H_
#define MCU_H_

/**
* @brief Initializes the MCU.
* @details Sets left and right slider button as input, ALE as output and
* joystick button as input.
*/
void mcu_init() {
	DDRB &= ~(1 << PB0); //Button left slider input
	DDRB &= ~(1 << PB1); //Button right slider input
	DDRE |= 1 << PE1; //ALE as output
	DDRD &= ~(1 << PD5); //Joystick button input
}



#endif /* MCU_H_ */
