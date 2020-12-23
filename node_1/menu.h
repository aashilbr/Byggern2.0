/**
* @file node_1/menu.h
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
* @brief Prints the current menu subsystem to the OLED.
* @param [in] p_node A pointer to a Menu_node object.
*/
void print_submenu(Menu_node* p_node);


/**
* @brief Calibrates the joystick via the OLED menu.
*/
void oled_calibrate_joystick(void);


#endif /* MENU_H_ */
