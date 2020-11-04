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
	message.data[0]=0;
	message.data[1]=0;
	message.length=2;	
	message.ID = 101;
	CAN_send_message(&message);
	
	message.ID =0;
	
	while (adc_joystick_dir(&joystick)!=BACK){
		adc_joystick_pos(&joystick);
		message.data[0]=joystick.x;
		message.data[1]=joystick.y;
		message.data[2]= adc_read_button_touch_r();
		message.length=3;		
		CAN_send_message(&message);
		printf("button: %d \n \r", message.data[2]);
	}
	message.data[0]=0;
	message.data[1]=0;
	message.data[2]=0;
	message.length=2;
	CAN_send_message(&message);
}