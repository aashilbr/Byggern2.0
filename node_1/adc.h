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
#include <stdint.h>

typedef enum {
    JOYSTICK_INVALID,
    JOYSTICK_LEFT,
    JOYSTICK_RIGHT,
    JOYSTICK_UP,
    JOYSTICK_DOWN,
    JOYSTICK_NEUTRAL
} JoystickDirection;

/**
 * Joystick:
 * @x Signed int containing horizontal axis of joystick.
 * @y Signed int containing vertical axis of joystick.
 * @x_offset Offset on horizontal from calibration.
 * @x_offset Offset on vertical from calibration.
 * @direction Direction of the joystick.
 * @direction_changed 1 if direction has changed since
 * the last update, 0 if not.
 */
typedef struct {
    int8_t x;
    int8_t y;
    int8_t x_offset;
    int8_t y_offset;
    JoystickDirection direction;
    uint8_t direction_changed;
} Joystick;

/**
* @brief Initializes the ADC.
*
* Sets the clock signal needed for the ADC.
*/
void adc_init();

/**
 * @brief Read the joystick, and update all
 * the fields of @p p_joystick accordingly.
 *
 * @param[out] p_joystick Pointer to a joystick
 * struct to be altered.
 */
void adc_read_joystick(Joystick * p_joystick);


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

#endif /* ADC_H_ */
