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
#include "pingpong.h"
#include "timer.h"

#include <avr/pgmspace.h>

static void menu_no_action(void){
	oled_print("Activation \n");
	
}
//
//static Menu_node m_menu_nodes[]={
	//{
		//"MAIN MENU",
		//NULL,
		//m_menu_nodes + 1,
		//NULL,
		//oled_menu_main
	//},
	//{
		//"GAMES",
		//m_menu_nodes + 0,
		//m_menu_nodes + 3,
		//m_menu_nodes + 2,
		//oled_menu_games
	//},
	//{
		//"SETTINGS",
		//m_menu_nodes + 0,
		//m_menu_nodes + 5,
		//NULL,
		//oled_menu_settings
	//},
	//{
		//"Tic Tac Toe",
		//m_menu_nodes + 1,
		//NULL,
		//m_menu_nodes + 4,
		//ttt_menu_game
	//},
	//{
		//"Ping Pong",
		//m_menu_nodes + 1,
		//m_menu_nodes + 9,
		//NULL,
		//oled_menu_games_sub
	//},
	//{
		//"Brightness",
		//m_menu_nodes + 2,
		//m_menu_nodes + 11,
		//m_menu_nodes + 6,
		//oled_menu_set_brightness
	//},
	//{
		//"Set Difficulty",
		//m_menu_nodes + 2,
		//m_menu_nodes + 14,
		//m_menu_nodes + 7,
		//oled_menu_difficulty
	//},
	//{
		//"Calibrate",
		//m_menu_nodes + 2,
		//NULL,
		//NULL,
		//oled_calibrate_joystick
	//},
	//{
		//"Tic Tac Toe - play",
		//m_menu_nodes + 3,
		//NULL,
		//NULL,
		//ttt_menu_game
	//},
	//{
		//"Stearing",
		//m_menu_nodes + 4,
		//m_menu_nodes + 16,
		//NULL,
		//oled_menu_stearing
	//},
	//{
		//"High score",//!!!!!!!!!!!!!!
		//m_menu_nodes + 4,
		//NULL,
		//NULL,
		//oled_menu_high_score_sub
	//},
	//{
		//"MIN",
		//m_menu_nodes + 5,
		//NULL,
		//m_menu_nodes + 12,
		//oled_set_brightness_lvl_min
	//},
	//{
		//"Medium",
		//m_menu_nodes + 5,
		//NULL,
		//m_menu_nodes + 13,
		//oled_set_brightness_lvl_med
	//},
	//{
		//"MAX",
		//m_menu_nodes + 5,
		//NULL,
		//NULL,
		//oled_set_brightness_lvl_max
	//},
	//{
		//"Easy",
		//m_menu_nodes + 6,
		//NULL,
		//m_menu_nodes + 15,
		//oled_easy_pid
	//},
	//{
		//"Hard",
		//m_menu_nodes + 6,
		//NULL,
		//NULL,
		//oled_hard_pid
	//},
	//{
		//"Joystick stearing",
		//m_menu_nodes + 9,
		//m_menu_nodes + 18,
		//m_menu_nodes + 17,
		//oled_menu_joystick_info
	//},
	//{
		//"Slider stearing",
		//m_menu_nodes + 9,
		//m_menu_nodes + 19,
		//NULL,
		//oled_menu_slider_info
	//},
	//{
		//"Play Joystick",
		//m_menu_nodes + 4,
		//NULL,
		//m_menu_nodes + 19,
		//pingpong_play_with_joystick
	//},
	//{
		//"Play sliders",
		//m_menu_nodes + 4,
		//NULL,
		//NULL,
		//pingpong_play_with_sliders
	//}
//};

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
		NULL,
		m_menu_nodes + 4,
		ttt_menu_game
	},
	{
		"Ping Pong",
		m_menu_nodes + 1,
		m_menu_nodes + 8,
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
		"Set Difficulty",
		m_menu_nodes + 2,
		m_menu_nodes + 13,
		m_menu_nodes + 7,
		oled_menu_difficulty
	},
	{
		"Calibrate",
		m_menu_nodes + 2,
		NULL,
		NULL,
		oled_calibrate_joystick
	},
	{
		"Stearing",
		m_menu_nodes + 4,
		m_menu_nodes + 15,
		m_menu_nodes + 9,
		oled_menu_stearing
	},
	{
		"High score",
		m_menu_nodes + 4,
		m_menu_nodes + 17,
		NULL,
		oled_menu_high_score_sub
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
		"Easy",
		m_menu_nodes + 6,
		NULL,
		m_menu_nodes + 14,
		oled_easy_pid
	},
	{
		"Hard",
		m_menu_nodes + 6,
		NULL,
		NULL,
		oled_hard_pid
	},
	{
		"Joystick stearing",
		m_menu_nodes + 8,
		NULL,
		m_menu_nodes + 16,
		pingpong_play_with_joystick
	},
	{
		"Slider stearing",
		m_menu_nodes + 8,
		NULL,
		NULL,
		pingpong_play_with_sliders
	},
	{
		"Reset highscore",
		m_menu_nodes + 9,
		NULL,
		NULL,
		reset_highscore
	}
};


const Menu_node * menu_root_node(){
	return m_menu_nodes;
}

Grid_state game_board[]={NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE};


int main(void){
	UART_Init(MYUBRR);
	xmem_init();
	pwm_init();
	mcu_init();
	oled_init();
	SPI_master_init();
	CAN_init(MODE_NORMAL);
	timer_init();
	
	
	oled_clear_all();
	adc_calibrate_joystick(&joystick);
	state current_state;
	current_state.current_node=menu_root_node();
	menu_init(&current_state);	
	adc_calibrate_joystick(&joystick);
	
	while(1){
		
		adc_joystick_pos(&joystick);
		oled_navigate(adc_joystick_dir(&joystick), &current_state);
		
	}
 	return 0;
}



