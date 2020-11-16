/*
 * external_memory.c
 *
 * Created: 02.09.2020 09:17:26
 * Author: andrschn
 */
#include "external_memory.h"
#include <avr/io.h>


#define SIZE_LOW_BYTE 1
#define SIZE_HIGH_BYTE 2
#define MIN_DATA_NR 200
#define MAX_DATA_NR 2240

#define EXT_MEM ((volatile uint8_t *)(0x1800))
#define DATA_ADDRESS 0x1803


void xmem_init(void){
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
}

void xmem_write(uint16_t addr, uint8_t data){
    EXT_MEM[addr] = data;
}


uint8_t xmem_read(uint16_t addr){
    return EXT_MEM[addr];
}

void xmem_save_movement(int8_t x_pos, uint8_t nr){
	printf("x: %d \n \r", x_pos);
	xmem_write(nr, x_pos);
}

uint8_t xmem_check_storing_condition(uint32_t count, uint8_t sampling){
	if(count % sampling == 0
       && count / sampling < MAX_DATA_NR
       && count / sampling > MIN_DATA_NR
    ){
        return 1;
    }
	else {
        return 0;
    }
}

void xmem_write_size(uint16_t data_store_nr){
	int8_t size_low = data_store_nr & 0xff;
	int8_t size_high = (data_store_nr & 0xff00) >> 8;

	xmem_write(SIZE_LOW_BYTE, size_low);
	xmem_write(SIZE_HIGH_BYTE, size_high);
}

uint16_t xmem_read_size(){
	uint8_t size_low = xmem_read(SIZE_LOW_BYTE);
	uint8_t size_high= xmem_read(SIZE_HIGH_BYTE);
	int16_t movement_size = (uint16_t) (size_low | (size_high<<8));
	return movement_size;
}
