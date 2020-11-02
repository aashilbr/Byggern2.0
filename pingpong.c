/*
 * pingpong.c
 *
 * Created: 31.10.2020 14:13:27
 *  Author: sandrgl
 */ 
#include "pingpong.h"
#include "adc.h"
#include "CAN.h"

void pingpong_play(void){
	Message message;
	
	while (adc_joystick_dir(&joystick)!=BACK){
		adc_joystick_pos(&joystick);
		message.data[0]=joystick.x;
		message.data[1]=joystick.y;
		message.length=2;		
		CAN_send_message(&message);
		printf("X: %d \n \r", message.data[1]);
	}
	message.data[0]=0;
	message.data[1]=0;
	message.length=2;
	CAN_send_message(&message);
}