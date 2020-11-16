/*
 * oled.h
 *
 * Created: 16.09.2020 11:36:39
 *  Author: andrschn
 */
#ifndef OLED_H_
#define OLED_H_
#include "menu.h"
#include <stdint.h>


/**
* @brief Initializes the OLED
*/
void oled_init();

/**
* @brief Selects the page to start writing from.
* @param [in] line Line to start writing from.
* @details Starts the writing function on the given line.
*/
void oled_goto_line(uint8_t line);

/**
* @brief Selects the column to start writing from.
* @param [in] column Column to start writing from.
* @details Starts the writing function on the given column.
*/
void oled_goto_column(uint8_t column);

/**
* @brief Clears the given line.
* @param [in] line Line to clear.
* @details Writes 0x00 to the given line thereby clearing the
* graphics from the OLED at the given line.
*/
void oled_clear_line(uint8_t line);

/**
* @brief Clears the whole OLED frame.
* @details Writes 0x00 to every OLED page.
*/
void oled_clear_all();

/**
* @brief Selects the page to start writing from.
* @param [in] line Line to start writing from.
* @param [in] column Column to start writing from.
* @details Starts the writing function on the given line and column.
*/
void oled_pos(uint8_t line, uint8_t column);

/**
* @brief Prints the given data to the OLED screen.
* @param [in] data Data to print to the OLED screen.
*/
void oled_print(char * data);

/**
 * @brief Print a menu node on the OLED display. the
 * line indicated by @p selected_item will be selected.
 *
 * @p p_node Points to the root of a (sub)menu. Its
 * @c name parameter will be used as the title of the
 * menu screen, while all its children will be printed
 * underneath. Navigation is handled independently by
 * the rest of the application code to decouple the
 * menu system from the rest of the code base.
 *
 * @param[in] p_node Pointer to a MenuNode that is to
 * be displayed on the OLED.
 * @param selected_item The selected item in the menu.
 * This parameter is zero-indexed, and goes all the way
 * up to the number of children in the menu - 1.
 *
 * @warning A call to @c oled_init must be invoked
 * before this function will operate as expected.
 */
void oled_print_menu(const MenuNode * p_node, uint8_t selected_item);

/**
 * @brief Set the brightness level of the OLED
 * display to the minimum possible setting.
 */
void oled_set_brightness_minimum();

/**
 * @brief Set the brightness level of the OLED
 * display to a medium setting.
 */
void oled_set_brightness_medium();

/**
 * @brief Set the brightness level of the OLED
 * display to the maximum possible setting.
 */
void oled_set_brightness_maximum();

#endif /* OLED_H_ */
