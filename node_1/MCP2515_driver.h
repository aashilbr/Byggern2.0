/**
* @file MCP2515_driver.h
* @author Andrea Schell
* @date 30.09.2020 11:05:32
* @copyright 2020 Joe Bloggs
* @brief DRiver for controlling the MCP2515.
*/



#include "SPI.h"
#include "mcp2515.h"
#define F_CPU 4915200
#include <util/delay.h>

#ifndef MCP2515_DRIVER_H_
#define MCP2515_DRIVER_H_

/**
* @brief Function for reading from MCP2515
* @param [in] address The 8-bit address sent to SPI write function
* @return data. The data frmo SPI send function.
* @details The READ instruction is started by lowering the CS pin.
* The READ instruction is then sent to the MCP2515 followed by
* @p address. Next, the data stored in the register
* at the selected address will be shifted out on the SO pin.
*/
uint8_t mcp_read(uint8_t address);

/**
* @brief Function for writing to MCP2515.
* @param [in] address Address
* @param [in] data What we ar going to write to the MCP2515.
* @details Write @p data to register beginning at @p address.
*/
void mcp_write(uint8_t address, uint8_t data);

/**
* @brief Function used to initiate message transmission for
* one or more of the transmit buffers.
* @param [in] buffer Number of the buffer used, either 0, 1 of 2.
* @details Bitwise or of the request-to-send-byte and left shifted buffer-value
* to set one of the least three bytes of the instruction.
*/
void mcp_request_to_send(uint8_t buffer);

/**
* @brief Function that allows single instruction
* access to some of the often used status bits for message
* reception and transmission.
* @return Returns 8-bit of data that contains the status.
* @details Quick polling command that reads several status bits for
* transmit and receive functions.
*/
uint8_t mcp_read_status();

/**
* @brief Function for setting or clearing individual
* bits in specific status and control registers
* @param [in] address Address byte
* @param [in] mask determines which bits in the register will
* be allowed to change. A ‘1’ in the mask byte will allow a bit
* in the register to change, while a ‘0’ will not.
* @param [in] data determines what value the modified bits in the register
* will be changed to. A ‘1’ in the data byte
* will set the bit and a ‘0’ will clear the bit, provided that
* the mask for that bit is set to a ‘1’
* @return <return_description>
*/
void mcp_bit_modify(uint8_t address, uint8_t mask, uint8_t data);

/**
* @brief Function to re-initialize internal registers of the MCP2515.
* @details Sets Configuration mode.
*/
void mcp_reset();

#endif /* MCP2515_DRIVER_H_ */
