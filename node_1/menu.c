/*
 * menu.c
 *
 * Created: 16.09.2020 18:59:34
 *  Author: andrschn
 */ 

#include "menu.h"
#include "external_memory.h"



void oled_menu_main(void) {
	oled_clear_all();
	oled_pos(0,4);
	oled_print("MAIN MENU:");
	oled_pos(2,4);
	oled_print("Games");
	oled_pos(4,4);
	oled_print("Settings");
}

void oled_menu_games(void) {
	
	oled_clear_all();
	oled_pos(0,4);
	oled_print("GAMES:");
	oled_pos(2,4);
	oled_print("Tic Tac Toe");
	oled_pos(4,4);
	oled_print("Ping Pong");
}

void oled_menu_settings(void) {
	
	oled_clear_all();
	oled_pos(0,4);
	oled_print("SETTINGS:");
	oled_pos(2,4);
	oled_print("Brightness");
	oled_pos(4,4);
	oled_print("Set difficulty");
	oled_pos(6,4);
	oled_print("Calibrate joystick");
}

void oled_menu_games_sub(void) {
	
	oled_clear_all();
	oled_pos(0,4);
	oled_print("GAMES:");
	oled_pos(2,4);
	oled_print("Play");
	oled_pos(4,4);
	oled_print("High score");
}

void oled_menu_high_score_sub(void) {
	
	oled_clear_all();
	oled_pos(0,4);
	oled_print("High score: ");
	char score[10];
	sprintf(score, "%d", (int) xmem_read(0x1801));
	oled_pos(0,70);
	oled_print(score);
	oled_pos(2,4);
	oled_print("Reset high score");
}

void oled_frame(uint8_t line){
	oled_pos(line,2);
	oled_write_data(0xff);
	oled_pos(line+1,2);
	for(int i=3;i<127;i++){
		oled_write_data(0x01);
	}
	oled_pos(line-1,2);
	for(int i=3;i<127;i++){
		oled_write_data(0x80);
	}
	oled_pos(line,126);
	oled_write_data(0xff);
}

void oled_clear_frame(uint8_t line){
	oled_clear_line(line-1);
	oled_clear_line(line+1);
	oled_pos(line,2);
	oled_write_data(0x00);
	oled_pos(line,126);
	oled_write_data(0x00);
}

void oled_set_brightness_lvl(uint8_t lvl){
	write_c(0x81);
	write_c(lvl);
}

void oled_menu_set_brightness(void) {
	oled_clear_all();
	oled_pos(0,4);
	oled_print("SET BRIGHTNESS LEVEL:");
	oled_pos(2,4);
	oled_print("Min");
	oled_pos(4,4);
	oled_print("Med");
	oled_pos(6,4);
	oled_print("Max");
}

void oled_menu_difficulty(void) {
	oled_clear_all();
	oled_pos(0,4);
	oled_print("SET DIFFICULTY:");
	oled_pos(2,4);
	oled_print("Easy");
	oled_pos(4,4);
	oled_print("Hard");
}

void oled_set_brightness_lvl_min(void){
	oled_set_brightness_lvl(0x00); 
	oled_clear_all();
	oled_pos(2,23);
	oled_print("THERE YOU GO :)");
}
void oled_set_brightness_lvl_med(void){
	oled_set_brightness_lvl(0x7e);
	oled_clear_all();
	oled_pos(2,23);
	oled_print("THERE YOU GO :)");
}
void oled_set_brightness_lvl_max(void){
	oled_set_brightness_lvl(0xff);
	oled_clear_all();
	oled_pos(2,23);
	oled_print("THERE YOU GO :)");
}



void oled_menu_stearing(void) {
	oled_clear_all();
	oled_pos(0,4);
	oled_print("Stearing mechanism:");
	oled_pos(2,4);
	oled_print("Joystick");
	oled_pos(4,4);
	oled_print("Sliders");
}



//void oled_menu_joystick_info(void) {
	//oled_clear_all();
	//oled_pos(0,4);
	//oled_print("Move with x");
	//oled_pos(2,4);
	//oled_print("Turn with y");
	//oled_pos(4,4);
	//oled_print("Shoot with right button");
	//oled_pos(6,4);
	//oled_print("Push joystick button to start");
//}
//
//
//
//void oled_menu_slider_info(void) {
	//oled_clear_all();
	//oled_pos(0,4);
	//oled_print("Move with right slider");
	//oled_pos(2,4);
	//oled_print("Turn with left slider");
	//oled_pos(4,4);
	//oled_print("Shoot with right button");
	//oled_pos(6,4);
	//oled_print("Push joystick button to start");
//}



void oled_navigate(direction dir, state *p_node) {
	switch (dir) {
		case UP:
			if (p_node->menu_pos>1){
				oled_clear_frame(p_node->menu_pos*2);
				p_node->menu_pos -=1;
				oled_frame(p_node->menu_pos*2);
				_delay_ms(1000);
			}
			break;
		case DOWN:
			if (p_node->menu_pos <menu_children(p_node->current_node, p_node->current_node->p_child)){
				oled_clear_frame(p_node->menu_pos*2);
				p_node->menu_pos +=1;
				oled_frame(p_node->menu_pos*2);
				_delay_ms(1000);
			}
			break;
		case PRESSED:
			if (p_node->current_node->p_child != NULL){
				oled_clear_all();
				p_node->current_node = p_node->current_node->p_child ;
				for (int i = 1; i<p_node->menu_pos; i++) {
					p_node->current_node = p_node->current_node->p_sibling;			
				}
				p_node->menu_pos=1;
				p_node->current_node->action();
				if (p_node->current_node->p_child != NULL){oled_frame(p_node->menu_pos*2);}
				_delay_ms(1000);
			}
			break;
		case BACK:
			if (p_node->current_node->p_parent!=NULL){
				oled_clear_all();
				p_node->current_node = p_node->current_node->p_parent;
				p_node->menu_pos=1;
				p_node->current_node->action();
				oled_frame(p_node->menu_pos*2);
				_delay_ms(1000);
			}
			break;	
		case NEUTRAL:
			break;	
		case GAME_OVER:
			if (p_node->current_node->p_parent!=NULL){
				oled_clear_all();
				p_node->current_node = p_node->current_node->p_parent;
				p_node->menu_pos=1;
				p_node->current_node->action();
				oled_frame(p_node->menu_pos*2);
				_delay_ms(1000);
			}
		default:
			break;
	}
}

int menu_children(const Menu_node * p_node, Menu_node ** pp_child){
	if(p_node->p_child==NULL){
		return 0;
	}
	*pp_child = p_node->p_child;
	int children = 0;
	Menu_node * it = p_node->p_child;
	while (it != NULL){
		children++;
		it = it->p_sibling;
	}
	return children;
}


void menu_init(state * start_state){
	oled_clear_all();
	//start_state->current_node
	start_state->menu_pos=1;
	start_state->current_node->action();
	oled_frame(2);
}

void oled_calibrate_joystick(void){
	oled_clear_all();
	oled_pos(3,50);
	oled_print("WAIT");
	_delay_ms(2000);
	oled_pos(4,50);
	oled_print("3");
	_delay_ms(2000);
	oled_clear_line(4);
	oled_print("2");
	adc_calibrate_joystick(&joystick);
	_delay_ms(2000);
	oled_clear_line(4);
	oled_print("1");
	_delay_ms(2000);
	oled_clear_line(4);
	oled_clear_line(3);
	oled_pos(4,7);
	oled_print("Joystick calibrated <3");
	
	
}