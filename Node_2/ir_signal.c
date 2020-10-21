/*
 * ir_signal.c
 *
 * Created: 21.10.2020 17:14:58
 *  Author: sandrgl
 */ 
#include "ir_signal.h"
void adc_init(){
	ADC->ADC_CHER |= ADC_CHER_CH0;
	PIOA->PIO_PER |= PIO_PDR_P2;
	ADC->ADC_MR |= ADC_MR_FREERUN_ON;
	ADC->ADC_COR |= ADC_COR_DIFF0;
	ADC->ADC_CR |= ADC_CR_SWRST;
	ADC->ADC_CR |= ADC_CR_START;
	/*ADC->ADC_IER |= ADC_IER_COMPE;*/
}
uint8_t read_ir_signal(){
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
