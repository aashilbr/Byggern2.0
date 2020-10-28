/*
 * CAN.c
 *
 * Created: 30.09.2020 14:01:09
 *  Author: andrschn
 */ 

#include "CAN.h"

uint8_t CAN_init(uint8_t mode){
	uint8_t value;
	SPI_master_init();
	mcp_reset();
	//mcp_write(0x0f, 0x80);
	
	
	value = mcp_read(MCP_CANSTAT); //self-test
	if ((value & MODE_MASK) != MODE_CONFIG){
		printf("MCP2515 is NOT in configuration mode after reset!\n\r");
		return 1;
	}
	mcp_bit_modify(MCP_CNF3, 0b00000111, 0x01);		//PS2: 2*Tq
		
	mcp_bit_modify(MCP_CNF2, 0b00000111, 0x05);		//PRSEG: 6*Tq
	mcp_bit_modify(MCP_CNF2, 0b00111000, 0x06<<3);	//PHSEG1: 7*Tq
	mcp_bit_modify(MCP_CNF2, 0b01000000, 0x00<<6);	//SAM: 0 Busline sample once
	mcp_bit_modify(MCP_CNF2, 0b10000000, 0x01<<7);	//BTLMODE: Length of PS2 determined by PHSEG2 bits in CNF3
		
	mcp_bit_modify(MCP_CNF1, 0b11000000, 0x00<<6);	//SJW: 1*Tq
	mcp_bit_modify(MCP_CNF1, 0b00111111, 0x03);		//BRP: Tq=8/F_osc=95ns
	

	
	if(mcp_read(MCP_CNF1)!=0x03){
		printf("CNF1 is NOT in configured!\n\r");
	}
	if(mcp_read(MCP_CNF2)!=0b10110101){
		printf("CNF2 is NOT in configured!\n\r");
	}
	if(mcp_read(MCP_CNF3)!=0x01){
		printf("CNF3 is NOT in configured!\n\r");
	}
	
	//mcp_bit_modify(MCP_RXB0CTRL, 0x60, 0x00);
	mcp_write(MCP_CANCTRL, mode); 
	//mcp_bit_modify(MCP_CANCTRL, 0x00, mode);
	value = mcp_read(MCP_CANSTAT);
	uint8_t mode_bits = (value & MODE_MASK);
	if (mode_bits != mode){
		printf("MCP2515 is NOT in correct mode!\n\r");
		return 1;	
	}
	return 0;
}

void CAN_send_message(Message *message){
	
	while (CAN_transmit_request()){}
	mcp_write(0x31, ((message->ID) >>3)); //0x31 ==MCP_TXB0SIDH
	mcp_write(0x32, ((message->ID) << 5));	//0x32 ==MCP_TXB0SIDL
	mcp_write(0x35 , message->length ); //MCP_TXB0DLC
	for (uint8_t i=0; i<(message->length); i++){
		mcp_write(0x36 +i , message->data[i]); //TXB0D0 -transmit buffer 0  data byte i

	}
	mcp_request_to_send(0);
}

uint8_t CAN_transmit_request(void){
	uint8_t reg= mcp_read(MCP_TXB0CTRL);
	return (reg & (1<<3)) ? 1 : 0;
}

void CAN_receive_message(Message *message){
	uint8_t receive_buffer = (mcp_read(MCP_CANINTF) & 0x3) -1; //check which buffer received a buffer
	
	uint8_t status = mcp_read_status();
	//printf("status %d", status);
	//while (status & 0x01){}
	message->ID = ((mcp_read(MCP_RXB0SIDH +(16*receive_buffer))<<3) | (mcp_read(0x62+(16*receive_buffer)) >> 5)); //RXB0SIDL
	//printf("%d", message.ID);
	message->length = (mcp_read(0x65+(16*receive_buffer))); //RXB0DLC
	for (uint8_t i = 0; i < message->length; i++) {
		message->data[i] = mcp_read((0x66+(16*receive_buffer))+ i);//MCP_RXB0D0
	}
}