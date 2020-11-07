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
	double dt;
	double error;
	double sum_error;
	double last_error;
	int8_t u;
	int8_t ref;
	int8_t measured;	

}Pid;

Pid pid;
void pid_init();

void pid_regulator();
#endif  PID.H_H_ 