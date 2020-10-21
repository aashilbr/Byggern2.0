/*
 * pwm_clock.c
 *
 * Created: 09.09.2020 12:36:02
 *  Author: andrschn
 */ 
#include "pwm_clock.h"
#include <avr/io.h>
#include <avr/interrupt.h>



void pwm_init(){
	cli();
		
	
	DDRD|=(1<<PD4);//set PD4 as output	
	TCCR3A|=(1<<COM3A1)|(0<<COM3A0)|(0<<COM3B1)|(0<<COM3B0)|(1<<WGM31);//set TCCR3A as ob1111--10: non-inverting compare output mode
	TCCR3A&=~(1<<WGM30);
	TCCR3B|=(1<<WGM33)|(1<<WGM32)|(1<<CS30);//set TCCR3B as 0b---11---
	ICR3=4;
	OCR3A=2;
	sei();
}

