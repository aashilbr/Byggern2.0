/*
 * uart.c
 *
 * Created: 26.08.2020 17:09:45
 *  Author: aashilbr
 */

#include "uart.h"


void UART_Init(unsigned int ubrr) {
	UBRR0H = (unsigned char) (ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	UCSR0C = (1<<URSEL0) | (1<<USBS0) | (3<<UCSZ00);
	fdevopen(UART_Transmit, UART_Recieve);


}
void UART_Transmit(unsigned char data) {
	while (!(UCSR0A & (1<<UDRE0))) ;
	UDR0 = data;
}

unsigned char UART_Recieve(void) {
	while (!((UCSR0A) & (1<<RXC0)));
	return UDR0;
}

void UART_printf(unsigned char data) {
	UART_Transmit(data);
	fdevopen(UART_Transmit, UART_Recieve);
}
