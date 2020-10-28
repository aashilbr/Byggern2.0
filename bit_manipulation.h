/*
 * bit_manipulation.h
 *
 * Created: 14.10.2020 19:38:14
 *  Author: sandrgl
 */ 


#ifndef BIT_MANIPULATION_H_
#define BIT_MANIPULATION_H_
#include <avr/io.h>


uint8_t set_bit(uint8_t reg, uint8_t bit);
uint8_t clear_bit(uint8_t reg, uint8_t bit);
uint8_t test_bit(uint8_t reg, uint8_t bit);


#endif /* BIT_MANIPULATION_H_ */