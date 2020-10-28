/*
 * pingpong_states.c
 *
 * Created: 28.10.2020 11:39:25
 *  Author: sandrgl
 */ 
#include "pingpong_states.h"

void count_score(void){
	if(pingpong_state.ball_detected==0 && read_ir_signal()<THRESHOLD_ADC){
		pingpong_state.score++;
		//printf("Count : %d \n", count);
		pingpong_state.ball_detected=1;
	}
	if (read_ir_signal()>THRESHOLD_ADC){
		pingpong_state.ball_detected=0;
	}
}