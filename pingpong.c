/*
 * pingpong.c
 *
 * Created: 31.10.2020 14:13:27
 *  Author: sandrgl
 */ 
#include "pingpong.h"
#include "adc.h"
#include "CAN.h"
#include "menu.h"
#include "timer.h"

int check_if_game_over(void){
	Message message;
	if (check_CAN_interrupt()){
		CAN_receive_message(&message);
		if(message.ID==0b1111){
			return 1;
		}
	}
	return 0;
}
void pingpong_play(void){
	Message message;
	message.data[0]=0;
	message.data[1]=0;
	message.length=2;	
	message.ID = 101;
	CAN_send_message(&message);
	GICR |= (1<<INT0); //external interrupt enabled
	message.ID =0;
	//START TIMER 
	start_timer();
	int game_over = 0; 
	while (adc_joystick_dir(&joystick)!=BACK && !game_over){ 
		adc_joystick_pos(&joystick);
		message.data[0]=joystick.x;
		message.data[1]=joystick.y;
		message.data[2]= adc_read_button_touch_r();
		message.length=3;		
		CAN_send_message(&message);
		printf("button: %d \n \r", message.data[2]);
		game_over = check_if_game_over();
	}
	GICR &= ~(1<<INT0); //external interrupt disabled
	oled_pos(3,30);
	int time_diff = get_count();
	oled_print("YOUR SCORE: ");
	oled_pos(4,50);
	char score[5];
	sprintf(score,"%d",time_diff);
	oled_print(score);
	message.data[0]=0;
	message.data[1]=0;
	message.data[2]=0;
	message.length=3;
	CAN_send_message(&message);
	_delay_ms(2000);
}