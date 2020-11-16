/*
 * menu.c
 *
 * Created: 16.09.2020 18:59:34
 *  Author: andrschn
 */ 

#include "menu.h"
#include "external_memory.h"

void print_submenu(Menu_node* p_node){
	oled_clear_all();
	
	Menu_node* p_child = p_node->p_child;
	uint8_t line = 0;
	
	oled_pos(line,4);
	oled_print(p_node->name);
	
	while (p_child != NULL && line<=7){
		line += 2;
		oled_pos(line, 4);
		oled_print(p_child->name);
		p_child = p_child->p_sibling;
	}
}


void oled_menu_high_score_sub(void) {
	
	oled_clear_all();
	oled_pos(0,4);
	oled_print("High score: ");
	char score[10];
	sprintf(score, "%d", (int) xmem_read(0));
	oled_pos(0,70);
	oled_print(score);
	oled_pos(2,4);
	oled_print("Reset");
}



void oled_navigate(direction dir, state *p_node) {
	switch (dir) {
		case UP:
			if (p_node->menu_pos>1){
				oled_clear_frame(p_node->menu_pos*2);
				p_node->menu_pos -=1;
				oled_frame(p_node->menu_pos*2);
				_delay_ms(200);
			}
			break;
		case DOWN:
			if (p_node->menu_pos <menu_children(p_node->current_node, p_node->current_node->p_child)){
				oled_clear_frame(p_node->menu_pos*2);
				p_node->menu_pos +=1;
				oled_frame(p_node->menu_pos*2);
				_delay_ms(200);
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
				//print_submenu(p_node->current_node);
				p_node->current_node->action();
				if (p_node->current_node->p_child != NULL){oled_frame(p_node->menu_pos*2);}
				_delay_ms(200);
			}
			break;
		case BACK:
			if (p_node->current_node->p_parent!=NULL){
				oled_clear_all();
				p_node->current_node = p_node->current_node->p_parent;
				p_node->menu_pos=1;
				//print_submenu(p_node->current_node);
				p_node->current_node->action();
				oled_frame(p_node->menu_pos*2);
				_delay_ms(200);
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
				_delay_ms(200);
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
	_delay_ms(200);
	oled_pos(4,50);
	oled_print("3");
	_delay_ms(800);
	oled_clear_line(4);
	oled_print("2");
	adc_calibrate_joystick(&joystick);
	_delay_ms(800);
	oled_clear_line(4);
	oled_print("1");
	_delay_ms(800);
	oled_clear_line(4);
	oled_clear_line(3);
	oled_pos(4,7);
	oled_print("Joystick calibrated <3");
	
	
}