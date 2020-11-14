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
#include "external_memory.h"

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



pingpong_init(void){
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
}


pingpong_print_score(){
	//oled_clear_all();
	oled_pos(3,30);
	int time_diff = get_count();
	oled_print("YOUR SCORE: ");
	oled_pos(4,50);
	char score[5];
	sprintf(score,"%d",time_diff);
	oled_print(score);
}



pingpong_move_with_joystick(void){
	int game_over = 0;
	while (adc_joystick_dir(&joystick)!=BACK && !game_over){
		adc_joystick_pos(&joystick);
		CAN_send_pos(joystick.x,joystick.y,adc_read_button_touch_r());
		game_over = check_if_game_over();
		pingpong_print_score();
	}
}



pingpong_move_with_sliders(void){
	int game_over = 0;
	while (adc_joystick_dir(&joystick)!=BACK && !game_over){
		adc_slider_pos(&joystick);
		CAN_send_pos(joystick.x,joystick.y,adc_read_button_touch_r());
		game_over = check_if_game_over();
		pingpong_print_score();
	}
}



void pingpong_play_with_sliders(void){
	pingpong_init();
	pingpong_move_with_sliders();
	pingpong_save_highscore(get_count());
	printf("score: %d \n\r",xmem_read(0x1801));
	CAN_send_pos(0,0,0);
	
}


void pingpong_play_with_joystick(void){
	pingpong_init();
	pingpong_move_with_joystick();
	pingpong_save_highscore(get_count());
	CAN_send_pos(0,0,0);
}

void pingpong_save_highscore(uint8_t score){
	uint8_t old_highscore = xmem_read(0x1801);
	if(score > old_highscore){
		xmem_write(score,0x1801);
	}
}

 void reset_highscore(void){
	 xmem_write(0,0x1801);
 }

/*

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
	//GICR |= (1<<INT0); //external interrupt enabled
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
		printf("CANINTE: %d \n\r", mcp_read(MCP_CANINTF)&0x3);
		//printf("button: %d \n \r", message.data[2]);
		game_over = check_if_game_over();
	}
	//GICR &= ~(1<<INT0); //external interrupt disabled
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
}*/