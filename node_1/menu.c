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

uint8_t menu_children(const MenuNode * p_node, MenuNode ** pp_child){
	MenuNode * p_child = p_node->p_child;
	uint8_t children = 0;

	while(p_child != NULL){
		children++;
		p_child = p_child->p_sibling;
	}

	return children;
}
