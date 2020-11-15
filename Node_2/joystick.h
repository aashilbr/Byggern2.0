/**
* @file joystick.h
* @author sandrgl
* @date  14.10.2020
* @breif Struct with joystick state
*/
#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "sam.h"
#include <stdlib.h>


/**
* @brief A struct for saving the joystick position and the shoot-button state
*/
typedef struct{
	int8_t x; /**< The x position of the joystick, between -100 and 100 */
	int8_t y; /**< The y position of the joystick, between -100 and 100 */
	int8_t shoot; /**< Is 1 if button to shoot is pushed and 0 otherwise */
}pos_js;


pos_js js_pos;



#endif /*JOYSTICK_H_*/
