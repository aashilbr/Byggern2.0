/*
 * external_memory.c
 *
 * Created: 02.09.2020 09:17:26
 *  Author: andrschn
 */ 
#include "external_memory.h"

void xmem_init(void){
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
}

void xmem_write(uint8_t data, uint16_t addr){
	volatile char *ext_mem=(char*) BASE_ADDRESS;
	//PORTE |= (1<<PE1); //ALE high
	//PORTD &= ~(1 << PD6);//setter write lav
	//se datasheet
	ext_mem[addr]=data;
}



uint8_t xmem_read(uint16_t addr){
	volatile char *ext_mem =(char*) BASE_ADDRESS;
	//PORTE |= (1<<PE1); //ALE high
	uint8_t ret_val= ext_mem[addr];
	//PORTD &= ~(1 << PD7);//setter rd lav
	
	return ret_val;
}