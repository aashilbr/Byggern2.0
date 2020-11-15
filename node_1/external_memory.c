/*
 * external_memory.c
 *
 * Created: 02.09.2020 09:17:26
 * Author: andrschn
 */
#include "external_memory.h"
#include <avr/io.h>

#define EXT_MEM (((volatile uint8_t *)(0x1000)))

void xmem_init(void){
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
}

void xmem_write(uint8_t data, uint16_t addr){
    EXT_MEM[addr] = data;
}

uint8_t xmem_read(uint16_t addr){
    return EXT_MEM[addr];
}
