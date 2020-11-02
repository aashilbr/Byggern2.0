/*
 * motor_controller.c
 *
 * Created: 28.10.2020 14:59:22
 *  Author: sandrgl
 */ 

#include "motor_controller.h"
#define DIFF_ENCODER 18000


void motor_init(void){
	PMC->PMC_PCER0 |= PMC_PCER0_PID13; //Enable clock on PIOC-controller
	PMC->PMC_PCER1 |= PMC_PCER1_PID38; //DACC ID
	DACC->DACC_MR |= DACC_MR_TAG_EN; //Tag selection mode enable
	//mode, tag, har 12- bits til pådrag. bitsene over 12 blir channel
	DACC->DACC_CHER |= DACC_CHER_CH1;//enable channel 1, corresponding to DAC1
	//DACC->DACC_CDR |= DACC_CDR_DATA;//sette output på DAC_CDR
	//sets !OE, SEL; !RTS, DIR, EN as outputs
	PIOD->PIO_PER |= PIO_PER_P0;
	PIOD->PIO_PER |= PIO_PER_P1;
	PIOD->PIO_PER |= PIO_PER_P2;
	PIOD->PIO_PER |= PIO_PER_P9;
	PIOD->PIO_PER |= PIO_PER_P10; 
	
	PIOD->PIO_OER |= PIO_OER_P0;
	PIOD->PIO_OER |= PIO_OER_P1;
	PIOD->PIO_OER |= PIO_OER_P2;
	PIOD->PIO_OER |= PIO_OER_P9;
	PIOD->PIO_OER |= PIO_OER_P10;
	
	//Sets DO0-DO7 as input 
	PIOC->PIO_PER |= PIO_PER_P1;
	PIOC->PIO_PER |= PIO_PER_P2;
	PIOC->PIO_PER |= PIO_PER_P3;
	PIOC->PIO_PER |= PIO_PER_P4;
	PIOC->PIO_PER |= PIO_PER_P5;
	PIOC->PIO_PER |= PIO_PER_P6;
	PIOC->PIO_PER |= PIO_PER_P7;
	PIOC->PIO_PER |= PIO_PER_P8; 
	
	PIOD->PIO_SODR = PIO_SODR_P9;
	PIOD->PIO_CODR = PIO_CODR_P10;
	PIOD->PIO_SODR |= PIO_SODR_P1;
	
	//calibrate encoder at the left side of the box
	DACC->DACC_CDR = (0x1000 | 2000);
	for (int i = 0; i<42000000; i++){}
	//set speed = 0
	DACC->DACC_CDR = (0x1000);
	//toggle
	PIOD->PIO_CODR |= PIO_CODR_P1;
	PIOD->PIO_SODR |= PIO_SODR_P1;
	
	
	
}

//sender man 0 til IO pinnen sender man 3.3V til releet

int16_t read_encoder(void){
	PIOD->PIO_CODR |= PIO_CODR_P0; //set !OE low to enable output of encoder
	PIOD->PIO_CODR |= PIO_CODR_P2; //Set SEL low to get high byte
	
	//vent 20micro s
	for (int i = 0; i<4000;i++){}
	uint8_t MSB = PIOC->PIO_PDSR ;
	
	PIOD->PIO_SODR |= PIO_SODR_P2; //Set SEL high to get low byte
	
	//vent 20 micro s
	for (int i = 0; i<4000;i++){}
	uint8_t LSB = PIOC->PIO_PDSR ;
	
	//toggle
	PIOD->PIO_CODR |= PIO_CODR_P1;
	PIOD->PIO_SODR |= PIO_SODR_P1;
	
	PIOD->PIO_SODR |= PIO_SODR_P0;
	
	int16_t encoder_data = (LSB | (MSB<<8));
	
	//Convert to -100,100
	
	
	//encoder_data = encoder_data/DIFF_ENCODER ;
	
	return encoder_data;
}

void set_direction_bit(int8_t reference){
	if (reference>0){
		PIOD->PIO_SODR = PIO_SODR_P10;
	}
	if(reference<=0){
		PIOD->PIO_CODR = PIO_CODR_P10;
	}
}

void controller_speed(int8_t pos_x) {
	set_direction_bit(pos_x);
	int speed = (abs(pos_x))*(4095/100);
	printf("dir: %d \n\r", PIO_SODR_P10);
	DACC->DACC_CDR = (0x1000 | speed);
}

