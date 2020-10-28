/*
 * MCU.h
 *
 * Created: 16.09.2020 16:56:25
 *  Author: andrschn
 */ 

#include <avr/io.h>

#ifndef MCU_H_
#define MCU_H_

void mcu_init() {
	DDRB &= ~(1 << PB0); //Button left slider input
	DDRB &= ~(1 << PB1); //Button right slider input
	DDRE |= 1 << PE1; //ALE as output
	DDRD &= ~(1 << PD5); //Joystick button input
}



#endif /* MCU_H_ */