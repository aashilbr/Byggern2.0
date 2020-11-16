/*
 * ir_signal.c
 *
 * Created: 21.10.2020 17:14:58
 *  Author: sandrgl
 */ 
#include "ir_signal.h"
void adc_init(){
	PMC->PMC_PCER1 |= PMC_PCER1_PID37; //Peripheral clock enable register, ADC has peripheral ID 37 -> PID37.

	ADC->ADC_CHER |= ADC_CHER_CH0; // Enable channel 0 

	ADC->ADC_MR |= ADC_MR_FREERUN_ON; //Mode register set to FREERUN
	ADC->ADC_MR |= ADC_MR_TRACKTIM(2);
	ADC->ADC_MR |= ADC_MR_TRANSFER(0);

	ADC->ADC_CR |= ADC_CR_START; //Control register, Begins analog to digital conversion

	
}
uint16_t read_ir_signal(){
	return ADC->ADC_CDR[0];
}


