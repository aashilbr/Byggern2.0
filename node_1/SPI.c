/*
 * SPI.c
 *
 * Created: 30.09.2020 08:44:58
 *  Author: andrschn
 */ 

#include "SPI.h"


void SPI_master_init(void){
	//cli();
	DDRB |= (1<<DDB5)|(1<<DDB7)|(1<<DDB4); //Sets MOSI and SCK and SS as output
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0); //Enable SPI, master, and clock freq
	
	//SPCR &= ~(1<<SPR1); //Oscillator frequency to f/16
	//SPCR &= ~(1<<CPOL); //Sets to SPI mode 0, to decide clock polarity and phase
	//SPCR &= ~(1<<CPHA); // Sets to SPI mode 0
	
	
	//MCUCR |= (1<<ISC01)|(1<<ISC00); //Interrupt on rising edge
	//GICR |= (1<<INT0); // Enable interrupt on PD2 (pin 12)
	
	PORTB |= (1<<PB4); //Set SS to high
	//sei();
}


	
void SPI_master_transmit(char data){ //Write function
	SPDR = data;
	while (!(SPSR & (1<<SPIF)));
}

char SPI_slave_recieve(void){ //read function
	SPI_master_transmit(0xFF);
	//SPDR =0x00;
	//while(!(SPSR & (1<<SPIF)));
	return SPDR; //returns data register
}

