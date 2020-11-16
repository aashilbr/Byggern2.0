/*
 * menu.c
 *
 * Created: 16.09.2020 18:59:34
 *  Author: andrschn
 */

#include "menu.h"

static MenuNode m_menu_nodes[] = {
	{
		"Main Menu",
		NULL,
		m_menu_nodes + 1,
		NULL,
		MENU_ENTER_SUBMENU
	},
	{
		"Games",
		m_menu_nodes + 0,
		m_menu_nodes + 3,
		m_menu_nodes + 2,
		MENU_ENTER_SUBMENU
	},
	{
		"Settings",
		m_menu_nodes + 0,
		m_menu_nodes + 5,
		NULL,
		MENU_ENTER_SUBMENU
	},
	{
		"Tic Tac Toe",
		m_menu_nodes + 1,
		NULL,
		m_menu_nodes + 4,
		MENU_PLAY_TIC_TAC_TOE
	},
	{
		"Ping Pong",
		m_menu_nodes + 1,
		m_menu_nodes + 8,
		NULL,
		MENU_ENTER_SUBMENU
	},
	{
		"Brightness",
		m_menu_nodes + 2,
		m_menu_nodes + 10,
		m_menu_nodes + 6,
		MENU_ENTER_SUBMENU
	},
	{
		"Set Difficulty",
		m_menu_nodes + 2,
		m_menu_nodes + 13,
		m_menu_nodes + 7,
		MENU_ENTER_SUBMENU
	},
	{
		"Calibrate",
		m_menu_nodes + 2,
		NULL,
		NULL,
		MENU_CALIBRATE
	},
	{
		"Steering",
		m_menu_nodes + 4,
		m_menu_nodes + 15,
		m_menu_nodes + 9,
		MENU_ENTER_SUBMENU
	},
	{
		"Highscore",
		m_menu_nodes + 4,
		m_menu_nodes + 17,
		NULL,
		MENU_ENTER_SUBMENU
	},
	{
		"Minimum",
		m_menu_nodes + 5,
		NULL,
		m_menu_nodes + 11,
		MENU_SET_BRIGHTNESS_MINIMUM
	},
	{
		"Medium",
		m_menu_nodes + 5,
		NULL,
		m_menu_nodes + 12,
		MENU_SET_BRIGHTNESS_MEDIUM
	},
	{
		"Maximum",
		m_menu_nodes + 5,
		NULL,
		NULL,
		MENU_SET_BRIGHTNESS_MAXIMUM
	},
	{
		"Easy",
		m_menu_nodes + 6,
		NULL,
		m_menu_nodes + 14,
		MENU_SET_DIFFICULTY_EASY
	},
	{
		"Hard",
		m_menu_nodes + 6,
		NULL,
		NULL,
		MENU_SET_DIFFICULTY_HARD
	},
	{
		"By Joystick",
		m_menu_nodes + 8,
		NULL,
		m_menu_nodes + 16,
		MENU_PLAY_PING_PONG_JOYSTICK
	},
	{
		"By Slider",
		m_menu_nodes + 8,
		NULL,
		m_menu_nodes + 18,
		MENU_PLAY_PING_PONG_SLIDER
	},
	{
		"Memory Playback",
		m_menu_nodes + 8,
		NULL,
		NULL,
		MENU_PLAY_PING_PONG_MEMORY
	},
	{
		"Reset Highscore",
		m_menu_nodes + 9,
		NULL,
		NULL,
		MENU_HIGHSCORE_RESET
	}
};

const MenuNode * menu_root_node(){
	return m_menu_nodes;
}

uint8_t menu_children(const MenuNode * p_node){
	MenuNode * p_child = p_node->p_child;
	uint8_t children = 0;

	while(p_child != NULL){
		children++;
		p_child = p_child->p_sibling;
	}

	return children;
}






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
				print_submenu(p_node->current_node);
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
				print_submenu(p_node->current_node);
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
