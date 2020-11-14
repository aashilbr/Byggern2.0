/*
 * pingpong_states.c
 *
 * Created: 28.10.2020 11:39:25
 *  Author: sandrgl
 */ 
#include "pingpong_states.h"
#include "can_controller.h"

void init_ppstate(){
	pingpong_state.ball_detected=0;
	pingpong_state.score =0;
}

void count_score(void){
	if(pingpong_state.ball_detected==0 && read_ir_signal()<THRESHOLD_ADC){
		pingpong_state.score++;
		printf("Count : %d \n", pingpong_state.score);
		pingpong_state.ball_detected=1;
	}
	if (read_ir_signal()>THRESHOLD_ADC){
		pingpong_state.ball_detected=0;
	}
}


void check_if_game_over(void){
	if(pingpong_state.ball_detected==0 && read_ir_signal()<THRESHOLD_ADC){
		CAN_MESSAGE message;
		message.id=0b1111;
		message.data_length = 1;
		message.data[0] = 100;
		while(can_send(&message,0));
		//while(can_send(&message,1));
		pingpong_state.ball_detected=1;
	}
}