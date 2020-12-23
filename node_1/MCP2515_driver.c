/*
 * MCP2515_driver.c
 *
 * Created: 30.09.2020 11:06:02
 *  Author: andrschn
 */ 
#include "MCP2515_driver.h"

uint8_t mcp_read(uint8_t address){
	PORTB &= ~(1<<PB4); //activate slave
	uint8_t data;
	SPI_master_transmit(MCP_READ);
	SPI_master_transmit(address);
	data = SPI_slave_recieve();
	PORTB |= (1<<PB4); //deactivate slave
	return data;
}

void mcp_write(uint8_t address, uint8_t data){
	PORTB &= ~(1<<PB4); //activate slave
	
	SPI_master_transmit(MCP_WRITE);
	SPI_master_transmit(address);
	SPI_master_transmit(data);
	
	PORTB |= (1<<PB4); //deactivate slave
}

void mcp_request_to_send(uint8_t buffer){
	PORTB &= ~(1<<PB4); //activate slave
	uint8_t instruction =0b10000000;
	SPI_master_transmit(instruction | (1<<buffer));
	PORTB |= (1<<PB4); //deactivate slave
}

uint8_t mcp_read_status(){
	PORTB &= ~(1<<PB4); //activate slave
	SPI_master_transmit(MCP_READ_STATUS);
	uint8_t status = SPI_slave_recieve();
	PORTB |= (1<<PB4); //deactivate slave
	return status;
}

void mcp_bit_modify(uint8_t address, uint8_t mask, uint8_t data){
	PORTB &= ~(1<<PB4); //activate slave
	SPI_master_transmit(MCP_BITMOD);
	SPI_master_transmit(address);
	SPI_master_transmit(mask);
	SPI_master_transmit(data);	
	
	PORTB |= (1<<PB4); //deactivate slave
}

void mcp_reset(){
	PORTB &= ~(1<<PB4); //activate slave
	SPI_master_transmit(MCP_RESET);
	PORTB |= (1<<PB4); //deactivate slave
	//_delay_ms(20);
}