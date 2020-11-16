/**
* @file node_1/oled.h
* @author andrschn
* @date 16.09.2020 11:36:39
* @brief Library for OLED functions.
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
* @details Settings menu contains the options Brightness, Music and Calibrate.
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
* @details High Score sub menu contains the options high score and reset.
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

#endif /* OLED_H_ */
