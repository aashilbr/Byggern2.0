/*
 * node_2.c
 *
 * Created: 07.10.2020 13:14:18
 * Author : andrschn
 */ 


#include "sam.h"
#include "uart.h"
#include "can_controller.h"
#include "timer.h"
//#include "can_interrupt.h"
#include "joystick.h"
#include "ir_signal.h"
#include "pingpong_states.h"
#include "motor_controller.h"







int main(void)
{
	configure_uart();
	
    /* Initialize the SAM system */
    SystemInit();
	PIOA->PIO_OER = 0x1u <<20;
	
	PIOA->PIO_OER = 0x1u <<19;
	
	PIOA->PIO_PER = 0x1u<<0;
	PIOA->PIO_PER = 0x1u<<1;
	can_init_def_tx_rx_mb(0x00290561);
	timer_init();
	adc_init();
	
//	CAN_MESSAGE mess;
// 	mess.id = 0b00001111;
// 	mess.data[0]=5;
// 	mess.data[1]=6;
// 	mess.data[2]=7;
// 	mess.data[3]=8;
// 	mess.data_length = 4;
// 	
	//can_send(&mess, )
	
	set_duty_cycle(7);
	CAN_MESSAGE m;
	int count= 0;
	motor_init();
	//PIOD->PIO_CODR = PIO_CODR_P10;
    while (1) 
    {	
		//printf("status %d \n \r", ADC->ADC_CDR[0]);
		//printf("adc : %d \n \r", read_ir_signal());
		count_score();
		printf("Score: %d \n\r", pingpong_state.score);
		
		/*for(double i=4.5; i<10.5; i+=0.5){
			set_duty_cycle(i);
		}*/
		/*if (i==0){
			PIOA->PIO_SODR =PIO_SODR_P19;
			i=1;
		}
		else{
			PIOA->PIO_CODR =PIO_CODR_P19;
			i=0;
		}*/
		//printf("x : %d y: %d \n \r", js_pos.x, js_pos.y);
		//for(int i = 0; i< 3*1600000; i++){}
		
		//can_receive(&m, 1);
		
    }
}

