/*
 * joystick.h
 *
 * Created: 14.10.2020 09:32:51
 *  Author: sandrgl
 */ 

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "sam.h"
#include <stdlib.h>

typedef struct{
	int8_t x;
	int8_t y;
	int8_t shoot;
}pos_js;


pos_js js_pos;



#endif /*JOYSTICK_H_*/