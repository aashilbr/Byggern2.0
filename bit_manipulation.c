/*
 * bit_manipulation.c
 *
 * Created: 14.10.2020 19:40:47
 *  Author: sandrgl
 */ 
#include "bit_manipulation.h"

uint8_t set_bit(uint8_t reg, uint8_t bit){
	return (reg|=(1<<bit));
}
uint8_t clear_bit(uint8_t reg, uint8_t bit){
	return (reg &= ~(1<<bit));
}
uint8_t test_bit(uint8_t reg, uint8_t bit){
	return (reg & (1<<bit));
}