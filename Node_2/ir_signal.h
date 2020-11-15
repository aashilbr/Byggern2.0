/*
 * ir_signal.h
 *
 * Created: 21.10.2020 17:14:07
 *  Author: sandrgl
 */


#ifndef IR_SIGNAL_H_
#define IR_SIGNAL_H_
#include "sam.h"

//Ta med adc_init funskjnen her???


/**
* @brief Function for reading IR signal and convert analog data.
* @return ADC channel 0 data register.
* @details Function for analog to digital conversion, returns the converted data.
*/
uint16_t read_ir_signal();



#endif /* IR_SIGNAL_H_ */
