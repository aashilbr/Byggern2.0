/*
 * oled.c
 *
 * Created: 16.09.2020 11:36:26
 *  Author: andrschn
 */
#include "oled.h"
#include "fonts.h"

#define OLED_C (*((volatile uint8_t *)(0x1000)))
#define OLED_D (*((volatile uint8_t *)(0x1300)))

void oled_init(){
	OLED_C = 0xae; // display off
	OLED_C = 0xa1; //segment remap
	OLED_C = 0xda; //common pads hardware: alternative
	OLED_C = 0x12;
	OLED_C = 0xc8; //common output scan direction:com63~com0
	OLED_C = 0xa8; //multiplex ration mode:63
	OLED_C = 0x3f;
	OLED_C = 0xd5; //display divide ratio/osc. freq. mode
	OLED_C = 0x80;
	OLED_C = 0x81; //contrast control
	OLED_C = 0x50;
	OLED_C = 0xd9; //set pre-charge period
	OLED_C = 0x21;
	OLED_C = 0x20; //Set Memory Addressing Mode
	OLED_C = 0x02;
	OLED_C = 0xdb; //VCOM deselect level mode
	OLED_C = 0x30;
	OLED_C = 0xad; //master configuration
	OLED_C = 0x00;
	OLED_C = 0xa4; //out follows RAM content
	OLED_C = 0xa6; //set normal display
	OLED_C = 0xaf; // display on
}

void oled_goto_line(uint8_t line){
	OLED_C = 0xb0 + line;
}

void oled_goto_column(uint8_t column){
	OLED_C = 0x00 + (column % 16);
	OLED_C = 0x10 + (column / 16);
}

void oled_clear_line(uint8_t line) {
	oled_goto_line(line);
	for (int i = 0; i < 128; i++) {
		OLED_D = 0x00;
	}
}

void oled_clear_all() {
	for(uint8_t i = 0; i < 8; i++){
		oled_goto_line(i);
		for(uint8_t j = 0; j < 128; j++){
			OLED_D = 0x00;
		}
	}
	oled_pos(0,0);
}

void oled_pos(uint8_t line, uint8_t column) {
	oled_goto_column(column);
	oled_goto_line(line);
}

void oled_print(char * data){
	while(*data != '\0'){
		for(uint8_t i = 0; i < 5; i++){
			OLED_D = pgm_read_byte(&(font[(*data) - 0x20][i]));
		}
	}
}
