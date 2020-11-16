/**
* @file node_2/ir_signal.h
* @author sandrgl
* @date 21.10.2020
* @brief Code for coverting analog IR signal to digital signal
*/


#ifndef IR_SIGNAL_H_
#define IR_SIGNAL_H_
#include "sam.h"

/**
* @brief Initialization for analog to digital converter
*/
void adc_init();

/**
* @brief Function for reading IR signal and convert analog data.
* @return ADC channel 0 data register.
* @details Function for analog to digital conversion, returns the converted data.
*/
uint16_t read_ir_signal();


#endif /* IR_SIGNAL_H_ */
