/*
 * oled.c
 *
 * Created: 16.09.2020 11:36:26
 *  Author: andrschn
 */ 
#include "oled.h"
#include "fonts.h"
void oled_init()
{
	write_c(0xae); // display off
	write_c(0xa1); //segment remap
	write_c(0xda); //common pads hardware: alternative
	write_c(0x12);
	write_c(0xc8); //common output scan direction:com63~com0
	write_c(0xa8); //multiplex ration mode:63
	write_c(0x3f);
	write_c(0xd5); //display divide ratio/osc. freq. mode
	write_c(0x80);
	write_c(0x81); //contrast control
	write_c(0x50);
	write_c(0xd9); //set pre-charge period
	write_c(0x21);
	write_c(0x20); //Set Memory Addressing Mode
	write_c(0x02);
	write_c(0xdb); //VCOM deselect level mode
	write_c(0x30);
	write_c(0xad); //master configuration
	write_c(0x00);
	write_c(0xa4); //out follows RAM content
	write_c(0xa6); //set normal display
	write_c(0xaf); // display on
}

void write_c(uint8_t data){
	volatile char* oled_c= (char*) OLED_BASE_C_ADDRESS;
	oled_c[0]=data;
}


void oled_goto_line(uint8_t line){
	write_c(0xb0+line);	
}

void oled_goto_column(uint8_t column){
	write_c(0x00 +(column%16));
	write_c(0x10+(column/16));
}

void oled_write_data(char data){ //volatile
	volatile char* oled_d= (char*) OLED_BASE_D_ADDRESS;
	oled_d[0]=data;
}

void oled_clear_all(void) {
	for (int i=0; i<8; i++){
		oled_goto_line(i);
		for (int j=0; j<128; j++){
			oled_write_data (0x00);
			
		}
	}
	oled_pos(0,0);
}
void oled_clear_line(uint8_t line) {
	oled_goto_line(line);
	for (int i=0; i<128; i++) {
		oled_write_data(0x00);
	}
}


void oled_pos(uint8_t line,uint8_t column) {
	oled_goto_column(column);
	oled_goto_line(line);
}

int oled_font_index(char data){
	int buffer_value=32;
	int index =data- buffer_value;
	return index;
}

void oled_print(char* data){
	for (int i=0; data[i]!= '\0'; i++){
		for (int j=0; j<5;j++){
			int index= oled_font_index(data[i]);
			oled_write_data(pgm_read_byte(&(font5[index][j])));
		}
	}
}
