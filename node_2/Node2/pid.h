 /** pid.h
 *
 * Created: 28.10.2020 20:52:51
 *  Author: sandrgl
  
*/


#ifndef PID.H_H_
#define PID.H_H_
#include "sam.h"
#include "joystick.h"
#include "motor_controller.h"

typedef struct Pid_s{
	double p_factor;
	double i_factor;
	double d_factor;
	int16_t error;
	int16_t sum_error;
	int16_t last_error;
	int u;
	int8_t ref;
	int8_t measured;	

}Pid;

int get_u(void); 

void pid_init();

void pid_regulator();

void set_pid_difficulty(uint8_t diff);
void pid_error_init();

#endif  PID.H_H_ 