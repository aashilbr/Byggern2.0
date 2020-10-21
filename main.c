/*
  * Exercise1.c
  *
  * Created: 26.08.2020 08:46:32
  * Author : aashilbr
  */

 #include <avr/io.h>
 //#include <util/delay.h>
 #include "uart.h"
 #include "external_memory.h"
 #include <stdio.h>
 #include "sram_test.h"
 #include "pwm_clock.h"
 #define OUTPUT (6)
#include "adc.h"
#include "oled.h"
#define F_CPU 4915200
#include <util/delay.h>
#include "mcu.h"
#include "menu.h"
#include "tictactoe.h"
#include "SPI.h"
#include "MCP2515_driver.h"
#include "CAN.h"

static void menu_no_action(void){
	oled_print("Activation \n");
	
}

static Menu_node m_menu_nodes[]={
	{
		"MAIN MENU",
		NULL,
		m_menu_nodes + 1,
		NULL,
		oled_menu_main
	},
	{
		"GAMES",
		m_menu_nodes + 0,
		m_menu_nodes + 3,
		m_menu_nodes + 2,
		oled_menu_games
	},
	{
		"SETTINGS",
		m_menu_nodes + 0,
		m_menu_nodes + 5,
		NULL,
		oled_menu_settings
	},
	{
		"Tic Tac Toe",
		m_menu_nodes + 1,
		m_menu_nodes + 8,
		m_menu_nodes + 4,
		oled_menu_games_sub
	},
	{
		"Ping Pong",
		m_menu_nodes + 1,
		m_menu_nodes + 9,
		NULL,
		oled_menu_games_sub
	},
	{
		"Brightness",
		m_menu_nodes + 2,
		m_menu_nodes + 11,
		m_menu_nodes + 6,
		oled_menu_set_brightness
	},
	{
		"Music",
		m_menu_nodes + 2,
		m_menu_nodes + 14,
		m_menu_nodes + 7,
		menu_no_action
	},
	{
		"Calibrate",
		m_menu_nodes + 2,
		NULL,
		NULL,
		menu_no_action//adc_calibrate()
	},
	{
		"Tic Tac Toe - play",
		m_menu_nodes + 3,
		NULL,
		NULL,
		ttt_menu_game
	},
	{
		"High score",
		m_menu_nodes + 4,
		NULL,
		m_menu_nodes + 10,
		oled_menu_high_score_sub
	},
	{
		"Play",
		m_menu_nodes + 4,
		NULL,
		NULL,
		menu_no_action//play pinpong
	},
	{
		"MIN",
		m_menu_nodes + 5,
		NULL,
		m_menu_nodes + 12,
		oled_set_brightness_lvl_min
	},
	{
		"Medium",
		m_menu_nodes + 5,
		NULL,
		m_menu_nodes + 13,
		oled_set_brightness_lvl_med
	},
	{
		"MAX",
		m_menu_nodes + 5,
		NULL,
		NULL,
		oled_set_brightness_lvl_max
	},
	{
		"ON",
		m_menu_nodes + 6,
		NULL,
		m_menu_nodes + 15,
		menu_no_action
	},
	{
		"OFF",
		m_menu_nodes + 6,
		NULL,
		NULL,
		menu_no_action
	}
};


const Menu_node * menu_root_node(){
	return m_menu_nodes;
}

Grid_state game_board[]={NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE};


int main(void)
{
    

	UART_Init(MYUBRR);
	xmem_init();
	pwm_init();
	mcu_init();
	oled_init();
	SPI_master_init();
	CAN_init(MODE_NORMAL);
	

	/*
	oled_clear_all();
	
	pos_js joystick;
	adc_calibrate(&joystick);
	state current_state;
	current_state.current_node=menu_root_node();
	menu_init(&current_state);
	
	Message mess;
	mess.ID = 0b10101010000;
	mess.data[0]=1;
	mess.data[1]=2;
	mess.data[2]=3;
	mess.length = 3;
	
	*/
	
	//printf("%x", mcp_read(MCP_CANINTF));
// 	
	
	//printf("%x", mcp_read(MCP_CANSTAT));
	
	//MENU
	/*
	
	oled_clear_all();
	pos_js joystick;
	adc_calibrate(&joystick);
	state current_state;
	current_state.current_node=menu_root_node();
	menu_init(&current_state);
	
		adc_joystick_pos(&joystick);
		oled_navigate(adc_joystick_dir(&joystick), &current_state);
		
	*/
	
	Message message;
	pos_js joystick;
	adc_calibrate(&joystick);
	
	//CAN_receive_message(&m);
	while(1){
		adc_joystick_pos(&joystick);
		message.data[0]=joystick.x;
		message.data[1]=joystick.y;
		message.length=2;
		printf("X_j: %d \n \r", joystick.x);
		//CAN_send_message(&message);
		printf("X: %d \n \r", message.data[0]);
	}
 	return 0;
}



