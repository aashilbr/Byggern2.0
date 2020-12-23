/*
 * @file external_memory.h
 *
 * Created: 02.09.2020 09:17:52
 *  Author: andrschn
 */

#ifndef EXTERNAL_MEMORY_H_
#define EXTERNAL_MEMORY_H_
#define BASE_ADDRESS 0x1000
#include <avr/io.h>


/**
* @brief Initializes external memory
* @details Emables the external memory interface by setting @c SRE in @c MCUCR.
* Sets @XMM2 in @ SFIOR register to 1 to release port pin PC7 - PC4 for
* external memory  address.
*/
void xmem_init(void);

/**
* @brief Write function to external memory
* @param [in] data 8-bit data bus
* @param [in] addr 16-bit address
* @details Function that writes @p data to @p address in external memory.
*/
void xmem_write(uint8_t data, uint16_t addr);

/**
* @brief Read function from external memory
* @param [in] addr Address we want ro read from
* @return Returns the read value from the external memory
*/
uint8_t xmem_read(uint16_t addr);




void xmem_save_movement(int8_t x_pos, int8_t y_pos, uint8_t button, uint8_t nr);

int8_t xmem_read_x_movement(uint8_t nr);
int8_t xmem_read_y_movement(uint8_t nr);
uint8_t xmem_read_button_movement(uint8_t nr);
int xmem_check_storing_condition(int count, int frequency);
void xmem_write_size(int data_store_nr);
int xmem_get_size(void);
#endif
