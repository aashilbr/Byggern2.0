/*
 * oled.h
 *
 * Created: 16.09.2020 11:36:39
 *  Author: andrschn
 */


#ifndef OLED_H_
#define OLED_H_
#define OLED_BASE_C_ADDRESS 0x1000
#define OLED_BASE_D_ADDRESS 0x1300
#include <avr/io.h>


/**
* @brief Writes command to OLED registers.
* @param [in] data Data command to write.
* @details Writes the given data command to
* the OLEDs command registers.
*/
void write_c(uint8_t data);

/**
* @brief Initializes the OLED
*/
void oled_init();

//void oled_reset();

//void oled_home();

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
void oled_clear_all(void);

/**
* @brief Selects the page to start writing from.
* @param [in] line Line to start writing from.
* @param [in] column Column to start writing from.
* @details Starts the writing function on the given line and column.
*/
void oled_pos(uint8_t line,uint8_t column);

/**
* @brief Writes data to OLED registers.
* @param [in] data Data to write to OLED.
* @details Writes the given data to the OLED data registers.
*/
void oled_write_data(char data);

/**
* @brief Prints the given data to the OLED screen.
* @param [in] data Data to print to the OLED screen.
*/
void oled_print(char* data);

/**
* @brief Find the font index from char value.
* @param [in] data Char we need the font index for.
*/
int oled_font_index(char data);

#endif /* OLED_H_ */
