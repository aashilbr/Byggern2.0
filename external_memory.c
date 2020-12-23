/*
 * external_memory.c
 *
 * Created: 02.09.2020 09:17:26
 *  Author: andrschn
 */ 
#include "external_memory.h"


#define MIN_DATA_NR 100
#define MAX_DATA_NR 2040+MIN_DATA_NR
#define SIZE_LOW_BYTE 0x1801
#define SIZE_HIGH_BYTE 0x1802
#define DATA_ADDRESS 0x1803


void xmem_init(void){
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
}

void xmem_write(uint8_t data, uint16_t addr){
	volatile char *ext_mem=(char*) BASE_ADDRESS;
	ext_mem[addr]=data;
}



uint8_t xmem_read(uint16_t addr){
	volatile char *ext_mem =(char*) BASE_ADDRESS;
	uint8_t ret_val= ext_mem[addr];

	return ret_val;
}

void xmem_save_movement(int8_t x_pos, int8_t y_pos, uint8_t button, uint8_t nr){
	if (nr<MAX_DATA_NR&&nr>MIN_DATA_NR)	{
		xmem_write(x_pos,DATA_ADDRESS+3*nr);
		xmem_write(y_pos,DATA_ADDRESS+3*nr+1);
		xmem_write(button,DATA_ADDRESS+3*nr+2);
	}
}

int8_t xmem_read_x_movement(uint8_t nr){
	return xmem_read(DATA_ADDRESS+3*nr);
}
int8_t xmem_read_y_movement(uint8_t nr){
	return xmem_read(DATA_ADDRESS+3*nr+1);
}
uint8_t xmem_read_button_movement(uint8_t nr){
	return xmem_read(DATA_ADDRESS+3*nr+2);
}
int xmem_check_storing_condition(int count, int frequency){
	if(count%frequency==0){return 1;}
	else{return 0;	}
}

void xmem_write_size(int data_store_nr){
	uint8_t size_low = (data_store_nr*3)&0xff;
	uint8_t size_high = ((data_store_nr*3)&0xff00)>>8;
	xmem_write(size_low,SIZE_LOW_BYTE);
	xmem_write(size_high,SIZE_HIGH_BYTE);
}

int xmem_get_size(void){
	uint8_t size_low = xmem_read(SIZE_LOW_BYTE);
	uint8_t size_high = xmem_read(SIZE_HIGH_BYTE);
	int movement_size = size_low|(size_high<<8);
	return movement_size;
}
/*
void delete_movement(uint8_t size){
	for (int i = 0; i<size; i++){
		xmem_write(0,0x1803+i);
	}
}*/

