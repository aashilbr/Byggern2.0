/*
 * motor_controller.h
 *
 * Created: 28.10.2020 14:59:39
 *  Author: sandrgl
 */ 

#include "sam.h"
#include "joystick.h"
#ifndef MOTOR_CONTROLLER_H_
#define MOTOR_CONTROLLER_H_

void motor_init(void);

int16_t read_encoder(void);

void set_direction_bit(int8_t reference);

void controller_speed(int8_t pos_x);

void shoot(uint8_t pressed);

#endif /* MOTOR_CONTROLLER_H_ */