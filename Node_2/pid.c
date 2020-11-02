 /* 
 *pid.c
 *
 * Created: 28.10.2020 20:52:39
 *  Author: sandrgl
 */ 

#include "pid.h"
#include "joystick.h"
#include "motor_controller.h"
#define p_factor 1
#define i_factor 1
#define d_factor 1
#define dt 0.084


void TC0_Handler(){
	if (TC0->TC_QISR){
		int16_t ref = js_pos.x;
		int16_t measured = read_encoder();
		
		int16_t error = ref - measured;
	}
}

