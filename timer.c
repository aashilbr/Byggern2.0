/*
 * timer.c
 *
 * Created: 11.11.2020 11:22:55
 *  Author: sandrgl
 */ 
#include "timer.h"

void timer_init(void){
	TCCR1A = 0x00;
	TCCR1B = (1<<CS10)|(1<<CS11);
	TIMSK = (1<<TOIE1); //Interrupts globally enabled
	TCNT1 = 90;
	start_timer();
}

ISR (TIMER1_OVF_vect){
	TIFR = 0x01;	
	TCNT1 = 90;
	timer.count++;
}


void start_timer(void){
	timer.count=0;
}

int get_count(void){
	return timer.count;
}

	
