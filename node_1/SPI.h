/**
* @file node_1/SPI.h
* @author andrschn
* @date 30.09.2020 08:45:09
* @brief Library for serial peripheral interface.
*/

#ifndef SPI_H_
#define SPI_H_
#include <avr/io.h>
#include <avr/interrupt.h>
/**
* @brief Initializes SPI.
* @details Sets MOSI, SCK and SS as outputs.
* Enable SPI, Master and clock frequency. Set SS high.
*/
void SPI_master_init(void);

/**
* @brief Transmits (writes) data.
* @param [in] data Data to be transmitted.
* @details Transmits data and wait for transmission to complete.
*/
void SPI_master_transmit(char data);

/**
* @brief Recieves (reads) transmitted data.
* @return Returns data register.
* @details Waits for reception complete and return data register.
*/
char SPI_slave_recieve(void);

#endif /* SPI_H_ */
