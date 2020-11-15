/*
 * external_memory.c
 *
 * Created: 02.09.2020 09:17:26
 *  Author: andrschn
 */ 
#include "external_memory.h"



#define SIZE_LOW_BYTE 1
#define SIZE_HIGH_BYTE 2
#define DATA_ADDRESS 6147 //0x1803
#define SRAM_FAILURE 127


void xmem_init(void){
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
}

void xmem_write(int8_t data, uint16_t addr){
	if(addr>=0 && addr <= 0x7FF){
		volatile char *ext_mem=(char*) BASE_ADDRESS;
		ext_mem[addr]=data;
	}
}


int8_t xmem_read(uint16_t addr){
	if(addr <= 0x7FF){
		volatile char *ext_mem =(char*) BASE_ADDRESS;
		int8_t ret_val= ext_mem[addr];

		return ret_val;
	}
	return SRAM_FAILURE;
}

void xmem_save_movement(int8_t x_pos, uint8_t nr){
	printf("x: %d \n \r", x_pos);
	xmem_write(x_pos,nr);
}

int8_t xmem_read_x_movement(uint8_t nr){
	return xmem_read(3*nr);
}
int8_t xmem_read_y_movement(uint8_t nr){
	return xmem_read(3*nr+1);
}
uint8_t xmem_read_button_movement(uint8_t nr){
	return xmem_read(3*nr+2);
}

int xmem_check_storing_condition(int count, int frequency){
	if(count%frequency==0 && count/frequency<MAX_DATA_NR && count/frequency>MIN_DATA_NR){return 1;}
	else{return 0;	}
}

void xmem_write_size(uint16_t data_store_nr){
	int8_t size_low = data_store_nr&0xff;
	int8_t size_high = (data_store_nr&0xff00)>>8;
	xmem_write(size_low,SIZE_LOW_BYTE);
	xmem_write(size_high, SIZE_HIGH_BYTE);
}

int16_t xmem_get_size(void){
	uint8_t size_low = xmem_read(SIZE_LOW_BYTE);
	uint8_t size_high= xmem_read(SIZE_HIGH_BYTE);
	int16_t movement_size = (int16_t) (size_low|(size_high<<8));
	return movement_size;
}
/*
void delete_movement(uint8_t size){
	for (int i = 0; i<size; i++){
		xmem_write(0,0x1803+i);
	}
}*/

