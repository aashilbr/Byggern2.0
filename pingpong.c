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



void pingpong_init(void){
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


void pingpong_print_score(){
	//oled_clear_all();
	oled_pos(4,30);
	int time_diff = get_count();
	oled_print("YOUR SCORE: ");
	oled_pos(5,50);
	char score[5];
	sprintf(score,"%d",time_diff);
	oled_print(score);
}


void print_game_finshed(int game_over){
	if (game_over)	{
		oled_pos(2,30);
		oled_print("GAME OVER!!");
	}
	else{
		oled_pos(2,22);
		oled_print("Game finished :(");
	}
}

void pingpong_store_data(int8_t x_pos, int8_t y_pos, uint8_t button, int count, int frequency){
	 if (xmem_check_storing_condition(count, frequency)){
		 xmem_save_movement(x_pos,y_pos,button,count);
	 }
}

void pingpong_move_with_joystick(void){
	int game_over = 0;
	int count = 0;
	int frequency = 12;
	while (adc_joystick_dir(&joystick)!=BACK && !game_over){
		count++;
		pingpong_store_data(joystick.x,joystick.y, adc_read_button_touch_r(),count,frequency);
		adc_joystick_pos(&joystick);
		CAN_send_pos(joystick.x,joystick.y,adc_read_button_touch_r());
		game_over = check_if_game_over();
		pingpong_print_score();
	}
	xmem_write_size(count/12);
	print_game_finshed(game_over);
}


void pingpong_move_with_sliders(void){
	int game_over = 0;
	int count = 0;
	int frequency = 8;
	while (adc_joystick_dir(&joystick)!=BACK && !game_over){
		count++;
		pingpong_store_data(joystick.x,joystick.y, adc_read_button_touch_r(),count,frequency);
		adc_slider_pos(&joystick);
		CAN_send_pos(joystick.x,joystick.y,adc_read_button_touch_r());
		game_over = check_if_game_over();
		pingpong_print_score();
	}
	xmem_write_size(count/frequency);
	print_game_finshed(game_over);
	printf("%d\n\r",count);
}



void pingpong_play_with_sliders(void){
	pingpong_init();
	pingpong_move_with_sliders();
	pingpong_save_highscore(get_count());
	CAN_send_pos(0,0,0);

}


void pingpong_play_with_joystick(void){
	pingpong_init();
	pingpong_move_with_joystick();
	pingpong_save_highscore(get_count());
	CAN_send_pos(0,0,0);
}

void pingpong_move_with_memory(void){
	pingpong_init();
	int movement_size = xmem_get_size();
	int data_nr = 0;
	while (adc_joystick_dir(&joystick)!=BACK && data_nr<movement_size){
		int8_t x_pos = xmem_read_x_movement(data_nr);
		int8_t y_pos = xmem_read_y_movement(data_nr);
		uint8_t button = xmem_read_button_movement(data_nr);
		data_nr++;
		CAN_send_pos(x_pos, y_pos, button);
		_delay_ms(20);
	}
}

void pingpong_save_highscore(uint8_t score){
	uint8_t old_highscore = xmem_read(0x1800);
	if(score > old_highscore){
		xmem_write(score,0x1800);
	}
}

 void reset_highscore(void){
	 xmem_write(0,0x1800);
 }
