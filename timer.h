/*
 * timer.h
 *
 * Created: 11.11.2020 11:22:32
 *  Author: sandrgl
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
typedef struct Timer_s{
	int count;
}Timer;

Timer timer;

void timer_init(void);

void start_timer(void);

int get_count(void);

#endif /* TIMER_H_ */