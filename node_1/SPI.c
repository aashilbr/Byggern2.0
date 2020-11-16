/*
 * SPI.c
 *
 * Created: 30.09.2020 08:44:58
 *  Author: andrschn
 */

#include "SPI.h"


void SPI_master_init(void){
	DDRB |= (1<<DDB5)|(1<<DDB7)|(1<<DDB4); //Sets MOSI and SCK and SS as output
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0); //Enable SPI, master, and clock freq

	PORTB |= (1<<PB4); //Set SS to high
}



void SPI_master_transmit(char data){ //Write function
	SPDR = data;
	while (!(SPSR & (1<<SPIF)));
}

char SPI_slave_recieve(void){ //read function
	SPI_master_transmit(0xFF);
	return SPDR; //returns data register
}
