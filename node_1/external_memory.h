/*
 * @file node_1/external_memory.h
 *
 * Created: 02.09.2020 09:17:52
 * Author: andrschn
 */

#ifndef EXTERNAL_MEMORY_H_
#define EXTERNAL_MEMORY_H_
#include <stdint.h>

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
void xmem_write(uint16_t addr, uint8_t data);

/**
* @brief Read function from external memory
* @param [in] addr Address we want ro read from
* @return Returns the read value from the external memory
*/
uint8_t xmem_read(uint16_t addr);

/**
* @brief Saves @p x_pos in xternal memory
* @param [in] x_pos The position to save
* @return Returns 0 is the saving was successful, otherwise 1
*/
uint8_t xmem_save_movement(int8_t x_pos);
/**
* @brief Loads a position from external memory
* @param [in] p_data pointer to write the loaded data in
* @return Returns 0 if loading was successful, otherwise 1
* @details
*/
uint8_t xmem_load_movement(uint8_t *p_data);


/**
* @brief Cheks if storing conditions are met
* @param [in] count The number of measurements made
* @param [in] sampling The sampling period for saving
* @return Returns 1 if conditions are met, if not it returns 0
*/
uint8_t xmem_check_storing_condition(uint32_t count, uint8_t sampling);

/**
* @brief Resets the tail to the front of the memory
* @details Enabeling loading of movement several times
*/
void xmem_reset_tail(void);
#endif
