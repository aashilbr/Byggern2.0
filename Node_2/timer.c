/*
 * timer.c
 *
 * Created: 21.10.2020 08:35:35
 *  Author: sandrgl
 */ 

#include "timer.h"

void timer_init(void){
	PMC->PMC_WPMR &= ~(ADC_WPMR_WPEN); //clear WPEN in PMC_WPMR
	PMC->PMC_PCER0 |= 1<<27; //enable peripheral clock 27(Timer counter channel 0)

	TC0->TC_CHANNEL[0].TC_CCR |= TC_CCR_CLKEN; // set CLKEN in TC_CCR0 -> enable the clock 
	TC0->TC_CHANNEL[0].TC_CCR &= ~(TC_CCR_CLKDIS); //clear CLKDIS  in TC_CCR0 
	TC0->TC_CHANNEL[0].TC_CCR |= TC_CCR_SWTRG; //set software trigger
	TC0->TC_CHANNEL[0].TC_CMR |= TC_CMR_WAVE; //set WAVE bit in TC_CMR0 and all other bits to zero
	TC0->TC_CHANNEL[0].TC_CMR |= TC_CMR_WAVSEL_UP_RC; //UP mode with automatic trigger on RC compare 
	TC0->TC_CHANNEL[0].TC_CMR |= TC_CMR_ACPA_CLEAR; //RA compare effect on TIOA
	TC0->TC_CHANNEL[0].TC_CMR |= TC_CMR_ACPC_SET; //RC compare effect on TIOA
	
	PIOB->PIO_PDR |=PIO_PDR_P25;//set PB25(PWM2) as output
	PIOB->PIO_ABSR |=PIO_ABSR_P25;//Peripheral select B
	
	TC0->TC_CHANNEL[0].TC_RA |=88200;
	TC0->TC_CHANNEL[0].TC_RC |= 840000;
	PMC->PMC_PCK[0] |= PMC_PCK_PRES_CLK_1;
		TC0->TC_QIER |= TC_QIDR_QERR; //Enable QERR in QDEC Interrupt Enable Register 
	TC0->TC_BMR |= TC_BMR_QDEN; // Enables the QDEC
	TC0->TC_BMR |= TC_BMR_POSEN; // Enables the position measure on channel 0 and 1
	TC0->TC_CHANNEL[0].TC_CMR |= TC_CMR_TCCLKS_XC0;  //TC_CMR0 configured to select XC0 input ??
	
	/*//TC0->TC_RC=0x19a280;
	TC0->TC_RA=
	
	CMR PRESCALAR
	TC_RC OG RA
*/
}


void set_duty_cycle(double percent){
	//uint8_t period = TC0->TC_CHANNEL[0].TC_RC;
	int period = 840000;
	percent=percent/100;
	int duty = period*percent;
	if(duty>88200){
		duty=88200;
	}
	if(duty<37800){
		duty=37800;
	}
	TC0->TC_CHANNEL[0].TC_RA = duty;
}


void pos_to_duty_cycle(int8_t pos){
	double percent= ((pos+100)*0.06/200+0.045)*100;
	set_duty_cycle(percent);
}

