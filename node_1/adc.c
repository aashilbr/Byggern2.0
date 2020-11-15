/*
 * adc.c
 *
 * Created: 09.09.2020 15:06:30
 *  Author: andrschn
 */ 

#include "adc.h"
#include "pwm_clock.h"
#include "pingpong.h"
#include <avr/io.h>

void adc_init (void){
	pwm_init();
}

uint8_t adc_read(uint8_t channel){
	volatile char* adc= (char*) 0x1400;
	adc[0]=0x80|channel;
	_delay_ms(2);
	uint8_t return_value=adc[8];
	return return_value;
} 
uint8_t adc_read_joystick_x(){
	return adc_read(0);
}

uint8_t adc_read_joystick_y(){
	return adc_read(1);
}

uint8_t adc_read_slider_left(){
	return adc_read(3);
}

uint8_t adc_read_slider_right(){
	return adc_read(2);
}


uint8_t adc_joystick_read_button(void){
	return (PIND & (1<<PIND5)) ? 1 : 0;
}

uint8_t adc_read_button_touch_l(void){
	return (PINB & (1<<PINB0)) ? 1:0;
}

uint8_t adc_read_button_touch_r(void){
	return (PINB & (1<<PINB1)) ? 1:0;
}


adc_update_pos(uint8_t x_pos, uint8_t y_pos,pos_js* js){
	if (x_pos <= js->x_offset){
		js->x= ((x_pos+ js->x_offset-127)*100/(127-js->x_offset));
		if (abs(js->x)>100){js->x=-100;}
	}
	if (x_pos > js->x_offset){
		js->x= ((x_pos- js->x_offset-127)*100/(127-js->x_offset));
		if (abs(js->x)>100){js->x=100;}
	}
	if (y_pos <= js->y_offset){
		js->y= ((y_pos+ js->y_offset-127)*100/(127-js->y_offset));
		if (abs(js->y)>100){js->y=-100;}
	}
	if (y_pos > js->y_offset){
		js->y= ((y_pos- js->y_offset-127)*100/(127-js->y_offset));
		if (abs(js->y)>100){js->y=100;}
	}
}

void adc_joystick_pos(pos_js* js){
	uint8_t x_pos=adc_read(0);//-js->x_offset;
	uint8_t y_pos=adc_read(1); //- js->y_offset;
	adc_update_pos(x_pos,y_pos,js);
}

void adc_slider_pos(pos_js* js){
	uint8_t x_pos=adc_read_slider_right();
	uint8_t y_pos=-adc_read_slider_left(); 
	adc_update_pos(x_pos,y_pos,js);
}


/*void adc_joystick_pos(pos_js* js){
	uint8_t x_pos=adc_read(0);//-js->x_offset;
	uint8_t y_pos=adc_read(1); //- js->y_offset;
	if (x_pos <= js->x_offset){
		js->x= ((x_pos+ js->x_offset-127)*100/(127-js->x_offset));
		if (abs(js->x)>100){js->x=-100;}
	}
	if (x_pos > js->x_offset){
		js->x= ((x_pos- js->x_offset-127)*100/(127-js->x_offset));
		if (abs(js->x)>100){js->x=100;}
	}
	if (y_pos <= js->y_offset){
		js->y= ((y_pos+ js->y_offset-127)*100/(127-js->y_offset));
		if (abs(js->y)>100){js->y=-100;}
	}
	if (y_pos > js->y_offset){
		js->y= ((y_pos- js->y_offset-127)*100/(127-js->y_offset));
		if (abs(js->y)>100){js->y=100;}
	}
}	 */

direction adc_joystick_dir(pos_js *js){
	if (adc_read_button_touch_l()){return BACK;}
	if (!adc_joystick_read_button()){return PRESSED;}
	if (js->x<-THRESHOLD&&abs(js->x)>abs(js->y)) {return LEFT;}
	if (js->x>THRESHOLD&&js->x>abs(js->y))	{return RIGHT;}
	if (js->y<-THRESHOLD&&abs(js->y)>abs(js->x)) {return DOWN;}
	if (js->y>THRESHOLD&&js->y>abs(js->x))	{return UP;}
	else {return NEUTRAL;}	 
}

void adc_calibrate_joystick(pos_js *js){
	js->x_offset =adc_read_joystick_x() -127;
	js->y_offset = adc_read_joystick_y() - 127;
}

const char *dir_name[] ={"LEFT", "RIGHT", "UP", "DOWN", "NEUTRAL"};

void printEnum(direction dir){
	printf("dir: %s\n\r", dir_name[dir]);
}
