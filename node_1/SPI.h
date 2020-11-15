/*
 * SPI.h
 *
 * Created: 30.09.2020 08:45:09
 *  Author: andrschn
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

void SPI_slave_init(void); //not in use

/**
* @brief Recieves (reads) transmitted data.
* @return Returns data register.
* @details Waits for reception complete and return data register.
*/
char SPI_slave_recieve(void);

#endif /* SPI_H_ */
