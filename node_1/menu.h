 /**
 * @file menu.h
 * @author andrschn
 * @date 16.09.2020 18:59:51
 * @brief Library to form a menu system.
 */
#include "oled.h"
#include <stdio.h>
#include "adc.h"

#ifndef MENU_H_
#define MENU_H_

/**
* @brief Declares a function pointer called Menu_function.
*/
typedef void (*Menu_function)();


/**
* Menu_node:
* @name A pointer to the first character in the name.
* @p_parent A pointer to parent node.
* @p_child A pointer to child node.
* @p_sibling A pointer to sibling node.
* @action A function pointer to the action that the menu node shall execute.
*/
typedef struct Menu_node_s{
	const char *name;
	struct Menu_node_s *p_parent;
	struct Menu_node_s *p_child;
	struct Menu_node_s *p_sibling;
	Menu_function action;
}Menu_node;


/**
* state:
* @current_node A pointer to the current menu_node.
* @menu_pos An integer which describes the position in the menu
* chosen by the joystick.
*/
typedef struct{
	Menu_node *current_node;
	int menu_pos;
}state;

//const Menu_node * menu_root_node();
/**
 * @brief Inquire about the children of the menu node pointed
 * to by @p p_node. At return, @p pp_child will have been updated
 * so that @c *pp_child points to the first child of @p p_node.
 * The number of children that @p p_node has is returned.
 *
 * @param[in] p_node Pointer to menu node.
 * @param[out] pp_child Reference to pointer of first child of @p p_node.
 *
 * @return The number of children that @p p_node has.
 * Zero if @p p_node is a leaf node.
 */
int menu_children(const Menu_node * p_node, Menu_node ** pp_child);

Menu_node *add_Menu_node(const char* name,struct Menu_node_s* parent); //not used

void set_child(Menu_node* parent, Menu_node* child); //not used

void set_sibling(Menu_node* menu, Menu_node* sibling); //not used

/**
* @brief A menu navigation system.
* @param [in] dir A direction enum object.
* @param [in] p_node Pointer to menu node.
* @details Uses the direction of the joystick along with the current menu node
* to navigate in the full menu on the OLED.
*/
void oled_navigate(direction dir, state *p_node);

/**
* @brief Initializes the menu set up.
* @param [in] start_state A state object.
* @details Setting the initial state of the menu as Main menu.
*/
void menu_init(state *start_state);

/**
* @brief Draws a square frame on the OLED around a page.
* @param [in] line The page being framed.
*/
void oled_frame(uint8_t line);

/**
* @brief Clears the existing frame at the OLED.
* @param [in] line The line being cleared of frame.
*/
void oled_clear_frame(uint8_t line);

/**
* @brief Prints the Main Menu graphics to the OLED.
* @details Main menu contains the options Games and Settings.
*/
void oled_menu_main(void);

/**
* @brief Prints the Game menu graphics to the OLED.
* @details Game menu contains the options TicTacToe and Ping Pong.
*/
void oled_menu_games(void);

/**
* @brief Prints the Settings menu graphics to the OLED.
* @details Settings menu contains the options Brightness, Difficulty and Calibrate.
*/
void oled_menu_settings(void);

//test
/**
* @brief Prints the Games sub menu to the OLED.
* @details Games sub menu contains the options Play and High Score.
*/
void oled_menu_games_sub(void);

/**
* @brief Prints the Ping Pong's High Score sub menu to the OLED.
* @details High Score sub menu contains the high score and reset function
* of the high score.
*/
void oled_menu_high_score_sub(void);

/**
* @brief Prints the Brightness menu to the OLED.
* @details Brightness menu consists of the options Min, Medium and Max brightness level.
*/
void oled_menu_set_brightness(void);

/**
* @brief Prints the Difficulty menu to the OLED.
* @details Difficulty menu consists of the options Easy and Hard.
*/
void oled_menu_difficulty(void);

/**
* @brief Sets the brightness level on the OLED.
*/
void oled_set_brightness_lvl(uint8_t lvl); //not used

/**
* @brief Sets the brightness level on the OLED to minimum value.
*/
void oled_set_brightness_lvl_min(void);

/**
* @brief Sets the brightness level on the OLED to medium value.
*/
void oled_set_brightness_lvl_med(void);

/**
* @brief Sets the brightness level on the OLED to maximum value.
*/
void oled_set_brightness_lvl_max(void);

/**
* @brief Calibrates the joystick via the OLED menu.
*/
void oled_calibrate_joystick(void);

/**
* @brief Prints the options of stearing mechanisms to the OLED.
* @details The stearing mechanism menu consists of the
* options Joystick and Sliders.
*/
void oled_menu_stearing(void);
/**
* @brief Prints the information on how to stear the game board
* racket by using the joystick.
*/

void oled_menu_joystick_info(void) ;

/**
* @brief Prints the information on how to stear the game board
* racket by using the touch sliders.
*/
void oled_menu_slider_info(void);



#endif /* MENU_H_ */
