/*
 * menu.h
 *
 * Created: 16.09.2020 18:59:51
 * Author: andrschn
 */
 /**
 * @file
 * @brief Library to form a menu system.
 */
#ifndef MENU_H_
#define MENU_H_
#include <stdint.h>

/**
* @brief Function instructions returned by each menu node.
*/
typedef enum {
	MENU_ENTER_SUBMENU,

	MENU_PLAY_TIC_TAC_TOE,
	MENU_PLAY_PING_PONG_JOYSTICK,
	MENU_PLAY_PING_PONG_SLIDER,
	MENU_PLAY_PING_PONG_MEMORY,

	MENU_HIGHSCORE_RESET,

	MENU_SET_DIFFICULTY_EASY,
	MENU_SET_DIFFICULTY_HARD,

	MENU_SET_BRIGHTNESS_MIN,
	MENU_SET_BRIGHTNESS_MEDIUM,
	MENU_SET_BRIGHTNESS_MAX,

	MENU_CALIBRATE
} MenuFunction;

/**
* Menu_node:
* @name A pointer to the first character in the name.
* @p_parent A pointer to parent node.
* @p_child A pointer to child node.
* @p_sibling A pointer to sibling node.
* @action A function pointer to the action that the menu node shall execute.
*/
typedef struct MenuNode_s {
	const char * name;
	struct MenuNode_s * p_parent;
	struct MenuNode_s * p_child;
	struct MenuNode_s * p_sibling;
	MenuFunction action;
} MenuNode;

/**
 * @brief Retrieve a pointer to the root of the
 * menu system. This pointer may then be used for
 * the other functions in this module.
 *
 * @return A pointer to the root of the menu nodes
 * contained in the application menu.
 */
const MenuNode * menu_root_node();

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
uint8_t menu_children(const MenuNode * p_node, MenuNode ** pp_child);

#endif /* MENU_H_ */
