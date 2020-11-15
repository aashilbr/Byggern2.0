/*
 * timer.h
 *
 * Created: 21.10.2020 08:35:17
 *  Author: sandrgl
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "sam.h"

int c;

void timer_init(void);

void pwm2_init(void);

void set_duty_cycle(double percent);

void pos_to_duty_cycle(int8_t pos);

#endif /* TIMER_H_ */