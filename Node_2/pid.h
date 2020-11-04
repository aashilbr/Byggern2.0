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
	int16_t p_factor;
	int16_t i_factor;
	int16_t d_factor;
	double dt;
	int16_t sum_error;
	int16_t last_error;
	int16_t u;	

}Pid;

Pid pid;
void pid_init();

#endif  PID.H_H_ 