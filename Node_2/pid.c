 /* 
 *pid.c
 *
 * Created: 28.10.2020 20:52:39
 *  Author: sandrgl
 */ 

#include "pid.h"

volatile Pid pid;

void pid_init(void){
	pid.p_factor =9;  
	pid.i_factor = 1;
	pid.d_factor = 3;
	pid.error = 0;
	pid.last_error = 0;
	pid.sum_error = 0;
	pid.u = 0;
	pid.ref = 0;
	pid.measured = 0;
}

void pid_error_init(){
		pid.error = 0;
		pid.last_error = 0;
		pid.sum_error = 0;
		pid.u = 0;
		pid.ref = 0;
		pid.measured = 0;
	
}

void pid_regulator(){
	pid.last_error = pid.error;
	pid.error =(int16_t)(pid.ref - pid.measured);
	printf("error: %d ref:%d measured:%d\n\r", pid.error,pid.ref,pid.measured);
	pid.sum_error += pid.error;
	int u = pid.p_factor*pid.error+pid.i_factor*pid.sum_error+(pid.d_factor)*(pid.error-pid.last_error);
	pid.u = u;
	
}

void set_pid_difficulty(uint8_t diff){
	if (diff==0){//hard
		pid.p_factor=1;
		pid.i_factor=1;
		pid.d_factor=1;
	}
	else{//easy
		pid.p_factor=15;
		pid.i_factor=0.05;
		pid.d_factor=0;
	}
}

int get_u(void){
	return pid.u;
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


void TC0_Handler(){
	int32_t status = TC0->TC_CHANNEL[0].TC_SR;
	pid.ref = 0.9*js_pos.x;
	pid.measured = read_encoder();
}
