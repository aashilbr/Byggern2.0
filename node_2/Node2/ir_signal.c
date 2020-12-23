/*
 * ir_signal.c
 *
 * Created: 21.10.2020 17:14:58
 *  Author: sandrgl
 */ 
#include "ir_signal.h"
void adc_init(){
	PMC->PMC_PCER1 |= PMC_PCER1_PID37; //Peripheral clock enable register, ADC has peripheral ID 37 -> PID37.
	//ADC->ADC_WPMR &= ~(ADC_WPMR_WPEN); //Disable WPEN (ADC write protect mode) register
	ADC->ADC_CHER |= ADC_CHER_CH0; // Enable channel 0 
	//PIOA->PIO_PER |= PIO_PDR_P2; // PIO Disable Register P2, disables the PIO from controlling pin 2. (Enables peripheral control of the pin)
	ADC->ADC_MR |= ADC_MR_FREERUN_ON; //Mode register set to FREERUN
	ADC->ADC_MR |= ADC_MR_TRACKTIM(2);
	ADC->ADC_MR |= ADC_MR_TRANSFER(0);
	//ADC->ADC_COR |= ADC_COR_DIFF0; //Channel offset register set to fully differential mode for channel 0
	//ADC->ADC_CR |= ADC_CR_SWRST; //Control register, Resets the ADC simulating a hardware reset
	ADC->ADC_CR |= ADC_CR_START; //Control register, Begins analog to digital conversion
	//ADC->ADC_IER |= ADC_IER_COMPE;
	
}
uint16_t read_ir_signal(){
	return ADC->ADC_CDR[0];
}

//ADC
/*
instance id 37
signal name VDDANA 3-3.6v[3.3v]
ADVREF reference voltage
AD0..AD15 inputs
ADTRG external trigger
enable adc controller mck in pmc
enable corresponding channel in adc_cher
- ADC_MR : ADC Mode Register
- ADC_CHER : ADC Channel Enable Register
- ADC_CR : ADC Control Register
- ADC_CDR[n] : ADC Channel n Data Register
- ADC_LCDR : ADC Last Converted Data Register
*/
