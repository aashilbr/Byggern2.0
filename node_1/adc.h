/*
 * joystick.h
 *
 * Created: 09.09.2020 14:11:12
 *  Author: andrschn
 */


#ifndef ADC_H_
#define ADC_H_
#define F_CPU 4915200
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define THRESHOLD 50
/**
* pos_js:
* @x Signed integer containing the x-coordinate value of the joystick.
* @y Signed integer containing the y-coordinate value of the joystick.
* @x_offset Offset of x-value from calibration.
* @y_offset Offset of y-value from calibration.
*/
typedef struct{
	int8_t x;
	int8_t y;
	int8_t x_offset;
	int8_t y_offset;
}pos_js;

pos_js joystick; 
/**
* direction:
* @brief An enum containing the direction of the joystick.
*/
typedef enum {LEFT, RIGHT, UP, DOWN, NEUTRAL, PRESSED, BACK, GAME_OVER} direction; 

/**
* @brief Initializes the ADC.
* @details Sets the clock signal needed for the ADC.
*/
void adc_init (void);

/**
* @brief Reads from the ADC.
* @param [in] channel Channel from ADC that we want to read from.
* @return Returns the read value from the given channel on the ADC.
*/
uint8_t adc_read(uint8_t channel); //volatile

uint8_t adc_read_joystick_x();

uint8_t adc_read_joystick_y();

uint8_t adc_read_slider_left();

uint8_t adc_read_slider_right();

/**
* @brief Reads the value of the joystick button.
* @return Returns 0 if the joystick button is pressed, 1 otherwise.
*/
uint8_t adc_joystick_read_button(void);

/**
* @brief Reads the value of the left touch button.
* @return Returns 1 if the left touch button is pressed, 0 otherwise.
*/
uint8_t adc_read_button_touch_l(void);

/**
* @brief Reads the value of the right touch button.
* @return Returns 1 if the right touch button is pressed, 0 otherwise.
*/
uint8_t adc_read_button_touch_r(void);

/**
* @brief Calibrates the joystick position.
* @param [in] js A pointer to a pos_js object.
* @details Calibrates the joystick such that when the
* joystick is in neutral, its x and y values are 0.
*/
void adc_calibrate_joystick(pos_js *js);

void adc_joystick_pos(pos_js* js);

void adc_slider_pos(pos_js* js);
/**
* @brief Gets the direction of the joystick.
* @param [in] js A pointer to a pos_js object.
* @return Returns the direction of the joystick.
*/
direction adc_joystick_dir(pos_js *js);

/**
* @brief Gets the position of the joystick.
* @param [in] js A pointer to a pos_js object.
* @details The position values are given in percentage of the maximum
* x and y position values.
*/
void adc_joystick_pos(pos_js *js);

/**
* @brief Prints an enum.
* @param [in] dir An enum of directions.
*/
void printEnum(direction dir);

#endif /* ADC_H_ */
