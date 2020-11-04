 /* 
 *pid.c
 *
 * Created: 28.10.2020 20:52:39
 *  Author: sandrgl
 */ 

#include "pid.h"



void pid_init(void){
	pid.p_factor = 1;
	pid.i_factor = 0;
	pid.d_factor = 1;
	pid.dt = 1/50;
	pid.last_error = 0;
	pid.sum_error = 0;
	pid.u = 0;
}



//
//void TC3_Handler(){
	//uint32_t status = TC1->TC_CHANNEL[0].TC_SR;
	//int16_t ref = js_pos.x;
	//int16_t measured = read_encoder();
	//int16_t error = ref - measured;
	//pid.sum_error += error;
	//int16_t u = pid.p_factor*error+pid.dt*pid.i_factor*pid.sum_error+pid.d_factor/pid.dt*(error-pid.last_error);
	//pid.last_error = error;
	//printf("u = %d \n \r", u);
	//controller_speed(u);
	//
	//
//}

