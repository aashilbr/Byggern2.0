/**
* @file uart.h
* @author aashilbr

*/



#ifndef UART_H_
#define UART_H_
#define F_OSC 4915200
#define BAUD 9600
#define MYUBRR F_OSC/16/BAUD-1

#include <avr/io.h>

/**
* @brief Initializes the UART
* @param [in] ubrr To set the baud rate.
* @details Enables reciever and trancmitter (UCSR0B), and sets
* the frame format (USCR0C)
*/
void UART_Init(unsigned int ubrr);

/**
* @brief data transmission initiated
* by loading the transmit buffer with the data to be transmitted
* @param [in] data
* @details The code waits for empty transmit buffer then puts @p data into
* buffer, sends data
*/
void UART_Transmit(unsigned char data);

/**
* @brief Recieve function for UART
* @return Recieved data from buffer
* @details The Receiver starts data reception when it detects a valid start bit.
* Each bit that follows the start bit will be sampled at the baud rate
*/
unsigned char UART_Recieve(void);

/**
* @brief Print function for UART
* @param [in] data What we want to print to UART

* @details uses @c UART_Transmit to transmit @p data to the UART.
* Then @c fdevopen to print.
*/
void UART_printf(unsigned char data);
#endif /* UART_H_ */
