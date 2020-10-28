/*
 * adc.c
 *
 * Created: 09.09.2020 15:06:30
 *  Author: andrschn
 */ 

#include "adc.h"
#include "pwm_clock.h"
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

uint8_t adc_joystick_read_button(void){
	return (PIND & (1<<PIND5)) ? 1 : 0;
}

uint8_t adc_read_button_touch_l(void){
	return (PINB & (1<<PINB0)) ? 1:0;
}

uint8_t adc_read_button_touch_r(void){
	return (PINB & (1<<PINB1)) ? 1:0;
}

void adc_joystick_pos(pos_js* js){
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
}	 

direction adc_joystick_dir(pos_js *js){
	if (js->x<-THRESHOLD&&abs(js->x)>abs(js->y)) {return LEFT;}
	if (js->x>THRESHOLD&&js->x>abs(js->y))	{return RIGHT;}
	if (js->y<-THRESHOLD&&abs(js->y)>abs(js->x)) {return DOWN;}
	if (js->y>THRESHOLD&&js->y>abs(js->x))	{return UP;}
	if (!adc_joystick_read_button()){return PRESSED;}
	if (adc_read_button_touch_l()){return BACK;}
	else {return NEUTRAL;}	 //if (js->x==0&&js->y==0)
}

void adc_calibrate(pos_js *js){
	js->x_offset =adc_read(0) -127;
	js->y_offset = adc_read(1) - 127;
}

const char *dir_name[] ={"LEFT", "RIGHT", "UP", "DOWN", "NEUTRAL"};

void printEnum(direction dir){
	printf("dir: %s\n\r", dir_name[dir]);
}
